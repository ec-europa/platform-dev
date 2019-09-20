<?php

/**
 * @file
 * tmgmt_poetry_mock_forms.inc
 */

use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;

/**
 * Setup form for Poetry Service Mock.
 */
function tmgmt_poetry_mock_setup_form($form, &$form_state) {
  $form['mock_setup'] = [
    '#title' => t('Options'),
    '#type' => 'fieldset',
  ];

  $form['mock_setup']['poetry_service_var'] = [
    '#title' => t('Setting POETRY Service Mock variable'),
    '#type' => 'fieldset',
  ];

  if (!_check_poetry_service_variable()) {
    $form['mock_setup']['poetry_service_var']['set_variable'] = [
      '#type' => 'submit',
      '#value' => t('Set variable'),
      '#submit' => ['_tmgmt_poetry_mock_set_poetry_service_var'],
    ];
  }
  else {
    $form['mock_setup']['poetry_service_var']['set_variable'] = [
      '#type' => 'item',
      '#markup' => t('Variable is configured properly.'),
    ];
  };

  return $form;
}

/**
 * Form for sending XML requests.
 */
function tmgmt_poetry_mock_send_request($form, &$form_state) {
  $form['send_request'] = [
    '#type' => 'submit',
    '#value' => t('Send request'),
    '#submit' => ['_tmgmt_poetry_mock_send_request_content'],
    '#weight' => 1,
  ];

  $form['request_content'] = [
    '#title' => t('Request content'),
    '#type' => 'textarea',
    '#description' => t('You can paste dumps from Kibana to this field.'),
    '#default_value' => '',
    '#rows' => 20,
    '#weight' => 2,
  ];

  return $form;
}

/**
 * Custom submit function which sends XML request based on pasted content.
 */
function _tmgmt_poetry_mock_send_request_content($form, &$form_state) {
  $request_content = $form_state['values']['request_content'];
  $request_content = html_entity_decode($request_content);
  $poetry_mock = new PoetryMock();
  $poetry_mock->sendRequestToDrupal($request_content);
}

/**
 * Helper form submit function for setting up poetry_service variable.
 *
 * It is not possible to set it up during installation of the module.
 * It can be only set up correctly from full bootstrapped Drupal.
 */
function _tmgmt_poetry_mock_set_poetry_service_var($form, &$form_state) {
  $poetry_service = tmgmt_poetry_mock_service_configuration();

  variable_set('poetry_service', $poetry_service);
}
