<?php
/**
 * @file
 * Custom VBO actions.
 */

use Drupal\tmgmt_poetry_test\Mock\PoetryMock;

/**
 * Implements hook_action_info().
 */
function tmgmt_poetry_test_action_info() {
  return array(
    'tmgmt_poetry_test_translate_job' => array(
      'type' => 'file',
      'label' => t('TMGMT Poetry Test | VBO | Translate job'),
      'configurable' => FALSE,
      'vbo_configurable' => TRUE,
    ),
    'tmgmt_poetry_test_refuse_job' => array(
      'type' => 'file',
      'label' => t('TMGMT Poetry Test | VBO | Refuse job'),
      'configurable' => FALSE,
    ),
  );
}

/**
 * Translate Job based on given request from the file.
 *
 * @param object $files
 *    Request translation file.
 * @param array $context
 *    Contains all useful information about the action, including
 *    the rows of the view used for VBO.
 */
function tmgmt_poetry_test_translate_job(&$files, $context) {
  $poetry_mock = new PoetryMock();
  if (isset($context['poetry_mock']['request_message'])) {
    // Get data submitted to additional form.
    $message = $context['poetry_mock']['request_message'];
    $lg_code = $context['language'];

    // Prepare responses array.
    $responses = $poetry_mock::prepareTranslationResponseData($message, $lg_code);
    foreach ($responses as $response) {
      $message = theme('poetry_receive_translation', $response);
      $poetry_mock->sendRequestToDrupal($message);
    }
  }
}

/**
 * Form with additional step for translate job action.
 */
function tmgmt_poetry_test_translate_job_form($settings, &$form_state) {
  $form = array();
  if (isset($form_state['selection'][0])) {
    $file_id = $form_state['selection'][0];
    $file_object = file_load($file_id);
    $message = file_get_contents($file_object->uri);
    $languages = PoetryMock::getLanguagesFromRequest($message);
    $form_state['poetry_mock']['request_message'] = $message;
    $form_state['poetry_mock']['languages'] = $languages;
  }
  $all_option = array('ALL' => 'ALL (processing one by one)');

  $form['language'] = array(
    '#type' => 'select',
    '#title' => t('Select language:'),
    '#options' => $all_option + $languages,
    '#default_value' => !empty($options['options']) ? $options['options'] : '',
  );

  return $form;
}

/**
 * Form submit function for additional step of translate job action.
 */
function tmgmt_poetry_test_translate_job_submit($form, $form_state) {
  return array(
    'language' => $form_state['values']['language'],
    'poetry_mock' => $form_state['poetry_mock'],
  );
}

/**
 * Refuse translation job based on given request from the file.
 *
 * @param object $file
 *    Request translation file.
 * @param array $context
 *    Contains all useful information about the action, including
 *    the rows of the view used for VBO.
 */
function tmgmt_poetry_test_refuse_job(&$file, $context) {
  $poetry_mock = new PoetryMock();
  $message = file_get_contents($file->uri);
  // Prepare responses array.
  $response = $poetry_mock::prepareRefuseJobResponseData($message);
  $message = theme('poetry_refuse_translation', $response);
  $poetry_mock->sendRequestToDrupal($message);
}