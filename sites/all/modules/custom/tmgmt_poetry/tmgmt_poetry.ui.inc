<?php

/**
 * @file
 * Provides Google Translator ui controller.
 */

/**
 * Google translator ui controller.
 */
class TMGMTPoetryTranslatorUIController extends TMGMTDefaultTranslatorUIController {

  /**
   * Overrides TMGMTDefaultTranslatorUIController::pluginSettingsForm().
   */
  public function pluginSettingsForm($form, &$form_state, TMGMTTranslator $translator, $busy = FALSE) {

    $form['poetry_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Poetry Settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    $poetry_message = _tmgmt_poetry_check_poetry_settings();
    $form['poetry_settings']['poetry_message'] = array(
      '#markup' => $poetry_message,
    );

    $contacts = $translator->getSetting('contacts');
    $form['contacts'] = array(
      '#type' => 'fieldset',
      '#title' => t('Contact usernames'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t("Contact persons for the translation request sent to Poetry. WARNING: Valid EC usernames must be used"),
    );
    $form['contacts']['author'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#required' => TRUE,
      '#default_value' => $contacts['author'],
    );
    $form['contacts']['secretary'] = array(
      '#type' => 'textfield',
      '#title' => t('Secretary'),
      '#required' => TRUE,
      '#default_value' => $contacts['secretary'],
    );
    $form['contacts']['contact'] = array(
      '#type' => 'textfield',
      '#title' => t('Contact'),
      '#required' => TRUE,
      '#default_value' => $contacts['contact'],
    );
    $form['contacts']['responsible'] = array(
      '#type' => 'textfield',
      '#title' => t('Responsible'),
      '#required' => TRUE,
      '#default_value' => $contacts['responsible'],
    );

    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

}
