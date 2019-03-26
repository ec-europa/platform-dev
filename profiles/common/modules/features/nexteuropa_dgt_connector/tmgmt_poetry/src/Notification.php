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
   * @var string
   */
  protected $reference;

  /**
   * Name of the translator that handles this notification.
   *
   * @var string
   */
  protected $translatorName = 'poetry';

  /**
   * Main job, used to register the messages and get translator and controller.
   *
   * @var \TMGMTJob
   */
  protected $mainJob;

  /**
   * Process notification StatusUpdated.
   *
   * @param \EC\Poetry\Messages\Notifications\StatusUpdated $message
   *   The Translation Received.
   */
  public function statusUpdated(StatusUpdated $message) {

    try {

      // Initial steps.
      $this->setReference($message);
      $this->storeMessage($message);
      $attributions_statuses = $message->getAttributionStatuses();
      $this->setMainJob();

      // Verify translator and get it.
      if (!in_array($this->mainJob->translator, array($this->translatorName, PoetryMock::TRANSLATOR_NAME))) {
        return FALSE;
      }
      $translator = tmgmt_translator_load($this->mainJob->translator);

      // 1. Check status of request.
      $request_status = $message->getRequestStatus();
      if ($request_status->getCode() != '0') {
        throw new \Exception(t(
          'Error reported in message status: @status',
          array('@status' => $request_status)
        ));
      }

      // 2. Check status of demand and update the whole request.
      $demand_status = $message->getDemandStatus();
      if (!empty($demand_status)) {
        $status_message = (string) constant('TMGMT_POETRY_STATUS_MSG_' . $demand_status->getCode());

        $this->mainJob->addMessage(
          t("DGT update received. Request status: @status. Message: @message"), array(
            '@status' => $status_message,
            '@message' => $demand_status->getMessage(),
          )
        );

        if (_tmgmt_poetry_is_mapped_job_status_aborted($demand_status->getCode())) {

          $ids = tmgmt_poetry_obtain_related_translation_jobs(array(), '%' . $this->reference)
            ->fetchAll();
          foreach ($ids as $id) {
            $job = tmgmt_job_load($id->tjid);
            $job->aborted(t('Request aborted by DGT.'), array());
          }
        }
        elseif ($this->mainJob->isAborted()) {
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
          $lang_code = drupal_strtolower($attribution_status->getLanguage());
          $lang_code = $translator->mapToLocalLanguage($lang_code);
          $lang_new_status_code = $attribution_status->getCode();

          $language_jobs_ids = tmgmt_poetry_obtain_related_translation_jobs(array($lang_code), $this->reference)
            ->fetchAll();
          $language_job_ids = $language_jobs_ids[0];
          /** @var \TMGMTJob $language_job */
          $language_job = tmgmt_job_load($language_job_ids->tjid);

          // If there are no changes is state, no need to continue.
          $language_status = constant('TMGMT_POETRY_STATUS_MSG_' . $lang_new_status_code);
          if ($language_status === _tmgmt_poetry_get_job_item_status($language_job_ids->tjiid)) {
            continue;
          }

          $msg = t("DGT update received. Affected language: @language. Request status: @status.");
          $msg_vars = array(
            '@language' => $lang_code,
            '@status' => $language_status,
          );
          $this->mainJob->addMessage($msg, $msg_vars);

          _tmgmt_poetry_update_item_status($language_job_ids->tjiid, $lang_code, $language_status, '');

          // If language was canceled, cancel its job and item.
          if (_tmgmt_poetry_is_mapped_job_status_aborted($lang_new_status_code)) {
            $language_job->setState(TMGMT_JOB_STATE_ABORTED, $msg, $msg_vars);
            /** @var \TMGMTJobItem $language_job_item */
            $language_job_item = tmgmt_job_item_load($language_job_ids->tjiid);
            $language_job_item->setState(TMGMT_JOB_ITEM_STATE_ABORTED, $msg, $msg_vars);
          }
        }
      }
    }
    catch (\Exception $e) {

      watchdog_exception('tmgmt_poetry', $e);

      if (isset($this->mainJob)) {
        $this->mainJob->addMessage('@message', array($e->getMessage()), 'error');
      }
    }
  }

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

    try {
      // Initial steps.
      $this->setReference($message);
      $this->storeMessage($message);
      $this->setMainJob();

      // Verify translator and get it.
      if (!in_array($this->mainJob->translator, array($this->translatorName, PoetryMock::TRANSLATOR_NAME))) {
        return FALSE;
      }
      $translator = tmgmt_translator_load($this->mainJob->translator);

      // Get controller.
      $controller = tmgmt_file_format_controller($this->mainJob->getSetting('export_format'));
      if (!$controller) {
        throw new \Exception(t(
          'Callback can not find controller with reference !reference .',
            array('!reference' => $this->reference)
        ));
      }

      // Do translation for each target.
      $targets = $message->getTargets();
      foreach ($targets as $target) {
        // Get language job.
        $language_job = $translator->mapToLocalLanguage(drupal_strtolower($target->getLanguage()));
        $ids = tmgmt_poetry_obtain_related_translation_jobs(array($language_job), $this->reference)
          ->fetchAll();
        $job_ids = $ids[0];
        $job = tmgmt_job_load($job_ids->tjid);

        // Verify format.
        $this->verifyFormatError($target->getFormat(), $job);

        // Import content using controller.
        $imported_file = base64_decode($target->getTranslatedFile());
        if ($language_job != $this->mainJob->target_language) {
          $imported_file = $this->tmgmtPoetryRewriteReceivedXml($imported_file, $job, $ids);
        }

        if (!($validated_job = $controller->validateImport($imported_file)) || $validated_job->tjid != $job->tjid || $job->isAborted()) {
          throw new \Exception('Import not possible.');
        }

        // Validation successful, start import.
        $job->addTranslatedData($controller->import($imported_file));

        $this->mainJob->addMessage(
          t('@language Successfully received the translation file.'),
          array('@language' => $job->target_language)
        );

        // Update the status to executed when we receive a translation.
        _tmgmt_poetry_update_item_status($job_ids->tjiid, "", "Executed", (string) $target->getAcceptedDelay());

        // Save the file and make it available in the job.
        $name = "JobID" . $job->tjid . '_' . $job->source_language . '_' . $job->target_language;
        $path = 'public://tmgmt_file/' . $name . '.' . $job->getSetting('export_format');
        $dirname = drupal_dirname($path);
        if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
          $file = file_save_data($imported_file, $path);
          file_usage_add($file, 'tmgmt_file', 'tmgmt_job', $job->tjid);
          $this->mainJob->addMessage(
            t('Received tanslation can be downloaded <a href="!link">here</a>.'),
            array('!link' => file_create_url($path))
          );
        }
      }
    }
    catch (\Exception $e) {

      watchdog_exception('tmgmt_poetry', $e);

      if (isset($this->mainJob)) {
        $this->mainJob->addMessage('@message', array('@message' => $e->getMessage()), 'error');
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
   * Set main job.
   */
  protected function setMainJob() {

    if (empty($this->reference)) {
      throw new \Exception('Reference not set.');
    }

    $ids = tmgmt_poetry_obtain_related_translation_jobs(array(), 'MAIN_%_POETRY_%' . $this->reference)->fetchAll();
    if (empty($ids)) {
      throw new \Exception('Callback can not find job with reference !reference.');
    }

    $main_ids = array_shift($ids);
    $this->mainJob = tmgmt_job_load($main_ids->tjid);
  }

  /**
   * Verify received format matches with expected by job.
   *
   * @param mixed $format
   *   The received format.
   * @param \TMGMTJob $job
   *   The job.
   *
   * @throws \Exception
   */
  protected function verifyFormatError($format, \TMGMTJob $job) {
    if (empty($format) || strpos($job->getSetting('export_format'), drupal_strtolower((string) $format) === FALSE)) {
      throw new \Exception(
        t('Received format "@format" is not compatible, translation job format "@job_format" should be used instead', array(
          '@format' => (string) $format,
          '@job_format' => $job->getSetting('export_format'),
        )));
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
   * @return string|bool|mixed
   *   The updated XML content.
   */
  protected function tmgmtPoetryRewriteReceivedXml($content, \TMGMTJob $job, array $ids_collection) {

    $job_item = tmgmt_job_item_load($ids_collection[0]->tjiid);
    return _tmgmt_poetry_replace_job_in_content($content, $job, $job_item);
  }

}
