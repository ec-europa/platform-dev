<?php

/**
 * @file
 * Provides the FTP translation plugin controller.
 */

/**
 * FTP translator plugin controller.
 */
class TMGMTFTPTranslatorUIController extends TMGMTDefaultTranslatorUIController {

  /**
   * Override parent pluginSettingsForm method.
   */
  public function pluginSettingsForm($form, &$form_state, TMGMTTranslator $translator, $busy = FALSE) {
    $form['ftp_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('FTP Settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['ftp_settings']['ftp_user'] = array(
      '#type' => 'textfield',
      '#title' => t('FTP User'),
      '#required' => TRUE,
      '#size'=> 30,
      '#default_value' => (isset($translator->settings['ftp_settings']['ftp_user']) ? $translator->settings['ftp_settings']['ftp_user'] : ''),
      '#description' => t('Please enter your ftp user name.'),
    );
    $form['ftp_settings']['ftp_pass'] = array(
      '#type' => 'textfield',
      '#title' => t('FTP Password'),
      '#required' => TRUE,
      '#size'=> 30,
      '#default_value' => (isset($translator->settings['ftp_settings']['ftp_pass']) ? $translator->settings['ftp_settings']['ftp_pass'] : ''),
      '#description' => t('Please enter your ftp password.'),
    );
    $form['ftp_settings']['ftp_ip'] = array(
      '#type' => 'textfield',
      '#title' => t('FTP IP Address - Domain'),
      '#required' => TRUE,
      '#size'=> 30,
      '#default_value' => (isset($translator->settings['ftp_settings']['ftp_ip']) ? $translator->settings['ftp_settings']['ftp_ip'] : ''),
      '#description' => t('Please enter the ip/domain where your drupal instance is installed.'),
    );
    
    // Default ftp port: 21.
    $form['ftp_settings']['ftp_port'] = array(
      '#type' => 'textfield',
      '#title' => t('FTP Port'),
      '#required' => FALSE,
      '#size'=> 30,
      '#default_value' => (isset($translator->settings['ftp_settings']['ftp_port']) ? $translator->settings['ftp_settings']['ftp_port'] : 21),
      '#description' => t('Please enter the port that the FTP service is lisening to.'),
    );
    
    // Any visible, writeable wrapper can potentially be used for the files
    // directory, including a remote file system that integrates with a CDN.
    foreach (file_get_stream_wrappers(STREAM_WRAPPERS_WRITE_VISIBLE) as $scheme => $info) {
      $options[$scheme] = check_plain($info['description']);
    }

    if (!empty($options)) {
      $form['scheme'] = array(
        '#type' => 'radios',
        '#title' => t('Download method'),
        '#default_value' => $translator->getSetting('scheme'),
        '#options' => $options,
        '#description' => t('Choose the location where exported files should be stored. The usage of a protected location (e.g. private://) is recommended to prevent unauthorized access.'),
      );
    }

    $form['priority'] = array(
       '#type' => 'select',
       '#title' => t('Priority'),
       '#options' => array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9),
       '#default_value' => $translator->getSetting('priority'),
       '#description' => t('9 is the highest priority. Request with highest priority will be processed first.'),
    );
    $form['custom_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom MT@EC url'),
      '#required' => TRUE,
      '#size'=> 150,
      '#default_value' => $translator->getSetting('custom_url'),
      '#description' => t('Please enter your custom MT@EC webservice location url.'),
    );
 
    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

  /**
   * Override parent checkoutSettingsForm method.
   */
  public function checkoutSettingsForm($form, &$form_state, TMGMTJob $job) {
    return parent::checkoutSettingsForm($form, $form_state, $job);
  }

  /**
   * Override parent checkoutInfo method.
   */
  public function checkoutInfo(TMGMTJob $job) {
    // If the job is finished, it's not possible to import translations anymore.
    if ($job->isFinished()) {
      return parent::checkoutInfo($job);
    }
    $form = array(
      '#type' => 'fieldset',
      '#title' => t('Import translated file'),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
      '#submit' => array('tmgmt_ftp_import_form_submit'),
    );
    return $this->checkoutInfoWrapper($job, $form);
  }
}
