<?php

/**
 * @file
 * Provides the FTP translation plugin controller.
 */

/**
 * FTP translator plugin controller.
 */
class TMGMTFTPPluginController extends TMGMTDefaultTranslatorPluginController {

  
  /**
   * Override parent canTranslate method.
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    // Anything can be exported.
    return TRUE;
  }

  /**
   * Override parent requestTranslation method.
   */
  public function requestTranslation(TMGMTJob $job) {
    $name = "JobID" . $job->tjid;

    $export = tmgmt_file_format_controller($job->getSetting('export_format'));

    $path = $job->getSetting('scheme') . '://tmgmt_ftp/' . $name . '.' .  $job->getSetting('export_format');
    $dirname = dirname($path);
    if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
      $file = file_save_data($export->export($job), $path);
      file_usage_add($file, 'tmgmt_ftp', 'tmgmt_job', $job->tjid);
      $job->submitted('Exported file can be downloaded <a href="!link">here</a>.', array('!link' => file_create_url($path)));
    }
  }

  /**
   * Override parent hasCheckoutSettings method.
   */
  public function hasCheckoutSettings(TMGMTJob $job) {
    return $job->getTranslator()->getSetting('allow_override');
  }

  /**
   * Override parent defaultSettings method.
   */
  public function defaultSettings() {
    return array(
      'export_format' => 'xlf',
      'allow_override' => TRUE,
      'scheme' => 'public',
      // Making this setting TRUE by default is more appropriate, however we
      // need to make it FALSE due to backwards compatibility.
      'xliff_processing' => TRUE,
    );
  }

  /**
   * Override parent getSupportedTargetLanguages method.
   */
  public function getSupportedTargetLanguages(TMGMTTranslator $translator, $source_language) {
    $languages = array();
    $list_languages = language_list();

    foreach ($list_languages as $key => $value) {
      $languages[$key] = $key;
    }

    return $languages;
  }

  /**
   * Override parent isAvailable method.
   */
  public function isAvailable(TMGMTTranslator $translator) {
    if (
      $translator->settings['ftp_settings']['ftp_user'] &&
      $translator->settings['ftp_settings']['ftp_pass'] &&
      $translator->settings['ftp_settings']['ftp_ip'] &&
      $translator->settings['ftp_settings']['ftp_port'] &&
      $translator->settings['custom_url']) {
      return TRUE;
    }
    return FALSE;
  }
}
