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
    '#description' => t('Force the change tracking by default on edit content pages; 
      it overrides !link configuration.', array('!link' => $cke_lite_admin_link)),
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
  $lite_plugin_settings = array(
    'lite_AcceptAll',
    'lite_RejectAll',
    'lite_AcceptOne',
    'lite_RejectOne',
    'lite_ToggleShow',
    'lite_ToggleTracking',
  );
  multisite_config_service('wysiwyg')->addButtonsToProfile(
    $profile,
    'lite',
    $lite_plugin_settings
  );

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
  $disable = TRUE;
  // TODO Add check on existign tracked changes.
  $lite_plugin_settings = array(
    'lite_AcceptAll',
    'lite_RejectAll',
    'lite_AcceptOne',
    'lite_RejectOne',
    'lite_ToggleShow',
    'lite_ToggleTracking',
  );
  if ($disable) {
    multisite_config_service('wysiwyg')->removeButtonsFromProfile(
      $profile,
      'lite',
      $lite_plugin_settings
    );
    drupal_set_message(t('Change tracking disabled on !profile WYSIWYG profile.', ['!profile' => $profile]));
  }
  drupal_goto('admin/config/content/wysiwyg/tracked_changes/setup');
}

/**
 * Helper function for fetching WYSIWYG profiles.
 *
 * @return array
 *    An array with WYSIWYG profiles.
 */
function _nexteuropa_trackedchanges_get_profiles() {
  $wysiwyg_profiles = [];
  $formats = filter_formats();

  // Only list profiles that have a WYSIWYG editor associated with.
  $profiles = wysiwyg_profile_load_all();
  $profiles = array_filter($profiles, function ($profile) {
    return !empty($profile->editor);
  });

  // Generating array with options array and change tracking status.
  foreach ($profiles as $key => $profile) {
    $wysiwyg_profiles['options'][$key] = $formats[$key]->name;
    $wysiwyg_profiles['info'][$key]['name'] = $formats[$key]->name;
    if (isset($profile->settings['buttons']['lite']) && count($profile->settings['buttons']['lite'])) {
      $wysiwyg_profiles['info'][$key]['status'] = TRUE;
    }
    else {
      $wysiwyg_profiles['info'][$key]['status'] = FALSE;
    }
  }

  // Removing profile which by default needs to have change tracking enabled.
  if (isset($wysiwyg_profiles['options']['full_html_track'])) {
    unset($wysiwyg_profiles['options']['full_html_track']);
  }
  return $wysiwyg_profiles;
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
    $status = $data_row['status'];
    $action = l(t('enable tracked changes buttons'), 'admin/config/content/wysiwyg/tracked_changes/' . $profile_name . '/enable');
    if ($status) {
      $action = l(t('disable tracked changes buttons'), 'admin/config/content/wysiwyg/tracked_changes/' . $profile_name . '/disable');
      if ($profile_name == 'full_html_track') {
        $action = t('Enabled by default. Can not be disabled.');
      }
    }
    $row = array(
      $data_row['name'],
      $profile_name,
      $data_row['status'] ? t('Enabled') : t('Disabled'),
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
