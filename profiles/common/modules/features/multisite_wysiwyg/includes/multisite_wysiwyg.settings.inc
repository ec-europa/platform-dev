<?php
/**
 * @file
 * multisite_wysiwyg.settings.inc
 */

/**
 * Multisite WYSIWYG settings form.
 */
function multisite_wysiwyg_settings_form($form, &$form_state) {
  $settings = variable_get('multisite_wysiwyg', array());
  $profiles = _multisite_wysiwyg_get_profiles();
  $info_table = _multisite_wysiwyg_render_info_table($profiles['info']);

  $form['multisite_wysiwyg'] = [
    '#title' => t('Change tracking options'),
    '#type' => 'fieldset',
    '#tree' => TRUE,
  ];

  $form['multisite_wysiwyg']['info'] = [
    '#title' => t('WYSIWYG profiles: change tracking status'),
    '#type' => 'item',
    '#markup' => $info_table,
    '#weight' => -10,
  ];

  if (!isset($profiles['info']['full_html_track'])) {
    $form['multisite_wysiwyg']['create_full_html_track'] = [
      '#type' => 'submit',
      '#value' => t('Create Full HTML + Change tracking profile'),
      '#submit' => ['_multisite_wysiwyg_create_full_html_track_profile'],
    ];
  }

  $form['multisite_wysiwyg']['change_tracking'] = [
    '#title' => t('[Enable/Disable] change tracking for selected WYSIWYG profile'),
    '#type' => 'fieldset',
  ];

  $form['multisite_wysiwyg']['change_tracking']['action'] = [
    '#title' => "Select operation",
    '#type' => 'select',
    '#options' => [
      'enable' => t('Enable change tracking'),
      'disable' => t('Disable change tracking'),
    ],
    '#default_value' => [],
  ];

  $form['multisite_wysiwyg']['change_tracking']['profile'] = [
    '#title' => "Select profile",
    '#type' => 'select',
    '#options' => $profiles['options'],
    '#default_value' => [],
  ];

  $form['multisite_wysiwyg']['change_tracking']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => ['_multisite_wysiwyg_set_change_tracking'],
  ];

  $form['multisite_wysiwyg']['dis_change_track_on_create'] = [
    '#title' => t('Disable on create content pages.'),
    '#type' => 'checkbox',
    '#description' => 'Disable change tracking on create content pages.',
    '#default_value' => isset($settings['dis_change_track_on_create']) ? $settings['dis_change_track_on_create'] : '',
  ];

  $form['multisite_wysiwyg']['en_change_track_on_edit'] = [
    '#title' => t('Enable tracking on edit content pages.'),
    '#type' => 'checkbox',
    '#description' => 'Enable change tracking on edit content pages.',
    '#default_value' => isset($settings['en_change_track_on_edit']) ? $settings['en_change_track_on_edit'] : '',
  ];

  return system_settings_form($form);
}

/**
 * Custom form submit function. Enabling and disabling change tracking.
 */
function _multisite_wysiwyg_set_change_tracking($form, &$form_state) {
  $lite_plugin_settings = array(
    'lite_AcceptAll',
    'lite_RejectAll',
    'lite_AcceptOne',
    'lite_RejectOne',
    'lite_ToggleShow',
    'lite_ToggleTracking',
  );
  $action = $form_state['values']['multisite_wysiwyg']['change_tracking']['action'];
  $profile = $form_state['values']['multisite_wysiwyg']['change_tracking']['profile'];
  switch ($action) {
    case 'enable':
      multisite_config_service('wysiwyg')->addButtonsToProfile(
        $profile,
        'lite',
        $lite_plugin_settings
      );
      drupal_set_message(t('Change tracking enabled on !profile WYSIWYG profile.', ['!profile' => $profile]));
      break;

    case 'disable':
      multisite_config_service('wysiwyg')->removeButtonsFromProfile(
        $profile,
        'lite',
        $lite_plugin_settings
      );
      drupal_set_message(t('Change tracking disabled on !profile WYSIWYG profile.', ['!profile' => $profile]));
      break;
  }
}

/**
 * Helper function for fetching WYSIWYG profiles.
 *
 * @return array
 *    An array with WYSIWYG profiles.
 */
function _multisite_wysiwyg_get_profiles() {
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
function _multisite_wysiwyg_render_info_table($info) {
  // Setting up table header.
  $header = [
    ['data' => t('Profile')],
    ['data' => t('Machine name')],
    ['data' => t('Status')],
    ['data' => t('Notes')],

  ];
  // Setting up table rows.
  foreach ($info as $key => $data_row) {
    $row = [
      $data_row['name'],
      $key,
      $data_row['status'] ? t('Enabled') : t('Disabled'),
      ($key == 'full_html_track' ? t('Enabled by default. Can not be disabled.') : ''),
    ];
    $rows[] = $row;
  }
  // Rendering table.
  $rendered_table = theme('table',
    [
      'header' => $header,
      'rows' => $rows,
      'attributes' => ['class' => ['table', 'table-striped']],
      'caption' => '',
      'colgroups' => [],
      'sticky' => FALSE,
      'empty' => FALSE,
    ]
  );

  return $rendered_table;
}

/**
 * Helper funtion to create Full HTML + Change tracking WYSIWYG profile.
 */
function _multisite_wysiwyg_create_full_html_track_profile() {
  // Preparing filer format required further to build WYSIWYG profile.
  $fl_html_filters = multisite_config_service('filter')->getFormatFilters('full_html');

  // Transforming array of objects in to array by small trick.
  $fl_html_filters = json_decode(json_encode($fl_html_filters), TRUE);
  $full_html_track_format = (object) array(
    'format' => 'full_html_track',
    'name' => 'Full HTML + Change tracking',
    'cache' => '0',
    'status' => '1',
    'weight' => '-10',
    'filters' => $fl_html_filters,
  );
  // Filter module function for saving and updating text formats.
  filter_format_save($full_html_track_format);

  // Create WYSIWYG profile for Full HTML text format with change tracking.
  // Creation based on Full HTML profile to keep a consistent functionality.
  $wys_fl_html = multisite_config_service('wysiwyg')->getProfile('full_html');
  $wys_fl_html_settings = (array) $wys_fl_html->settings;
  multisite_config_service('wysiwyg')->createProfile(
    'full_html_track',
    'ckeditor',
    $wys_fl_html_settings
  );

  // Adding LITE plugin change tracking functionality to new profile.
  // Enable ckeditor_lite WYSIWYG plugin.
  $lite_plugin_settings = array(
    'lite_AcceptAll',
    'lite_RejectAll',
    'lite_AcceptOne',
    'lite_RejectOne',
    'lite_ToggleShow',
    'lite_ToggleTracking',
  );
  multisite_config_service('wysiwyg')->addButtonsToProfile(
    'full_html_track',
    'lite',
    $lite_plugin_settings
  );

  // Cloning roles to 'Full HTML + Change tracking' text format.
  $fl_html_roles = multisite_config_service('filter')->getFormatRoles('full_html');
  multisite_config_service('filter')->setFormatRoles('full_html_track', $fl_html_roles);
}
