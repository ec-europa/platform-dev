<?php
/**
 * @file
 * Handles the theming.
 */

/**
 * Implements hook_theme().
 */
function tmgmt_poetry_mock_theme($existing, $type, $theme, $path) {
  return [
    'poetry_confirmation_of_receiving_translation_request' => [
      'variables' => [
        'demande_id' => NULL,
      ],
      'template' => 'poetry-confirmation-of-receiving-the-translation-request',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ],
    'poetry_receive_translation' => [
      'variables' => [
        'demande_id' => NULL,
        'content' => NULL,
        'language' => NULL,
        'format' => NULL,
      ],
      'template' => 'poetry-receive-translation',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ],
    'poetry_refuse_translation' => [
      'variables' => [
        'demande_id' => NULL,
        'languages' => NULL,
        'format' => NULL,
        'status' => NULL,
      ],
      'template' => 'poetry-refuse-translation',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ],
    'poetry_wsdl' => [
      'variables' => [
        'uri' => NULL,
      ],
      'template' => 'poetry-wsdl',
      'path' => TMGMT_POETRY_MOCK_TEMPLATES_PATH,
    ],
  ];
}
