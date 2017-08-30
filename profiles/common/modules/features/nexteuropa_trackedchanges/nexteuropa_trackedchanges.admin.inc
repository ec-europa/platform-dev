<?php
/**
 * @file
 * Hooks for nexteuropa_trackedchanges admin interfaces.
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
 * Helper function renders array with information about profiles.
 *
 * @param array $info
 *    An array with WYSIWYG profile information.
 *
 * @return [a-zA-Z]+
 *   [a-zA-Z]+ with rendered table.
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

  return system_settings_form($form);
}

/**
 * Menu callback enables CKEditor LITE button for a specific WYSIWYG profile.
 *
 * @param string $profile
 *   The machine name of the WYSIWYG profile.
 */
function _nexteuropa_trackedchanges_wysiwyg_tracking_settings_enable($profile) {
  nexteuropa_trackedchanges_enable_buttons($profile);

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
  variable_set('nexteuropa_trackedchanges_rebuild_lock', 1);

  // Then, do the control.
  $operations = array(
    array('_nexteuropa_trackedchanges_revisions_scanning_process', array($profile)),
    array('_nexteuropa_trackedchanges_entity_scanning_process', array($profile)),
    array('_nexteuropa_trackedchanges_table_rebuilt_process', array($profile)),
  );

  $batch = array(
    'operations' => $operations,
    'finished' => '_nexteuropa_trackedchanges_remove_field_scanning_finished',
    'title' => t('Processing disabling validation'),
    'init_message' => t('Disabling check is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Disabling check has encountered an error.'),
  );
  batch_set($batch);
  batch_process('admin/config/content/wysiwyg/tracked_changes/setup');
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

  // If we're not coming from the confirmation form, module activation parameter
  // are stored in "value][modules".
  if (empty($form_state['storage'])) {
    $proceed_validation = (!$values['modules']['NextEuropa']['nexteuropa_trackedchanges']['enable']);

    // Reset the value flag for nexteuropa_trackedchanges to 1 in order to
    // be able to treat later in a batch process.
    $form_state['values']['modules']['NextEuropa']['nexteuropa_trackedchanges']
      = array('enable' => 1);
  }
  else {
    // If we are coming from the confirmation form, fetch
    // the modules out of "storage][modules".
    $modules = $form_state['storage']['modules'];
    $proceed_validation = (!$modules['nexteuropa_trackedchanges']['enabled']);
    $form_state['storage']['modules']['nexteuropa_trackedchanges']['enabled'] = 1;
  }
  $form_state['values']['nexteuropa_trackedchanges_disabling'] = $proceed_validation;
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
 * Submit callback called on Feature set forms.
 *
 * It trigger a batch process that checks if no WYSIWYG field contains
 * any tracked changes.
 * If its the case, the disabling process must stop and come back to the
 * form (Feature set forms).
 *
 * @see features_admin_form()
 */
function _nexteuropa_trackedchanges_feature_disable_check_submit($form, &$form_state) {
  // Check for which module/feature is called.
  $values = $form_state['values'];

  if (!empty($values['nexteuropa_trackedchanges_disabling'])) {
    $finished_batch = '_nexteuropa_trackedchanges_feature_disable_field_scanning_finished';
    _nexteuropa_trackedchanges_scanning_batch_set($finished_batch);
  }
}

/**
 * Validate Callback forcing the enable value for the module to 1.
 *
 * It is designed to bypass the default disabling system related to the
 * features admin form in to allow the check on the existence of tracked
 * changes in field values before disabling or not the module afterwards.
 *
 * @see nexteuropa_trackedchanges_form_features_admin_form_alter()
 * @see features_admin_form_submit()
 * @see _nexteuropa_trackedchanges_feature_disable_check_submit()
 */
function _nexteuropa_trackedchanges_feature_disable_check_validate($form, &$form_state) {
  // Put a flag to indicate that the module is to disable and must be
  // controlled.
  $values = $form_state['values'];
  $proceed_validation = (empty($values['status']['nexteuropa_trackedchanges']));
  $form_state['values']['nexteuropa_trackedchanges_disabling'] = $proceed_validation;

  // Reset the value flag for nexteuropa_trackedchanges to 1 in order to
  // be able to treat later in a batch process.
  $form_state['values']['status']['nexteuropa_trackedchanges'] = 1;
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
  variable_set('nexteuropa_trackedchanges_rebuild_lock', 1);

  // Then, do the control.
  $operations = array(
    array('_nexteuropa_trackedchanges_revisions_scanning_process', array('')),
    array('_nexteuropa_trackedchanges_entity_scanning_process', array('')),
    array('_nexteuropa_trackedchanges_table_rebuilt_process', array('')),
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

/*
 * Finished callbacks designed for batches.
 *
 * They perform fields scanning detecting tracked changing in them.
 */

/**
 * Finished callback of the batch field for tracked changes values.
 *
 * It is ran in the case where change tracking buttons (CKEditore LITE) are
 * removed from a WYSIWYG process.
 *
 * @see nexteuropa_trackedchanges_disable_buttons()
 */
function _nexteuropa_trackedchanges_remove_field_scanning_finished($success, $results, $operations) {
  $message_level = 'error';
  if ($success) {
    $text_format = $results['text_format'];

    // Here we do something meaningful with the results.
    if (!empty($results['detected_entities'])) {
      $message = t('The deactivation of the change tracking feature for the 
        @name profile stopped because tracked changes have been detected.',
        array('@name' => $text_format));
      $message .= '<br />';
      $message .= t('Please accept or reject them before proceeding to the deactivation; 
      the list of entities with tracked changes is available !here.',
        array('!here' => l(t('here'), 'admin/content/tracked_changes')));
    }
    else {
      nexteuropa_trackedchanges_disable_buttons($text_format);
      $message = t('Change tracking disabled on !profile WYSIWYG profile.',
        array('!profile' => $text_format));
      $message_level = 'status';
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
  }

  if ($message) {
    drupal_set_message($message, $message_level);
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
  $message = FALSE;
  if ($success) {
    // Here we do something meaningful with the results.
    if (!empty($results['detected_entities'])) {
      $message = t('The deactivation stopped because tracked changes have been 
        detected in contents.');
      $message .= '<br />';
      $message .= t('Please accept or reject them before proceeding to the deactivation; 
      the list of entities with tracked changes is available !here.',
        array('!here' => l(t('here'), 'admin/content/tracked_changes')));
    }
    else {
      $featureset = feature_set_get_featureset('nexteuropa_trackedchanges');
      feature_set_disable_feature_set($featureset);
      // Required to flush thecache to ensure that all references to the
      // module have disappeared.
      // @see system_modules_submit()
      drupal_flush_all_caches();
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
  }

  if ($message) {
    drupal_set_message($message, 'error');
  }
}


/**
 * Finished callback of the batch field for tracked changes values.
 *
 * It is run in the case where the feature is disabled.
 *
 * @see _nexteuropa_trackedchanges_feature_disable_check_submit()
 */
function _nexteuropa_trackedchanges_feature_disable_field_scanning_finished($success, $results, $operations) {
  $message = FALSE;
  if ($success) {
    // Here we do something meaningful with the results.
    if (!empty($results['detected_entities'])) {
      $message = t('The deactivation stopped because tracked changes have been 
        detected in contents.');
      $message .= '<br />';
      $message .= t('Please accept or reject them before proceeding to the deactivation; 
      the list of entities with tracked changes is available !here.',
        array('!here' => l(t('here'), 'admin/content/tracked_changes')));
    }
    else {
      module_disable(array('nexteuropa_trackedchanges'));
      // Required to flush thecache to ensure that all references to the
      // module have disappeared.
      // @see system_modules_submit()
      drupal_flush_all_caches();
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
  }

  if ($message) {
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
  $message = FALSE;
  if ($success) {
    // Here we do something meaningful with the results.
    if ($results['detected_entities']) {
      $message = t('The deactivation stopped because tracked changes have been 
        detected in contents.');
      $message .= '<br />';
      $message .= t('Please accept or reject them before proceeding to the deactivation; 
      the list of entities with tracked changes is available !here.',
        array('!here' => l(t('here'), 'admin/content/tracked_changes')));
    }
    else {
      module_disable(array('nexteuropa_trackedchanges'));
      // Required to flush thecache to ensure that all references to the
      // module have disappeared.
      // @see system_modules_submit()
      drupal_flush_all_caches();
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
  }

  if ($message) {
    drupal_set_message($message, 'error');
  }
}

/**
 * Page Callback of the List of entities containing tracked changes.
 *
 * @return string
 *   Page display.
 */
function nexteuropa_trackedchanges_rebuild_status($form, &$form_state) {
  $last_rebuilt = variable_get('nexteuropa_trackedchanges_last_rebuild_time');
  $is_lock = variable_get('nexteuropa_trackedchanges_rebuild_lock');
  $output = '<p>' . t('The logs table has never been rebuilt.') . '</p>';
  if ($last_rebuilt) {
    $date = format_date($last_rebuilt, 'custom', 'd/m/y H:i:s');
    $output = '<p>' . t('The tracked changes scanning has been executed on the @date.', array('@date' => $date)) . '</p>';
  }

  $form['nexteuropa_trackedchanges_rebuild_elapse_time'] = array(
    '#title' => t('Tracked changes table refresh frequency'),
    '#type' => 'textfield',
    '#field_suffix' => t('seconds'),
    '#size' => 3,
    '#description' => t('Set the elapse time between 2 refreshes of listing 
    entities having tracked changes. 0 second means the list will be refreshed
    each time the drupal cron is executed.'),
    '#default_value' => variable_get('nexteuropa_trackedchanges_rebuild_elapse_time'),
    '#required' => TRUE,
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array('nnexteuropa_trackedchanges_rebuild_elapse_time_submit'),
    '#validate' => array('nexteuropa_trackedchanges_rebuild_elapse_time_validate'),
  );

  $form['table_status'] = array(
    '#markup' => $output,
  );
  if (!$is_lock) {
    $form['force_rebuild'] = array(
      '#type' => 'submit',
      '#value' => t('Force scanning'),
      '#submit' => array('nexteuropa_trackedchanges_table_rebuilt_submit'),
      '#description' => t('Force the system to scan entities immediately. This process can take times.'),
    );
  }
  else {
    $form['table_status'] = array(
      '#markup' => t('The rebuild of the logs table is under way.'),
    );
  }

  return $form;
}

/**
 * Form submit callback.
 *
 * @see nexteuropa_trackedchanges_rebuild_status()
 */
function nnexteuropa_trackedchanges_rebuild_elapse_time_submit($form, &$form_state) {
  $values = $form_state['values'];
  $elapse_time_value = (!empty($values['nexteuropa_trackedchanges_rebuild_elapse_time'])) ? $values['nexteuropa_trackedchanges_rebuild_elapse_time'] : 0;

  variable_set('nexteuropa_trackedchanges_rebuild_elapse_time', $elapse_time_value);
}

/**
 * Form validate callback.
 *
 * @see nexteuropa_trackedchanges_rebuild_status()
 */
function nexteuropa_trackedchanges_rebuild_elapse_time_validate($form, &$form_state) {
  $values = $form_state['values'];
  $elapse_time_value = $values['nexteuropa_trackedchanges_rebuild_elapse_time'];
  if (!is_numeric($elapse_time_value) || ($elapse_time_value < 0)) {
    form_set_error('nexteuropa_trackedchanges_rebuild_elapse_time',
      t('The "refresh frequency" field must be a positive number.'));
  }
}

/**
 * Submit form call back triggering the netc_info table.
 *
 * @see nexteuropa_trackedchanges_rebuild_status()
 */
function nexteuropa_trackedchanges_table_rebuilt_submit($form, &$form_state) {
  // Empty the table and "lock" it.
  variable_set('nexteuropa_trackedchanges_rebuild_lock', 1);

  // It is a rebuild, then we flush the tables.
  _nexteuropa_trackedchanges_clean_db();

  $operations = array();
  // The 2nd argument is useless in this case because the default Batch API
  // process fulfils function requirements.
  $operations[] = array('_nexteuropa_trackedchanges_revisions_scanning_process', array(''));
  $operations[] = array('_nexteuropa_trackedchanges_entity_scanning_process', array(''));
  $operations[] = array('_nexteuropa_trackedchanges_table_rebuilt_process', array(''));

  $batch = array(
    'operations' => $operations,
    'finished' => '_nexteuropa_trackedchanges_table_rebuilt_finished',
    'title' => t('Processing the rebuild of the tracked change table'),
    'init_message' => t('Content scanning is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('The rebuild has encountered an error.'),
  );
  batch_set($batch);
}

/**
 * Finished callback of the batch rebuilding the "Info" table.
 *
 * The "Info" table is "nexteuropa_trackedchanges_info".
 *
 * @see nexteuropa_trackedchanges_table_rebuilt()
 */
function _nexteuropa_trackedchanges_table_rebuilt_finished($success, $results, $operations) {
  // Unlock the table to allow a new rebuild if it failed.
  variable_set('nexteuropa_trackedchanges_rebuild_lock', 0);
  variable_set('nexteuropa_trackedchanges_last_rebuild_time', REQUEST_TIME);

  $message = t('The tracked changes table is rebuilt.');
  $message_level = 'status';
  if (!$success) {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message_args = array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    );
    $message = t('An error occurred during the rebuild process on the 
      %error_operation with arguments: @arguments', $message_args);
    $message_level = 'error';
  }

  drupal_set_message($message, $message_level);
}

/**
 * Callback displaying the Content tracked changes page.
 *
 * @see nexteuropa_trackedchanges_views_default_views()
 */
function nexteuropa_trackedchanges_workbench() {
  $last_time = variable_get('nexteuropa_trackedchanges_last_rebuild_time');
  // If the variable is empty, that means the table has never been filed.
  // Then we redirect the user to the Btach process to ensure that the system
  // does not miss data.
  if (is_null($last_time)) {
    drupal_goto('admin/config/content/wysiwyg/tracked_changes/table_status/init');
  }

  return views_embed_view('content_tracked_changes', 'default');
}

/**
 * Menu callback triggering the netc_info table rebuild.
 */
function nexteuropa_trackedchanges_table_init() {
  // Empty the table and "lock" it.
  variable_set('nexteuropa_trackedchanges_rebuild_lock', 1);

  // It is a rebuild, then we flush the tables.
  _nexteuropa_trackedchanges_clean_db();

  $operations = array();
  // The 2nd argument is useless in this case because the default Batch API
  // process fulfils function requirements.
  $operations[] = array('_nexteuropa_trackedchanges_revisions_scanning_process', array(''));
  $operations[] = array('_nexteuropa_trackedchanges_entity_scanning_process', array(''));
  $operations[] = array('_nexteuropa_trackedchanges_table_rebuilt_process', array(''));

  $batch = array(
    'operations' => $operations,
    'finished' => '_nexteuropa_trackedchanges_table_rebuilt_finished',
    'title' => t('Processing the initialisation of the tracked change table'),
    'init_message' => t('Content scanning is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('The initialisation has encountered an error.'),
  );
  batch_set($batch);
  batch_process('admin/content/tracked_changes');
}
