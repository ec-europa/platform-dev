<?php
/**
 * @file
 * Provides MT@EC Translator ui controller.
 */

/**
 * MT@EC translator ui controller.
 */
class TMGMTMtecTranslatorUIController extends TMGMTDefaultTranslatorUIController {

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

    $ftp_message = _tmgmt_mtect_check_ftp_settings();
    $form['ftp_settings']['ftp_message'] = array(
      '#markup' => $ftp_message,
    );

    $form['mtec_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('MT@EC Settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    $ftp_message = _tmgmt_mtect_check_mtec_settings();
    $form['mtec_settings']['ftp_message'] = array(
      '#markup' => $ftp_message,
    );

    $mtec_settings = $translator->getSetting('mtec_settings');
    $form['mtec_settings']['user_name'] = array(
      '#type' => 'textfield',
      '#title' => t('User name'),
      '#default_value' => $mtec_settings['user_name'],
      '#description' => t('Please, enter an user identifier'),
      '#required' => TRUE,
    );
    $form['mtec_settings']['institution'] = array(
      '#type' => 'textfield',
      '#title' => t('Institution'),
      '#default_value' => $mtec_settings['institution'],
      '#description' => t('Please enter the institution the site belongs to'),
      '#required' => TRUE,
    );
    $form['mtec_settings']['departmentNumber'] = array(
      '#type' => 'textfield',
      '#title' => t('Department Number'),
      '#default_value' => $mtec_settings['departmentNumber'],
      '#description' => t('Please enter the department number the site belongs to'),
      '#required' => TRUE,
    );
    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

}
