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
   * {@inheritdoc}
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
    $form['ftp_settings']['ftp_port'] = array(
      '#type' => 'textfield',
      '#title' => t('FTP Port'),
      '#required' => TRUE,
      '#size'=> 30,
      '#default_value' => (isset($translator->settings['ftp_settings']['ftp_port']) ? $translator->settings['ftp_settings']['ftp_port'] : ''),
      '#description' => t('Please enter the port that the FTP service is lisening to.'),
    );
    
    $form['export_format'] = array(
      '#type' => 'radios',
      '#title' => t('Export to'),
      '#options' => tmgmt_file_format_plugin_labels(),
      '#default_value' => $translator->getSetting('export_format'),
      '#description' => t('Please select the format you want to export data.'),
    );

    $form['xliff_processing'] = array(
      '#type' => 'checkbox',
      '#title' => t('Extended XLIFF processing'),
      '#description' => t('Check to further process content semantics and mask HTML tags instead just escaping it.'),
      '#default_value' => $translator->getSetting('xliff_processing'),
    );

    $form['allow_override'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow to override the format per job'),
      '#default_value' => $translator->getSetting('allow_override'),
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
    $form['app_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Application number'),
      '#default_value' => $translator->getSetting('app_name'),
      '#description' => t('Please enter a valid Application name.'),
    );
    $form['user_name'] = array(
      '#type' => 'textfield',
      '#title' => t('User name'),
      '#default_value' => $translator->getSetting('user_name'),
      '#description' => t('Please, enter an user identifier'),
    );
    $form['institution'] = array(
      '#type' => 'textfield',
      '#title' => t('Institution'),
      '#default_value' => $translator->getSetting('institution'),
      '#description' => t('Please enter the institution the site belongs to'),
    );
    $form['departmentNumber'] = array(
      '#type' => 'textfield',
      '#title' => t('Department Number'),
      '#default_value' => $translator->getSetting('departmentNumber'),
      '#description' => t('Please enter the department number the site belongs to'),
    );
 
    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

  /**
   * {@inheritdoc}
   */
  public function checkoutSettingsForm($form, &$form_state, TMGMTJob $job) {
    if ($job->getTranslator()->getSetting('allow_override')) {
      $form['export_format'] = array(
        '#type' => 'radios',
        '#title' => t('Export to'),
        '#options' => tmgmt_file_format_plugin_labels(),
        '#default_value' => $job->getTranslator()->getSetting('export_format'),
        '#description' => t('Please select the format you want to export data.'),
      );
    }
    return parent::checkoutSettingsForm($form, $form_state, $job);
  }

  /**
   * {@inheritdoc}
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

    $supported_formats = array_keys(tmgmt_file_format_plugin_info());
    $form['file'] = array(
      '#type' => 'file',
      '#title' => t('File file'),
      '#size' => 50,
      '#description' => t('Supported formats: @formats.', array('@formats' => implode(', ', $supported_formats))),
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
      '#submit' => array('tmgmt_file_import_form_submit'),
    );
    return $this->checkoutInfoWrapper($job, $form);
  }
}
