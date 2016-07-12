<?php
/**
 * @file
 * tmgmt_poetry_mock_forms.inc
 */

/**
 * Forms for Poetry Service Mock.
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
 * Helper form submit function for setting up poetry_service variable.
 *
 * It is not possible to set it up during installation of the module.
 * It can be only set up correctly from full bootstrapped Drupal.
 */
function _tmgmt_poetry_mock_set_poetry_service_var($form, &$form_state) {
  $poetry_service = [
    'address' => _get_poetry_service_mock_wsdl(),
    'method' => 'requestService',
    'callback_user' => 'Callback',
    'callback_password' => 'CallbackPWD',
    'poetry_user' => 'Poetry',
    'poetry_password' => 'PoetryPWD',
    'drupal_wsdl' => _get_drupal_soap_server_mock_wsdl(),
    'poetry_endpoint' => _get_poetry_mock_endpoint(),
  ];

  variable_set('poetry_service', $poetry_service);
}
