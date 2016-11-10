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
 * @see nexteuropa_editorial_field_widget_text_textarea_form_alter()
 * @see nexteuropa_editorial_field_widget_text_textarea_with_summary_form_alter()
 * @see nexteuropa_editorial_field_widget_text_textfield_form_alter()
 */
function _nexteuropa_editorial_field_widget_tracking_form_alter(&$element, &$form_state, $context) {
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

    $tracking_settings = _nexteuropa_editorial_wysiwyg_tracking_settings($entity);
    if ($tracking_settings['is_activate']) {
      $instance_settings = $context['instance']['settings'];
      if (isset($instance_settings['text_processing']) && $instance_settings['text_processing']) {
        // Tracking change is only possible on fields on which
        // a text format can be set.
        $element['#element_validate'][] = '_nexteuropa_editorial_tracking_field_validate';
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
 *   have been detected.
 *
 * @throws EntityMalformedException
 *   If the entity bundle is not set.
 */
function _nexteuropa_editorial_set_tracking_flags($entity, $type = 'node') {
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
function _nexteuropa_editorial_tracking_entity_validate($form, &$form_state) {
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

    $current_status = $values['status'];
    $tracking_to_check = _nexteuropa_editorial_tracking_is_on($entity, $current_wbm_state, $current_status);
    // Generates errors only if required by WYSIWYG tracking workflow settings.
    if ($tracking_to_check) {
      $tracking_activate = _nexteuropa_editorial_set_tracking_flags($entity);
      // Unset because current form could be emptied of its tracked changes.
      unset($tracking_activate[$current_ent_lang]);
      // Unset because it is common to all translations;even the current one.
      unset($tracking_activate[LANGUAGE_NONE]);

      // Treating current revision.
      if (isset($form_state['tracking_changes_detected']) && $form_state['tracking_changes_detected']) {
        // Ensure that an error message for the whole entity will be displayed.
        $tracking_activate[$current_ent_lang] = $current_ent_lang;
      }

      // Treating other translation revisions.
      if ($tracking_activate) {
        $entity_message = _nexteuropa_editorial_tracking_entity_message($tracking_activate, $entity);
        form_set_error('tracking_activate', $entity_message);
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
 * @see nexteuropa_editorial_form_workbench_moderation_moderate_form_alter()
 */
function _nexteuropa_editorial_tracking_wbm_validate($form, &$form_state) {
  $values = $form_state['values'];
  $entity = $values['node'];
  $current_wbm_state = $values['state'];
  $tracking_to_check = _nexteuropa_editorial_tracking_is_on($entity, $current_wbm_state);
  // Generates errors only if required by WYSIWYG tracking workflow settings.
  if ($tracking_to_check) {
    $tracking_activate = _nexteuropa_editorial_set_tracking_flags($entity);

    // Treating other translation revisions.
    if ($tracking_activate) {
      $entity_message = _nexteuropa_editorial_tracking_entity_message($tracking_activate, $entity);
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
 * @see _nexteuropa_editorial_tracking_entity_validate()
 */
function _nexteuropa_editorial_tracking_field_validate($element, &$form_state, $form) {
  $entity = $element['#entity'];
  $values = $form_state['values'];

  $current_wbm_state = FALSE;
  if (isset($values['workbench_moderation_state_new'])) {
    $current_wbm_state = $form_state['values']['workbench_moderation_state_new'];
  }

  $current_status = $values['status'];
  $is_to_check = _nexteuropa_editorial_tracking_is_on($entity, $current_wbm_state, $current_status);

  if ($is_to_check) {
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
 * @see _nexteuropa_editorial_tracking_entity_validate()
 */
function _nexteuropa_editorial_tracking_entity_message($tracking_lang, $entity) {

  $lang_related = _nexteuropa_editorial_tracking_message_for_languages($tracking_lang);
  $state_related = _nexteuropa_editorial_tracking_message_for_wbm_states($entity);

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
 * @see _nexteuropa_editorial_tracking_entity_message()
 */
function _nexteuropa_editorial_tracking_message_for_languages($tracking_lang) {
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
 * @see _nexteuropa_editorial_tracking_entity_message()
 */
function _nexteuropa_editorial_tracking_message_for_wbm_states($entity) {
  $settings = _nexteuropa_editorial_wysiwyg_tracking_settings($entity);
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
function _nexteuropa_editorial_tracking_is_on($entity, $current_wbm_state = FALSE, $current_status = FALSE) {
  $type = $entity->entity_type;
  // So far, only nodes are support.
  if ($type == 'node') {
    // Prepared for other entities if needed.
    list($id) = entity_extract_ids($type, $entity);
    $cached_settings = &drupal_static(__FUNCTION__ . '_' . $type . '_' . $id);
    if (empty($cached_settings)) {
      $settings = _nexteuropa_editorial_wysiwyg_tracking_settings($entity);
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
function _nexteuropa_editorial_wysiwyg_tracking_settings($entity = NULL) {
  if ($entity && isset($entity->entity_type)) {
    $type = $entity->entity_type;
    $cached_settings = &drupal_static(__FUNCTION__ . '_' . $type);

    // So far, only nodes are supported.
    if (empty($cached_settings) && ($type == 'node')) {
      $status = variable_get('nexteuropa_editorial_tracking_status');
      $states = variable_get('nexteuropa_editorial_tracking_wbm_states', array());
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
 * Form callback for the settings form.
 *
 * @see system_settings_form()
 */
function nexteuropa_editorial_wysiwyg_tracking_settings_form($form, &$form_state) {

  $options = workbench_moderation_state_labels();

  $form['node_workflow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node tracking change workflow'),
    '#description' => t("Set when content with tracking change cannot be saved."),
  );

  $form['node_workflow']['nexteuropa_editorial_tracking_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Block if status is true'),
    '#default_value' => variable_get('nexteuropa_editorial_tracking_status'),
    '#description' => t('If checked, all content types cannot be saved if
       tracking changes feature is enabled; except content types which are
       using the workbench moderation flow with states selected in the field
       below.'),
  );

  $form['node_workflow']['nexteuropa_editorial_tracking_wbm_states'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Block the saving for these Workbench Moderation states'),
    '#options' => $options,
    '#default_value' => variable_get('nexteuropa_editorial_tracking_wbm_states', array()),
    '#description' => t('Choose states where content saving must be blocked if tracked changes exists.'),
  );

  return system_settings_form($form);
}

/**
 * Removes the "ckeditor_lite" post render callback.
 *
 * It is replaced by one matching platform needs.
 *
 * @param array $build
 *   Entity view build.
 *
 * @see nexteuropa_editorial_entity_view_alter()
 */
function _nexteuropa_editorial_ckeditor_lite_view_alter(&$build, $type) {
  if ($type == 'node' &&  user_access('ckeditor_lite highlight changes')) {
    // Only applicable on node., other entity does not have the same workflow.
    // If the user does not have the permission, we leave ckeditor_lite
    // working normally.
    if (isset($build['#post_render'])) {
      $key = array_search('_ckeditor_lite_entity_post_render', $build['#post_render']);
      if ($key !== FALSE) {
        unset($build['#post_render'][$key]);
        $build['#post_render'][] = '_nexteuropa_editorial_ckeditor_lite_entity_post_render';

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
function _nexteuropa_editorial_ckeditor_lite_entity_post_render($output, $element) {
  // First we check if change tracking exist.
  if (preg_match('/<span[^>]+class="[^"]*ice-[^>]+>/', $output)) {
    // We only support node here.
    $node = $element['#node'];
    $bundle = node_type_get_name($node);
    $settings = _nexteuropa_editorial_wysiwyg_tracking_settings($node);

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
