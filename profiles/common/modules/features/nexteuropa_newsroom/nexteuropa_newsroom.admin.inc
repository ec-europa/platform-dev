<?php
/**
 * @file
 * Nexteuropa Newsroom administration page.
 */

include_once 'nexteuropa_newsroom.multilingual.inc';
include_once drupal_get_path('module', 'pathauto') . '/pathauto.inc';

/**
 * Nexteuropa newsroom admin form.
 */
function nexteuropa_newsroom_admin_settings($form, &$form_state) {
  // Be aware about the selected content types in the fields fieldset.
  $sel_ct = _nexteuropa_newsroom_get_instances('select');
  $top_ct = _nexteuropa_newsroom_get_instances('topic');
  // Get some information basing on the activation of the universe id.
  $universe_id = _nexteuropa_newsroom_check_universe_id();

  // Check the value for multilingualism.
  $multilingual = variable_get('newsroom_multilingual', FALSE);

  // This is special, made just to hold the universe_id field.
  $form['universe_id'] = array(
    '#type' => 'container',
    '#title' => t('Newsroom Universe ID'),
    '#attributes' => array('class' => array($universe_id['class'])),
  );

  // After initital setup disable Universe ID field.
  if (variable_get('newsroom_universe_id', NULL) !== NULL) {
    $universe_id_disabled = TRUE;
    $universe_id_description = t('To change the Newsroom Universe ID contact the site administrator.');
  }
  else {
    $universe_id_disabled = FALSE;
    $universe_id_description = t('After setting the Newsroom Universe ID for the first time content will be imported from the Newsroom service. This might take a few minutes.');
  }

  $form['universe_id']['newsroom_universe_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Universe ID value'),
    '#required' => TRUE,
    '#disabled' => $universe_id['disabled'],
    '#description' => $universe_id['description'],
    '#default_value' => variable_get('newsroom_universe_id', NULL),
    '#element_validate' => array('nexteuropa_newsroom_universe_id_validate'),
  );

  // Other settings for the newsroom.
  $form['newsroom_others'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom client settings'),
    '#description' => t("These settings will determine newsroom behavior in your website.
      In particular you can choose here whether to import multilingual content from the newsroom or not.
      Mind the fact that we rely on the enabled languages in your website, so you will not be able to import items in a language that doesn't exist yet."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#access' => user_access('administer newsroom advanced settings'),
  );

  $form['newsroom_others']['multilingual'] = array(
    '#type' => 'checkbox',
    '#title' => t('Is your universe multilingual?'),
    '#default_value' => $multilingual,
  );

  if ($multilingual) {
    $form['newsroom_others']['rebuild'] = array(
      '#type' => 'submit',
      '#value' => 'Rebuild importers on the fly',
      '#prefix' => '<div id="newsroom_rebuild">',
      '#suffix' => '<div class="description">' . t("Rebuild the importers if you enabled or disabled languages or if you are noticing unexpected behaviors like fields not imported.") . '</div></div>',
      '#ajax' => array(
        'callback' => '_nexteuropa_newsroom_rebuild_importers',
        'event' => 'click',
        'wrapper' => 'newsroom_rebuild',
        'effect' => 'fade',
        'method' => 'replace',
      ),
    );
  }

  $form['newsroom_others']['newsroom_block_by'] = array(
    '#type' => 'select',
    '#title' => t('List items in the summary blocks by'),
    '#options' => array(
      'type' => 'Item type',
      'collection' => 'Collection',
    ),
    '#default_value' => variable_get('newsroom_block_by', 'type'),
  );

  $form['newsroom_others']['newsroom_order_by_last_update'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort newsroom boxes chronologically in the summary blocks'),
    '#default_value' => variable_get('newsroom_order_by_last_update', 0),
  );

  $form['newsroom_others']['newsroom_display_highlights_begin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Highlighted topics are displayed at the begining of the list.'),
    '#default_value' => variable_get('newsroom_display_highlights_begin', 1),
  );

  $form['newsroom_others']['newsroom_display_agenda'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate agenda functionality'),
    '#default_value' => variable_get('newsroom_display_agenda', 1),
  );

  $form['newsroom_others']['newsroom_agenda_after_highlights'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Agenda after the highlights'),
    '#default_value' => variable_get('newsroom_agenda_after_highlights', 1),
  );

  $form['newsroom_others']['newsroom_url_mode'] = array(
    '#type' => 'select',
    '#title' => t('Newsroom URL pattern based on'),
    '#options' => array(
      'name' => 'Term Name',
      'tid' => 'Term ID',
    ),
    '#default_value' => variable_get('newsroom_url_mode', 'name'),
  );

  $form['newsroom_others']['newsroom_proposal_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsroom proposal URL'),
    '#default_value' => variable_get('newsroom_proposal_url', NULL),
  );

  $vocabulary = taxonomy_vocabulary_machine_name_load('newsroom_item_type');
  $types = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));

  if (!empty($types)) {
    $form['newsroom_paths'] = array(
      '#type' => 'fieldset',
      '#title' => t('Newsroom content path settings'),
      '#prefix' => '<div id="newsroom_reset">',
      '#suffix' => '</div>',
      '#description' => t("You can define here a root path for your items basing on the item type. The default behavior is to have sections correponding to the types, so if you have two types like
            news and events you will get pattern like news/[node:title], events/[node:title], you can override the root path for your elements here. Do not use leading por trailing slashes"),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#access' => user_access('administer newsroom settings'),
    );

    $form['newsroom_paths']['patterns'] = array(
      '#type' => 'checkbox',
      '#title' => t('Do you want to take over the configuration of pattern for node aliases?'),
      '#description' => t('if this is unchecked the newsroom will not alter the aliases for its nodes.'),
      '#default_value' => variable_get('newsroom_patterns', FALSE),
    );

    foreach ($types as $tid => $type) {
      $type_name = pathauto_cleanstring(drupal_strtolower($type->name));
      $parents = taxonomy_get_parents($type->tid);
      $parent = '';

      if (!empty($parents)) {
        $parent = reset($parents);
        $parent = pathauto_cleanstring(drupal_strtolower($parent->name)) . '/';
      }

      $form['newsroom_paths'][$type_name . '_rootpath'] = array(
        '#type' => 'textfield',
        '#title' => t('Pattern for %type', array('%type' => $type_name)),
        '#required' => FALSE,
        '#description' => t('aliases pattern for the %type_name topic', array('%type_name' => $type_name)),
        '#default_value' => variable_get('newsroom_' . $type_name . '_root', $parent . $type_name),
        '#element_validate' => array('nexteuropa_newsroom_type_root_validate'),
      );
    }

    $form['newsroom_paths']['reset'] = array(
      '#type' => 'submit',
      '#value' => 'Reset to the defaults',
      '#ajax' => array(
        'callback' => '_nexteuropa_newsroom_reset_paths',
        'event' => 'click',
        'wrapper' => 'newsroom_reset',
        'effect' => 'fade',
        'method' => 'replace',
      ),
    );
  }
  // Settings about the newsroom fields.
  $form['newsroom_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom fields settings'),
    '#description' => t('Here you can easily manage the addition or the removal of the newsroom fields from your content types. Refer to the documentation for having detailed information about the usage of the newsroom fields.  They are meant to give you the chance to associate topics to you contents so that matching news coming from the newsroom can be shown or mentioned contextually.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#access' => user_access('administer newsroom advanced settings'),
  );

  $form['newsroom_fields']['newsroom_content_types_topic'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Newsroom content types topic'),
    '#description' => t('Choose the content types in which you want to activate a relationship with a newsroom topic.'),
    '#options' => _nexteuropa_newsroom_prepare_options('ct'),
    '#multiple' => TRUE,
    '#default_value' => $top_ct,
  );

  $form['newsroom_fields']['newsroom_content_types_delete_topic'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete all the existing instances in this content type'),
    '#description' => t('If you want to delete all the instance of the topic field together check this.'),
    '#default_value' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['newsroom_fields']['newsroom_content_types_select'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Newsroom content types select'),
    '#description' => t('Choose the content types in which you want to activate a complex relationship with the newsroom items.'),
    '#options' => _nexteuropa_newsroom_prepare_options('ct'),
    '#multiple' => TRUE,
    '#default_value' => $sel_ct,
  );

  $form['newsroom_fields']['newsroom_content_types_delete_select'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete all the existing instances in this content type'),
    '#description' => t('If you want to delete all the instance of the select field together check this.'),
    '#default_value' => 0,
  );

  // Settings about the universe.
  $form['newsroom_universe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom universe settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $universe_id['collapsing'],
  );

  $form['newsroom_universe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom universe settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['newsroom_universe']['newsroom_url_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('URL prefix'),
    '#default_value' => variable_get('newsroom_url_prefix', ''),
    '#description' => t('The prefix which comes after https://ec.europa.eu/ and before the drupal path.'),
  );

  $form['newsroom_universe']['newsroom_allowed_ips'] = array(
    '#type' => 'textfield',
    '#title' => t('IP addresses allowed for import'),
    '#default_value' => variable_get('newsroom_allowed_ips', '127.0.0.1'),
    '#description' => t('Comma separated list of IP addresses where the importer can be launched from.'),
  );

  $form['newsroom_universe']['newsroom_single_item_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single item import'),
    '#default_value' => variable_get('newsroom_single_item_import_segment', 'fullrss-multilingual.cfm?item_id='),
  );

  $form['newsroom_universe']['newsroom_single_topic_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single topic import'),
    '#default_value' => variable_get('newsroom_single_topic_import_segment', 'rss-service-multilingual.cfm?topic_id='),
  );

  $form['newsroom_universe']['newsroom_single_type_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single type import'),
    '#default_value' => variable_get('newsroom_single_type_import_segment', 'rss-item-type-multilingual.cfm?item_type_id='),
  );

  $form['newsroom_universe']['newsroom_single_service_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single service import'),
    '#default_value' => variable_get('newsroom_single_service_import_segment', 'rss-service-multilingual.cfm?service_id='),
  );

  $form['newsroom_universe']['newsroom_single_item_edit_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk to edit an item in the Newsroom'),
    '#default_value' => variable_get('newsroom_single_item_edit_segment', 'item.cfm?item_id='),
  );

  // Settings about the newsroom blocks.
  $form['newsroom_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom blocks settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['newsroom_blocks']['newsroom_summary_block_columns'] = array(
    '#type' => 'select',
    '#title' => t('Number of columns to use on the summary blocks'),
    '#options' => _nexteuropa_newsroom_prepare_options(2),
    '#default_value' => variable_get('newsroom_summary_block_columns', 1),
  );

  $form['newsroom_blocks']['newsroom_summary_block_num_items'] = array(
    '#type' => 'select',
    '#title' => t('Number of items in boxes in the summary blocks'),
    '#options' => _nexteuropa_newsroom_prepare_options(5),
    '#default_value' => variable_get('newsroom_summary_block_num_items', 3),
  );

  $form['newsroom_blocks']['newsroom_summary_block_num_highlighted_items'] = array(
    '#type' => 'select',
    '#title' => t('Number of items in boxes of highlighted types in the summary blocks'),
    '#options' => _nexteuropa_newsroom_prepare_options(6),
    '#default_value' => variable_get('newsroom_summary_block_num_highlighted_items', 3),
  );

  $form['newsroom_blocks']['home_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom home blocks settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // Settings about newsroom blocks in the home page.
  $form['newsroom_blocks']['home_blocks']['newsroom_summary_home_block_num_items'] = array(
    '#type' => 'select',
    '#title' => t('Number of items in boxes in the summary block on the homepage'),
    '#options' => _nexteuropa_newsroom_prepare_options(5),
    '#default_value' => variable_get('newsroom_summary_home_block_num_items', 3),
  );

  $form['newsroom_blocks']['home_blocks']['newsroom_summary_home_block_num_highlighted_items'] = array(
    '#type' => 'select',
    '#title' => t('Number of items in boxes of highlighted types in the summary block on the homepage'),
    '#options' => _nexteuropa_newsroom_prepare_options(6),
    '#default_value' => variable_get('newsroom_summary_home_block_num_highlighted_items', 3),
  );

  $form['newsroom_blocks']['home_blocks']['newsroom_summary_home_block_num_agenda'] = array(
    '#type' => 'select',
    '#title' => t('Number of days to list in the Agenda block on the homepage'),
    '#options' => _nexteuropa_newsroom_prepare_options(6),
    '#default_value' => variable_get('newsroom_summary_home_block_num_agenda', 3),
  );

  // Attach a css to the admin settings form.
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'nexteuropa_newsroom') . '/nexteuropa_newsroom_admin_setting.css',
  );
  // Validate function.
  $form['#validate'][] = 'nexteuropa_newsroom_admin_settings_form_validate';
  // Submit handler.
  $form['#submit'][] = 'nexteuropa_newsroom_admin_settings_form_submit';

  if (variable_get('newsroom_universe_id') != NULL) {
    $form['actions']['run'] = array(
      '#type' => 'submit',
      '#value' => t('Run the importers'),
      '#access' => TRUE,
      '#submit' => array('nexteuropa_newsroom_admin_settings_form_run_importers'),
      '#weight' => 10,
    );
  }

  // Define the fields_form array().
  $form_state['fields_form'] = array();
  $form_state['fields_form']['topic'] = $top_ct;
  $form_state['fields_form']['select'] = $sel_ct;

  // Confirmation step_needed.
  if (isset($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    return _nexteuropa_newsroom_delete_confirm($form, $form_state);
  }
  // Normal form.
  else {
    return system_settings_form($form);
  }
}

/**
 * Validation step for the the newsroom admin form.
 */
function nexteuropa_newsroom_admin_settings_form_validate($form, &$form_state) {
  // If we are not during a confirm or this has happened right before.
  if (!isset($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    $check_values = _nexteuropa_newsroom_prepare_check($form_state['fields_form'], $form_state['input']);

    // Check every topic instance if requested.
    if ($check_values['delete']['topic'] == 1) {
      $test = _nexteuropa_newsroom_check_deletion('topic', 'all');
    }
    // If there are less values than before, check instances.
    else {
      if (!empty($check_values['check']['topic'][0])) {
        $test = _nexteuropa_newsroom_check_deletion('topic', $check_values['check']['topic'][0]);
      }
    }

    // Check every select instance if requested.
    if ($check_values['delete']['select'] == 1) {
      $test = _nexteuropa_newsroom_check_deletion('select', 'all');
    }
    // If there are less values than before, check instances.
    else {
      if (!empty($check_values['check']['select'][0])) {
        $test = _nexteuropa_newsroom_check_deletion('select', $check_values['check']['select'][0]);
      }
    }
    if (!empty($test)) {
      $form_state['storage']['confirm'] = TRUE;
      $form_state['confirm']['values'] = $test;
    }
  }
}

/**
 * Submit handler for the newsroom admin form.
 */
function nexteuropa_newsroom_admin_settings_form_submit($form, &$form_state) {
  dsm($form_state['values']);
  $multilingual = $form_state['values']['multilingual'] == 1 ? TRUE : FALSE;
  $patterns = isset($form_state['values']['patterns']) && $form_state['values']['patterns'] == 1 ? TRUE : FALSE;
  $keys = array_keys($form_state['values']);
  $rootpaths = preg_grep('/rootpath/', $keys);
  // Shouldn't be needed, it is a setting form.
  if (!empty($rootpaths)) {
    foreach ($rootpaths as $type) {
      $typename = str_replace('_rootpath', '', $type);
      variable_set('newsroom_' . $typename . '_root', $form_state['values'][$type]);
    }
  }

  $patterns ? variable_set('newsroom_patterns', 1) : variable_set('newsroom_patterns', 0);

  $multilingual ? variable_set('newsroom_multilingual', 1) : variable_set('newsroom_multilingual', 0);

  // Create default importers if new Newsroom Universe ID detected.
  if ($form_state['values']['newsroom_universe_id'] <> $form['universe_id']['newsroom_universe_id']['#default_value']) {
    variable_set('newsroom_universe_id', $form_state['values']['newsroom_universe_id']);

    _newsroom_create_default_importers(NEWSROOM_URL . $form_state['values']['newsroom_universe_id'], 'admin', url('admin/config/content/newsroom'), $multilingual);
  }

  // Disabled importers.
  $disabled = variable_get('default_feeds_importer', array());

  // Activate multilingualism for the newsroom if the checkbox is checked.
  if ($form_state['values']['multilingual'] != $form['newsroom_others']['multilingual']['#default_value']) {

    $importer_id['items'] = $multilingual ? 'newsroom_items' : 'newsroom_items_multilingual';
    $importer_id['topics'] = $multilingual ? 'newsroom_topics' : 'newsroom_topics_multilingual';
    $importer_id['services'] = $multilingual ? 'newsroom_services' : 'newsroom_services_multilingual';
    $importer_id['types'] = $multilingual ? 'newsroom_type' : 'newsroom_types_multilingual';

    foreach ($importer_id as $key => $importer) {
      $disabling[] = $importer;
    }

    // Toggle the default importers.
    _nexteuropa_newsroom_disable_importer($disabled, $disabling, TRUE);
  }

  // If the validation returns the confirm request.
  if (isset($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    $form_state['rebuild'] = TRUE;
  }
  else {
    $check_values = _nexteuropa_newsroom_prepare_check($form_state['fields_form'], $form_state['values']);

    // Remove every topic instance if requested.
    if ($check_values['delete']['topic'] == 1) {
      _nexteuropa_newsroom_remove_fields('topic', 'all');
    }
    else {
      if (!empty($check_values['selected']['topic']) && !empty($check_values['check']['topic'][1])) {
        // Add new instances.
        _nexteuropa_newsroom_add_fields('topic', $check_values['check']['topic'][1]);
      }

      elseif (!empty($check_values['check']['topic'][0])) {
        // Remove instances.
        _nexteuropa_newsroom_remove_fields('topic', $check_values['check']['topic'][0]);
      }
    }

    // Remove every select instance if requested.
    if ($check_values['delete']['select'] == 1) {
      _nexteuropa_newsroom_remove_fields('select', 'all');
    }
    else {
      if (!empty($check_values['selected']['select']) && !empty($check_values['check']['select'][1])) {
        // Add new instances.
        _nexteuropa_newsroom_add_fields('select', $check_values['check']['select'][1]);
      }

      elseif (!empty($check_values['check']['select'][0])) {
        // Remove instances.
        _nexteuropa_newsroom_remove_fields('select', $check_values['check']['select'][0]);
      }
    }

    cache_clear_all('newsroom:', 'cache', TRUE);
  }
}

/**
 * Run the importers.
 */
function nexteuropa_newsroom_admin_settings_form_run_importers() {
  $multilingual = variable_get('newsroom_multilingual') == 1 ? TRUE : FALSE;
  _newsroom_create_default_importers(NEWSROOM_URL . variable_get('newsroom_universe_id'), 'admin', url('admin/config/content/newsroom'), $multilingual);
}

/**
 * Add a confirmation step if needed.
 */
function _nexteuropa_newsroom_delete_confirm($form, &$form_state) {
  $form_state['confirm']['processed'] = TRUE;
  $values = $form_state['confirm']['values'];
  $desc = '<div class="messages error"><h3>' . t('Part of the form has not been submitted yet. You have:') . '</h3></br><i>';
  foreach ($values as $field => $nodes) {
    for ($i = 0; $i < count($values[$field]); $i++) {
      $desc .= t('@num nodes containing values for the field @field in the content type @ct',
        array(
          '@num' => $values[$field][$i]['nodes'],
          '@field' => $field,
          '@ct' => $values[$field][$i]['ct'],
        )
      ) . '<br/>';
    }
  }
  $desc .= '</i>' . t('If you continue these information could be lost.') . '</p>';
  $form['process'] = array('#type' => 'hidden', '#value' => 'true');
  return confirm_form($form, 'Confirmation needed for removing field instances with values in the current database', 'admin/config/content/newsroom', check_markup($desc, 'full_html'), 'Continue', 'Restart');
}

/**
 * Implements hook_validate().
 */
function nexteuropa_newsroom_universe_id_validate($element, &$form_state) {
  if (!_newsroom_validate_universe($form_state['values']['newsroom_universe_id'])) {
    form_error($element, t('You must enter a valid Newsroom Universe ID.'));
  }
}

/**
 * Implements hook_validate().
 */
function nexteuropa_newsroom_type_root_validate($element, &$form_state) {
  $value = preg_replace('@^/|/$@', '', $element['#value']);
  $value_array = explode('/', $value);
  $pattern = '';

  for ($i = 1; $i <= count($value_array); $i++) {
    $segment = pathauto_cleanstring($value_array[$i - 1]);
    $pattern .= $segment;
    if ($i < count($value_array) && $segment != '') {
      $pattern .= '/';
    }
  }

  if ($form_state['values'][$element['#name']] != $pattern) {
    drupal_set_message(t('The value for the %el has been modified. BEFORE: %or ::: AFTER: %mod', array('%el' =>  $element['#name'], '%or' => $form_state['values'][$element['#name']], '%mod' => $pattern)), 'warning');
    $form_state['values'][$element['#name']] = $pattern;
  }
}

/**
 * Reset values in the path patterns field for the newsroom items.
 */
function _nexteuropa_newsroom_reset_paths($form, &$form_state) {
  $vocabulary = taxonomy_vocabulary_machine_name_load('newsroom_item_type');
  $types = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));

  foreach ($types as $tid => $type) {
    $type_name = pathauto_cleanstring(drupal_strtolower($type->name));
    $parents = taxonomy_get_parents($type->tid);
    $parent = '';

    if (!empty($parents)) {
      $parent = reset($parents);
      $parent = pathauto_cleanstring(drupal_strtolower($parent->name)) . '/';
    }

    $form['newsroom_paths'][$type_name . '_rootpath']['#value'] = $parent . $type_name;
  }
  return $form['newsroom_paths'];
}