<?php
/**
 * @file
 * Handles the theming.
 */

/**
 * Implements hook_theme().
 */
function tmgmt_poetry_mock_theme($existing, $type, $theme, $path) {
  return array(
    'poetry_confirmation_of_receiving_translation_request' => array(
      'variables' => array(
        'demande_id' => NULL,
      ),
      'template' => 'poetry-confirmation-of-receiving-the-translation-request',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ),
    'poetry_receive_translation' => array(
      'variables' => array(
        'demande_id' => NULL,
        'content' => NULL,
        'language' => NULL,
        'format' => NULL,
      ),
      'template' => 'poetry-receive-translation',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ),
    'poetry_refuse_translation' => array(
      'variables' => array(
        'demande_id' => NULL,
        'languages' => NULL,
        'format' => NULL,
        'status' => NULL,
      ),
      'template' => 'poetry-refuse-translation',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ),
    'poetry_wsdl' => array(
      'variables' => array(
        'uri' => NULL,
      ),
      'template' => 'poetry-wsdl',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ),
  );
}
