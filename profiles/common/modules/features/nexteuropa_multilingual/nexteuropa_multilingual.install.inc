<?php
/**
 * @file
 * Code for the Nexteuropa Multilingual module.
 */

/**
 * Helper function to make all file types translatable.
 */
function _nexteuropa_multilingual_make_files_translatable() {

  // Add files as translatable entities.
  $translatable_entities = variable_get('entity_translation_entity_types', array('node' => 'node'));
  if (in_array('file', $translatable_entities)) {
    // Files are already translatable, skip changes.
    return;
  }

  // Make File entity translatable.
  $translatable_entities['file'] = 'file';
  variable_set('entity_translation_entity_types', $translatable_entities);

  // Add entity_translation configuration for the default file entities.
  $default_file_types = array(
    'audio',
    'document',
    'image',
    'video',
  );
  foreach ($default_file_types as $default_file_type) {
    $file_type_configuration = variable_get('entity_translation_settings_file__' . $default_file_type, array());
    $file_type_configuration['hide_language_selector'] = 0;
    $file_type_configuration['default_language'] = LANGUAGE_NONE;
    variable_set('entity_translation_settings_file__' . $default_file_type, $file_type_configuration);
    if (title_field_replacement_toggle('file', $default_file_type, 'filename')) {
      title_field_replacement_batch_set('file', $default_file_type, 'filename');
    }
  }

  // Make default image title and alt fields translatable.
  $image_fields = array(
    'field_file_image_alt_text',
    'field_file_image_title_text',
    'field_caption',
    'field_video_description',
  );
  foreach ($image_fields as $image_field_name) {
    $image_field = field_info_field($image_field_name);
    if (isset($image_field['translatable'])) {
      $image_field['translatable'] = TRUE;
      field_update_field($image_field);
    }
  }
}
