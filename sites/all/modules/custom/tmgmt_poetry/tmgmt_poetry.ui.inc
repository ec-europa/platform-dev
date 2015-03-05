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
    $form['contacts']['auteur'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#required' => TRUE,
      '#default_value' => $contacts['auteur'],
    );
    $form['contacts']['secretaire'] = array(
      '#type' => 'textfield',
      '#title' => t('Secretaire'),
      '#required' => TRUE,
      '#default_value' => $contacts['secretaire'],
    );
    $form['contacts']['contact'] = array(
      '#type' => 'textfield',
      '#title' => t('Contact'),
      '#required' => TRUE,
      '#default_value' => $contacts['contact'],
    );
    $form['contacts']['responsable'] = array(
      '#type' => 'textfield',
      '#title' => t('Responsible'),
      '#required' => TRUE,
      '#default_value' => $contacts['responsable'],
    );

    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

}
