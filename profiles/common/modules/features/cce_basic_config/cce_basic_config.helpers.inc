<?php

/**
 * @file
 * cce_basic_config.helpers.inc
 */

/**
 * Custom function to import images.
 *
 * @param array $images
 *   This parameter is an array of array.
 *   The keys of each item of this array are:
 *     - scheme: The streamwrapper scheme (ex: public://)
 *     - dest_directory: The destination directory
 *     - source_path: The source path
 *     - filename: The filename
 *     - variable: The variable name containing the file id (fid) of the saved
 *                 file if it has been successfully saved.
 */
function _cce_basic_config_import_images($images) {
  foreach ($images as $default_image_data) {
    $full_dir = $default_image_data['scheme'] . $default_image_data['dest_directory'];
    $file_uri = $full_dir . '/' . $default_image_data['filename'];

    file_prepare_directory($full_dir, FILE_CREATE_DIRECTORY);
    file_unmanaged_copy($default_image_data['source_path'], $file_uri, FILE_EXISTS_REPLACE);

    $file = (object) array(
      'uid' => 1,
      'status' => FILE_STATUS_PERMANENT,
      'filename' => $default_image_data['filename'],
      'uri' => $file_uri,
      'filemime' => file_get_mimetype($default_image_data['source_path']),
    );
    $file = file_save($file);

    if ($file) {
      variable_set($default_image_data['variable'], $file->uri);
    }
  }
}

/**
 * Field widget form alter callback.
 *
 * It injects a specific validate callback in charge of scanning field value.
 *
 * @see cce_basic_config_field_widget_text_textarea_form_alter()
 * @see cce_basic_config_field_widget_text_textarea_with_summary_form_alter()
 * @see cce_basic_config_field_widget_text_textfield_form_alter()
 * @see NEPT-1679
 * @see https://www.drupal.org/project/drupal/issues/2488180
 * @see https://www.drupal.org/node/2754539
 * To be removed when UTF-8 will be supported.
 */
function _cce_basic_config_field_widget_form_alter(&$element, &$form_state, $context) {
  if (isset($element['#entity'])) {
    $element['#element_validate'][] = '_cce_basic_config_field_validate';
  }
}

/**
 * A "Text" field validation callback.
 *
 * It checks if the field value contains emoji characters.
 * If it contains ones, it stores the field name in the form_state.
 * It will be used during the entity validation.
 *
 * @param array $element
 *   Field element that has been edited.
 * @param array $form_state
 *   Form_state related to the submitted form.
 * @param array $form
 *   Submitted form.
 *
 * @see _cce_basic_config_entity_validate()
 * @see NEPT-1679
 * @see https://www.drupal.org/project/drupal/issues/2488180
 * @see https://www.drupal.org/node/2754539
 * To be removed in NEPT-1817
 */
function _cce_basic_config_field_validate($element, &$form_state, $form) {
  $entity = $element['#entity'];

  $value = '';
  if (isset($element['#value'])) {
    $value = $element['#value'];
  }
  elseif (isset($element['value'])) {
    // The callback is called twice for field with text format.
    // In this case, the inserted value is stored differently.
    $value = $element['value']['#value'];
    $element = $element['value'];
  }

  $emoji = _cce_basic_config_get_emoji($value);
  if (!empty($emoji)) {

    // Get the field label.
    $title = $element['#title'];
    if (empty($element['#title'])) {
      // Multi value fields have an empty '#title'.
      $info = field_info_instance($entity->entity_type, $element['#field_name'], $element['#bundle']);
      $title = check_plain($info['label']);
    }

    $message = _cce_basic_config_emoji_error($title, $emoji[0]);
    form_error($element, $message);
  }
}

/**
 * Returns an error message regarding the use of emojis.
 *
 * @param string $title
 *   Title of field.
 * @param img $emoji
 *   Emoji character.
 *
 * @return string
 *   The error message.
 */
function _cce_basic_config_emoji_error($title, $emoji) {
  $message = t('The !title field has at least this !emoji forbidden emoji. Please check your content before saving.',
      array('!title' => $title, '!emoji' => $emoji));
  return $message;
}

/**
 * This evaluate if there is an emoji in the text and return it.
 *
 * @param string $string
 *   Text to evaluate.
 *
 * @return array
 *   It will return an array with emojis found otherwise an empty array.
 *
 * @see NEPT-1679
 * @see https://www.drupal.org/project/drupal/issues/2488180
 * @see https://www.drupal.org/node/2754539
 * To be removed in NEPT-1817
 */
function _cce_basic_config_get_emoji($string) {

  $regexes = array(
    // Match Dingbats.
    '/[\x{2700}-\x{27BF}]/u',
    // Match Emoticons.
    '/[\x{1F600}-\x{1F64F}]/u',
    // Match Miscellaneous Symbols.
    '/[\x{2600}-\x{26FF}]/u',
    // Match Transport And Map Symbols.
    '/[\x{1F680}-\x{1F6FF}]/u',
    // Match Miscellaneous Symbols and Pictographs.
    '/[\x{1F300}-\x{1F5FF}]/u',
  );

  foreach ($regexes as $regex) {
    preg_match($regex, $string, $matches);
    if (!empty($matches)) {
      return $matches;
    }
  }

  return array();
}

/**
 * Validate subject.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @see NEPT-1679
 * @see https://www.drupal.org/project/drupal/issues/2488180
 * @see https://www.drupal.org/node/2754539
 * To be removed in NEPT-1817
 */
function _cce_basic_config_subject_validate($form, &$form_state) {
  if (isset($form_state['values']['subject']) && !empty($form_state['values']['subject'])) {
    $title = isset($form_state['complete form']['subject']['#title']) ? $form_state['complete form']['subject']['#title'] : 'Title field';
    $emoji = _cce_basic_config_get_emoji($form_state['values']['subject']);
    if (!empty($emoji)) {
      $message = _cce_basic_config_emoji_error($title, $emoji[0]);
      form_set_error('title', $message);
    }
  }
}

/**
 * Validate title.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @see NEPT-1679
 * @see https://www.drupal.org/project/drupal/issues/2488180
 * @see https://www.drupal.org/node/2754539
 * To be removed in NEPT-1817
 */
function _cce_basic_config_title_validate($form, &$form_state) {
  if (isset($form_state['values']['title']) && !empty($form_state['values']['title'])) {
    $title = 'Title';
    $emoji = _cce_basic_config_get_emoji($form_state['values']['title']);
    if ($emoji) {
      $message = _cce_basic_config_emoji_error($title, $emoji[0]);
      form_set_error('title', $message);
    }
  }
}
