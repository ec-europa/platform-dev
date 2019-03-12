<?php

namespace Drupal\tmgmt_dgt_connector;

use Drupal\tmgmt_poetry\Notification as BaseNotification;
use EC\Poetry\Messages\Notifications\TranslationReceived;

/**
 * Subscriber with listeners for Server events.
 *
 * @package Drupal\tmgmt_dgt_connector
 */
class Notification extends BaseNotification {

  /**
   * Name of the translator that handles this notification.
   *
   * @var string
   */
  protected $translatorName = TMGMT_DGT_CONNECTOR_TRANSLATOR_NAME;

  /**
   * Process notification TranslationReceived.
   *
   * @param \EC\Poetry\Messages\Notifications\TranslationReceived $message
   *   The Translation Received.
   *
   * @return bool
   *   Return True if the translation is received without issues.
   */
  public function translationReceived(TranslationReceived $message) {

    // Initial steps.
    $this->setReference($message);
    $this->storeMessage($message);

    $ids = tmgmt_poetry_obtain_related_translation_jobs(array(), 'MAIN_%_POETRY_%' . $this->reference)->fetchAll();
    if (empty($ids)) {
      watchdog(
        "tmgmt_poetry",
        "Callback can't find job with reference !reference .",
        array('!reference' => $this->reference),
        WATCHDOG_ERROR
      );
      return FALSE;
    }

    // Get main job in order to register the messages and
    // get translator and controller.
    $main_id = array_shift($ids);
    $main_job = tmgmt_job_load($main_id->tjid);

    // Verify translator and get it.
    if ($main_job->translator !== $this->translatorName) {
      return FALSE;
    }
    $translator = tmgmt_translator_load($main_job->translator);

    if ($main_job->isAborted()) {
      watchdog(
        "tmgmt_poetry",
        "Translation received for aborted job with reference !reference .",
        array('!reference' => $this->reference),
        WATCHDOG_ERROR
      );
      return FALSE;
    }

    // Get controller.
    $controller = tmgmt_file_format_controller($main_job->getSetting('export_format'));
    if (!$controller) {
      watchdog(
        "tmgmt_poetry",
        "Callback can't find controller with reference !reference .",
        array('!reference' => $this->reference),
        WATCHDOG_ERROR
      );
      return FALSE;
    }

    // Do translation for each target.
    $targets = $message->getTargets();
    foreach ($targets as $target) {
      // Get language job.
      $language_job = $translator->mapToLocalLanguage(drupal_strtolower($target->getLanguage()));
      $ids = tmgmt_poetry_obtain_related_translation_jobs(array($language_job), $this->reference)
        ->fetchAll();
      $job_id = $ids[0];
      $job = tmgmt_job_load($job_id->tjid);
      $job_item = tmgmt_job_item_load($job_id->tjiid);

      // Verify format.
      if ($xml_error = $this->verifyFormatError($target->getFormat(), $job, $main_job)) {
        return $xml_error;
      }

      // Update the delai provided by DGT.
      $delay = $target->getAcceptedDelay();
      if (!empty($delay)) {
        _tmgmt_poetry_update_item_status($job_item->tjiid, "", "", (string) $delay);
      }

      // Import content using controller.
      $imported_file = base64_decode($target->getTranslatedFile());
      if ($language_job != $main_job->target_language) {
        $imported_file = $this->tmgmtPoetryRewriteReceivedXml($imported_file, $job, $ids);
      }

      try {
        // Validation successful, start import.
        $job->addTranslatedData($controller->import($imported_file));

        $main_job->addMessage(
          t('@language Successfully received the translation file.'),
          array('@language' => $job->target_language)
        );

        // Update the status to executed when we receive a translation.
        _tmgmt_poetry_update_item_status($job_item->tjiid, "", "Executed", "");
      }
      catch (Exception $e) {
        $main_job->addMessage(
          t('@language File import failed with the following message: @message'),
          array(
            '@language' => $job->target_language,
            '@message' => $e->getMessage(),
          ),
          'error'
        );
        watchdog_exception('tmgmt_poetry', $e);
      }
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
  private function tmgmtPoetryRewriteReceivedXml($content, \TMGMTJob $job, array $ids_collection) {

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

        /** @var \SimpleXMLElement $div */
        foreach ($parent_div->div as $div) {
          if ($div['class'] == 'atom') {
            $data = drupal_substr($div['id'], 1);
            $data = base64_decode(str_pad(strtr($data, '-_', '+/'), drupal_strlen($data) % 4, '=', STR_PAD_RIGHT));
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

}
