<?php

/**
 * @file
 * Nexteuropa Newsroom administration page.
 */

/**
 * Nexteuropa newsroom admin form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Form array.
 */
function nexteuropa_newsroom_admin_settings($form, &$form_state) {
  // Be aware about the selected content types in the fields fieldset.
  $sel_ct = NewsroomHelper::getFieldInstances('select');
  $top_ct = NewsroomHelper::getFieldInstances('topic');
  $newsroom_universe_id = NewsroomHelper::getUniverseId();
  // Get some information basing on the activation of the universe id.
  if (!empty($newsroom_universe_id)) {
    $universe_id_info['disabled'] = TRUE;
    $universe_id_info['description'] = t('To change the Newsroom Universe ID contact the site administrator.');
    $universe_id_info['class'] = 'selected';
    $universe_id_info['collapsing'] = FALSE;
  }
  else {
    $universe_id_info['disabled'] = FALSE;
    $universe_id_info['description'] = t('After setting the Newsroom Universe ID for the first time content will be imported from the Newsroom service. This might take a few minutes.');
    $universe_id_info['class'] = 'not-selected';
    $universe_id_info['collapsing'] = TRUE;
  }

  // This is special, made just to hold the universe_id field.
  $form['universe_id'] = array(
    '#type' => 'container',
    '#title' => t('Newsroom Universe ID'),
    '#attributes' => array('class' => array($universe_id_info['class'])),
  );

  $form['universe_id']['newsroom_universe_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Universe ID value'),
    '#required' => TRUE,
    '#disabled' => $universe_id_info['disabled'],
    '#description' => $universe_id_info['description'],
    '#default_value' => $newsroom_universe_id,
    '#element_validate' => array('_nexteuropa_newsroom_admin_universe_id_validate'),
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

  $form['newsroom_others']['importers_link'] = array(
    '#type' => 'item',
    '#markup' => l(t('Feed importers'), 'import'),
  );

  $form['newsroom_others']['newsroom_subsite'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of the subsite, if any.'),
    '#description' => t('The value you enter here will be used to filter the items belonging to this website.'),
    '#default_value' => variable_get('newsroom_subsite'),
    '#element_validate' => array('_nexteuropa_newsroom_admin_subsite_validate'),
  );

  $form['newsroom_others']['newsroom_use_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the stylesheets provided by this feature'),
    '#default_value' => variable_get('newsroom_use_css', 1),
  );

  $form['newsroom_others']['newsroom_use_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the stylesheets provided by this feature'),
    '#default_value' => variable_get('newsroom_use_css', 1),
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

  $form['newsroom_others']['newsroom_agenda_after_highlights'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Agenda after the highlights'),
    '#default_value' => variable_get('newsroom_agenda_after_highlights', 1),
  );

  $types = NewsroomHelper::getNewsroomTypes();

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
      $type_name = pathauto_cleanstring($type->name);
      $parents = taxonomy_get_parents($type->tid);
      $parent = '';

      if (!empty($parents)) {
        $parent = reset($parents);
        $parent = pathauto_cleanstring($parent->name) . '/';
      }

      $form['newsroom_paths'][$type_name . '_rootpath'] = array(
        '#type' => 'textfield',
        '#title' => t('Pattern for %type', array('%type' => $type_name)),
        '#required' => FALSE,
        '#description' => t('aliases pattern for the %type_name topic', array('%type_name' => $type_name)),
        '#default_value' => variable_get('newsroom_' . $type_name . '_root', $parent . $type_name),
        '#element_validate' => array('_nexteuropa_newsroom_admin_type_root_validate'),
      );
    }

    $form['newsroom_paths']['reset'] = array(
      '#type' => 'submit',
      '#value' => 'Reset to the defaults',
      '#ajax' => array(
        'callback' => '_nexteuropa_newsroom_admin_reset_paths',
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
    '#description' => t('Here you can easily manage the addition or the removal of the newsroom fields from your content types. Refer to the <a href="@documentation">documentation</a> for having detailed information about the usage of the newsroom fields.  They are meant to give you the chance to associate topics to you contents so that matching news coming from the newsroom can be shown or mentioned contextually.', array('@documentation' => 'https://webgate.ec.europa.eu/fpfis/wikis/pages/viewpage.action?spaceKey=MULTISITE&title=%5BFPFIS%5D+Nexteuropa+Newsroom+-+Documentation')),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#access' => user_access('administer newsroom advanced settings'),
  );

  $form['newsroom_fields']['newsroom_content_types_topic'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Direct topic relation field in your content types'),
    '#description' => t('Choose the content types in which you want to activate a relationship with a newsroom topic.'),
    '#options' => NewsroomHelper::prepareOptions('ct'),
    '#multiple' => TRUE,
    '#default_value' => $top_ct,
  );

  $form['newsroom_fields']['newsroom_content_types_delete_topic'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete all the topic relation fields in your content types'),
    '#description' => t('If you want to delete all the instance of the topic field together check this.'),
    '#default_value' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['newsroom_fields']['newsroom_content_types_select'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Advanced and configurable reference with newsroom items'),
    '#description' => t('Choose the content types in which you want to activate a complex relationship with the newsroom items.'),
    '#options' => NewsroomHelper::prepareOptions('ct'),
    '#multiple' => TRUE,
    '#default_value' => $sel_ct,
  );

  $form['newsroom_fields']['newsroom_content_types_delete_select'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete all the newsroom select fields in your content types'),
    '#description' => t('If you want to delete all the instance of the select field together check this.'),
    '#default_value' => 0,
  );

  // Settings about the universe.
  $form['newsroom_universe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom universe settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $universe_id_info['collapsing'],
  );

  $form['newsroom_universe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom universe settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['newsroom_universe']['newsroom_app'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsroom app'),
    '#default_value' => variable_get('newsroom_app'),
  );

  $form['newsroom_universe']['newsroom_app_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsroom key'),
    '#default_value' => variable_get('newsroom_app_key'),
  );

  $form['newsroom_universe']['newsroom_subscription_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsroom subscription URL'),
    '#default_value' => variable_get('newsroom_subscription_url'),
  );

  $form['newsroom_universe']['newsroom_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsroom universe base URL'),
    '#default_value' => variable_get('newsroom_base_url', NEXTEUROPA_NEWSROOM_BASE_URL),
    '#description' => t('The base url of newsroom feeds.'),
  );

  $form['newsroom_universe']['newsroom_allowed_ips'] = array(
    '#type' => 'textfield',
    '#title' => t('IP addresses allowed for import'),
    '#default_value' => variable_get('newsroom_allowed_ips', '127.0.0.1'),
    '#description' => t('Comma separated list of IP addresses where the importer can be launched from.'),
  );

  $form['newsroom_universe']['newsroom_item_import_script'] = array(
    '#type' => 'textfield',
    '#title' => t('Item import script name'),
    '#default_value' => variable_get('newsroom_item_import_script', NEXTEUROPA_NEWSROOM_ITEM_SCRIPT),
  );
  $form['newsroom_universe']['newsroom_single_item_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single item import'),
    '#default_value' => variable_get('newsroom_single_item_import_segment', NEXTEUROPA_NEWSROOM_ITEM_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_topic_import_script'] = array(
    '#type' => 'textfield',
    '#title' => t('Topic import script name'),
    '#default_value' => variable_get('newsroom_topic_import_script', NEXTEUROPA_NEWSROOM_TOPIC_SCRIPT),
  );
  $form['newsroom_universe']['newsroom_single_topic_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single topic import'),
    '#default_value' => variable_get('newsroom_single_topic_import_segment', NEXTEUROPA_NEWSROOM_TOPIC_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_type_import_script'] = array(
    '#type' => 'textfield',
    '#title' => t('Type import script name'),
    '#default_value' => variable_get('newsroom_type_import_script', NEXTEUROPA_NEWSROOM_TYPE_SCRIPT),
  );
  $form['newsroom_universe']['newsroom_single_type_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single type import'),
    '#default_value' => variable_get('newsroom_single_type_import_segment', NEXTEUROPA_NEWSROOM_TYPE_SEGMENT),
  );

  // For topics and services we use the same script name.
  $form['newsroom_universe']['newsroom_service_import_script'] = array(
    '#type' => 'textfield',
    '#title' => t('Service import script name'),
    '#default_value' => variable_get('newsroom_service_import_script', NEXTEUROPA_NEWSROOM_TOPIC_SCRIPT),
  );
  $form['newsroom_universe']['newsroom_single_service_import_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk for single service import'),
    '#default_value' => variable_get('newsroom_single_service_import_segment', NEXTEUROPA_NEWSROOM_SERVICE_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_single_item_edit_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('URL chunk to edit an item in the Newsroom'),
    '#default_value' => variable_get('newsroom_single_item_edit_segment', NEXTEUROPA_NEWSROOM_ITEM_EDIT_SEGMENT),
  );

  $form['newsroom_universe']['newsroom_proposal_script'] = array(
    '#type' => 'textfield',
    '#title' => t('Newsroom proposal script'),
    '#default_value' => variable_get('newsroom_proposal_script', NEXTEUROPA_NEWSROOM_PROPOSAL_SCRIPT),
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
    '#default_value' => variable_get('newsroom_newsletter_privacy'),
  );

  // Settings about the newsroom blocks.
  $form['newsroom_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsroom blocks settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
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
  $form['newsroom_blocks']['home_blocks']['newsroom_days_number_for_new_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of days from now where we check new newsroom items'),
    '#default_value' => variable_get('newsroom_days_number_for_new_user', 14),
  );

  // Attach a css to the admin settings form.
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'nexteuropa_newsroom') . '/styles/nexteuropa_newsroom_admin_setting.css',
  );
  // Validate function.
  $form['#validate'][] = '_nexteuropa_newsroom_admin_settings_form_validate';
  // Submit handler.
  $form['#submit'][] = '_nexteuropa_newsroom_admin_settings_form_submit';

  if ($newsroom_universe_id) {
    $form['actions']['run'] = array(
      '#type' => 'submit',
      '#value' => t('Run importers'),
      '#submit' => array('_nexteuropa_newsroom_import_importers'),
      '#access' => user_access('administer newsroom advanced settings'),
      '#weight' => 10,
    );
    $form['actions']['rebuild'] = array(
      '#type' => 'submit',
      '#value' => t('Rebuild importers'),
      '#submit' => array('_nexteuropa_newsroom_admin_rebuild_importers'),
      '#access' => user_access('administer newsroom advanced settings'),
      '#weight' => 11,
    );
    $form['actions']['clean_cache'] = array(
      '#type' => 'submit',
      '#value' => 'Clean cache',
      '#submit' => array('_nexteuropa_newsroom_admin_clean_cache'),
      '#access' => user_access('administer newsroom advanced settings'),
      '#weight' => 12,
    );
  }

  // Define the fields_form array().
  $form_state['fields_form'] = array();
  $form_state['fields_form']['topic'] = $top_ct;
  $form_state['fields_form']['select'] = $sel_ct;

  // Confirmation step_needed.
  if (isset($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    return _nexteuropa_newsroom_admin_delete_confirm($form, $form_state);
  }
  // Normal form.
  else {
    return system_settings_form($form);
  }
}

/**
 * Validation step for the the newsroom admin form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function _nexteuropa_newsroom_admin_settings_form_validate($form, &$form_state) {
  // If we are not during a confirm or this has happened right before.
  if (!isset($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    $check_values = _nexteuropa_newsroom_admin_prepare_check($form_state['fields_form'], $form_state['input']);

    // Check every topic instance if requested.
    if ($check_values['delete']['topic'] == 1) {
      $test = _nexteuropa_newsroom_admin_check_deletion('topic', NEXTEUROPA_NEWSROOM_ALL);
    }
    // If there are less values than before, check instances.
    elseif (!empty($check_values['check']['topic'][0])) {
      $test = _nexteuropa_newsroom_admin_check_deletion('topic', $check_values['check']['topic'][0]);
    }

    // Check every select instance if requested.
    if ($check_values['delete']['select'] == 1) {
      $test = _nexteuropa_newsroom_admin_check_deletion('select', NEXTEUROPA_NEWSROOM_ALL);
    }
    // If there are less values than before, check instances.
    elseif (!empty($check_values['check']['select'][0])) {
      $test = _nexteuropa_newsroom_admin_check_deletion('select', $check_values['check']['select'][0]);
    }

    if (!empty($test)) {
      $form_state['storage']['confirm'] = TRUE;
      $form_state['confirm']['values'] = $test;
    }
  }
}

/**
 * Submit handler for the newsroom admin form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function _nexteuropa_newsroom_admin_settings_form_submit($form, &$form_state) {
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
  if ($form_state['values']['newsroom_universe_id']) {
    variable_set('newsroom_universe_id', $form_state['values']['newsroom_universe_id']);
  }

  // If the validation returns the confirm request.
  if (isset($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    $form_state['rebuild'] = TRUE;
  }
  else {
    $check_values = _nexteuropa_newsroom_admin_prepare_check($form_state['fields_form'], $form_state['values']);

    // Remove every topic instance if requested.
    if ($check_values['delete']['topic'] == 1) {
      _nexteuropa_newsroom_admin_remove_fields('topic', NEXTEUROPA_NEWSROOM_ALL);
    }
    else {
      if (!empty($check_values['selected']['topic']) && !empty($check_values['check']['topic'][1])) {
        // Add new instances.
        _nexteuropa_newsroom_admin_add_fields('topic', $check_values['check']['topic'][1]);
      }
      elseif (!empty($check_values['check']['topic'][0])) {
        // Remove instances.
        _nexteuropa_newsroom_admin_remove_fields('topic', $check_values['check']['topic'][0]);
      }
    }

    // Remove every select instance if requested.
    if ($check_values['delete']['select'] == 1) {
      _nexteuropa_newsroom_admin_remove_fields('select', NEXTEUROPA_NEWSROOM_ALL);
    }
    else {
      if (!empty($check_values['selected']['select']) && !empty($check_values['check']['select'][1])) {
        // Add new instances.
        _nexteuropa_newsroom_admin_add_fields('select', $check_values['check']['select'][1]);
      }
      elseif (!empty($check_values['check']['select'][0])) {
        // Remove instances.
        _nexteuropa_newsroom_admin_remove_fields('select', $check_values['check']['select'][0]);
      }
    }

    cache_clear_all('newsroom:', 'cache', TRUE);
  }
}

/**
 * Add a confirmation step if needed.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Confirmation form array.
 */
function _nexteuropa_newsroom_admin_delete_confirm($form, &$form_state) {
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
 * Checks universe ID for valid value.
 *
 * @param array $element
 *   Form element.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_admin_universe_id_validate($element, &$form_state) {
  if (!NewsroomHelper::validateUniverse($form_state['values']['newsroom_universe_id'])) {
    form_error($element, t('You must enter a valid Newsroom Universe ID.'));
  }
}

/**
 * Checks subsite for valid value.
 *
 * @param array $element
 *   Form element.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_admin_subsite_validate($element, &$form_state) {
  $subsite = $form_state['values']['newsroom_subsite'];
  $universe_id = $form_state['values']['newsroom_universe_id'];

  if (!NewsroomHelper::validateSubsite($universe_id, $subsite)) {
    form_error($element, t("This subsite doesn't seem to exist, please check the value you entered."));
  }
}

/**
 * Validates newsroom URL patterns.
 *
 * @param array $element
 *   Form element.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_admin_type_root_validate($element, &$form_state) {
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
 * Callback: Resets values in the path patterns field for the newsroom items.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 *
 * @return array
 *   Pathes.
 */
function _nexteuropa_newsroom_admin_reset_paths($form, &$form_state) {
  $types = NewsroomHelper::getNewsroomTypes();
  foreach ($types as $tid => $type) {
    $type_name = pathauto_cleanstring($type->name);
    $parents = taxonomy_get_parents($type->tid);
    $parent = '';
    if (!empty($parents)) {
      $parent = reset($parents);
      $parent = pathauto_cleanstring($parent->name) . '/';
    }
    $form['newsroom_paths'][$type_name . '_rootpath']['#value'] = $parent . $type_name;
  }
  return $form['newsroom_paths'];
}

/**
 * Cleans newsroom cache - Ajax callback.
 */
function _nexteuropa_newsroom_admin_clean_cache() {
  cache_clear_all('*', NEXTEUROPA_NEWSROOM_CACHE_TABLE, TRUE);
  drupal_set_message(t('Cache has been cleaned.'));
}

/**
 * Adds fields to selected content types.
 *
 * @param string $type
 *   Select or topic fo the moment.
 * @param array $sel_ct
 *   Array of content types machine names.
 */
function _nexteuropa_newsroom_admin_add_fields($type = 'topic', $sel_ct = array()) {
  $field_name = 'field_newsroom_associated_' . $type;

  if (!empty($sel_ct)) {
    foreach ($sel_ct as $machine_name => $content_type) {
      $exist = field_info_instance('node', $field_name, $machine_name);
      // Check for existing instances.
      if ($exist === NULL) {
        $instance = array(
          'field_name' => $field_name,
          'entity_type' => 'node',
          'bundle' => $machine_name,
          'label' => 'Newsroom ' . $type,
          'description' => '',
          'required' => 0,
        );
        field_create_instance($instance);
        // Call the field_group helper function, we surely have to update it.
        _nexteuropa_newsroom_admin_field_group($machine_name, $field_name);
        // Set a message to inform the user about the field instance creation.
        drupal_set_message(t('Created instance of @field in the @bundle content type', array('@field' => $field_name, '@bundle' => $machine_name)));
      }
    }
  }
}

/**
 * Creates a field_group to hold the newsroom fields in a vertical tab.
 *
 * @param string $machine_name
 *   Content type machine name.
 * @param string $field_name
 *   Field machine name.
 */
function _nexteuropa_newsroom_admin_field_group($machine_name, $field_name) {
  // Get info about the group, it's likely to be already in the database.
  $groups = field_group_info_groups('node', $machine_name, 'form', TRUE);
  $fields = array('topic', 'select');
  $group_name = 'group_' . $machine_name . '_newsroom';
  $instances = FALSE;
  // Check for instances of the newsroom fields inside the given content type.
  foreach ($fields as $field) {
    $field_name = 'field_newsroom_associated_' . $field;
    if (field_info_instance('node', $field_name, $machine_name) != NULL) {
      $instances[] = field_info_instance('node', $field_name, $machine_name);
    }
  }
  // If the group is already there, remove it.
  if (isset($groups[$group_name])) {
    db_delete('field_group')
      ->condition('bundle', $machine_name, '=')
      ->condition('group_name', 'group_' . $machine_name . '_newsroom', '=')
      ->execute();
  }
  // Create the group with the right children.
  if ($instances) {
    $field_group = (object) array(
      'identifier' => $group_name . '|node|' . $machine_name . '|form',
      'group_name' => $group_name,
      'entity_type' => 'node',
      'bundle' => $machine_name,
      'mode' => 'form',
      'children' => array(),
      'parent_name' => '',
      'weight' => 5,
      'label' => 'Newsroom fields',
      'format_type' => 'tab',
      'disabled' => FALSE,
      'format_settings' => array(
        'instance_settings' => array(
          'required_fields' => 0,
          'classes' => 'group-newsroom field-group-tab',
          'description' => '',
        ),
        'formatter' => 'closed',
      ),
    );

    foreach ($instances as $instance) {
      $field_group->children[] = $instance['field_name'];
    }

    field_group_group_save($field_group);
  }
  // Remove the group since we don't have fields to show.
  else {
    drupal_set_message(t('Removed the fieldgroup @name from the @content_type content type', array('@name' => $group_name, '@content_type' => $machine_name)), 'status');
  }
}

/**
 * Removes all the instances of a fields.
 *
 * @param string $type
 *   Select or topic fo the moment.
 * @param array $sel_ct
 *   Array of content types machine names.
 */
function _nexteuropa_newsroom_admin_remove_fields($type = 'topic', $sel_ct = array()) {
  // This function runs after checking for existing field values in the databas.
  $field_name = 'field_newsroom_associated_' . $type;
  // All is the parameter we get when an user want to delete all the instances.
  if ($sel_ct == NEXTEUROPA_NEWSROOM_ALL) {
    $instances = NewsroomHelper::getFieldInstances($type);
  }
  // Limit the search to the selected content types.
  elseif (!empty($sel_ct)) {
    foreach ($sel_ct as $content_type) {
      $instances[] = $content_type;
    }
  }

  if (!empty($instances)) {
    // Loop through the instances to delete them.
    foreach ($instances as $instance) {
      $instance = field_info_instance('node', $field_name, $instance);
      field_delete_instance($instance, FALSE);
      // Call the field_group helper function, we could have to delete it.
      _nexteuropa_newsroom_admin_field_group($instance['bundle'], $field_name);
      // Add the message to queue.
      drupal_set_message(t('Deleted instance of @field in the @bundle content type', array('@field' => $field_name, '@bundle' => $instance['bundle'])));
    }
  }
}

/**
 * Checks if it safe to delete field instances.
 *
 * @param string $type
 *   Select or topic fo the moment.
 * @param array $checks
 *   Array of items to check.
 *
 * @return array
 *   Information about the field name and nodes found.
 */
function _nexteuropa_newsroom_admin_check_deletion($type, $checks = array()) {
  $nodes = array();
  // "All" is the parameter we get to delete all the instances.
  if ($checks == NEXTEUROPA_NEWSROOM_ALL) {
    $instances = NewsroomHelper::getFieldInstances($type);
  }
  else {
    if (!empty($checks)) {
      // Get the instances to check for.
      foreach ($checks as $field => $check) {
        $instances[] = $check;
      }
    }
  }

  if (!empty($instances)) {
    foreach ($instances as $instance) {
      // Check in the database for values of the selected field.
      $query = db_select('field_data_field_newsroom_associated_' . $type, 'ch');
      $query->condition('bundle', $instance, '=');
      $num_rows = $query->countQuery()->execute()->fetchField();
      // There are values, we store the number of nodes to show it to the user.
      if ($num_rows > 0) {
        $nodes['field_data_field_newsroom_associated_' . $type][] = array(
          'ct' => $instance,
          'nodes' => $num_rows,
        );
      }
    }
  }
  return $nodes;
}

/**
 * Prepares check for instances deletion.
 *
 * @param array $previous
 *   Old values.
 * @param array $input
 *   New values.
 *
 * @return array
 *   Variables to pass.
 */
function _nexteuropa_newsroom_admin_prepare_check(array $previous, array $input) {
  // Set some values.
  $selected['topic'] = array_filter($input['newsroom_content_types_topic']);
  $selected['select'] = array_filter($input['newsroom_content_types_select']);
  $check_topic = array();
  $check_select = array();
  // Check the two array for differences. we need to catch also a deselection.
  if ($selected != $previous) {
    $check_topic[] = array_diff($previous['topic'], $selected['topic']);
    $check_topic[] = array_diff($selected['topic'], $previous['topic']);
    $check_select[] = array_diff($previous['select'], $selected['select']);
    $check_select[] = array_diff($selected['select'], $previous['select']);
  }
  // Prepare all the relevant data formatted into an array().
  $infos = array(
    'selected' => array(
      'topic' => $selected['topic'],
      'select' => $selected['select'],
    ),
    'delete' => array(
      'topic' => $input['newsroom_content_types_delete_topic'],
      'select' => $input['newsroom_content_types_delete_select'],
    ),
    'check' => array(
      'topic' => $check_topic,
      'select' => $check_select,
    ),
  );

  return $infos;
}

/**
 * Rebuilds multilingual importers.
 */
function _nexteuropa_newsroom_admin_rebuild_importers() {
  // Remove importers.
  $importers = array(
    'items' => NEXTEUROPA_NEWSROOM_ITEM_IMPORTER,
    'services' => NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER,
    'topics' => NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER,
    'types' => NEXTEUROPA_NEWSROOM_TYPE_IMPORTER,
    'newsletter' => NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER,
  );

  foreach ($importers as $key => $importer) {
    // WE drop all tampers for the current importer.
    db_delete('feeds_tamper')
      ->condition('importer', $importer)
      ->execute();
    feeds_importer($importer)->delete();
    // Recreate them.
    call_user_func('_nexteuropa_newsroom_create_multilingual_' . $key . '_importer');
  }

  drupal_set_message(t('Newsroom importers have been successfully recreated.'));
}
