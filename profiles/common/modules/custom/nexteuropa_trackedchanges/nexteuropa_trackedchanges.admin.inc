<?php
/**
 * @file
 * Hooks for nexteuropa_trackedchanges admin interrfaces.
 */

/**
 * Multisite WYSIWYG settings form.
 */
function nexteuropa_trackedchanges_settings_form($form, &$form_state) {
  $profiles = _nexteuropa_trackedchanges_get_profiles();
  $info_table = _nexteuropa_trackedchanges_render_info_table($profiles['info']);

  $form['wysiwyg_profiles_info'] = array(
    '#title' => t('WYSIWYG profiles: change tracking status'),
    '#type' => 'item',
    '#markup' => $info_table,
    '#weight' => -10,
    '#description' => t('<strong>Warning</strong>: The disabling of the "change
      tracking" buttons in a profile will be blocked if any tracked changes 
      exist in any fields using this profile.'),
  );

  $form['nexteuropa_trackedchanges_disable_track_on_create'] = array(
    '#title' => t('Disable on create content pages.'),
    '#type' => 'checkbox',
    '#description' => t('Disable change tracking on create content pages.'),
    '#default_value' => variable_get('nexteuropa_trackedchanges_disable_track_on_create'),
  );
  $cke_lite_admin_link = l(t('CKEditor LITE'), 'admin/config/content/ckeditor_lite');
  $form['nexteuropa_trackedchanges_force_track_on_edit'] = array(
    '#title' => t('Enable tracking on edit content pages.'),
    '#type' => 'checkbox',
    '#description' => t("Force the change tracking by default on edit content pages. 
      It overrides the !link's configuration.", array('!link' => $cke_lite_admin_link)),
    '#default_value' => variable_get('nexteuropa_trackedchanges_force_track_on_edit'),
  );

  return system_settings_form($form);
}

/**
 * Menu callback enables CKEditor LITE button for a specific WYSIWYG profile.
 *
 * @param string $profile
 *   The machine name of the WYSIWYG profile.
 */
function _nexteuropa_trackedchanges_wysiwyg_tracking_settings_enable($profile) {
  _nexteuropa_trackedchanges_enable_buttons($profile);

  drupal_set_message(t('Change tracking enabled on !profile WYSIWYG profile.', ['!profile' => $profile]));

  drupal_goto('admin/config/content/wysiwyg/tracked_changes/setup');
}

/**
 * Menu callback disables CKEditor LITE button for a specific WYSIWYG profile.
 *
 * @param string $profile
 *   The machine name of the WYSIWYG profile.
 */
function _nexteuropa_trackedchanges_wysiwyg_tracking_settings_disable($profile) {
  $operations = array();
  // The 2nd argument is useless in this case because the default Batch API
  // process fulfils function requirements.
  $operations[] = array('_nexteuropa_trackedchanges_field_scanning_process', array($profile));

  $batch = array(
    'operations' => $operations,
    'finished' => '_nexteuropa_trackedchanges_remove_field_scanning_finished',
    'title' => t('Processing deactivation validation'),
    'init_message' => t('Deactivation check is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Deactivation check has encountered an error.'),
  );
  batch_set($batch);
  batch_process('admin/config/content/wysiwyg/tracked_changes/setup');
}

/**
 * Validate Callback forcing the enable value for the module to 1.
 *
 * It is designed to bypass the default disabling system related to the
 * system_modules form in to allow the check on the existence of tracked
 * changes in field values before disabling or not the module afterwards.
 *
 * @see nexteuropa_trackedchanges_form_system_modules_alter()
 * @see system_modules()
 * @see _nexteuropa_trackedchanges_system_disable_check_submit()
 */
function _nexteuropa_trackedchanges_system_disable_check_validate($form, &$form_state) {
  // Put a flag to indicate that the module is to disable and must be
  // controlled.
  $values = $form_state['values'];
  $proceed_validation = (!$values['modules']['NextEuropa']['nexteuropa_trackedchanges']['enable']);
  $form_state['nexteuropa_trackedchanges_disabling'] = $proceed_validation;

  // Reset the value flag for nexteuropa_trackedchanges to 1 in order to
  // be able to treat later in a batch process.
  $form_state['values']['modules']['NextEuropa']['nexteuropa_trackedchanges']
    = array('enable' => 1);
}

/**
 * Validate Callback forcing the enable value for the module to 1.
 *
 * It is designed to bypass the default disabling system related to the
 * system_modules form in to allow the check on the existence of tracked
 * changes in field values before disabling or not the module afterwards.
 *
 * @see nexteuropa_trackedchanges_form_feature_set_admin_form_alter()
 * @see feature_set_admin_form_submit()
 * @see _nexteuropa_trackedchanges_disable_check_submit()
 */
function _nexteuropa_trackedchanges_disable_check_validate($form, &$form_state) {
  // Put a flag to indicate that the module is to disable and must be
  // controlled.
  $values = $form_state['values'];
  $proceed_validation = (empty($values['featureset-nexteuropa_trackedchanges'])
    || (isset($values['featureset']) && ($values['featureset'] == 'nexteuropa_trackedchanges')));
  $form_state['values']['nexteuropa_trackedchanges_disabling'] = $proceed_validation;

  // Reset the value flag for nexteuropa_trackedchanges to 1 in order to
  // be able to treat later in a batch process.
  $form_state['values']['featureset-nexteuropa_trackedchanges'] = 1;
}

/**
 * Submit callback called on Modules form.
 *
 * It trigger a batch process that checks if no WYSIWYG field contains
 * any tracked changes.
 * If its the case, the disabling process must stop and come back to the
 * form (Module deactivation form).
 *
 * @see system_modules()
 */
function _nexteuropa_trackedchanges_system_disable_check_submit($form, &$form_state) {
  // Check for which module/feature is called.
  $values = $form_state['values'];
  if (!empty($values['nexteuropa_trackedchanges_disabling'])) {
    $finished_batch = '_nexteuropa_trackedchanges_system_disable_field_scanning_finished';
    _nexteuropa_trackedchanges_scanning_batch_set($finished_batch);
  }
}

/**
 * Submit callback called on Feature set forms.
 *
 * It trigger a batch process that checks if no WYSIWYG field contains
 * any tracked changes.
 * If its the case, the disabling process must stop and come back to the
 * form (Feature set forms).
 *
 * @see feature_set_disable_url()
 * @see feature_set_admin_form()
 */
function _nexteuropa_trackedchanges_disable_check_submit($form, &$form_state) {
  // Check for which module/feature is called.
  $values = $form_state['values'];

  if (!empty($values['nexteuropa_trackedchanges_disabling'])) {
    $finished_batch = '_nexteuropa_trackedchanges_disable_field_scanning_finished';
    _nexteuropa_trackedchanges_scanning_batch_set($finished_batch);
  }
}

/**
 * Set the batch process in charge of validating the module disabling.
 *
 * The batch will check the presence of tracked changes in all WYSIWYG fields
 * and block or not the module disabling.
 *
 * @param string $finished_batch
 *    The name of the "finished" callback that must be executed.
 *
 * @see _nexteuropa_trackedchanges_system_disable_field_scanning_finished()
 */
function _nexteuropa_trackedchanges_scanning_batch_set($finished_batch) {
  // Then, do the control.
  $operations = array(
    array('_nexteuropa_trackedchanges_field_scanning_process', array('')),
  );

  $batch = array(
    'operations' => $operations,
    'finished' => $finished_batch,
    'title' => t('Processing disabling validation'),
    'init_message' => t('Disabling check is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Disabling check has encountered an error.'),
  );
  batch_set($batch);

}

/**
 * Helper function renders array with information about profiles.
 *
 * @param array $info
 *    An array with WYSIWYG profile information.
 *
 * @return string
 *    Markup with rendered table.
 */
function _nexteuropa_trackedchanges_render_info_table($info) {
  // Setting up table header.
  $header = array(
    array('data' => t('Profile')),
    array('data' => t('Machine name')),
    array('data' => t('Status')),
    array('data' => t('Actions')),
  );
  // Setting up table rows.
  foreach ($info as $profile_name => $data_row) {
    $status = $data_row['cke_lite_status'];
    $action = l(t('enable tracked changes buttons'), 'admin/config/content/wysiwyg/tracked_changes/' . $profile_name . '/enable');
    if ($status) {
      $action = l(t('disable tracked changes buttons'), 'admin/config/content/wysiwyg/tracked_changes/' . $profile_name . '/disable');
      if ($profile_name == NEXTEUROPA_TRACKEDCHANGES_FHT_MACHINE_NAME) {
        $action = t('Enabled by default. Can not be disabled.');
      }
    }
    $row = array(
      $data_row['name'],
      $profile_name,
      $status ? t('Enabled') : t('Disabled'),
      $action,
    );
    $rows[] = $row;
  }
  // Rendering table.
  $rendered_table = theme('table',
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('class' => array('table', 'table-striped')),
      'caption' => '',
      'colgroups' => array(),
      'sticky' => FALSE,
      'empty' => FALSE,
    )
  );

  return $rendered_table;
}

/**
 * Form callback for the settings form.
 *
 * @see system_settings_form()
 */
function nexteuropa_trackedchanges_wysiwyg_tracking_settings_form($form, &$form_state) {

  $options = workbench_moderation_state_labels();

  $form['node_workflow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node tracking change workflow'),
    '#description' => t("Set when content with tracking change cannot be saved."),
  );

  $form['node_workflow']['nexteuropa_trackedchanges_tracking_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Block if status is true'),
    '#default_value' => variable_get('nexteuropa_trackedchanges_tracking_status'),
    '#description' => t('If checked, all content types cannot be saved if
       tracking changes feature is enabled; except content types which are
       using the workbench moderation flow with states selected in the field
       below.'),
  );

  $form['node_workflow']['nexteuropa_trackedchanges_tracking_wbm_states'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Block the saving for these Workbench Moderation states'),
    '#options' => $options,
    '#default_value' => variable_get('nexteuropa_trackedchanges_tracking_wbm_states', array()),
    '#description' => t('Choose states where content saving must be blocked if tracked changes exists.'),
  );

  $form['nexteuropa_trackedchanges_revuild_elapse_time'] = array(
    '#title' => t('Tracked changes table refresh frequence'),
    '#type' => 'textfield',
    '#field_suffix' => t('seconds'),
    '#size' => 3,
    '#description' => t('Set the elapse time between 2 refreshes of listing 
    entities having tracked changes. 0 second means the list will be refreshed
    each time the "!page" page is accessed.',
      array('!page' => l(t('Tracked changes overview'), 'admin/content/tracked_changes/entities_list'))),
    '#default_value' => variable_get('nexteuropa_trackedchanges_revuild_elapse_time'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Implements hook_form_validate().
 *
 * @see nexteuropa_trackedchanges_settings_form()
 */
function nexteuropa_trackedchanges_wysiwyg_tracking_settings_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  $elapse_time_value = $values['nexteuropa_trackedchanges_revuild_elapse_time'];
  if (!is_numeric($elapse_time_value) || ($elapse_time_value < 0)) {
    form_set_error('nexteuropa_trackedchanges_revuild_elapse_time',
      t('The "refresh frequency" field must be a positive number.'));
  }
}

/**
 * Function and callbacks designed for batches.
 *
 * They perform fields scanning detecting tracked changing in them.
 */

/**
 * Batch Operation Callback scanning field for tracked changes values.
 *
 * @param string $text_format
 *   The text_format on which the scanning process needs to focus.
 *   If set, the process scans only values using this text format.
 * @param array $context
 *   Batch context.
 */
function _nexteuropa_trackedchanges_field_scanning_process($text_format, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['results'] = array(
      'text_format' => $text_format,
      'detected_item' => array(),
    );
    $context['sandbox']['field_list'] = _nexteuropa_trackedchanges_wysiwyg_fields_info();
    $context['sandbox']['max'] = count($context['sandbox']['field_list']);
  }

  $field_name = array_shift($context['sandbox']['field_list']);
  $context['message'] = t('@field_name is scanned', array('@field_name' => $field_name));

  $scanning_results = _nexteuropa_trackedchanges_check_field_values($field_name, $text_format);

  if ($scanning_results) {
    $previous_detected_items = $context['results']['detected_item'];
    $results = array_merge($previous_detected_items, $scanning_results);
    $context['results']['detected_item'] = $results;
  }
  $context['sandbox']['progress']++;

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finished callback of the batch field for tracked changes values.
 *
 * It is ran in the case where change tracking buttons (CKEditore LITE) are
 * removed from a WYSIWYG process.
 *
 * @see _nexteuropa_trackedchanges_disable_buttons()
 */
function _nexteuropa_trackedchanges_remove_field_scanning_finished($success, $results, $operations) {
  if ($success) {
    $text_format = $results['text_format'];
    // Here we do something meaningful with the results.
    if ($results['detected_item']) {
      $message = t('The deactivation of the change tracking feature for the 
        @name profile stopped because tracked changes have been detected.',
        array('@name' => $text_format));
      $message .= '<br />';
      $message .= t('Please accept or reject them before proceeding to the deactivation.');

      drupal_set_message($message, 'error');
    }
    else {
      _nexteuropa_trackedchanges_disable_buttons($text_format);
      drupal_set_message(t('Change tracking disabled on !profile WYSIWYG profile.',
        array('!profile' => $text_format)));
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message_args = array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    );
    $message = t('An error occurred during the deactivation process on the 
      %error_operation with arguments: @arguments', $message_args);
    $message .= '<br />';
    $message .= t('The deactivation is impossible.');
    drupal_set_message($message, 'error');
  }
}

/**
 * Finished callback of the batch field for tracked changes values.
 *
 * It is run in the case where the feature set is disabled.
 *
 * @see _nexteuropa_trackedchanges_disable_check_submit()
 */
function _nexteuropa_trackedchanges_disable_field_scanning_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    if ($results['detected_item']) {
      $text_format = $results['text_format'];
      $message = t('The deactivation stopped because tracked changes have been 
        detected in contents.', array('@name' => $text_format));
      $message .= '<br />';
      $message .= t('Please accept or reject them before proceeding to the deactivation.');
      drupal_set_message($message, 'error');
    }
    else {
      $featureset = feature_set_get_featureset('nexteuropa_trackedchanges');
      feature_set_disable_feature_set($featureset);
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message_args = array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    );
    $message = t('An error occurred during the deactivation on the 
      %error_operation with arguments: @arguments', $message_args);
    $message .= '<br />';
    $message .= t('The deactivation is impossible.');
    drupal_set_message($message, 'error');
  }
}

/**
 * Finished callback of the batch field for tracked changes values.
 *
 * It is run in the case where the module is disabled.
 *
 * @see _nexteuropa_trackedchanges_system_disable_check_submit
 */
function _nexteuropa_trackedchanges_system_disable_field_scanning_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    if ($results['detected_item']) {
      $text_format = $results['text_format'];
      $message = t('The deactivation stopped because tracked changes have been 
        detected in contents.', array('@name' => $text_format));
      $message .= '<br />';
      $message .= t('Please accept or reject them before proceeding to the deactivation.');
      drupal_set_message($message, 'error');
    }
    else {
      module_disable(array('nexteuropa_trackedchanges'));
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message_args = array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    );
    $message = t('An error occurred during the deactivation on the 
      %error_operation with arguments: @arguments', $message_args);
    $message .= '<br />';
    $message .= t('The deactivation is impossible.');
    drupal_set_message($message, 'error');
  }
}
