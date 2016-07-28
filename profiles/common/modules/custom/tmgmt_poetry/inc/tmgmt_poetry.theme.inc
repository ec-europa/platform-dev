<?php

/**
 * @file
 * Handles the theming.
 */

/**
 * Implements hook_theme().
 */
function tmgmt_poetry_theme($existing, $type, $theme, $path) {
  return [
    'poetry_callback_answer' => [
      'variables' => [
        'demande_id' => NULL,
        'code' => NULL,
        'message' => NULL,
      ],
      'template' => 'poetry-callback-answer',
      'path' => TMGMT_POETRY_XML_TEMPLATES_PATH,
    ],
  ];
}
