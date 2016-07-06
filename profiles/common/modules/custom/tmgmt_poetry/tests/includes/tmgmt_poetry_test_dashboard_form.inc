<?php

/**
 * @file
 * tmgmt_poetry_test_dashboard_form.inc
 */

/**
 * Dashboard form for Poetry Web Service Mock.
 */
function tmgmt_poetry_test_dashboard_form($form, &$form_state) {
  $form['mock_dashboard'] = [
    '#title' => t('POETRY Mock - Actions'),
    '#type' => 'fieldset',
    '#tree' => TRUE,
  ];


  return $form;
}

function _tmgmt_poetry_test_request_translation_file_list() {

}
