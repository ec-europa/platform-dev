<?php

/**
 * @file
 * Provides events subscriber for TMGMT DGT Connector.
 */

namespace Drupal\tmgmt_dgt_connector;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use EC\Poetry\Events\Notifications\TranslationReceivedEvent;
use EC\Poetry\Events\Notifications\StatusUpdatedEvent;
use EC\Poetry\Messages\Notifications\TranslationReceived;
use EC\Poetry\Messages\Notifications\StatusUpdated;

/**
 * Subscriber with listeners for Server events.
 *
 * @package Drupal\tmgmt_dgt_connector
 */
class Subscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return array(
      TranslationReceivedEvent::NAME => 'onTranslationReceivedEvent',
      StatusUpdatedEvent::NAME => 'onStatusUpdatedEvent',
    );
  }

  /**
   * Listener for the event onTranslationReceivedEvent.
   *
   * @param \EC\Poetry\Events\Notifications\TranslationReceivedEvent $event
   *   The event for the Translation Received.
   */
  public function onTranslationReceivedEvent(TranslationReceivedEvent $event) {
    $translator = tmgmt_translator_load(TMGMT_DGT_CONNECTOR_TRANSLATOR_NAME);

    /** @var \EC\Poetry\Messages\Notifications\StatusUpdated $message */
    $message = $event->getMessage();
    $reference = $message->getIdentifier()->getFormattedIdentifier();

    // Get main job in order to register the messages and get translator.
    $main_reference = 'MAIN_%_POETRY_%' . $reference;
    $targets = $message->getTargets();
    /** @var \EC\Poetry\Messages\Components\Target $target */
    $target = array_shift($targets);

    $ids = _tmgmt_poetry_obtain_related_translation_jobs(
      array(),
      $main_reference
    )->fetchAll();
    if (empty($ids)) {
      watchdog(
        "tmgmt_poetry",
        "Callback can't find job with reference !reference .",
        array('!reference' => $main_reference),
        WATCHDOG_ERROR
      );
      return FALSE;
    }

    // Get right controller from main job.
    $main_id = array_shift($ids);
    $main_job = tmgmt_job_load($main_id->tjid);
    if ($main_job->isAborted()) {
      return FALSE;
    }
    $controller = tmgmt_file_format_controller($main_job->getSetting('export_format'));
    if (!$controller) {
      return FALSE;
    }

    // Get main job.
    $language_job = $translator->mapToLocalLanguage(drupal_strtolower($target->getLanguage()));
    $ids = _tmgmt_poetry_obtain_related_translation_jobs(array($language_job), $reference)
      ->fetchAll();
    $main_ids = $ids[0];
    $job = tmgmt_job_load($main_ids->tjid);
    $job_item = tmgmt_job_item_load($main_ids->tjiid);

    // Import content using controller.
    $imported_file = base64_decode($target->getTranslatedFile());
    if ($language_job != $main_job->target_language) {
      $imported_file = $this->tmgmtPoetryRewriteReceivedXml($imported_file, $job, $ids);
    }
    $content = $controller->import($imported_file);

    try {
      // Validation successful, start import.
      $job->addTranslatedData($content);

      $main_job->addMessage(
        t('@language Successfully received the translation file.'),
        ['@language' => $job->target_language]
      );

      // Update the status to executed when we receive a translation.
      _tmgmt_poetry_update_item_status($job_item->tjiid, "", "Executed", "");

    }
    catch (Exception $e) {

      $main_job->addMessage(
        t('@language File import failed with the following message: @message'),
        [
          '@language' => $job->target_language,
          '@message' => $e->getMessage(),
        ],
        'error'
      );
      watchdog_exception('tmgmt_poetry', $e);
    }
  }

  /**
   * Replace job id in received content.
   *
   * @param string $content
   *   The XML content.
   * @param \TMGMTJob $job
   *   The job.
   * @param array $ids_collection
   *   The array of pairs with jobs and job items.
   *
   * @return bool|mixed
   *   The updated XML content.
   */
  private function tmgmtPoetryRewriteReceivedXml($content, $job, $ids_collection) {

    $dom = new \DOMDocument();
    if (!multisite_drupal_toolbox_load_html($dom, $content)) {
      return FALSE;
    }

    // Workaround for saveXML() generating two xmlns attributes.
    // See https://bugs.php.net/bug.php?id=47666.
    if ($dom->documentElement->hasAttributeNS(NULL, 'xmlns')) {
      $dom->documentElement->removeAttributeNS(NULL, 'xmlns');
    }

    $xml = simplexml_import_dom($dom);

    if (count($xml->head->meta) > 0) {
      foreach ($xml->head->meta as $meta_tag) {
        if (isset($meta_tag['name'])) {
          switch ($meta_tag['name']) {
            case 'JobID':
              $meta_tag['content'] = $job->tjid;
              break;

            case 'languageSource':
              $meta_tag['content'] = $job->getTranslator()
                ->mapToRemoteLanguage($job->source_language);
              break;

            case 'languageTarget':
              $meta_tag['content'] = $job->getTranslator()
                ->mapToRemoteLanguage($job->target_language);
              break;
          }
        }
      }
    }
    if (isset($xml->head->title)) {
      $xml->head->title = "Job ID " . $job->tjid;
    }
    foreach ($xml->body->div as $parent_div) {
      if ($parent_div['class'] == 'meta' && $parent_div['id'] == 'languageTarget') {
        $parent_div[0] = $job->target_language;
      }
      if ($parent_div['class'] == 'asset') {

        /** @var SimpleXMLElement $div */
        foreach ($parent_div->div as $div) {
          if ($div['class'] == 'atom') {
            $data = substr($div['id'], 1);
            $data = base64_decode(str_pad(strtr($data, '-_', '+/'), strlen($data) % 4, '=', STR_PAD_RIGHT));
            $data = explode(']', $data);
            $main_tjiid = $data[0];
            // This is the main job item for main job.
            $main_job_item = tmgmt_job_item_load($main_tjiid);

            $corresponding_tjiid = 0;
            foreach ($ids_collection as $ids) {
              $job_item_to_test = tmgmt_job_item_load($ids->tjiid);
              if ($job_item_to_test->item_id == $main_job_item->item_id && $job_item_to_test->item_type == $main_job_item->item_type) {
                // This is the corresponding job item.
                $corresponding_tjiid = $ids->tjiid;
                continue;
              }
            }

            $data[0] = $corresponding_tjiid;
            $data = implode(']', $data);
            $div['id'] = 'b' . rtrim(strtr(base64_encode($data), '+/', '-_'), '=');
          }
        }
      }
    }

    $result = $xml->saveXML();
    return $result;
  }


  /**
   * Listener for the event onStatusUpdatedEvent.
   *
   * @param StatusUpdatedEvent $event
   *   The event for the Status Update.
   */
  public function onStatusUpdatedEvent(StatusUpdatedEvent $event) {
    $translator = tmgmt_translator_load(TMGMT_DGT_CONNECTOR_TRANSLATOR_NAME);

    /** @var \EC\Poetry\Messages\Notifications\StatusUpdated $message */
    $message = $event->getMessage();
    $reference = $message->getIdentifier()->getFormattedIdentifier();
    $attributions_statuses = $message->getAttributionStatuses();

    // Get main job in order to register the messages.
    $main_reference = 'MAIN_%_POETRY_%' . $reference;
    $languages_jobs = [];
    /** @var \EC\Poetry\Messages\Components\Status $attribution_status */
    foreach ($attributions_statuses as $attribution_status) {
      $languages_jobs[] = $attribution_status->getLanguage();
    }
    $ids = _tmgmt_poetry_obtain_related_translation_jobs(
      $languages_jobs,
      $main_reference
    )->fetchAll();
    if (!$ids) {
      watchdog(
        "tmgmt_poetry",
        "Callback can't find a job with remote reference !reference .",
        ['!reference' => $reference],
        WATCHDOG_ERROR
      );
      return;
    }
    $main_id = $ids[0];
    $main_job = tmgmt_job_load($main_id->tjid);

    // 1. Check status of request.
    $request_status = $message->getRequestStatus();
    if ($request_status->getCode() != '0') {
      watchdog(
        'tmgmt_poetry',
        'Job @reference received a Status Update with issues. Message: @message',
        [
          '@reference' => $reference,
          '@message' => $message->getRaw(),
        ],
        WATCHDOG_ERROR
      );
      return;
    }

    watchdog(
      'tmgmt_poetry',
      'Job @reference got a Status Update. Message: @message',
      [
        '@reference' => $reference,
        '@message' => $message->getRaw(),
      ],
      WATCHDOG_INFO
    );

    // 2. Check status of demand and update the whole request.
    $demand_status = $message->getDemandStatus();
    if (!empty($demand_status)) {
      $cancelled = FALSE;
      $status_message = "";

      // Check status code.
      switch ($demand_status->getCode()) {
        case 'SUS':
          $status_message = POETRY_STATUS_MESSAGE_SUS;
          $cancelled = FALSE;
          break;

        case 'ONG':
          $status_message = POETRY_STATUS_MESSAGE_ONG;
          $cancelled = FALSE;
          break;

        case 'LCK':
          $status_message = POETRY_STATUS_MESSAGE_LCK;
          $cancelled = FALSE;
          break;

        case 'EXE':
          $status_message = POETRY_STATUS_MESSAGE_EXE;
          $cancelled = FALSE;
          break;

        case 'REF':
          $status_message = POETRY_STATUS_MESSAGE_REF;
          $cancelled = TRUE;
          break;

        case 'CNL':
          $status_message = POETRY_STATUS_MESSAGE_CNL;
          $cancelled = TRUE;
          break;
      }

      $main_job->addMessage(
        t("DGT update received. Request status: @status. Message: @message"),
        [
          '@status' => $status_message,
          '@message' => $demand_status->getMessage(),
        ]
      );

      if ($cancelled) {
        $reference = '%' . $reference;

        $ids = _tmgmt_poetry_obtain_related_translation_jobs([], $reference)
          ->fetchAll();
        foreach ($ids as $id) {
          $job = tmgmt_job_load($id->tjid);
          $job->aborted(t('Request aborted by DGT.'), []);
        }
      }
      elseif ($main_job->isAborted()) {
        $reference = '%' . $reference;
        $ids = _tmgmt_poetry_obtain_related_translation_jobs([], $reference)
          ->fetchAll();

        foreach ($ids as $id) {
          $reopen_job = tmgmt_job_load($id->tjid);
          $reopen_job->setState(
            TMGMT_JOB_STATE_ACTIVE,
            t('Request re-opened by DGT.')
          );
          $reopen_job_item = tmgmt_job_item_load($ids->tjiid);
          $reopen_job_item->active();
        }
      }

      // 3. Check Status for specific languages.
      foreach ($attributions_statuses as $attribution_status) {
        $language_code = drupal_strtolower($attribution_status->getLanguage());
        $language_code = $translator->mapToLocalLanguage($language_code);
        $language_job = [$language_code];

        $ids = _tmgmt_poetry_obtain_related_translation_jobs($language_job, $reference)
          ->fetchAll();
        $ids = array_shift($ids);
        $job = tmgmt_job_load($ids->tjid);
        $job_item = tmgmt_job_item_load($ids->tjiid);

        if (!empty($job->target_language) && !empty($languages[(string) $job->target_language])) {
          $language = $languages[(string) $job->target_language]->name;
        }
        else {
          $language = "";
        }

        $main_job->addMessage(
          t("DGT update received. Affected language: @language. Request status: @status."),
          [
            '@language' => $language,
            '@status' => $status_message,
          ]
        );

        _tmgmt_poetry_update_item_status($job_item->tjiid, "", $status_message, "");
      }
    }
  }

}
