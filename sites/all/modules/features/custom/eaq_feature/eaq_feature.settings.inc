<?php

/**
 * @file
 * 
 */

function eaq_feature_general_settings_form($form) {
  $form = array();
  
  $form['redirect_page'] = array(
    '#title' => t('Thank you Page'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
  );
  
  $form['redirect_page']['eaq_feature_message'] = array(
    '#title' => t('Default Thank you Message'),
    '#type' => 'textfield',
    '#default_value' => variable_get('eaq_feature_message', t('Thanks for filling in our Ask a Question form.')),
  );
  
  $form['redirect_page']['eaq_feature_redirect_page'] = array(
    '#title' => t('Default Thank you Page'),
    '#type' => 'textfield',
    '#description' => t('Optionally, specify a relative URL to display as the thank you page. Leave blank to redirect to the homepage.'),
    '#default_value' => variable_get('eaq_feature_redirect_page', ''),
  );
  
  $form['users'] = array(
    '#title' => t('Assignment Users'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
  );

  $user_roles = user_roles(TRUE);
  $form['users']['eaq_feature_role_assignee_user'] = array(
    '#title' => t('Assignee role'),
    '#type' => 'select',
    '#options' => $user_roles,
    '#default_value' => variable_get('eaq_feature_role_assignee_user', ''),
  );
  
  $user = user_load(variable_get('eaq_feature_default_assignee_user', ''));
  $form['users']['eaq_feature_default_assignee_user'] = array(
    '#title' => t('Default Assignee'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'ask-a-question/autocomplete/users',
    '#default_value' => (isset($user) && $user->uid != 0) ? $user->name . ' [uid:' . variable_get('eaq_feature_default_assignee_user', '') . ']' : '',
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array(
      'eaq_feature_settings_form_submit',
    ),
  );
  
  return $form;
}

function eaq_feature_mail_settings_form($form) {
  $form = array();
  
  $form['mail'] = array(
    '#title' => t('E-mails'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
  );
  
  $form['mail']['eaq_feature_mail_default_email'] = array(
    '#title' => t('Default E-mail address'),
    '#type' => 'textfield',
    '#default_value' => variable_get('eaq_feature_mail_default_email', ''),
    '#maxlength' => 180,
  );
  
  $form['mail']['default'] = array(
    '#title' => t('Default mails'),
    '#description' => t('Those mails are used when no translation is present.'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
  );
  
  $form['mail']['default']['question'] = array(
    '#title' => t('New Question'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );
  
  $form['mail']['default']['question']['eaq_feature_mail_default_question_subject'] = array(
    '#title' => t('New Question: Subject'),
    '#type' => 'textfield',
    '#default_value' => variable_get('eaq_feature_mail_default_question_subject', ''),
    '#maxlength' => 180,
  );
  
  $form['mail']['default']['question']['eaq_feature_mail_default_question_body'] = array(
    '#title' => t('New Question: Body'),
    '#type' => 'textarea',
    '#default_value' => variable_get('eaq_feature_mail_default_question_body', ''),
    '#rows' => 10,
  );
  
  $form['mail']['default']['handle'] = array(
    '#title' => t('Question Handled'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );
  
  $form['mail']['default']['handle']['eaq_feature_mail_default_handle_subject'] = array(
    '#title' => t('Question Handled: Subject'),
    '#type' => 'textfield',
    '#default_value' => variable_get('eaq_feature_mail_default_handle_subject', ''),
    '#maxlength' => 180,
  );
  
  $form['mail']['default']['handle']['eaq_feature_mail_default_handle_body'] = array(
    '#title' => t('Question Handled: Body'),
    '#type' => 'textarea',
    '#default_value' => variable_get('eaq_feature_mail_default_handle_body', ''),
    '#rows' => 10,
  );
  
  $form['mail']['default']['reassign'] = array(
    '#title' => t('Reassigned Question'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );
  
  $form['mail']['default']['reassign']['eaq_feature_mail_default_reassign_subject'] = array(
    '#title' => t('Reassigned Question: Subject'),
    '#type' => 'textfield',
    '#default_value' => variable_get('eaq_feature_mail_default_reassign_subject', ''),
    '#maxlength' => 180,
  );
  
  $form['mail']['default']['reassign']['eaq_feature_mail_default_reassign_body'] = array(
    '#title' => t('Reassigned Question: Body'),
    '#type' => 'textarea',
    '#default_value' => variable_get('eaq_feature_mail_default_reassign_body', ''),
    '#rows' => 10,
  );
  
  $languages = language_list('language');
  foreach ($languages as $langcode => $language) {
    $form['mail'][$langcode] = array(
      '#title' => t($language->name . ' mails'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => FALSE,
    );
    
    $form['mail'][$langcode]['question'] = array(
      '#title' => t('New Question'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => FALSE,
    );
    
    $form['mail'][$langcode]['question']['eaq_feature_mail_' . $langcode . '_question_subject'] = array(
      '#title' => t('New Question: Subject'),
      '#type' => 'textfield',
      '#default_value' => variable_get('eaq_feature_mail_' . $langcode . '_question_subject', ''),
      '#maxlength' => 180,
    );
    
    $form['mail'][$langcode]['question']['eaq_feature_mail_' . $langcode . '_question_body'] = array(
      '#title' => t('New Question: Body'),
      '#type' => 'textarea',
      '#default_value' => variable_get('eaq_feature_mail_' . $langcode .'_question_body', ''),
      '#rows' => 10,
    );
    
    $form['mail'][$langcode]['handle'] = array(
      '#title' => t('Question Handled'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => FALSE,
    );
    
    $form['mail'][$langcode]['handle']['eaq_feature_mail_' . $langcode .'_handle_subject'] = array(
      '#title' => t('Question Handled: Subject'),
      '#type' => 'textfield',
      '#default_value' => variable_get('eaq_feature_mail_' . $langcode .'_handle_subject', ''),
      '#maxlength' => 180,
    );
    
    $form['mail'][$langcode]['handle']['eaq_feature_mail_' . $langcode .'_handle_body'] = array(
      '#title' => t('Question Handled: Body'),
      '#type' => 'textarea',
      '#default_value' => variable_get('eaq_feature_mail_' . $langcode .'_handle_body', ''),
      '#rows' => 10,
    );
    
    $form['mail'][$langcode]['reassign'] = array(
      '#title' => t('Reassigned Question'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => FALSE,
    );
    
    $form['mail'][$langcode]['reassign']['eaq_feature_mail_' . $langcode .'_reassign_subject'] = array(
      '#title' => t('Reassigned Question: Subject'),
      '#type' => 'textfield',
      '#default_value' => variable_get('eaq_feature_mail_' . $langcode .'_reassign_subject', ''),
      '#maxlength' => 180,
    );
    
    $form['mail'][$langcode]['reassign']['eaq_feature_mail_' . $langcode .'_reassign_body'] = array(
      '#title' => t('Reassigned Question: Body'),
      '#type' => 'textarea',
      '#default_value' => variable_get('eaq_feature_mail_' . $langcode .'_reassign_body', ''),
      '#rows' => 10,
    );
  }
  
  $form['mail']['tokens'] = array(
    '#title' => t('Tokens'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );
  
  $form['mail']['tokens']['token_tree'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('node'),
    '#global_types' => TRUE,
    '#click_insert' => FALSE,
  );
  
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array(
      'eaq_feature_settings_form_submit',
    ),
  );
  
  return $form;
}

function eaq_feature_settings_form_submit($form, &$form_state) {
  form_state_values_clean($form_state);

  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    
    if ($key == 'eaq_feature_default_assignee_user') {
      preg_match('/\[uid:(\d+)\]/', $value, $matches);
      if (isset($matches[1])) {
        $value = $matches[1];
      }
    }
    if ($key == 'eaq_feature_mail_default_email') {
      if (!empty($value) && !valid_email_address($value)) {
        form_set_error('eaq_feature_mail_default_email', t('Please fill in a valid email address'));
      }
    }
    variable_set($key, $value);
  }
  
  drupal_set_message(t('The configuration options have been saved.'));
}