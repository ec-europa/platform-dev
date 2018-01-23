<?php

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultTranslatorUIController;

use TMGMTDefaultTranslatorUIController;
use TMGMTTranslator;

/**
 * TMGMT DGT FTT translator plugin controller.
 */
class TmgmtDgtFttTranslatorUiController extends TMGMTDefaultTranslatorUIController {

  /**
   * Overrides TMGMTDefaultTranslatorUIController::pluginSettingsForm().
   */
  public function pluginSettingsForm($form, &$form_state, TMGMTTranslator $translator, $busy = FALSE) {
    $settings = $translator->getSetting('settings');
    $form['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('DGT FTT Translator settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t("Settings for the DGT FTT translator requests."),
    );
    $form['settings']['dgt_counter'] = array(
      '#type' => 'textfield',
      '#title' => t('Counter'),
      '#required' => TRUE,
      '#default_value' => $settings['dgt_counter'],
    );
    $form['settings']['dgt_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Requester code'),
      '#required' => TRUE,
      '#default_value' => $settings['dgt_code'],
    );
    $form['settings']['callback_username'] = array(
      '#type' => 'textfield',
      '#title' => t('Callback User'),
      '#required' => TRUE,
      '#default_value' => $settings['callback_username'],
    );
    $form['settings']['callback_password'] = array(
      '#type' => 'password',
      '#title' => t('Callback Password'),
      '#required' => TRUE,
      '#default_value' => $settings['callback_password'],
    );
    $form['settings']['dgt_ftt_username'] = array(
      '#type' => 'textfield',
      '#title' => t('DGT FTT - username'),
      '#required' => TRUE,
      '#default_value' => $settings['dgt_ftt_username'],
    );
    $form['settings']['dgt_ftt_password'] = array(
      '#type' => 'password',
      '#title' => t('DGT FTT - password'),
      '#required' => TRUE,
      '#default_value' => $settings['dgt_ftt_password'],
    );
    $form['settings']['dgt_ftt_workflow_code'] = array(
      '#type' => 'textfield',
      '#title' => t('DGT FTT - workflow code'),
      '#maxlength' => 15,
      '#required' => TRUE,
      '#default_value' => $settings['dgt_ftt_workflow_code'],
    );

    // Organization details.
    $organization = $translator->getSetting('organization');
    $form['organization'] = array(
      '#type' => 'fieldset',
      '#title' => t('Organization'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t("Requester organization information."),
    );
    $form['organization']['responsible'] = array(
      '#type' => 'textfield',
      '#title' => t('Responsible'),
      '#required' => TRUE,
      '#default_value' => $organization['responsible'],
      '#description' => t("Eg.: DIGIT"),
    );
    $form['organization']['author'] = array(
      '#type' => 'textfield',
      '#title' => t('DG Author'),
      '#required' => TRUE,
      '#default_value' => $organization['author'],
      '#description' => t("Eg.: IE/CE/DIGIT"),
    );
    $form['organization']['requester'] = array(
      '#type' => 'textfield',
      '#title' => t('Requester'),
      '#required' => TRUE,
      '#default_value' => $organization['requester'],
      '#description' => t("Eg.: IE/CE/DIGIT/A/3"),
    );

    // Contact details.
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

    // Feedback contacts details.
    $feedback_contacts = $translator->getSetting('feedback_contacts');
    $form['feedback_contacts'] = array(
      '#type' => 'fieldset',
      '#title' => t('DGT Contacts'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t("Contact persons for send a feedback."),
    );
    $form['feedback_contacts']['email_to'] = array(
      '#type' => 'textfield',
      '#title' => t('Email to'),
      '#required' => TRUE,
      '#default_value' => $feedback_contacts['email_to'],
    );
    $form['feedback_contacts']['email_cc'] = array(
      '#type' => 'textfield',
      '#title' => t('Email CC'),
      '#required' => TRUE,
      '#default_value' => $feedback_contacts['email_cc'],
    );

    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

  // @todo: check if the validation for this form is needed.
}
