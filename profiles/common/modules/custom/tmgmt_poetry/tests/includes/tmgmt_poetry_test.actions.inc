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
  );
}

function tmgmt_poetry_test_translate_job_form($settings, &$form_state) {
  $form = array();
  if (isset($form_state['selection'][0])) {
    $file_id = $form_state['selection'][0];
  }

  $form['options'] = array(
    '#type' => 'select',
    '#title' => t('Select language:'),
    '#options' => array(
      'Iron Man' => t('abc'),
      'Bat Man' => t('efg'),
    ),
    '#default_value' => !empty($options['options']) ? $options['options'] : '',
  );

  return $form;
}

function tmgmt_poetry_test_translate_job_submit($form, $form_state) {
  $return = array();
  //$return['hero'] = $form_state['values']['hero'];
  return $return; //Note, return value here must be an array.
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
  $message = file_get_contents($files->uri);
  $poetry_mock = new PoetryMock();
  if ($message) {
    $responses = $poetry_mock::prepareTranslationResponseData($message);
    foreach ($responses as $response) {
      $message = theme('poetry_receive_translation', $response);
      $poetry_mock->sendRequestToDrupal($message);
    }
  }
}
