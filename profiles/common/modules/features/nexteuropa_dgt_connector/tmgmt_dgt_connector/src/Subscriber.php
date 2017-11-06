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

    // Get main job in order to register the messages.
    $main_reference = 'MAIN_%_POETRY_%' . $reference;
    $targets = $message->getTargets();

    /** @var \EC\Poetry\Messages\Components\Target $target */
    foreach ($targets as $target) {
      $language_job = [$translator->mapToLocalLanguage(drupal_strtolower($target->getLanguage()))];

      $ids = _tmgmt_poetry_obtain_related_translation_jobs(
        $language_job,
        $main_reference
      )->fetchAll();
      if (!$ids) {
        watchdog(
          "tmgmt_poetry",
          "Callback can't find !language for job with remote reference !reference .",
          ['!language' => $target->getLanguage(), '!reference' => $reference],
          WATCHDOG_ERROR
        );
        return FALSE;
      }

      // Get right controller from main job.
      $main_id = $ids[0];
      $main_job = tmgmt_job_load($main_id->tjid);
      if ($main_job->isAborted()) {
        return FALSE;
      }
      $controller = tmgmt_file_format_controller($main_job->getSetting('export_format'));
      if (!$controller) {
        return FALSE;
      }

      // Import content using controller.
      $imported_file = base64_decode($target->getTranslatedFile());
      $content = $controller->import($imported_file);

      foreach ($ids as $id) {

        $job = tmgmt_job_load($id->tjid);
        $job_item = tmgmt_job_item_load($id->tjiid);

        try {
          // Validation successful, start import.
          $job->addTranslatedData($content);

          $job->addMessage(
            t('@language Successfully received the translation file.'),
            ['@language' => $job->target_language]
          );

          // Update the status to executed when we receive a translation.
          _tmgmt_poetry_update_item_status($job_item->tjiid, "", "Executed", "");

        }
        catch (Exception $e) {
          $job->addMessage(
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
    }
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
