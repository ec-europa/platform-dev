<?php
/**
 * @file
 * Code specific to customization for the change tracking management.
 */

/**
 * Field widget form alter callback.
 *
 * It injects a specific validate callback in charge of scanning field value.
 *
 * @see nexteuropa_trackedchanges_field_widget_text_textarea_form_alter()
 * @see nexteuropa_trackedchanges_field_widget_text_textarea_with_summary_form_alter()
 * @see nexteuropa_trackedchanges_field_widget_text_textfield_form_alter()
 */
function _nexteuropa_trackedchanges_field_widget_tracking_form_alter(&$element, &$form_state, $context) {
  if (isset($element['#entity'])) {
    $entity = $element['#entity'];
    // Workaround for entities that do not use "entity_load" correctly
    // like "comment".
    if (!isset($entity->entity_type) && isset($element['#entity_type'])) {
      $entity->entity_type = $element['#entity_type'];
    }

    if ($entity->entity_type != 'node') {
      // Only nodes are supported.
      return;
    }

    $tracking_settings = _nexteuropa_trackedchanges_wysiwyg_tracking_settings($entity);
    if ($tracking_settings['is_activate']) {
      $instance_settings = $context['instance']['settings'];
      if (isset($instance_settings['text_processing']) && $instance_settings['text_processing']) {
        // Tracking change is only possible on fields on which
        // a text format can be set.
        $element['#element_validate'][] = '_nexteuropa_trackedchanges_tracking_field_validate';
      }
    }
  }
}

/**
 * Flags the entity if it or its translations contain tracked changes.
 *
 * The check on translations is only done if entity translations are
 * managed by "Entity translation".
 *
 * @param object $entity
 *   Entity to treat.
 * @param string $type
 *   Entity type.
 *
 * @return array
 *   An associative array containing all languages where tracked changes
 *   have been detected; otherwise it returns an empty array.
 *
 * @throws EntityMalformedException
 *   If the entity bundle is not set.
 */
function _nexteuropa_trackedchanges_set_tracking_flags($entity, $type = 'node') {
  // Tracking changes are only present n the following "field widget types".
  $screened_field_types = array(
    'text_textarea',
    'text_textarea_with_summary',
    'text_textfield',
  );
  // Prepare the future when it will be extended to other entity.
  list(,, $bundle) = entity_extract_ids($type, $entity);
  $entity_language = entity_language($type, $entity);

  $tracking_activate = array();

  // Content translation case.
  $available_transl_langs = array($entity_language);
  if (isset($entity->translations)) {
    // Entity translation case.
    $available_transl = $entity->translations;
    $available_transl_langs = array_keys($available_transl->data);
  }

  $ent_field_instances = field_info_instances($type, $bundle);
  // Note: special field types like field collection or paragraphs
  // are not supported yet.
  foreach ($ent_field_instances as $field_name => $ent_field_instance) {
    $field_info = field_info_field($field_name);
    $widget_type = $ent_field_instance['widget']['type'];
    // To cover the case where a field is not translatable while
    // the entity is.
    $field_languages = array(LANGUAGE_NONE);
    if ($field_info['translatable'] && $available_transl_langs) {
      $field_languages = $available_transl_langs;
    }
    // Detecting tracked changes in entity by screening fields.
    if (in_array($widget_type, $screened_field_types)) {
      if ($ent_field_instance['settings']['text_processing']) {
        foreach ($field_languages as $translation_lang) {
          $values = field_get_items($type, $entity, $field_name, $translation_lang);
          if ($values) {
            foreach ($values as $value) {
              if (preg_match('/<span[^>]+class="[^"]*ice-[^>]+>/', $value['value'])) {
                $tracking_activate[$translation_lang] = $translation_lang;
              }
            }
          }
        }
      }
    }
  }

  return $tracking_activate;
}

/**
 * Entity validation callback.
 *
 * It checks if the submitted form contains tracking changes.
 * If not, it checks if the previous entity revision or translations
 * contained some.
 * Then, depending on settings, it blocks the form submitting.
 *
 * @param array $form
 *   Submitted form.
 * @param array $form_state
 *   Form state of the submitted form.
 */
function _nexteuropa_trackedchanges_tracking_entity_validate($form, &$form_state) {
  $values = $form_state['values'];

  // So far, we only support "node" entity type.
  if (isset($form_state['node'])) {
    $entity = $form_state['node'];

    $current_wbm_state = FALSE;
    if (isset($values['workbench_moderation_state_new'])) {
      $current_wbm_state = $values['workbench_moderation_state_new'];
    }

    // Get current entity language.
    $current_ent_lang = $values['language'];
    if (isset($form_state['entity_translation'])) {
      // Entity translation case.
      $current_ent_lang = $form_state['entity_translation']['form_langcode'];
    }
    $current_detected = (!empty($form_state['tracking_changes_detected'])) ? $form_state['tracking_changes_detected'] : array();

    // active_tracking_lang/inactive_tracking_lang: store the list of languages
    // for _nexteuropa_trackedchanges_tracking_entity_log uses.
    if ($current_detected) {
      $form_state['active_tracking_lang'] = $current_ent_lang;
    }
    else {
      $form_state['inactive_tracking_lang'] = $current_ent_lang;
    }

    $current_status = $values['status'];
    $tracking_to_check = _nexteuropa_trackedchanges_tracking_is_on($entity, $current_wbm_state, $current_status);

    if ($tracking_to_check) {
      $tracking_activate = _nexteuropa_trackedchanges_set_tracking_flags($entity);
      // Merge the tracked change scan in DB and the one on form values.
      if ($tracking_activate && !$current_detected) {
        unset($tracking_activate[$current_ent_lang]);
        // Unset because it is common to all translations;even the
        // current one.
        unset($tracking_activate[LANGUAGE_NONE]);
      }
      elseif ($current_detected) {
        $tracking_activate[$current_ent_lang] = $current_ent_lang;
      }

      // Treating other translation revisions.
      if ($tracking_activate) {
        $entity_message = _nexteuropa_trackedchanges_tracking_entity_message($tracking_activate, $entity);
        form_set_error('tracking_activate', $entity_message);
      }
    }

  }
}

/**
 * Submit callback for entity edit form.
 *
 * It is in charge of saving a netc_info if tracked
 * changes have been detected in one of its WYSIWYG fields.
 */
function _nexteuropa_trackedchanges_tracking_entity_log($form, &$form_state) {
  $node = $form_state['node'];
  if (!empty($node->nid)) {
    $node_wrapper = entity_metadata_wrapper('node', $node);
    $rel_entity_state = NEXTEUROPA_TRACKEDCHANGES_ENTITY_NO_STATE;
    $rel_entity_language = entity_language('node', $node);

    $values = $form_state['values'];
    if (isset($values['workbench_moderation_state_new'])) {
      $rel_entity_state = $values['workbench_moderation_state_new'];
    }

    $info_entities = nexteuropa_trackedchanges_info_load_by_entity('node', $node);
    $stored_langs = array();
    if ($info_entities) {
      $info_entity = reset($info_entities);
      $wrapper = entity_metadata_wrapper('netc_info', $info_entity);
      $stored_langs = $wrapper->field_netc_info_languages->value();
    }

    $active_tracking_lang = (isset($form_state['active_tracking_lang'])) ? $form_state['active_tracking_lang'] : FALSE;

    if ($active_tracking_lang) {
      if (!isset($info_entity)) {
        $values = array(
          'rel_entity_type' => 'node',
          'rel_entity_id' => $node->nid,
          'rel_entity_bundle' => $node->type,
        );
        $info_entity = entity_create('netc_info', $values);
        $wrapper = entity_metadata_wrapper('netc_info', $info_entity);
      }

      $wrapper->rel_entity_label->set($node_wrapper->label());
      $wrapper->rel_entity_state->set($rel_entity_state);
      $wrapper->rel_entity_language->set($rel_entity_language);

      $node_uri = entity_uri('node', $node);
      $wrapper->rel_entity_path->set($node_uri['path']);

      // If the array contains "und" while the current lang is not "und",
      // we unset it because an entity cannot be "und" and in the same time
      // having a language set.
      $key = array_search(LANGUAGE_NONE, $stored_langs);
      if (($key !== FALSE) && ($active_tracking_lang != LANGUAGE_NONE)) {
        unset($stored_langs[$key]);
      }

      // We add the language if not set yet.
      $key = array_search($active_tracking_lang, $stored_langs);
      if ($key === FALSE) {
        $stored_langs[] = $active_tracking_lang;
      }

      $wrapper->field_netc_info_languages = array_values($stored_langs);
      $wrapper->save();
    }
    elseif ($info_entities) {
      $inactive_tracking_lang = $form_state['inactive_tracking_lang'];
      $key = array_search($inactive_tracking_lang, $stored_langs);
      if ($key !== FALSE) {
        unset($stored_langs[$key]);
        if ($stored_langs) {
          $wrapper->field_netc_info_languages->set(array_values($stored_langs));
          $wrapper->rel_entity_label->set($node->title);
          $wrapper->rel_entity_state->set($rel_entity_state);
          $wrapper->rel_entity_language->set($rel_entity_language);
          $wrapper->save();
        }
        else {
          $wrapper = entity_metadata_wrapper('netc_info', $info_entity);
          $wrapper->delete();
        }
      }
    }
  }
}

/**
 * Node validation callback.
 *
 * It checks if the node or one of these translations contains tracking changes.
 * Then, depending on settings, it blocks the form submitting.
 *
 * @param array $form
 *   Submitted form.
 * @param array $form_state
 *   Form state of the submitted form.
 *
 * @see nexteuropa_trackedchanges_form_workbench_moderation_moderate_form_alter()
 */
function _nexteuropa_trackedchanges_tracking_wbm_validate($form, &$form_state) {
  $values = $form_state['values'];
  $entity = $values['node'];
  $current_wbm_state = $values['state'];
  $tracking_to_check = _nexteuropa_trackedchanges_tracking_is_on($entity, $current_wbm_state);
  // Generates errors only if required by WYSIWYG tracking workflow settings.
  if ($tracking_to_check) {
    $tracking_activate = _nexteuropa_trackedchanges_set_tracking_flags($entity);

    // Treating other translation revisions.
    if ($tracking_activate) {
      $entity_message = _nexteuropa_trackedchanges_tracking_entity_message($tracking_activate, $entity);
      form_set_error('tracking_activate', $entity_message);
    }
  }
}

/**
 * A "Text" field validation callback.
 *
 * It checks if the field value contains tracked changes.
 * If it contains ones, it stores the field name in the form_state.
 * It will be used during the entity validation.
 *
 * @param array $element
 *   Field element that has been edited.
 * @param array $form_state
 *   Form_state related to the submitted form.
 * @param array $form
 *   Submitted form.
 *
 * @see _nexteuropa_trackedchanges_tracking_entity_validate()
 */
function _nexteuropa_trackedchanges_tracking_field_validate($element, &$form_state, $form) {
  $entity = $element['#entity'];
  $values = $form_state['values'];

  $current_wbm_state = FALSE;
  if (isset($values['workbench_moderation_state_new'])) {
    $current_wbm_state = $form_state['values']['workbench_moderation_state_new'];
  }

  $current_status = $values['status'];

  $value = '';
  if (isset($element['#value'])) {
    $value = $element['#value'];
  }
  elseif (isset($element['value'])) {
    // The callback is called twice for field with text format.
    // In this case, the inserted value is stored differently.
    $value = $element['value']['#value'];
    $element = $element['value'];
  }

  $field_path = implode('][', $element['#parents']);
  unset($form_state['tracking_changes_detected'][$field_path]);
  // We still need to scan because we need this data for
  // _nexteuropa_trackedchanges_tracking_entity_log uses.
  if (preg_match('/<span[^>]+class="[^"]*ice-[^>]+>/', $value)) {
    // Flag used in entity validate callback.
    $form_state['tracking_changes_detected'][$field_path] = TRUE;

    // Get the field label.
    $title = $element['#title'];
    if (empty($element['#title'])) {
      // Multi value fields have an empty '#title'.
      $info = field_info_instance($entity->entity_type, $element['#field_name'], $element['#bundle']);
      $title = check_plain($info['label']);
    }

    // Only raise the error if the validation control is on on the entity.
    $is_to_check = _nexteuropa_trackedchanges_tracking_is_on($entity, $current_wbm_state, $current_status);
    if ($is_to_check) {
      $message = t('!title contains tracked changes information.',
        array('!title' => $title));
      form_error($element, $message);
    }
  }
}

/**
 * Gets the entity level error message for tracked changes are detected.
 *
 * @param array $tracking_lang
 *   List of languages where tracked changes are detected.
 * @param object $entity
 *   The entity for which the message is required.
 *
 * @return string
 *   Message to display
 *
 * @see _nexteuropa_trackedchanges_tracking_entity_validate()
 */
function _nexteuropa_trackedchanges_tracking_entity_message($tracking_lang, $entity) {

  $lang_related = _nexteuropa_trackedchanges_tracking_message_for_languages($tracking_lang);
  $state_related = _nexteuropa_trackedchanges_tracking_message_for_wbm_states($entity);

  return $lang_related . ' ' . $state_related;

}

/**
 * Gets error message related to languages where tracked changes are detected.
 *
 * It is used by tracking change validation process.
 *
 * @param array $tracking_lang
 *   The language list for which tracked changes are detected.
 *
 * @return string
 *   The error message
 *
 * @see _nexteuropa_trackedchanges_tracking_entity_message()
 */
function _nexteuropa_trackedchanges_tracking_message_for_languages($tracking_lang) {
  // LANGUAGE_NONE means all languages and then the current one too.
  unset($tracking_lang[LANGUAGE_NONE]);

  $count = count($tracking_lang);
  switch ($count) {
    case 0:
      // LANGUAGE_NONE case.
      return t('Tracked changes detected in this revision.');

    case 1:
      $implied_lang = end($tracking_lang);
      $lang_name = locale_language_name($implied_lang);
      $message_param = array('@lang' => $lang_name);
      return t('Tracked changes detected in the @lang version.',
        $message_param);

    default:
      $language_names = array();
      foreach ($tracking_lang as $lang) {
        $language_names[$lang] = locale_language_name($lang);
      }
      $message_param = array('@lang' => implode(', ', $language_names));
      return t('Tracked changes detected in the @lang versions.',
        $message_param);
  }
}

/**
 * Gets error message related to Workbench moderation states.
 *
 * It is used by tracking change validation process.
 *
 * @param object $entity
 *   The entity for which errors have been detected.
 *
 * @return string
 *   The error message
 *
 * @see _nexteuropa_trackedchanges_tracking_entity_message()
 */
function _nexteuropa_trackedchanges_tracking_message_for_wbm_states($entity) {
  $settings = _nexteuropa_trackedchanges_wysiwyg_tracking_settings($entity);
  $blocked_states = $settings['wbm_states'];

  if (!$blocked_states) {
    // If ok_state is empty, that means all state block the saving with
    // tracked changes.
    // If $blocked_states is empty, that means "check_entity_status" is true
    // and the node status is 1 as the process reaches this step.
    return t('Please reject or accept changes before saving the content');
  }

  // Retrieve state labels and using them into the message.
  $state_labels = workbench_moderation_state_labels();

  $blocked_param = array();
  foreach ($blocked_states as $state) {
    $blocked_param[] = $state_labels[$state];
  }
  $message_param = array(
    '@blocked' => implode(' or ', $blocked_param),
  );

  return t('Please reject or accept changes before setting the state to 
  @blocked.', $message_param);
}

/**
 * Checks if the change tracking must be tested on given entity.
 *
 * @param object $entity
 *   Entity to check.
 * @param bool|FALSE $current_wbm_state
 *   Submitted entity workbench moderation state (node only).
 * @param bool|FALSE $current_status
 *   Submitted entity current status (node without workbench moderation only).
 *
 * @return bool
 *   TRUE if it needs to be tested; otherwise FALSE.
 */
function _nexteuropa_trackedchanges_tracking_is_on($entity, $current_wbm_state = FALSE, $current_status = FALSE) {
  $type = $entity->entity_type;
  // So far, only nodes are support.
  if ($type == 'node') {
    // Prepared for other entities if needed.
    list($id) = entity_extract_ids($type, $entity);
    $cached_settings = &drupal_static(__FUNCTION__ . '_' . $type . '_' . $id);
    if (empty($cached_settings)) {
      $settings = _nexteuropa_trackedchanges_wysiwyg_tracking_settings($entity);
      if ($settings['is_activate']) {
        if (in_array($current_wbm_state, $settings['wbm_states'])) {
          $cached_settings = TRUE;
        }
        elseif ($settings['check_entity_status'] && !$current_wbm_state) {
          $cached_settings = $current_status;
        }
      }
    }

    return $cached_settings;
  }

  return FALSE;
}

/**
 * Get the WYSIWYG tracking workflow settings for the entity.
 *
 * @param object $entity
 *   Entity from which retrieving settings.
 *
 * @return array
 *   An associative array containing:
 *   - is_activate: flag indicating if controls are active about change
 *       tracking.
 *   - check_entity_status: flag indicating if savings just with entity status
 *      should be blocked if tracked changes information exist.
 *   - wbm_states: (only node) it gives the list of state to take into account.
 */
function _nexteuropa_trackedchanges_wysiwyg_tracking_settings($entity = NULL) {
  if ($entity && isset($entity->entity_type)) {
    $type = $entity->entity_type;
    $cached_settings = &drupal_static(__FUNCTION__ . '_' . $type);

    // So far, only nodes are supported.
    if (empty($cached_settings) && ($type == 'node')) {
      $status = variable_get('nexteuropa_trackedchanges_tracking_status');
      $states = variable_get('nexteuropa_trackedchanges_tracking_wbm_states', array());
      $states_to_check = array_filter($states);
      $cached_settings = array(
        'is_activate' => TRUE,
        'check_entity_status' => $status,
        'wbm_states' => $states_to_check,
      );
    }
    return $cached_settings;
  }

  return array(
    'is_activate' => FALSE,
    'check_entity_status' => FALSE,
    'wbm_states' => array(),
  );
}

/**
 * Removes the "ckeditor_lite" post render callback.
 *
 * It is replaced by one matching platform needs.
 *
 * @param array $build
 *   Entity view build.
 *
 * @see nexteuropa_trackedchanges_entity_view_alter()
 */
function _nexteuropa_trackedchanges_ckeditor_lite_view_alter(&$build, $type) {
  if ($type == 'node' &&  user_access('ckeditor_lite highlight changes')) {
    // Only applicable on node., other entity does not have the same workflow.
    // If the user does not have the permission, we leave ckeditor_lite
    // working normally.
    if (isset($build['#post_render'])) {
      $key = array_search('_ckeditor_lite_entity_post_render', $build['#post_render']);
      if ($key !== FALSE) {
        unset($build['#post_render'][$key]);
        $build['#post_render'][] = '_nexteuropa_trackedchanges_ckeditor_lite_entity_post_render';

        // Add the ckeditor_lite.js in order to use "highlighting" css classes.
        $path = drupal_get_path('module', 'ckeditor_lite');
        isset($build['#attached']) ?: $build['#attached'] = array();
        isset($build['#attached']['css']) ?: $build['#attached']['css'] = array();
        $build['#attached']['css'][] = array('data' => $path . '/css/ckeditor_lite.css', 'type' => 'file');
      }
    }
  }
}

/**
 * Post render callback forcing the presence of the required ckeditor_lite css.
 */
function _nexteuropa_trackedchanges_ckeditor_lite_entity_post_render($output, $element) {
  // First we check if change tracking exist.
  if (preg_match('/<span[^>]+class="[^"]*ice-[^>]+>/', $output)) {
    // We only support node here.
    $node = $element['#node'];
    $bundle = node_type_get_name($node);
    $settings = _nexteuropa_trackedchanges_wysiwyg_tracking_settings($node);

    // Set the warning message,depending on settings.
    $message = t('<strong>The change tracking is activated</strong> on some fields of this "@type" content.',
      array('@type' => $bundle));
    if ($settings['is_activate']) {
      $message = t('<strong>The change tracking was activated</strong> on some fields of this "@type" content
       before the control process was activated.<br />
       <small>Please accept or reject tracked changes in order to avoid bad content display.</small>',
        array('@type' => $bundle));

      $use_draft_message = TRUE;
      if (isset($node->workbench_moderation) && isset($node->workbench_moderation['published'])) {
        $wbm_published_vid = $node->workbench_moderation['published']->vid;
        $use_draft_message = ($wbm_published_vid != $node->vid);
      }
      if ($settings['wbm_states'] && $use_draft_message) {
        // Only if the published version is not displayed.
        $params = array(
          '@type' => $bundle,
          '@states' => implode(' or ', $settings['wbm_states']),
        );
        $message = t('<strong>The change tracking is activated</strong> on some fields of this "@type" content.<br />
          <small>Please accept or reject tracked changes before setting the content state to @states.</small>',
          $params);
      }
      elseif ($settings['check_entity_status'] && (!$node->status)) {
        $message = t('<strong>The change tracking is activated</strong> on some fields of this "@type" content.<br />
          <small>Please accept or reject tracked changes before publishing it.</small>',
          array('@type' => $bundle));
      }
    }
    drupal_set_message($message, 'warning');

    // Injecting css classes required to highlight tracked changes.
    $pattern = array(
      // Activate Highlighting - div with node-page class.
      '/( class="[^"]*node) (.+")/',
      // Tracked inserts - spans with "ice-ins" class.
      '/( class="[^"]*ice-ins) (.+")/',
      // Tracked deletes  spans with "ice-del" class.
      '/( class="[^"]*ice-del) (.+")/',
    );
    $replacement = array(
      // Activate Highlighting - div with node-page class.
      '$1 ICE-Tracking $2',
      // Tracked inserts - spans with "ice-ins" class.
      '$1 ckeditor-lite-ins $2',
      // Tracked deletes  spans with "ice-del" class.
      '$1 ckeditor-lite-del-inv $2',
    );
    $output = preg_replace($pattern, $replacement, $output);
  }
  return $output;
}

/**
 * Add all buttons related to CKEditor Lite in the WYSIWYG profile.
 *
 * @param string $profile_name
 *   The machine name of the profile's text format.
 */
function nexteuropa_trackedchanges_enable_buttons($profile_name) {
  $lite_plugin_settings = array(
    'lite_AcceptAll',
    'lite_RejectAll',
    'lite_AcceptOne',
    'lite_RejectOne',
    'lite_ToggleShow',
    'lite_ToggleTracking',
  );
  multisite_config_service('wysiwyg')->addButtonsToProfile(
    $profile_name,
    'lite',
    $lite_plugin_settings
  );
}

/**
 * Remove all buttons related to CKEditor Lite in the WYSIWYG profile.
 *
 * That has the same effect as deleting 'lite' settings from the profile.
 *
 * @param string $profile_name
 *   The machine name of the profile's text format.
 */
function nexteuropa_trackedchanges_disable_buttons($profile_name) {
  $profile = multisite_config_service('wysiwyg')->getProfile($profile_name);

  if (isset($profile->settings['buttons']['lite'])) {
    unset($profile->settings['buttons']['lite']);
  }

  multisite_config_service('wysiwyg')->updateProfile($profile);
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
      $wysiwyg_profiles['info'][$key]['cke_lite_status'] = TRUE;
    }
    else {
      $wysiwyg_profiles['info'][$key]['cke_lite_status'] = FALSE;
    }
  }

  // Removing profile which by default needs to have change tracking enabled.
  if (isset($wysiwyg_profiles['options'][NEXTEUROPA_TRACKEDCHANGES_FHT_MACHINE_NAME])) {
    unset($wysiwyg_profiles['options'][NEXTEUROPA_TRACKEDCHANGES_FHT_MACHINE_NAME]);
  }
  return $wysiwyg_profiles;
}

/**
 * Scan the field revision table for traccked changes.
 *
 * @param string $field_name
 *   The field machine name of the table to scan.
 * @param string $text_format
 *   The text format machine name on which the scan must focus.
 *
 * @return array|bool
 *   Array listing entity types and bundle for which tracked changes have
 *   been detected.
 */
function _nexteuropa_trackedchanges_check_field_revisions($field_name, $text_format = '') {
  // 2. Scan field revision table to see if tracked changes tag are present.
  // Because of Workbench moderation, field data table could not contain any
  // tags for node values while the draft revision (contained in the revision
  // tables could have.
  $query = db_select('field_revision_' . $field_name, 'fr');
  $query->where('fr.' . $field_name . '_value REGEXP \'<span[^>]+class="[^"]*ice-[^>]+>\'')
    ->condition('fr.deleted', 0);
  if ($text_format) {
    $query->condition('fr.' . $field_name . '_format', $text_format);
  }
  $query->fields('fr', array('entity_type', 'bundle'));
  $query->distinct(TRUE);

  $results = $query->execute()->fetchAll();

  if ($results) {
    $return = array();
    foreach ($results as $result) {
      $key = $field_name . '-' . $result->entity_type . '-' . $result->bundle;
      $result->field_name = $field_name;
      $return[$key] = $result;
    }

    return $return;
  }

  return FALSE;
}

/**
 * Get entities that have tracked changes in values for a specific field.
 *
 * @param string $field_name
 *    The field machine name to scan.
 * @param string $entity_type
 *    The type of entities to scan.
 * @param string $bundle
 *    The bundle of entities to scan.
 * @param string $text_format
 *   The text_format on which the scanning process needs to focus.
 *   If set, the process scans only values using this text format.
 *
 * @return array|bool
 *   Array of NETCInfo equivalent arrays;
 *   FALSE if not tracked changes have been detected.
 */
function _nexteuropa_trackedchanges_check_field_entities($field_name, $entity_type = 'node', $bundle = 'page', $text_format = '') {
  $return = array();

  switch ($entity_type) {
    case 'node':
      // 3.a.1 Check if workbench moderation is active for the node.
      // Check content published and "draft" versions.
      if (module_exists('workbench_moderation')) {
        if (workbench_moderation_node_type_moderated($bundle)) {
          $query = db_select('field_revision_' . $field_name, 'fr');
          $query->join('node', 'n', 'fr.entity_id = n.nid');
          $query->join('workbench_moderation_node_history', 'wmhn', 'fr.revision_id = wmhn.vid');
          $query->where('fr.' . $field_name . '_value REGEXP \'<span[^>]+class="[^"]*ice-[^>]+>\'')
            ->condition('wmhn.is_current', 1)
            ->condition('fr.bundle', $bundle);
          if ($text_format) {
            $query->condition('fr.' . $field_name . '_format', $text_format);
          }
          $query->fields('fr', array('language'))
            ->fields('n', array('nid'))
            ->fields('wmhn', array('state'));
          $query->addField('fr', $field_name . '_format', 'format');
          $query->distinct();
          $node_scans = $query->execute()->fetchAll();

          foreach ($node_scans as $node_scan) {
            $info = array(
              'rel_entity_type' => $entity_type,
              'rel_entity_bundle' => $bundle,
              'rel_entity_id' => $node_scan->nid,
              'rel_entity_state' => $node_scan->state,
              'rel_entity_language' => $node_scan->language,
            );

            $return[] = $info;
          }

          // Code executed below is useless as already checked here.
          // Then, break.
          break;
        }
      }

      // 3.a.2 Check other nodes on the field data table which is the current
      // version to take into account.
      $query = db_select('field_data_' . $field_name, 'fd');
      $query->join('node', 'n', 'fd.entity_id = n.nid');
      $query->condition('fr.bundle', $bundle)
        ->where('fd.' . $field_name . '_value REGEXP \'<span[^>]+class="[^"]*ice-[^>]+>\'');
      if ($text_format) {
        $query->condition('fd.' . $field_name . '_format', $text_format);
      }
      $query->fields('fd', array('language'))
        ->fields('n', array('nid'));
      $query->distinct();
      $node_scans = $query->execute()->fetchAll();

      foreach ($node_scans as $node_scan) {
        $info = array(
          'rel_entity_type' => $entity_type,
          'rel_entity_bundle' => $bundle,
          'rel_entity_id' => $node_scan->nid,
          'rel_entity_state' => FALSE,
          'rel_entity_language' => $node_scan->language,
        );

        $return[] = $info;
      }
      break;

    default:
      // 3.b. Get info on related entities.
      $query = db_select('field_data_' . $field_name, 'fd');
      $query->condition('fd.bundle', $bundle)
        ->where('fd.' . $field_name . '_value REGEXP \'<span[^>]+class="[^"]*ice-[^>]+>\'');
      if ($text_format) {
        $query->condition('fd.' . $field_name . '_format', $text_format);
      }
      $query->fields('fd', array('entity_id', 'language'));
      $query->distinct();
      $node_scans = $query->execute()->fetchAll();

      foreach ($node_scans as $entity_scan) {
        $info = array(
          'rel_entity_type' => $entity_type,
          'rel_entity_bundle' => $bundle,
          'rel_entity_id' => $entity_scan->entity_id,
          'rel_entity_state' => NEXTEUROPA_TRACKEDCHANGES_ENTITY_NO_STATE,
          'rel_entity_language' => $entity_scan->language,
        );

        $return[] = $info;
      }
      break;
  }

  return $return;
}

/**
 * Get machine name of potential WYSIWYG fields.
 *
 * These fields are of the following types: text_long, text, text_with_summary.
 *
 * @return array
 *    list of field machine names.
 *
 * @see field_info_field_map
 */
function _nexteuropa_trackedchanges_wysiwyg_fields_info() {
  $field_types = array(
    'text_long',
    'text_with_summary',
    'text',
  );
  $field_info_map = field_info_field_map();
  $filtered = array_filter($field_info_map, function ($item) use ($field_types) {
    return in_array($item['type'], $field_types);
  });

  return array_keys($filtered);
}

/**
 * Batch operation callback scanning field revision tables for tracked changes.
 *
 * @param string $wysiwyg_profile
 *    The machine name of the wysiwyg profile to take into account during the
 *    scanning.
 *
 * @see nexteuropa_trackedchanges_table_rebuilt()
 * @see nexteuropa_trackedchanges_disable_buttons()
 * @see _nexteuropa_trackedchanges_scanning_batch_set()
 */
function _nexteuropa_trackedchanges_revisions_scanning_process($wysiwyg_profile, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['results']['detected_entity_types'] = array();
    $context['sandbox']['field_list'] = _nexteuropa_trackedchanges_wysiwyg_fields_info();
    $context['sandbox']['max'] = count($context['sandbox']['field_list']);
    $context['results']['text_format'] = $wysiwyg_profile;
  }

  $field_name = array_shift($context['sandbox']['field_list']);
  $context['message'] = t("@field_name's revision table is scanned", array('@field_name' => $field_name));

  $scanning_results = _nexteuropa_trackedchanges_check_field_revisions($field_name, $wysiwyg_profile);

  if ($scanning_results) {
    $previous_detected_items = $context['results']['detected_entity_types'];
    $results = array_merge($previous_detected_items, $scanning_results);
    $context['results']['detected_entity_types'] = $results;
  }
  $context['sandbox']['progress']++;

  if (empty($context['sandbox']['field_list'])) {
    $context['finished'] = 1;
  }
  elseif ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch operation scanning field revision tables for tracked changes.
 *
 * @param string $wysiwyg_profile
 *    The machine name of the wysiwyg profile to take into account during the
 *    scanning.
 *
 * @see nexteuropa_trackedchanges_table_rebuilt()
 * @see nexteuropa_trackedchanges_disable_buttons()
 * @see _nexteuropa_trackedchanges_scanning_batch_set()
 */
function _nexteuropa_trackedchanges_entity_scanning_process($wysiwyg_profile, &$context) {
  if (!isset($context['sandbox']['detected_entity_types'])) {
    $context['sandbox']['progress'] = 0;
    $context['results']['detected_entities'] = array();
    $context['sandbox']['detected_entity_types'] = $context['results']['detected_entity_types'];
    $context['sandbox']['max'] = count($context['sandbox']['detected_entity_types']);
    $context['results']['text_format'] = $wysiwyg_profile;
  }

  $message['message'] = t('No scan to perform on entities.');
  if (!empty($context['sandbox']['detected_entity_types'])) {
    $field_entity_info = array_shift($context['sandbox']['detected_entity_types']);
    $field_name = $field_entity_info->field_name;
    $entity_type = $field_entity_info->entity_type;
    $bundle = $field_entity_info->bundle;
    $context['message'] = t("@field_name's entities are scanned", array('@field_name' => $field_name));

    $scanning_results = _nexteuropa_trackedchanges_check_field_entities($field_name, $entity_type, $bundle, $wysiwyg_profile);

    if ($scanning_results) {
      $previous_detected_items = $context['results']['detected_entities'];
      foreach ($scanning_results as $scanning_result) {
        $key = $scanning_result['rel_entity_type'] . '-' . $scanning_result['rel_entity_bundle'] . '-' . $scanning_result['rel_entity_id'];
        $scanned_language = $scanning_result['rel_entity_language'];

        if (isset($previous_detected_items[$key])) {
          // From _nexteuropa_trackedchanges_check_field_entities, we know there
          // is only one language in the "languages" array.
          if (!in_array($scanned_language, $previous_detected_items[$key]['field_netc_info_languages'])) {
            $previous_detected_items[$key]['field_netc_info_languages'][] = $scanned_language;
          }
        }
        else {
          $previous_detected_items[$key] = $scanning_result;
          $previous_detected_items[$key]['field_netc_info_languages'] = array($scanned_language);
        }
      }

      $context['results']['detected_entities'] = $previous_detected_items;
    }
  }
  $context['sandbox']['progress']++;

  if (empty($context['sandbox']['detected_entity_types'])) {
    $context['finished'] = 1;
  }
  elseif ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch operation saving info on entity in the DB.
 *
 * @param string $wysiwyg_profile
 *    The machine name of the wysiwyg profile to take into account during the
 *    scanning.
 *
 * @see nexteuropa_trackedchanges_table_rebuilt()
 * @see nexteuropa_trackedchanges_disable_buttons()
 * @see _nexteuropa_trackedchanges_scanning_batch_set()
 */
function _nexteuropa_trackedchanges_table_rebuilt_process($wysiwyg_profile, &$context) {
  if (!isset($context['sandbox']['saving_progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['saving_progress'] = 1;
    $context['sandbox']['detected_entities'] = $context['results']['detected_entities'];
    $context['sandbox']['max'] = count($context['sandbox']['detected_entities']);
    $context['results']['text_format'] = $wysiwyg_profile;
  }

  $message['message'] = t('No info related to detected tracked changes in any entities to save.');
  if (!empty($context['sandbox']['detected_entities'])) {
    $detected_entity = array_shift($context['sandbox']['detected_entities']);

    $t_args = array('@type' => $detected_entity['rel_entity_type'], '@id' => $detected_entity['rel_entity_id']);
    $context['message'] = t('Info on the "@type" entity with @id is saved', $t_args);

    $src_entities = entity_load($detected_entity['rel_entity_type'], array($detected_entity['rel_entity_id']));
    $src_entity = reset($src_entities);
    $src_wrapper = entity_metadata_wrapper($detected_entity['rel_entity_type'], $src_entity);

    $entities = nexteuropa_trackedchanges_info_load_by_entity($detected_entity['rel_entity_type'], $src_entity);

    if ($entities) {
      $entity = reset($entities);
    }
    else {
      $entity = entity_create('netc_info', $detected_entity);
    }
    $entity_wrapper = entity_metadata_wrapper('netc_info', $entity);
    $entity_wrapper->rel_entity_label->set($src_wrapper->label());
    $new_languages = array_values($detected_entity['field_netc_info_languages']);
    $src_entity_uri = entity_uri($detected_entity['rel_entity_type'], $src_entity);
    $entity_wrapper->rel_entity_path->set($src_entity_uri['path']);
    $entity_wrapper->rel_entity_state->set($detected_entity['rel_entity_state']);

    if ($context['results']['text_format']) {
      // If we take a profile into account, we only update the language list as
      // the entity (node, file ...) could have other WYSIWYG field using
      // another profile where the change tracking is activate.
      $persisted_values = $entity_wrapper->field_netc_info_languages->value();
      foreach ($new_languages as $new_language) {
        if (!in_array($new_language, $persisted_values)) {
          $persisted_values[] = $new_languages;
        }
      }
      $new_languages = $persisted_values;
    }
    $entity_wrapper->field_netc_info_languages->set($new_languages);

    $entity_wrapper->save();
  }
  $context['sandbox']['progress']++;

  if (empty($context['sandbox']['detected_entities'])) {
    $context['finished'] = 1;
    // Unlock the table and record the rebuild time.
    variable_set('nexteuropa_trackedchanges_rebuild_lock', 0);
    variable_set('nexteuropa_trackedchanges_last_rebuild_time', REQUEST_TIME);
  }
  elseif ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Check if the netc_info table must/can be rebuilt.
 *
 * @return bool
 *   True if it is possible/required; otherwise FALSE.
 */
function _nexteuropa_trackedchanges_table_rebuild() {
  $is_lock = variable_get('nexteuropa_trackedchanges_rebuild_lock');

  if ($is_lock) {
    return FALSE;
  }
  $rebuild_time = variable_get('nexteuropa_trackedchanges_last_rebuild_time');
  $frequency = variable_get('nexteuropa_trackedchanges_rebuild_elapse_time', 3600);
  if ($rebuild_time) {
    $now = REQUEST_TIME;
    $ellapse_time = ($now - $rebuild_time);
    return ($ellapse_time >= $frequency);
  }

  return TRUE;
}

/**
 * Truncate data related to 'netc_info' into the DB.
 */
function _nexteuropa_trackedchanges_clean_db() {
  db_truncate('netc_info')->execute();
  db_delete('field_revision_field_netc_info_languages')->condition('entity_type', 'netc_info')->execute();
  db_delete('field_data_field_netc_info_languages')->condition('entity_type', 'netc_info')->execute();
}

/**
 * Save a netc_info object on the basis of cron output.
 *
 * @param array $info_to_save
 *   Array containing data to save in the netc_info.
 *
 * @see nexteuropa_trackedchanges_cron()
 */
function _nexteuropa_trackedchanges_info_save($info_to_save) {

  if (!$info_to_save) {
    // If empty, then, it is the item indicating that the queue is done and
    // we can set the time and end the process.
    variable_set('nexteuropa_trackedchanges_last_rebuild_time', REQUEST_TIME);
    variable_set('nexteuropa_trackedchanges_rebuild_lock', 0);

    watchdog('nexteuropa_trackedchanges cron', 'Tracked change detected in non-node entities, logging ended.', array(), WATCHDOG_INFO);
    return;
  }

  $src_entities = entity_load($info_to_save['rel_entity_type'], array($info_to_save['rel_entity_id']));
  $src_entity = reset($src_entities);
  $src_wrapper = entity_metadata_wrapper($info_to_save['rel_entity_type'], $src_entity);

  $entities = nexteuropa_trackedchanges_info_load_by_entity($info_to_save['rel_entity_type'], $src_entity);

  if ($entities) {
    $entity = reset($entities);
  }
  else {
    $entity = entity_create('netc_info', $info_to_save);
  }

  $entity_wrapper = entity_metadata_wrapper('netc_info', $entity);

  $entity_wrapper->rel_entity_label->set($src_wrapper->label());

  $src_entity_uri = entity_uri($info_to_save['rel_entity_type'], $src_entity);
  $entity_wrapper->rel_entity_path->set($src_entity_uri['path']);

  $entity_wrapper->rel_entity_state->set($info_to_save['rel_entity_state']);

  $new_language = $info_to_save['rel_entity_language'];
  $persisted_values = $entity_wrapper->field_netc_info_languages->value();
  if (empty($persisted_values) || !in_array($new_language, $persisted_values)) {
    $persisted_values[] = $new_language;
  }
  $entity_wrapper->field_netc_info_languages->set($persisted_values);

  $entity_wrapper->save();

  watchdog('nexteuropa_trackedchanges cron',
    'Tracked change detected in @label saved.',
    array('@label' => $src_wrapper->label()), WATCHDOG_INFO);
}
