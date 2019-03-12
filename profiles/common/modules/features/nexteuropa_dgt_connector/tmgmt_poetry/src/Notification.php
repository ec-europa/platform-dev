<?php

namespace Drupal\tmgmt_poetry;

use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;
use EC\Poetry\Messages\MessageInterface;
use EC\Poetry\Messages\Notifications\StatusUpdated;
use EC\Poetry\Messages\Notifications\TranslationReceived;

/**
 * Subscriber with listeners for Server events.
 *
 * @package Drupal\tmgmt_poetry
 */
class Notification {

  /**
   * The DGT request reference.
   *
   * @var reference
   */
  protected $reference;

  /**
   * Name of the translator that handles this notification.
   *
   * @var string
   */
  protected $translatorName = 'poetry';

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
    if (!in_array($main_job->translator, array($this->translatorName, PoetryMock::TRANSLATOR_NAME))) {
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

      // Import content using controller.
      $imported_file = base64_decode($target->getTranslatedFile());
      if ($language_job != $main_job->target_language) {
        $imported_file = _tmgmt_poetry_replace_job_in_content($imported_file, $job, $job_item);
      }

      try {

        if (!($validated_job = $controller->validateImport($imported_file)) || $validated_job->tjid != $job->tjid || $job->isAborted()) {
          throw new \Exception('Import not possible.');
        }

        // Validation successful, start import.
        $job->addTranslatedData($controller->import($imported_file));

        $main_job->addMessage(
          t('@language Successfully received the translation file.'),
          array('@language' => $job->target_language)
        );

        // Save the file and make it available in the job.
        $name = "JobID" . $job->tjid . '_' . $job->source_language . '_' . $job->target_language;
        $path = 'public://tmgmt_file/' . $name . '.' . $job->getSetting('export_format');

        $dirname = drupal_dirname($path);
        if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
          $file = file_save_data($imported_file, $path);
          file_usage_add($file, 'tmgmt_file', 'tmgmt_job', $job->tjid);
          $main_job->addMessage(
            t('Received tanslation can be downloaded <a href="!link">here</a>.'),
            array('!link' => file_create_url($path))
          );
        }

        // Update the status to executed when we receive a translation.
        _tmgmt_poetry_update_item_status($job_item->tjiid, "", "Executed", (string) $target->getAcceptedDelay());
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
   * Process notification StatusUpdated.
   *
   * @param \EC\Poetry\Messages\Notifications\StatusUpdated $message
   *   The Translation Received.
   */
  public function statusUpdated(StatusUpdated $message) {

    // Initial steps.
    $this->setReference($message);
    $this->storeMessage($message);

    $attributions_statuses = $message->getAttributionStatuses();

    // Get main job in order to register the messages.
    $ids = tmgmt_poetry_obtain_related_translation_jobs([], 'MAIN_%_POETRY_%' . $this->reference)->fetchAll();
    if (!$ids) {
      watchdog(
        "tmgmt_poetry",
        "Callback can't find a job with remote reference !reference .",
        array('!reference' => $this->reference),
        WATCHDOG_ERROR
      );
      return;
    }
    $main_id = array_shift($ids);
    $main_job = tmgmt_job_load($main_id->tjid);

    // Verify translator and get it.
    if (!in_array($main_job->translator, array($this->translatorName, PoetryMock::TRANSLATOR_NAME))) {
      return FALSE;
    }
    $translator = tmgmt_translator_load($main_job->translator);

    // 1. Check status of request.
    $request_status = $message->getRequestStatus();
    if ($request_status->getCode() != '0') {
      $msg_info = array(
        '@reference' => $this->reference,
        '@message' => $message->getRaw(),
      );
      watchdog(
        'tmgmt_poetry',
        'Job @reference received a Status Update with issues. Message: @message',
        $msg_info,
        WATCHDOG_ERROR
      );
      $main_job->addMessage(
        'Job @reference received a Status Update with issues. Message: @message',
        $msg_info,
        'error'
      );
      return;
    }

    watchdog(
      'tmgmt_poetry',
      'Job @reference got a Status Update. Message: @message',
      array(
        '@reference' => $this->reference,
        '@message' => $message->getRaw(),
      ),
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
        t("DGT update received. Request status: @status. Message: @message"), array(
          '@status' => $status_message,
          '@message' => $demand_status->getMessage(),
        )
      );

      if ($cancelled) {

        $ids = tmgmt_poetry_obtain_related_translation_jobs(array(), '%' . $this->reference)
          ->fetchAll();
        foreach ($ids as $id) {
          $job = tmgmt_job_load($id->tjid);
          $job->aborted(t('Request aborted by DGT.'), array());
        }
      }
      elseif ($main_job->isAborted()) {
        $ids = tmgmt_poetry_obtain_related_translation_jobs(array(), '%' . $this->reference)
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
        $language_job = array($language_code);

        $ids = tmgmt_poetry_obtain_related_translation_jobs($language_job, $this->reference)
          ->fetchAll();
        $ids = array_shift($ids);
        $job_item = tmgmt_job_item_load($ids->tjiid);

        $main_job->addMessage(
          t("DGT update received. Affected language: @language. Request status: @status."), array(
            '@language' => $language_code,
            '@status' => $status_message,
          )
        );

        _tmgmt_poetry_update_item_status($job_item->tjiid, '', $status_message, '');
      }
    }
  }

  /**
   * Extract reference and set it.
   *
   * @param \EC\Poetry\Messages\MessageInterface $msg
   *   The message.
   */
  protected function setReference(MessageInterface $msg) {
    $this->reference = $msg->getIdentifier()->getFormattedIdentifier();
  }

  /**
   * Save message in a file to the filesystem.
   *
   * @param \EC\Poetry\Messages\MessageInterface $msg
   *   The message.
   */
  protected function storeMessage(MessageInterface $msg) {

    // Watchdog is only temporary information, save the file to the filesystem.
    $path = 'public://tmgmt_file/dgt_responses/' . $this->reference . '.xml';
    $dirname = drupal_dirname($path);
    if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
      file_save_data($msg, $path);
    }
  }

  /**
   * Verify received format matches with expected by job.
   *
   * @param mixed $format
   *   The received format.
   * @param \TMGMTJob $job
   *   The job.
   * @param \TMGMTJob $main_job
   *   The main job.
   *
   * @return mixed
   *   FALSE if format is ok, XML with error otherwise.
   */
  protected function verifyFormatError($format, \TMGMTJob $job, \TMGMTJob $main_job) {
    if (empty($format) || strpos($job->getSetting('export_format'), drupal_strtolower((string) $format) === FALSE)) {
      $main_job->addMessage(
        t('Received format "@format" is not compatible, translation job format "@job_format" should be used instead'),
        array(
          '@format' => (string) $format,
          '@job_format' => $job->getSetting('export_format'),
        )
      );

      $xml = _tmgmt_poetry_generate_answer_xml($main_job, 'ERROR: Received format is not compatible', -1);

      return $xml->asXML();
    }

    return FALSE;
  }

}
