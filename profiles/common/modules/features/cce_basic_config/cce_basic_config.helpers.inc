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
