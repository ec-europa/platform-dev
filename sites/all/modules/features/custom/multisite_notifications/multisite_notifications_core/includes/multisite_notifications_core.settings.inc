<?php

/**
 *
 * @return type
 */

function multisite_notifications_core_general_settings() {

//Subscription
  $form['subscription_block_settings'] = array(
      '#title' => t('Subscribe block settings'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );

  $form['subscription_block_settings']['subscribe_confirmation'] = array(
      '#title' => t('Subscribe confirmation mail'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );

  //Subject
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['subscribe_confirmation']['subscribe_subject_' . $language->language] = array(
        '#title' => t('Subscribe mail subject: ' . $language->name),
        '#type' => 'textfield',
        '#default_value' => variable_get('subscribe_subject_' . $language->language, ''),
    );
  }

  //Body
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['subscribe_confirmation']['subscribe_message_' . $language->language] = array(
        '#title' => t('Subscribe mail body: ' . $language->name),
        '#type' => 'textarea',
        '#default_value' => variable_get('subscribe_message_' . $language->language, ''),
    );
  }


  //Unsubscription

   $form['subscription_block_settings']['unsubscribe_confirmation'] = array(
      '#title' => t('Unsubscribe confirmation mail'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );


    //Subject
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['unsubscribe_confirmation']['unsubscribe_subject_' . $language->language] = array(
        '#title' => t('Unsubscribe mail subject: ' . $language->name),
        '#type' => 'textfield',
        '#default_value' => variable_get('unsubscribe_subject_' . $language->language, ''),
    );
  }

   //Body
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['unsubscribe_confirmation']['unsubscribe_message_' . $language->language] = array(
        '#title' => t('Unsubscribe mail body: ' . $language->name),
        '#type' => 'textarea',
        '#default_value' => variable_get('unsubscribe_message_' . $language->language, ''),
    );
  }


  return system_settings_form($form);

}