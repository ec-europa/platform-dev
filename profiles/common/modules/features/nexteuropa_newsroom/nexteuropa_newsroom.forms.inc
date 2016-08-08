<?php

/**
 * @file
 * Nexteuropa Newsroom Forms.
 */

/**
 * Submit handler for config restore form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 *
 * @return string
 *   Form submit result.
 */
function nexteuropa_newsroom_restore_conf($form, &$form_state) {
  $def_lang = language_default()->language;
  $voc = $form['vocabulary_machine_name']['#value'];
  // Get the id coming from the newsroom.
  $id = _nexteuropa_newsroom_get_ids($voc, $form['#term']);
  // The name of the variable contains the id.
  $name = $voc . '_backup';
  $backup = variable_get($name, array());

  if (empty($backup)) {
    drupal_set_message(t('No backup has been found for the vocabulary: @voc and the term: @name.', array(
      '@voc' => $voc,
      '@name' => $form['#term']['name'],
    )), 'warning');
    return '';
  }

  $term = $backup[$id];

  if (empty($term)) {
    drupal_set_message(t('No backup has been found for the term: @name.', array('@name' => $form['#term']['name'])), 'warning');
    return '';
  }

  // Override values basing on the backup ones.
  foreach ($term as $propname => $prop) {
    for ($i = 0; $i < count($prop); $i++) {
      switch ($propname) {
        case 'field_newsroom_topic':
          $form_state['values'][$propname][LANGUAGE_NONE][$i]['tid'] = $prop[$i];
          break;

        case 'field_newsroom_featured_item':
          $form_state['values'][$propname][LANGUAGE_NONE][$i]['target_id'] = $prop[$i];
          break;

        case 'field_newsroom_category_domain':
          $form_state['values'][$propname][$def_lang][$i]['value'] = $prop[$i];
          break;

        default:
          $form_state['values'][$propname][LANGUAGE_NONE][$i]['value'] = $prop[$i];
      }
    }
  }

  // Set a message for the user.
  drupal_set_message(t('The configuration for the term "@name" has been restored from the backup version.', array('@name' => $form['#term']['name'])), 'status');
  // Submit the form so the term get saved.
  return taxonomy_form_term_submit($form, $form_state);
}

/**
 * Checks backup info.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return bool
 *   Check result.
 */
function _nexteuropa_newsroom_check_backup($form, &$form_state) {

  $voc = $form['#vocabulary']->machine_name;
  // Get the current variable for the specific vocubulary.
  $backup = variable_get($voc . '_backup', array());

  if (empty($backup)) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}

/**
 * Submit handler for config restore conf all form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 */
function nexteuropa_newsroom_restore_conf_all($form, &$form_state) {
  $voc = $form['#vocabulary']->machine_name;
  // Get the current backup.
  $backup = variable_get($voc . '_backup', array());
  // Divide terms into chunks, grouping five of them.
  $chunks = array_chunk($backup, 5, TRUE);
  $num_operations = $sandbox['limit'] = count($chunks);
  $operations = array();

  for ($i = 0; $i < $num_operations; $i++) {
    $operations[] = array(
      'nexteuropa_newsroom_restore_batch',
      array(
        $chunks[$i],
        $voc,
        array('(Operation: ' => $i),
      ),
    );
  }

  $batch = array(
    'operations' => $operations,
    'finished' => 'nexteuropa_newsroom_restore_batch_finished',
    'title' => t('Restore configuration for terms'),
    'init_message' => t('The restore of your configuration has been started'),
    'progress_message' => t(
      'Current: @current | Remaining:
      @remaining | Total: @total | Percentage: @percentage | Estimate:
      @estimate | Elapsed: @elapsed'
    ),
    'error_message' => t('The restore did not work.'),
  );

  batch_set($batch);
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function nexteuropa_newsroom_form_nexteuropa_newsroom_admin_settings_alter(&$form, &$form_state, $form_id) {

  // If we are in a confimation step, change the form visualization.
  if (isset($form_state['storage']['confirm'])) {
    drupal_set_message(t('You are in a confirmation page, to submit all the form settings check the box below'), 'warning');
    $form['newsroom_universe']['#collapsible'] = TRUE;
    $form['newsroom_universe']['#collapsed'] = TRUE;
    $form['newsroom_fields']['#collapsed'] = FALSE;
  }
}

/**
 * Submit handler for config form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 */
function nexteuropa_newsroom_backup_conf($form, &$form_state) {
  // Save the term.
  taxonomy_form_term_submit($form, $form_state);
  $voc = $form['vocabulary_machine_name']['#value'];
  // Get the current backup.
  $current_values = variable_get($voc . '_backup', array());
  $id = _nexteuropa_newsroom_get_ids($voc, $form_state['values']);
  $term = (object) $form_state['values'];
  $new_values = _nexteuropa_newsroom_export_prepare_values($term);
  // If no backup have been saved, save it for for the first time.
  if (empty($current_values)) {
    variable_set($voc . '_backup', $new_values);
  }
  else {
    // Override the values for the specific term.
    $new_values = reset($new_values);
    $current_values[$id] = $new_values;
  }

  // Set values for the newsroom backup.
  variable_set($voc . '_backup', $current_values);

  // Set a message to the user.
  drupal_set_message(t('We saved a backup of your configuration for the term "@name". if you need to restore the values in the backup click on the "Restore & Save" button', array('@name' => $form['#term']['name'])), 'status');
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function nexteuropa_newsroom_form_taxonomy_form_term_alter(&$form, &$form_state) {

  $voc_name = $form['vocabulary_machine_name']['#value'];

  switch ($voc_name) {
    case NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY:
    case NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY:
    case NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY:
      if (variable_get($voc_name . '_backup', FALSE)) {
        $form['actions']['restore_config'] = array(
          '#type' => 'submit',
          '#value' => t('Restore conf & Save'),
          '#submit' => array('nexteuropa_newsroom_restore_conf'),
        );
      }

      $form['actions']['backup_config'] = array(
        '#type' => 'submit',
        '#value' => t('Backup conf & Save'),
        '#submit' => array('nexteuropa_newsroom_backup_conf'),
      );
      break;
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function nexteuropa_newsroom_form_taxonomy_overview_terms_alter(&$form, &$form_state) {

  $vocs = array(
    NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
    NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY,
    NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY,
  );

  $value = _nexteuropa_newsroom_check_backup($form, $form_state) ? t('[Newsroom] Override existing backup') : t('[Newsroom] Backup configuration');

  if (in_array($form['#vocabulary']->machine_name, $vocs)) {
    $form['actions']['backup_config'] = array(
      '#type' => 'submit',
      '#value' => $value,
      '#submit' => array('nexteuropa_newsroom_backup_conf_all'),
    );

    if ($check = _nexteuropa_newsroom_check_backup($form, $form_state)) {
      $form['actions']['restore_config'] = array(
        '#type' => 'submit',
        '#value' => t('[Newsroom] Restore configuration'),
        '#submit' => array('nexteuropa_newsroom_restore_conf_all'),
      );
    }
  }
}

/**
 * Implements hook_date_popup_process_alter().
 */
function nexteuropa_newsroom_date_popup_process_alter(&$element, &$form_state, $context) {
  if ($form_state['build_info']['form_id'] == 'nexteuropa_newsroom_agenda_datepicker_form') {
    unset($element['date']['#title']);
    unset($element['date']['#description']);
  }
  if ($form_state['build_info']['form_id'] == 'nexteuropa_newsroom_newsroom_page_filter_form') {
    unset($element['date']['#title']);
  }
}

/**
 * Implements hook_form_alter().
 */
function nexteuropa_newsroom_form_field_ui_display_overview_form_alter(&$form, &$form_state, $form_id) {
  if ($form['#bundle'] == 'newsroom_item') {
    $form['newsroom_introduction'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="messages status">' . t('This is the newsroom content type, you can freely customize the teaser and full node view modes without affecting the feature which will stay in default state.') . '</div>',
      '#weight' => -100,
    );

    if ($form['#view_mode'] == 'full' ||  $form['#view_mode'] == 'teaser') {
      // Existing backup is stored into this variable.
      $backup = variable_get('nexteuropa_newsroom_view_modes_backup', FALSE);
      // Get the current export.
      $current = _nexteuropa_newsroom_export_modes();
      // Prepare the default value for the  import textarea, if we have it.
      $default_value = !empty($backup) ? $backup : '';
      // Show different help text basing on the availability of a backup.
      $title = empty($backup) ? t('Paste here the code previously exported') : t('Paste here the serailized export of your configuration to restore it.');

      $form['newsroom_export'] = array(
        '#type' => 'markup',
        '#markup' => '<div class="newsroom_export"><div id="newsroom_export_content"></div></div>',
        '#weight' => 95,
      );

      $form['newsroom_status'] = array(
        '#type' => 'markup',
        '#markup' => '<div id="newsroom_status"></div>',
        '#weight' => 96,
      );

      // This is just a toggler, basically.
      $form['actions']['reveal_modes'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="newsroom-reveal-modes">',
        '#suffix' => '</div>',
        '#value' => t('[Newsroom] Export/Import settings'),
        '#weight' => 97,
      );

      $form['export']['export_code'] = array(
        '#type' => 'textarea',
        '#prefix' => '<div id="newsroom-export-code">',
        '#suffix' => '</div>',
        '#title' => t('Copy this text and save it, you can use the import button then to restore your configurations. You can also choose to save the configuration in the database clicking on the backup button.'),
        '#description' => t('This is the export of your current configurations'),
        '#value' => $current,
        '#format' => 'html',
        '#resizable' => TRUE,
        '#wysiwyg' => FALSE,
        '#rows' => 20,
        '#weight' => 98,
      );

      $form['export_modes'] = array(
        '#type' => 'submit',
        '#value' => t('[Newsroom] Backup settings in the database'),
        '#prefix' => '<div id="newsroom-backup-submit">',
        '#suffix' => '</div>',
        '#ajax' => array(
          'callback' => '_nexteuropa_newsroom_export_modes_submit',
          'event' => 'click',
          'wrapper' => 'newsroom_status',
          'effect' => 'fade',
          'method' => 'replace',
          '#weight' => 99,
        ),
      );

      $form['import']['import_code'] = array(
        '#prefix' => '<div id="newsroom-import-code">',
        '#suffix' => '</div>',
        '#type' => 'textarea',
        '#title' => $title,
        '#description' => t('Serialized code export'),
        '#attributes' => array('id' => 'nexteuropa_newsroom_exported_instances'),
        '#format' => 'plain_text',
        '#resizable' => TRUE,
        '#wysiwyg' => FALSE,
        '#rows' => 20,
        '#weight' => 100,
      );

      $form['import']['import_modes'] = array(
        '#type' => 'submit',
        '#name' => 'newsroom_import',
        '#prefix' => '<div id="newsroom_import_submit">',
        '#suffix' => '</div>',
        '#value' => t('[Newsroom] Import settings'),
        '#weight' => 101,
        '#submit' => array('_nexteuropa_newsroom_restore_modes'),
        '#validate' => array('_nexteuropa_newsroom_validate_modes'),
        '#states' => array(
          'visible' => array(
            ':input[id="nexteuropa_newsroom_exported_instances"]' => array('filled' => TRUE),
          ),
        ),
      );

      if ($export = variable_get('nexteuropa_newsroom_view_modes_backup', FALSE)) {
        $form['import']['restore_modes'] = array(
          '#type' => 'submit',
          '#name' => 'newsroom_restore',
          '#prefix' => '<div id="newsroom_import_backup">',
          '#suffix' => '</div>',
          '#value' => t('[Newsroom] Import settings from the existing backup'),
          '#weight' => 102,
          '#submit' => array('_nexteuropa_newsroom_restore_modes'),
        );
      }

      // Attach a css to the admin settings form.
      $form['#attached']['css'] = array(
        drupal_get_path('module', 'nexteuropa_newsroom') . '/styles/nexteuropa_newsroom_admin_setting.css',
      );
      $form['#attached']['js'] = array(
        drupal_get_path('module', 'nexteuropa_newsroom') . '/js/node_view_mode_form.js',
      );
    }
  }
}

/**
 * Implements hook_form_alter().
 */
function nexteuropa_newsroom_form_newsroom_item_node_form_alter(&$form, &$form_state, $form_id) {
  // Build language aware options list for taxonomy reference fields.
  $terms = array();
  global $language;
  $def_lang = language_default()->language;
  $curr_lang = $language->language;

  $taxonomy_fields = array(
    'field_newsroom_item_type',
    'field_newsroom_primary_topic',
    'field_newsroom_topics',
    'field_newsroom_highlighted_topic',
  );

  $type_vid = NewsroomHelper::getNewsroomTypeVocabulary()->vid;
  $topic_vid = NewsroomHelper::getNewsroomTopicVocabulary()->vid;

  $terms[NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY] = i18n_taxonomy_get_tree($type_vid, $def_lang);
  $terms[NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY] = i18n_taxonomy_get_tree($topic_vid, $def_lang);

  // Fields with wrong translation in node edit form.
  foreach ($taxonomy_fields as $taxonomy_field) {
    $tree = $taxonomy_field == 'field_newsroom_item_type' ? $terms[NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY] : $terms[NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY];

    foreach ($tree as $key => $value) {
      $i18n_object = i18n_get_object('taxonomy_term', $value->tid);
      $t_term = $i18n_object->localize($curr_lang);
      $pref = $value->parents[0] != 0 ? '- ' : '';
      $form[$taxonomy_field][LANGUAGE_NONE]['#options'][$value->tid] = $pref . $t_term->name;
    }

    // The default value is lost in the translations,
    // so we need to set it this way.
    if (!empty($form['#node']->$taxonomy_field)) {
      $values = array();
      $value_array = $form['#node']->$taxonomy_field;
      foreach ($value_array[LANGUAGE_NONE] as $value) {
        $values[] = $value['tid'];
        $form[$taxonomy_field][LANGUAGE_NONE]['#default_value'] = $values;
      }
    }
  }

  // The widget will loose this settings, otherwise.
  $form['field_newsroom_topics'][LANGUAGE_NONE]['#multiple'] = TRUE;
}

/**
 * Exports selected view modes.
 *
 * @param array $view_modes
 *   View modes array.
 * @param string $bundle
 *   Bundle name.
 *
 * @return string
 *   Serialized exported settings.
 */
function _nexteuropa_newsroom_export_modes($view_modes = array('full', 'teaser'), $bundle = NEXTEUROPA_NEWSROOM_CONTENT_TYPE) {
  // Get the current instances.
  $fields = field_info_instances('node', $bundle);
  $export = array();

  foreach ($fields as $field_name => $field_instance) {
    foreach ($view_modes as $view_mode) {
      $export['instances'][$field_name][$view_mode] = isset($fields[$field_name]['display'][$view_mode]) ? $fields[$field_name]['display'][$view_mode] : NULL;
    }
  }

  // Add the groups export.
  $export['groups'] = _nexteuropa_newsroom_get_real_groups();

  return serialize($export);
}

/**
 * Submit handler, exports selected view modes.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 *
 * @return string
 *   Serialized iexported settings for view mode.
 */
function _nexteuropa_newsroom_export_modes_submit(&$form, &$form_state) {
  $export = $form_state['values']['export_code'];

  if (!empty($export)) {
    variable_set('nexteuropa_newsroom_view_modes_backup', $export);
  }

  $form['newsroom_export'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="newsroom_export"><div class="messages status"> ' . t('Your settings have been saved in the database.') . '</div></div>',
    '#weight' => 97,
  );

  return $form['newsroom_export'];
}

/**
 * Validation handler for view mode importer.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_validate_modes(&$form, &$form_state) {
  if (!empty($form_state['values']['import_code'])) {
    $export = unserialize($form_state['values']['import_code']);

    if (empty($export['instances'])) {
      form_set_error('import_code', t("The code you pasted doesn't seem to contain a valid export of your settings."));
    }
  }
  else {
    form_set_error('import_code', t('There was nothing to restore from, did you paste the exported code..?'));
  }
}

/**
 * Submit handler, get the settings to be restored.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_restore_modes(&$form, &$form_state) {
  $trigger = $form_state['triggering_element']['#name'];

  switch ($trigger) {
    case 'newsroom_restore':
      $export = unserialize(variable_get('nexteuropa_newsroom_view_modes_backup'));
      break;

    default:
      $export = unserialize($form_state['values']['import_code']);
  }

  _nexteuropa_newsroom_import_modes($export);

}

/**
 * Restores settings.
 *
 * @param array $export
 *   Exported view mode settings.
 *
 * @return string
 *   Message string.
 */
function _nexteuropa_newsroom_import_modes($export) {
  $view_modes = array('full', 'teaser');

  if (!empty($export['groups'])) {
    $groups = $export['groups'];
    foreach ($view_modes as $view_mode) {
      if (!empty($groups[$view_mode])) {
        // Clean up the groups before the import.
        $view_mode_groups = field_group_info_groups('node', NEXTEUROPA_NEWSROOM_CONTENT_TYPE, $view_mode, TRUE);
        // We need to check the disabled groups, which can be deleted through
        // UI.
        $view_mode_disabled_groups = field_group_read_groups(
          array(
            'entity_type' => 'node',
            'bundle' => NEXTEUROPA_NEWSROOM_CONTENT_TYPE,
            'mode' => $view_mode,
          ), FALSE);
        if ($view_mode_disabled_groups) {
          $view_mode_groups = array_merge($view_mode_groups, $view_mode_disabled_groups['node'][NEXTEUROPA_NEWSROOM_CONTENT_TYPE][$view_mode]);
        }

        foreach ($view_mode_groups as $group) {
          field_group_group_export_delete($group);
        }
        // Clean cache to see the actual groups later.
        cache_clear_all('field_groups', 'cache_field');

        foreach ($groups[$view_mode] as $group_name => $group) {
          if (field_group_exists($group->group_name, $group->entity_type, $group->bundle, $group->mode)) {
            $old_group = field_group_load_field_group($group->group_name, $group->entity_type, $group->bundle, $group->mode);
            if ($old_group) {
              $group->id = $old_group->id;
            }
          }
          else {
            // We set export_type to 0, if we need to create a new field group.
            $group->export_type = 0;
          }
          $group->disabled = FALSE;

          field_group_group_save($group);
          // The group was deleted through UI, it will be marked as disabled in
          // ctools. We need to enable it.
          if ((isset($group->disabled) && ($group->disabled == TRUE)) ? TRUE : FALSE) {
            ctools_export_crud_enable('field_group', $group->identifier);
          }
        }
      }
    }

    // We clean the cache for the groups to make them visible.
    cache_clear_all('field_groups', 'cache_field');
  }

  if (!empty($export['instances'])) {
    $fields_instances = field_info_instances('node', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    foreach ($export['instances'] as $field_name => $export_instance) {
      if (isset($fields_instances[$field_name])) {
        foreach ($view_modes as $view_mode) {
          if (isset($export_instance[$view_mode])) {
            $fields_instances[$field_name]['display'][$view_mode] = $export_instance[$view_mode];
            // Update the instance.
            field_update_instance($fields_instances[$field_name]);
          }
        }
      }
    }
  }

  return drupal_set_message(t('Your settings have been restored.'), 'status');
}

/**
 * Gets form rendable array for newsroom proposal page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_newsroom_proposal_form($form, $form_state) {

  global $user;

  $account = user_load($user->uid);
  $form['#action'] = $newsroom_url = NewsroomHelper::getUniverseUrl() . variable_get('newsroom_proposal_script');
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => 'Title of your Newsroom item (mandatory)',
    '#default_value' => '',
    '#required' => TRUE,
  );

  $form['teaser'] = array(
    '#title' => t('Teaser'),
    '#type' => 'textarea',
    '#description' => t('Teaser of your Newsroom item (a teaser is a brief description of the subject of your item)'),
    '#size' => 18,
  );

  $form['body'] = array(
    '#title' => t('Full content'),
    '#type' => 'textarea',
    '#description' => t('Full content of the Newsroom item (mandatory - The full content is the body of your item)'),
    '#required' => TRUE,
  );

  $form['url'] = array(
    '#title' => t('URL'),
    '#type' => 'textfield',
    '#description' => t('Add a link to another web page'),
  );

  $form['start_date'] = array(
    '#title' => t('Date'),
    '#type' => 'date',
    '#description' => t('Publication or event date'),
  );

  $form['end_date'] = array(
    '#title' => t('End date'),
    '#type' => 'date',
    '#description' => t('End date'),
  );

  $form['venue'] = array(
    '#title' => t('Venue'),
    '#type' => 'textfield',
    '#description' => t('Name and address of the venue'),
  );

  $form['topic_id'] = array(
    '#title' => t('Topic ID'),
    '#type' => 'hidden',
    '#value' => isset($_REQUEST['topic_id']) ? filter_xss($_REQUEST['topic_id']) : NULL,
    '#required' => TRUE,
  );

  $form['email'] = array(
    '#title' => t('E-mail'),
    '#type' => 'hidden',
    '#value' => $account->mail,
    '#required' => TRUE,
  );

  $form['lastname'] = array(
    '#title' => t('Last name'),
    '#type' => 'hidden',
    '#value' => NewsroomHelper::getFieldValue($account, 'field_lastname'),
    '#required' => TRUE,
  );

  $form['firstname'] = array(
    '#title' => t('First name'),
    '#type' => 'hidden',
    '#value' => NewsroomHelper::getFieldValue($account, 'field_firstname'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );

  return $form;
}

/**
 * Gets form rendable array for newsletter subscription block.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_newsletter_subscription_form($form, &$form_state) {

  $args = $form_state['build_info']['args'][0];
  $form = array();
  $form['#prefix'] = '<div class="CTAnewsletter">';
  $form['#suffix'] = '</div>';
  $form['#token'] = FALSE;
  $form['#action'] = NewsroomHelper::getNewsroomUrl('subscription-quick-generic.cfm');
  $form['intro'] = array(
    '#markup' => '<div class="title">' . $args['name'] . '</div>',
  );

  $form['feedback'] = array(
    '#markup' => '<div class="feedback"></div>',
  );

  $form['email'] = array(
    '#prefix' => '<div class="inputMail">',
    '#suffix' => '</div>',
    '#type' => 'textfield',
    '#attributes' => array(
      'placeholder' => t('Your e-mail'),
      'class' => array(),
    ),
  );

  $form['submit_email_prefix'] = array(
    '#markup' => '<div class="inputSubscribe">',
  );

  $form['submit_email'] = array(
    '#type' => 'button',
    '#value' => t('Subscribe'),
    '#ajax' => array(
      'callback' => '_nexteuropa_nexteuropa_newsroom_newsletter_subscription_form_ajax',
    ),
  );

  $form['submit_email_submit'] = array(
    '#markup' => '</div>',
  );

  $form['service_id'] = array(
    '#type' => 'hidden',
    '#value' => $args['tid'],
  );

  $form['previous'] = array(
    '#markup' => '<div class="linkPreviousIssues"><a href="' . NewsroomHelper::getNewsroomUrl('newsletter-specific-archive.cfm?serviceId=' . $args['tid']) . '">' . t('Previous issues') . '</a></div>',
  );

  return $form;
}

/**
 * Sends request to unsubscribe user.
 *
 * @param string $url
 *   Service URL.
 * @param string $email
 *   User email.
 *
 * @return string
 *   Object decoded from JSON.
 */
function _nexteuropa_newsroom_send_unsubscription_request($url, $email) {
  $input = array(
    'key' => NewsroomHelper::getEmailHash($email),
    'app' => variable_get('newsroom_app'),
  );
  $request = drupal_http_request($url . '&' . drupal_http_build_query($input));
  return isset($request->data) ? drupal_json_decode($request->data) : NULL;
}

/**
 * Sends request to the newsroom subscription script.
 *
 * @param string $url
 *   Service URL.
 * @param int $service_id
 *   ID.
 *   Service ID.
 * @param string $email
 *   User email.
 *
 * @return string
 *   Object decoded from JSON.
 */
function _nexteuropa_newsroom_send_subscription_request($url, $service_id, $email) {
  $input = array(
    'service_id' => $service_id,
    'email' => $email,
    'response_type' => 'json',
  );
  $request = drupal_http_request($url . '?' . drupal_http_build_query($input));
  if (isset($request->data)) {
    $data = drupal_json_decode($request->data);
  }

  return isset($data['subscription']) ? $data['subscription'] : NULL;
}

/**
 * Newsletter subscription form ajax callback.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Ajax callback array.
 */
function _nexteuropa_nexteuropa_newsroom_newsletter_subscription_form_ajax($form, &$form_state) {

  $form_id = $form['#form_id'];
  $selector = '#' . str_replace('_', '-', $form_id);

  $subscription = _nexteuropa_newsroom_send_subscription_request($form['#action'], $form_state['input']['service_id'], $form_state['input']['email']);

  if ($subscription['status'] == 'Failed') {
    form_set_error('email', $subscription['feedbackMessage']);
    $commands[] = ajax_command_invoke($selector . ' #edit-email', 'addClass', array('error'));
  }
  else {
    $type = ($subscription['isNewUser'] === 'False' && $subscription['isNewSubscription'] === 'False') ? 'warning' : 'status';
    drupal_set_message($subscription['feedbackMessage'], $type);
    $commands[] = ajax_command_invoke($selector . ' #edit-email', 'removeClass', array('error'));
  }

  $replacement = theme_status_messages(array('display' => NULL));
  $commands[] = ajax_command_replace($selector . ' .feedback', '<div class="feedback">' . $replacement . '</div>');

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Gets form rendable array for filter on the agenda page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param string $view
 *   View type: schedule, month, week, day.
 * @param int $type_id
 *   Newsroom type ID.
 * @param int $topic_id
 *   Newsroom Topic ID.
 * @param string $current_date
 *   Current date.
 * @param array $result_topics
 *   Topics to filter out the option list.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_agenda_filter_form($form, &$form_state, $view, $type_id, $topic_id, $current_date, $result_topics) {
  $topic_options = NewsroomHelper::getNewsroomTopicOptions($result_topics);

  $form = array();
  $form['type_id'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => NewsroomHelper::getNewsroomTypeOptions(TRUE),
    '#default_value' => $type_id,
  );
  $form['topic_id'] = array(
    '#type' => 'select',
    '#title' => t('Topic'),
    '#options' => $topic_options,
    '#default_value' => $topic_id,
  );
  $form['current_date'] = array(
    '#type' => 'hidden',
    '#value' => $current_date,
  );
  $form['view'] = array(
    '#type' => 'hidden',
    '#value' => $view,
  );
  $form['button'] = array(
    '#type' => 'button',
    '#button_type' => 'button',
    '#ajax' => array(
      'callback' => '_nexteuropa_newsroom_agenda_ajax_form_submit',
    ),
    '#value' => t('Filter'),
  );

  return $form;
}

/**
 * Gets form rendable array for date fitler block on the newsroom page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_agenda_datepicker_form($form, &$form_state, $view, $type_id = NULL, $topic_id = NULL, $current_date = NULL) {
  $form = array();
  $form['current_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Current date'),
    '#default_value' => $current_date,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'd-m-Y',
    '#date_increment' => 1,
    '#date_year_range' => '-2:+2',
    '#ajax' => array(
      'callback' => '_nexteuropa_newsroom_agenda_ajax_form_submit',
    ),
  );

  $form['view'] = array(
    '#type' => 'hidden',
    '#value' => $view,
  );

  $form['type_id'] = array(
    '#type' => 'hidden',
    '#value' => $type_id,
  );

  $form['topic_id'] = array(
    '#type' => 'hidden',
    '#value' => $topic_id,
  );

  return $form;
}

/**
 * Ajax submit handler.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Ajax callback array.
 */
function _nexteuropa_newsroom_agenda_ajax_form_submit(&$form, &$form_state) {

  $view = isset($form_state['input']['view']) ? $form_state['input']['view'] : NULL;

  if (isset($form_state['input']['current_date']['date'])) {
    $date = $form_state['input']['current_date']['date'];
  }
  elseif (isset($form_state['input']['current_date'])) {
    $date = $form_state['input']['current_date'];
  }
  else {
    $date = NewsroomHelper::getFormatedDate();
  }

  $topic_id = isset($form_state['input']['topic_id']) ? $form_state['input']['topic_id'] : NULL;
  $type_id = isset($form_state['input']['type_id']) ? $form_state['input']['type_id'] : NULL;

  $topic = NewsroomHelper::getNewsroomTopic($topic_id);
  $type = NewsroomHelper::getNewsroomType($type_id);
  $builder = new NewsroomBuilder();
  $agenda = $builder->buildAgenda($view, $type, $topic, new DateTime($date));

  ctools_include('ajax');
  $commands[] = ctools_ajax_command_redirect($agenda->getNavigationUrl($agenda->getCurrentDate()));

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Gets form rendable array for subscription button on newsletter page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param int $service_id
 *   Newsletter subscription service ID.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_subscription_newsletter_form($form, $form_state, $service_id = NULL) {
  global $user;

  $form['#action'] = NewsroomHelper::getNewsroomUrl('subscription-quick-generic.cfm');
  $form['email'] = array(
    '#title' => t('E-mail'),
    '#type' => 'hidden',
    '#value' => user_is_logged_in() ? $user->mail : NULL,
    '#required' => TRUE,
  );

  $form['service_id'] = array(
    '#type' => 'hidden',
    '#value' => $service_id,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => '_nexteuropa_nexteuropa_newsletter_subscription_form_ajax',
    ),
    '#value' => t('Subscribe'),
  );

  $form['submit-response'] = array(
    '#markup' => '<div class="submit-response"></div>',
  );

  return $form;
}

/**
 * Gets form rendable array for unsubscription button on newsletter page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param string $url
 *   Unsubscription URL.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_unsubscription_newsletter_form($form, $form_state, $url = NULL) {
  global $user;
  $form['#action'] = $url;
  $form['email'] = array(
    '#title' => t('E-mail'),
    '#type' => 'hidden',
    '#value' => user_is_logged_in() ? $user->mail : NULL,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => '_nexteuropa_nexteuropa_newsletter_unsubscription_form_ajax',
    ),
    '#value' => t('Unsubscribe'),
  );

  $form['submit-response'] = array(
    '#markup' => '<div class="submit-response"></div>',
  );

  return $form;
}

/**
 * Newsletter subscription form ajax callback.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Ajax callback array.
 */
function _nexteuropa_nexteuropa_newsletter_subscription_form_ajax($form, &$form_state) {
  $subscription = _nexteuropa_newsroom_send_subscription_request($form['#action'], $form_state['input']['service_id'], $form_state['input']['email']);
  $message = $subscription['feedbackMessage'];
  if ($subscription['status'] == 'Failed') {
    $type = 'error';
  }
  else {
    if ($subscription['isNewUser'] === 'False' && $subscription['isNewSubscription'] === 'False') {
      $type = 'warning';
    }
    else {
      $message = t('You successfully subscribed to this newsletter');
      $type = 'status';
    }
  }

  drupal_set_message($message, $type);
  $replacement = theme_status_messages(array('display' => NULL));
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' .submit-response', '<div class="submit-response">' . $replacement . '</div>');
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' input', '');

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Newsletter unsubscription form ajax callback.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Ajax callback array.
 */
function _nexteuropa_nexteuropa_newsletter_unsubscription_form_ajax($form, &$form_state) {
  $subscription = _nexteuropa_newsroom_send_unsubscription_request($form['#action'], $form_state['input']['email']);

  if ($subscription && $subscription['SUCCESS'] == 1) {
    $text = t('You successfully unsubscribed from this newsletter');
    $type = 'status';
  }
  else {
    $text = t('An error has happened during unsubscription process');
    $type = 'error';
  }

  drupal_set_message($text, $type);
  $replacement = theme_status_messages(array('display' => NULL));
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' .submit-response', '<div class="submit-response">' . $replacement . '</div>');
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' input', '');

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * The batch operation.
 *
 * @param array $chunk
 *   The terms to be updated.
 * @param string $voc
 *   Vocabulary's machine name.
 * @param array $operation_details
 *   Array of values.
 */
function nexteuropa_newsroom_restore_batch(array $chunk, $voc, array $operation_details) {
  $def_lang = language_default()->language;

  // Get the id coming from the newsroom.
  $id = _nexteuropa_newsroom_get_ids($voc, $form['#term']);
  // The name of the variable contains the id.
  $name = $voc . '_backup';
  $backup = variable_get($name, array());

  foreach ($chunk as $id => $fields) {
    // Try to find the corresponding term basing on its ID.
    $term = _nexteuropa_newsroom_get_term_from_id($id, $voc);

    if ($term) {
      $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
      // Let's work with an array.
      $term = get_object_vars($term);

      if (!empty($fields)) {
        // Override values.
        foreach ($fields as $field_name => $values) {
          switch ($field_name) {
            case 'field_newsroom_topic':
              for ($i = 0; $i < count($fields); $i++) {
                $term_wrapper->{$field_name}[] = $values[$i];
              }
              break;

            default:
              $term_wrapper->{$field_name}->set($values[0]);
          }
        }

        if (isset($context)) {
          // Build the worked term name list.
          $context['results'][] .= $conf['name'] . ', ';
          $context['message'] = t('Restoring "@title" @operations', array(
            '@title' => $term['name'],
            '@operations' => $operation_details,
          ));
        }

        $term_wrapper->save();
      }
    }
  }
}

/**
 * Backups config form submit handler.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function nexteuropa_newsroom_backup_conf_all($form, &$form_state) {

  $voc = $form['#vocabulary']->machine_name;
  // We need the whole tree here.
  $tree = taxonomy_get_tree($form['#vocabulary']->vid, 0, NULL, TRUE);

  foreach ($tree as $term) {
    $id = _nexteuropa_newsroom_get_ids($voc, (array) $term);

    // Working with arrays.
    $term = _nexteuropa_newsroom_export_prepare_values($term);
    $term = reset($term);
    $values[$id] = $term;
  }

  // Save the variable.
  variable_set($voc . '_backup', $values);

  // Set a message to the user.
  drupal_set_message(t('We saved a backup of your configuration for the vocabulary: "@name". if you need to restore the values in the backup click on the "Restore" button', array('@name' => $voc)), 'status');
}

/**
 * Gets newsroom id values.
 *
 * @param string $voc
 *   Vocabulary name.
 * @param array $data
 *   Taxonomy term.
 *
 * @return int
 *   Newsroom ID.
 */
function _nexteuropa_newsroom_get_ids($voc, $data) {

  switch ($voc) {
    case NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY:
      $id = $data['field_newsroom_type_id'][LANGUAGE_NONE][0]['value'];
      break;

    case NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY:
      $id = $data['field_newsroom_service_id'][LANGUAGE_NONE][0]['value'];
      break;

    case NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY:
      $id = $data['field_newsroom_topic_id'][LANGUAGE_NONE][0]['value'];
      break;
  }
  return $id;
}

/**
 * Grabs the newsroom fields from a term.
 *
 * @param object $term
 *   The term to get the values from.
 *
 * @return array
 *   Formatted values for the newsroom related fields.
 */
function _nexteuropa_newsroom_export_prepare_values($term) {
  $term_array = get_object_vars($term);
  $voc = $term->vocabulary_machine_name;
  $id = _nexteuropa_newsroom_get_ids($voc, $term_array);
  $values = array();
  $values[$id] = array();
  $voc = str_replace('_item', '', $voc);

  foreach ($term_array as $propname => $prop) {
    // Should work only with custom fields.
    if (strpos($propname, 'field') === 0) {
      if ($propname == 'field_' . $voc . '_id') {
        continue;
      }

      $check_value = field_get_items('taxonomy_term', $term, $propname);

      if (!empty($check_value)) {
        foreach ($check_value as $value) {
          if (!empty($value['value'])) {
            $values[$id][$propname][] = $value['value'];
          }
          elseif (!empty($value['tid'])) {
            $values[$id][$propname][] = $value['tid'];
          }
          elseif (!empty($value['target_id'])) {
            $values[$id][$propname][] = $value['target_id'];
          }
        }
      }
    }
  }

  return $values;
}

/**
 * Finds a term basing on its newsroom id.
 *
 * @param string $id
 *   The id coming from the newsroom.
 * @param string $voc
 *   Vocabulay's machine name.
 *
 * @return object
 *   The term object.
 */
function _nexteuropa_newsroom_get_term_from_id($id, $voc) {

  $field = str_replace('_item', '', $voc);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', $voc)
    ->fieldCondition('field_' . $field . '_id', 'value', $id, '=');

  $results = $query->execute();

  if (!empty($results)) {
    $result = reset($results['taxonomy_term']);
    $tid = $result->tid;
    $term = taxonomy_term_load($tid);
  }
  else {
    $term = FALSE;
  }
  return $term;
}

/**
 * Gets form rendable array for filter on the newsroom page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param object|null $type
 *   Newsroom type.
 * @param object|null $topic
 *   Newsroom Topic.
 * @param string $start_date
 *   Start date.
 * @param string $end_date
 *   End date.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_newsroom_page_filter_form($form, &$form_state, $type = NULL, $topic = NULL, $start_date = NULL, $end_date = NULL) {
  $topic_options = NewsroomHelper::getNewsroomTopicOptions(NewsroomHelper::getPageUsedTopicsIds());

  $form = array();
  $form['type_id'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => NewsroomHelper::getNewsroomTypeOptions(),
    '#default_value' => $type ? $type->tid : NULL,
  );
  $form['topic_id'] = array(
    '#type' => 'select',
    '#title' => t('Topic'),
    '#options' => $topic_options,
    '#default_value' => $topic ? $topic->tid : NULL,
  );
  $form['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('From date'),
    '#default_value' => $start_date ? $start_date->format('Y-m-d') : NULL,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'd-m-Y',
    '#date_increment' => 1,
    '#date_year_range' => '-2:+2',
    '#element_validate' => NULL,
  );
  $form['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('To date'),
    '#default_value' => $end_date ? $end_date->format('Y-m-d') : NULL,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'd-m-Y',
    '#date_increment' => 1,
    '#date_year_range' => '-2:+2',
    '#element_validate' => NULL,
  );
  $form['button'] = array(
    '#type' => 'submit',
    '#submit' => array('nexteuropa_newsroom_newsroom_page_filter_form_submit'),
    '#validate' => array('_nexteuropa_newsroom_validate_date'),
    '#button_type' => 'button',
    '#value' => t('Filter'),
  );

  return $form;
}

/**
 * Submit handler.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function nexteuropa_newsroom_newsroom_page_filter_form_submit(&$form, &$form_state) {
  $topic_id = isset($form_state['input']['topic_id']) ? $form_state['input']['topic_id'] : NULL;
  $type_id = isset($form_state['input']['type_id']) ? $form_state['input']['type_id'] : NULL;
  $start_date = isset($form_state['input']['start_date']['date']) ? $form_state['input']['start_date']['date'] : NULL;
  $end_date = isset($form_state['input']['end_date']['date']) ? $form_state['input']['end_date']['date'] : NULL;
  $topic = NewsroomHelper::getNewsroomTopic($topic_id);
  $type = NewsroomHelper::getNewsroomType($type_id);
  $builder = new NewsroomBuilder();
  $newsroom_page = $builder->buildNewsroomPage($type, $topic, $start_date, $end_date);
  // Redirect user to prepared URL.
  drupal_goto($newsroom_page->getNavigationUrl(), array(), 301);
}

/**
 * Validation handler for date fields.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_validate_date(&$form, &$form_state) {

  $start_date = NULL;
  $end_date = NULL;
  $regex = '/^\d{4}-\d{2}-\d{2}$/';

  if (!empty($form_state['values']['start_date']) && is_string($form_state['values']['start_date'])) {
    if (!$start_date = NewsroomHelper::checkDateFormat($form_state['values']['start_date'], $regex)) {
      form_set_error('start_date', t('The wrond date format.'));
    }
  }

  if (!empty($form_state['values']['end_date']) && is_string($form_state['values']['end_date'])) {
    if (!$end_date = NewsroomHelper::checkDateFormat($form_state['values']['end_date'], $regex)) {
      form_set_error('end_date', t('The wrond date format.'));
    }
  }

  if ($start_date && $end_date &&  $start_date > $end_date) {
    form_set_error('end_date', t('The wrong date range.'));
  }
}
