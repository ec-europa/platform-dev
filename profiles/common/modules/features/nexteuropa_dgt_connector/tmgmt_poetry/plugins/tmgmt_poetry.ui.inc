<?php

/**
 * @file
 * Provides Google Translator ui controller.
 */

/**
 * DGT connector translator ui controller.
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

    $poetry_message = $this->checkPoetrySettings();
    $form['poetry_settings']['poetry_message'] = array(
      '#markup' => $poetry_message,
    );

    $settings = $translator->getSetting('settings');
    $form['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('General settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t("General settings for the requests"),
    );
    $form['settings']['counter'] = array(
      '#type' => 'textfield',
      '#title' => t('Counter'),
      '#required' => TRUE,
      '#default_value' => $settings['counter'],
    );
    $form['settings']['code'] = array(
      '#type' => 'textfield',
      '#title' => t('Requester code'),
      '#required' => TRUE,
      '#default_value' => $settings['code'],
    );
    $form['settings']['callback_user'] = array(
      '#type' => 'textfield',
      '#title' => t('Callback User'),
      '#required' => TRUE,
      '#default_value' => $settings['callback_user'],
    );
    $form['settings']['callback_password'] = array(
      '#type' => 'textfield',
      '#title' => t('Callback Password'),
      '#required' => TRUE,
      '#default_value' => $settings['callback_password'],
    );
    $form['settings']['poetry_user'] = array(
      '#type' => 'textfield',
      '#title' => t('Poetry User'),
      '#required' => TRUE,
      '#default_value' => $settings['poetry_user'],
    );
    $form['settings']['poetry_password'] = array(
      '#type' => 'textfield',
      '#title' => t('Poetry Password'),
      '#required' => TRUE,
      '#default_value' => $settings['poetry_password'],
    );

    $organization = $translator->getSetting('organization');
    $form['organization'] = array(
      '#type' => 'fieldset',
      '#title' => t('Organization'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t("Requester organization information"),
    );
    $form['organization']['responsable'] = array(
      '#type' => 'textfield',
      '#title' => t('Responsable'),
      '#required' => TRUE,
      '#default_value' => $organization['responsable'],
      '#description' => t("Eg.: DIGIT"),
    );
    $form['organization']['auteur'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#required' => TRUE,
      '#default_value' => $organization['auteur'],
      '#description' => t("Eg.: IE/CE/DIGIT"),
    );
    $form['organization']['demandeur'] = array(
      '#type' => 'textfield',
      '#title' => t('Requester'),
      '#required' => TRUE,
      '#default_value' => $organization['demandeur'],
      '#description' => t("Eg.: IE/CE/DIGIT/A/3"),
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

    $feedback_contacts = $translator->getSetting('feedback_contacts');
    $form['feedback_contacts'] = array(
      '#type' => 'fieldset',
      '#title' => t('DGT Contacts'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t("Contact persons for send a feedback"),
    );
    $form['feedback_contacts']['to'] = array(
      '#type' => 'textfield',
      '#title' => t('Email to'),
      '#required' => TRUE,
      '#default_value' => $feedback_contacts['to'],
    );
    $form['feedback_contacts']['cc'] = array(
      '#type' => 'textfield',
      '#title' => t('Email CC'),
      '#required' => TRUE,
      '#default_value' => $feedback_contacts['cc'],
    );

    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

  /**
   * {@inheritdoc}
   */
  public function checkoutInfo(TMGMTJob $job) {
    $form_state = array();
    $form['settings'] = $this->checkoutSettingsForm(array(), $form_state, $job);

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function checkoutSettingsForm($form, &$form_state, TMGMTJob $job) {
    // Build the sortable table header.
    $header = array(
      'language' => t('Language'),
    );

    if ($job->state > TMGMT_JOB_STATE_UNPROCESSED) {
      $header['state'] = t('State');
      $header['delai'] = t('Delivery date');
      $header['operations'] = t('Operations');
    }

    $target_language = isset($form_state['values']['target_language'])
      ? $form_state['values']['target_language']
      : $job->target_language;

    $default_value = array();

    foreach (language_list() as $language) {
      if ($language->language == $job->source_language) {
        continue;
      }

      $language_job_ids = _tmgmt_poetry_obtain_related_translation_jobs(array($language->language), '%' . str_replace('MAIN_', '', $job->reference))->fetchAll();
      if (count($language_job_ids) > 0) {
        $language_job_id = array_shift($language_job_ids);
        $language_job_item = tmgmt_job_item_load($language_job_id->tjiid);
        $result = db_select('poetry_status', 'ps')
          ->fields('ps')
          ->condition('tjiid', $language_job_item->tjiid, '=')
          ->execute()
          ->fetchAssoc();
        if (!empty($result)) {
          $options[$language->language]['state'] = $result['status'];
          $options[$language->language]['delai'] = $result['delai'];
        }
        if (in_array($language_job_item->state, array(TMGMT_JOB_ITEM_STATE_REVIEW, TMGMT_JOB_ITEM_STATE_ACCEPTED))) {
          $options[$language->language]['operations']  = l(t('View'), 'admin/tmgmt/items/' . $language_job_item->tjiid, array('query' => array('destination' => 'admin/tmgmt/jobs/' . $job->tjid)));
        }
      }

      if (!isset($options[$language->language]['state'])) {
        $options[$language->language]['state'] = t('Not sent');
      }

      if (!isset($options[$language->language]['delai'])) {
        $options[$language->language]['delai'] = '';
      }

      if (!isset($options[$language->language]['operations'])) {
        $options[$language->language]['operations'] = '';
      }
      $options[$language->language]['language'] = $language->name;
      if ($language->language == $target_language) {
        $default_value[$target_language] = $target_language;
      }
    }

    if (isset($job->settings['languages'])) {
      foreach ($job->settings['languages'] as $selected_language) {
        if (!empty($selected_language)) {
          $default_value[$selected_language] = $selected_language;
        }
      }
    }

    // NEXTEUROPA-7719 - Simplifying Poetry UI.
    // Get languages that were chosen during creation of translation request.
    // This should work only for new translation requests to prevent an impact
    // off stored in session language array.
    if (is_null($job->settings)) {
      $chosen_languages = _tmgmt_workbench_get_request_languages();
      foreach ($chosen_languages as $lg_code => $language) {
        if ($lg_code !== 'main') {
          $default_value[$language] = $language;
        }
      }
    }
    $form['languages'][$target_language]['#disabled'] = FALSE;

    // Build the tableselect.
    $form['languages'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#default_value' => $default_value,
      '#empty' => t('No content available.'),
    );

    // Load translator settings : Contacts.
    $translator = $job->getTranslator();
    $contacts = $translator->getSetting('contacts');
    $form['contacts'] = array(
      '#type' => 'fieldset',
      '#title' => t('Contact usernames'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t("Contact persons for the translation request sent to Poetry. WARNING: Valid EC usernames must be used"),
    );
    $form['contacts']['auteur'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#required' => TRUE,
      '#default_value' => (!empty($job->settings['contacts']['auteur']) ? $job->settings['contacts']['auteur'] : $contacts['auteur']),
    );
    $form['contacts']['secretaire'] = array(
      '#type' => 'textfield',
      '#title' => t('Secretaire'),
      '#required' => TRUE,
      '#default_value' => (!empty($job->settings['contacts']['secretaire']) ? $job->settings['contacts']['secretaire'] : $contacts['secretaire']),
    );
    $form['contacts']['contact'] = array(
      '#type' => 'textfield',
      '#title' => t('Contact'),
      '#required' => TRUE,
      '#default_value' => (!empty($job->settings['contacts']['contact']) ? $job->settings['contacts']['contact'] : $contacts['contact']),
    );
    $form['contacts']['responsable'] = array(
      '#type' => 'textfield',
      '#title' => t('Responsible'),
      '#required' => TRUE,
      '#default_value' => (!empty($job->settings['contacts']['responsable']) ? $job->settings['contacts']['responsable'] : $contacts['responsable']),
    );

    // Load translator settings : Organization.
    $organization = $translator->getSetting('organization');
    $form['organization'] = array(
      '#type' => 'fieldset',
      '#title' => t('Organization'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t("Requester organization information"),
    );
    $form['organization']['responsable'] = array(
      '#type' => 'textfield',
      '#title' => t('Responsable'),
      '#required' => TRUE,
      '#default_value' => $organization['responsable'],
      '#description' => t("Eg.: DIGIT"),
    );
    $form['organization']['auteur'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#required' => TRUE,
      '#default_value' => $organization['auteur'],
      '#description' => t("Eg.: IE/CE/DIGIT"),
    );
    $form['organization']['demandeur'] = array(
      '#type' => 'textfield',
      '#title' => t('Requester'),
      '#required' => TRUE,
      '#default_value' => $organization['demandeur'],
      '#description' => t("Eg.: IE/CE/DIGIT/A/3"),
    );

    $form['delai'] = array(
      '#type' => 'date_popup',
      '#title' => t('Requested delivery date'),
      '#default_value' => (!empty($job->settings['delai']) ? $job->settings['delai'] : date('Y-m-d', strtotime('+1 month'))),
      '#date_format' => 'd/m/Y',
      '#date_year_range' => '-3:+3',

    );

    $form['remark'] = array(
      '#type' => 'textfield',
      '#title' => t('Remark'),
      '#size' => 128,
      '#maxlength' => 255,
      '#default_value' => (!empty($job->settings['remark']) ? $job->settings['remark'] : ''),
      '#description' => t("Comment to be sent along with the request"),
    );

    if ($job->state != TMGMT_JOB_STATE_UNPROCESSED) {
      $form['languages']['#disabled'] = TRUE;
      $form['contacts']['#disabled'] = TRUE;
      $form['organization']['#disabled'] = TRUE;
      $form['delai']['#disabled'] = TRUE;
      $form['remark']['#disabled'] = TRUE;
    }

    return $form;
  }

  /**
   * Helper module to check connector settings.
   */
  protected function checkPoetrySettings() {
    $messages = array();
    $poetry_settings = variable_get('poetry_service');

    $translator = tmgmt_translator_load('poetry');
    $settings = $translator->getSetting('settings');

    if (empty($poetry_settings['address'])) {
      $messages[] = t('The DGT webservice address is not set. Please contact your support team.');
      $type = 'error';
    }
    if (empty($settings['callback_user']) || empty($settings['callback_password'])) {
      $messages[] = t('The credentials for your drupal service are not correctly set. Please contact COMM EUROPA MANAGEMENT.');
      $type = 'error';
    }
    if (empty($settings['poetry_user']) || empty($settings['poetry_password'])) {
      $messages[] = t('The credentials for your DGT service are not correctly set. Please contact COMM EUROPA MANAGEMENT.');
      $type = 'error';
    }
    if (empty($messages)) {
      $messages[] = t('Main "poetry_service" variable is properly set.');
      $type = 'status';
    }
    return $this->themeMessages($messages, $type);
  }

  /**
   * Helper module to theme connector messages.
   *
   * @param array $messages
   *   Array of messages to be displayed.
   * @param string $type
   *   Type of the messages.
   *
   * @return string
   *   Themed messages.
   */
  protected function themeMessages(array $messages, $type) {
    $output = '';
    if (!empty($messages)) {
      $output .= "<div class=\"messages $type\">\n";
      if (count($messages) > 1) {
        $output .= " <ul>\n";
        foreach ($messages as $message) {
          $output .= '  <li>' . $message . "</li>\n";
        }
        $output .= " </ul>\n";
      }
      else {
        $output .= $messages[0];
      }
      $output .= "</div>\n";
    }
    return $output;
  }

  /**
   * {@inheritdoc}
   */
  public function reviewFormSubmit($form, &$form_state, TMGMTJobItem $item) {
    // Check if the user clicked on 'Accept', 'Submit' or 'Reject'.
    if (!empty($form['actions']['accept']) && $form_state['triggering_element']['#value'] == $form['actions']['accept']['#value']) {
      _tmgmt_poetry_update_item_status($item->tjiid, "", "Translation accepted", "");
    }
  }

}
