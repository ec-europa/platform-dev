<?php
/**
 * @file
 * Nexteuropa Newsroom administration page.
 */

/**
 * Nexteuropa newsroom admin form.
 */
function nexteuropa_newsroom_admin_settings($form, &$form_state) {
  // Be aware about the selected content types in the fields fieldset.
  $sel_ct = NewsroomHelper::getFieldInstances('select');
  $top_ct = NewsroomHelper::getFieldInstances('topic');
  $newsroom_universe_id = variable_get('newsroom_universe_id', NULL);
  // Get some information basing on the activation of the universe id.
  $universe_id = _nexteuropa_newsroom_check_universe_id();

  // This is special, made just to hold the universe_id field.
  $form['universe_id'] = array(
    '#type' => 'container',
    '#title' => t('Newsroom Universe ID'),
    '#attributes' => array('class' => array($universe_id['class'])),
  );

  // After initital setup disable Universe ID field.
  if ($newsroom_universe_id !== NULL) {
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
    '#default_value' => $newsroom_universe_id,
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

  if ($newsroom_universe_id) {
    $form['newsroom_others']['rebuild'] = array(
      '#type' => 'submit',
      '#value' => t('Rebuild importers on the fly'),
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

  $form['newsroom_others']['clean_cache'] = array(
    '#type' => 'submit',
    '#value' => 'Clean newsroom cache',
    '#description' => t('Clean all newsroom cache entries'),
    '#prefix' => '<div id="newsroom_clean_cache">',
    '#suffix' => '<div class="feedback"></div></div>',
    '#ajax' => array(
      'callback' => '_nexteuropa_newsroom_clean_cache',
    ),
  );

  $form['newsroom_others']['toggle_title'] = array(
    '#type' => 'submit',
    '#value' => 'Switch title fields',
    '#description' => t('Switch title and name fields'),
    '#prefix' => '<div id="newsroom_toggle_title">',
    '#suffix' => '<div class="feedback"></div></div>',
    '#ajax' => array(
      'callback' => '_nexteuropa_newsroom_toggle_title',
    ),
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

  $form['newsroom_others']['newsroom_proposal_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsroom proposal URL'),
    '#default_value' => variable_get('newsroom_proposal_url', NULL),
  );

  $vocabulary = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
  $types = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));

  if (!empty($types)) {
    $form['newsroom_paths'] = array(
      '#type' => 'fieldset',
      '#title' => t('Newsroom content path settings'),
      '#prefix' => '<div id="newsroom_reset">',
      '#suffix' => '</div>',
      '#description' => t("You can define here a root path for your items basing on the item type. The default behavior is to have sections correponding to the types, so if you have two types like
            news and events you will get pattern like news/[node:title], events/[node:title], you can override the root path for your elements here. Do not use leading or trailing slashes"),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
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
    '#options' => NewsroomHelper::prepareOptions('ct'),
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
    '#options' => NewsroomHelper::prepareOptions('ct'),
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
    '#default_value' => variable_get('newsroom_single_item_import_segment', NEXTEUROPA_NEWSROOM_ITEM_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_single_topic_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single topic import'),
    '#default_value' => variable_get('newsroom_single_topic_import_segment', NEXTEUROPA_NEWSROOM_TOPIC_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_single_type_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single type import'),
    '#default_value' => variable_get('newsroom_single_type_import_segment', NEXTEUROPA_NEWSROOM_TYPE_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_single_service_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single service import'),
    '#default_value' => variable_get('newsroom_single_service_import_segment', NEXTEUROPA_NEWSROOM_SERVICE_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_single_item_edit_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk to edit an item in the Newsroom'),
    '#default_value' => variable_get('newsroom_single_item_edit_segment', 'item.cfm?item_id='),
  );

  $form['newsroom_pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom page settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['newsroom_pages']['newsroom_newsletter_privacy'] = array(
    '#type' => 'textarea',
    '#title' => t('Privacy statement'),
    '#default_value' => variable_get('newsroom_newsletter_privacy', NULL),
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
    '#options' => NewsroomHelper::prepareOptions(2),
    '#default_value' => variable_get('newsroom_summary_block_columns', 1),
  );

  $form['newsroom_blocks']['newsroom_summary_block_num_items'] = array(
    '#type' => 'select',
    '#title' => t('Number of items in boxes in the summary blocks'),
    '#options' => NewsroomHelper::prepareOptions(5),
    '#default_value' => variable_get('newsroom_summary_block_num_items', 3),
  );

  $form['newsroom_blocks']['newsroom_summary_block_num_highlighted_items'] = array(
    '#type' => 'select',
    '#title' => t('Number of items in boxes of highlighted types in the summary blocks'),
    '#options' => NewsroomHelper::prepareOptions(6),
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
    '#options' => NewsroomHelper::prepareOptions(5),
    '#default_value' => variable_get('newsroom_summary_home_block_num_items', 3),
  );

  $form['newsroom_blocks']['home_blocks']['newsroom_summary_home_block_num_highlighted_items'] = array(
    '#type' => 'select',
    '#title' => t('Number of items in boxes of highlighted types in the summary block on the homepage'),
    '#options' => NewsroomHelper::prepareOptions(6),
    '#default_value' => variable_get('newsroom_summary_home_block_num_highlighted_items', 3),
  );

  $form['newsroom_blocks']['home_blocks']['newsroom_summary_home_block_num_agenda'] = array(
    '#type' => 'select',
    '#title' => t('Number of days to list in the Agenda block on the homepage'),
    '#options' => NewsroomHelper::prepareOptions(6),
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

  if ($newsroom_universe_id) {
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
    elseif (!empty($check_values['check']['topic'][0])) {
      $test = _nexteuropa_newsroom_check_deletion('topic', $check_values['check']['topic'][0]);
    }

    // Check every select instance if requested.
    if ($check_values['delete']['select'] == 1) {
      $test = _nexteuropa_newsroom_check_deletion('select', 'all');
    }
    // If there are less values than before, check instances.
    elseif (!empty($check_values['check']['select'][0])) {
      $test = _nexteuropa_newsroom_check_deletion('select', $check_values['check']['select'][0]);
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

  // Create default importers if new Newsroom Universe ID detected.
  if ($form_state['values']['newsroom_universe_id'] <> $form['universe_id']['newsroom_universe_id']['#default_value']) {
    variable_set('newsroom_universe_id', $form_state['values']['newsroom_universe_id']);

    _nexteuropa_newsroom_create_default_importers($form_state['values']['newsroom_universe_id']);
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
  _nexteuropa_newsroom_create_default_importers(variable_get('newsroom_universe_id'));
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
  if (!_nexteuropa_newsroom_validate_universe($form_state['values']['newsroom_universe_id'])) {
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
    drupal_set_message(
      t('The value for the %el has been modified. BEFORE: %or ::: AFTER: %mod',
      array(
        '%el' => $element['#name'],
        '%or' => $form_state['values'][$element['#name']],
        '%mod' => $pattern,
      )),
      'warning'
    );
    $form_state['values'][$element['#name']] = $pattern;
  }
}

/**
 * Reset values in the path patterns field for the newsroom items.
 */
function _nexteuropa_newsroom_reset_paths($form, &$form_state) {
  $vocabulary = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
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

/**
 * Cleans newsroom cache.
 */
function _nexteuropa_newsroom_clean_cache() {
  cache_clear_all('*', NEXTEUROPA_NEWSROOM_CACHE_TABLE, TRUE);
  $commands[] = ajax_command_replace('#newsroom_clean_cache .feedback', '<div class="messages status">Cache cleaned</div>');

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Switch titles.
 */
function _nexteuropa_newsroom_toggle_title() {
  title_field_replacement_toggle('node', NEXTEUROPA_NEWSROOM_CONTENT_TYPE, 'title');
  title_field_replacement_toggle('taxonomy_term', NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY, 'name');
  title_field_replacement_toggle('taxonomy_term', NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY, 'name');
  title_field_replacement_toggle('taxonomy_term', NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY, 'name');
  cache_clear_all('*', 'cache_field', TRUE);
  $commands[] = ajax_command_replace('#newsroom_toggle_title .feedback', '<div class="messages status">Titles switched</div>');
  return array('#type' => 'ajax', '#commands' => $commands);
}
