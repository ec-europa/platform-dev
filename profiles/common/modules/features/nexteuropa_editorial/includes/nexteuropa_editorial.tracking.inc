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
 *   The entity to treat.
 * @param string $type
 *   The entity type.
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

  if (!isset($entity->tracking_activate)) {
    $entity->tracking_activate = array();
  }

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
    if ($field_info['translatable']) {
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
                $entity->tracking_activate[$translation_lang] = $translation_lang;
              }
            }
          }
        }
      }
    }
  }
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
 *   The submitted form.
 * @param array $form_state
 *   The form state of the submitted form.
 */
function _nexteuropa_editorial_tracking_entity_validate($form, &$form_state) {
  $values = $form_state['values'];

  // So far, we only support "node" entity type.
  if (isset($form_state['node'])) {
    $entity = $form_state['node'];
    $current_wbm_state = $values['workbench_moderation_state_new'];

    // Get current entity language.
    $current_ent_lang = $values['language'];
    if (isset($form_state['entity_translation'])) {
      // Entity translation case.
      $current_ent_lang = $form_state['entity_translation']['form_langcode'];
    }

    $tracking_to_check = _nexteuropa_editorial_tracking_is_saving_stop($entity, $current_wbm_state);
    // Generates errors only if required by WYSIWYG tracking workflow settings.
    if ($tracking_to_check) {
      $tracking_activate = $values['tracking_activate'];

      // Unset because current form could be emptied of its tracked changes.
      unset($tracking_activate[$current_ent_lang]);
      // Unset because it is common to all translations;even the current one.
      unset($tracking_activate[LANGUAGE_NONE]);

      // Treating current revision.
      if (isset($form_state['tracked_changed_detected']) && $form_state['tracked_changed_detected']) {
        // Ensure that an error message for the whole entity will be displayed.
        $tracking_activate[$current_ent_lang] = $current_ent_lang;
      }

      // Treating other translation revisions.
      if ($tracking_activate) {
        $entity_message = _nexteuropa_editorial_tracking_entity_message($tracking_activate);
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
 *   The submitted form.
 * @param array $form_state
 *   The form state of the submitted form.
 *
 * @see nexteuropa_editorial_form_workbench_moderation_moderate_form_alter()
 */
function _nexteuropa_editorial_tracking_wbm_validate($form, &$form_state) {
  $values = $form_state['values'];
  // Get current entity language.
  $current_ent_lang = $values['language'];
  if (isset($form_state['entity_translation'])) {
    $current_ent_lang = $form_state['entity_translation']['form_langcode'];
  }
  $entity = $values['node'];
  $current_wbm_state = $values['state'];
  $tracking_to_check = _nexteuropa_editorial_tracking_is_saving_stop($entity, $current_wbm_state);
  // Generates errors only if required by WYSIWYG tracking workflow settings.
  if ($tracking_to_check) {
    $tracking_activate = $values['tracking_activate'];

    // Treating other translation revisions.
    if ($tracking_activate) {
      $entity_message = _nexteuropa_editorial_tracking_entity_message($tracking_activate);
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
 *   The form_state related to the submitted form.
 * @param array $form
 *   The submitted form.
 *
 * @see _nexteuropa_editorial_tracking_entity_validate()
 */
function _nexteuropa_editorial_tracking_field_validate($element, &$form_state, $form) {
  $entity = $element['#entity'];
  $current_wbm_state = FALSE;
  if (isset($form_state['values']['workbench_moderation_state_new'])) {
    $current_wbm_state = $form_state['values']['workbench_moderation_state_new'];
  }

  $is_to_check = _nexteuropa_editorial_tracking_is_saving_stop($entity, $current_wbm_state);
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
    unset($form_state['tracked_changed_detected'][$field_path]);
    if (preg_match('/<span[^>]+class="[^"]*ice-[^>]+>/', $value)) {
      // Flag used in entity validate callback.
      $form_state['tracked_changed_detected'][$field_path] = TRUE;

      // Get the field label.
      if (!empty($element['#title'])) {
        $title = $element['#title'];
      }
      else {
        // Multi value fields have an empty '#title'.
        $info = field_info_instance($entity->entity_type, $element['#field_name'], $element['#bundle']);
        $title = check_plain($info['label']);
      }

      $message = t('!title contains tracked changes that may not be saved.',
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
 *
 * @return string
 *   The message to display
 *
 * @see _nexteuropa_editorial_tracking_entity_validate()
 */
function _nexteuropa_editorial_tracking_entity_message($tracking_lang) {
  // LANGUAGE_NONE means all languages and then the current one too.
  unset($tracking_lang[LANGUAGE_NONE]);

  $count = count($tracking_lang);
  switch ($count) {
    case 0:
      // LANGUAGE_NONE case.
      return t('Tracked changes detected in this revision.
      To save progress, please accept or reject them, or
       change the content state.');

    case 1:
      $implied_lang = end($tracking_lang);
      $lang_name = locale_language_name($implied_lang);
      $message_param = array('@lang' => $lang_name);
      return t('Tracked changes detected in the @lang version. To
       save progress, please accept or reject them, or change the content
       state.',
        $message_param);

    default:
      $language_names = array();
      foreach ($tracking_lang as $lang) {
        $language_names[$lang] = locale_language_name($lang);
      }
      $message_param = array('@lang' => implode(', ', $language_names));
      return t('Tracked changes detected in the @lang versions. To
      save progress, please accept or reject them, or change the content
      state.',
        $message_param);
  }
}

/**
 * Checks if the saving of the entity must be blocked or not.
 *
 * @param object $entity
 *   The entity to check.
 * @param bool|FALSE $current_wbm_state
 *   The entity current workbench moderation state (node only).
 *
 * @return bool
 *   TRUE if the saving must be blocked; otherwise FALSE.
 */
function _nexteuropa_editorial_tracking_is_saving_stop($entity, $current_wbm_state = FALSE) {
  $type = $entity->entity_type;
  // So far, only nodes are support.
  if ($type == 'node') {
    // Prepare the future when it will be extended to other entity.
    list($id) = entity_extract_ids($type, $entity);
    $cached_settings = &drupal_static(__FUNCTION__ . '_' . $type . '_' . $id);
    if (empty($cached_settings)) {
      $settings = _nexteuropa_editorial_wysiwyg_tracking_settings($entity);

      if ($settings['is_activate']) {
        if (empty($settings['wbm_states'])) {
          $cached_settings = $settings['saving_blocking'];
        }
        elseif (in_array($current_wbm_state, $settings['wbm_states'])) {
          $cached_settings = TRUE;
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
 *   The entity from which retrieving settings.
 *
 * @return array
 *   An associative array containing:
 *   - is_activate: flag indicating if controls are active about change
 *       tracking.
 *   - saving_blocking: flag indicating if savings must blocked if tracked
 *      changes exist.
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
      $states_to_check = array_keys($states);

      $cached_settings = array(
        'is_activate' => TRUE,
        'saving_blocking' => $status,
        'wbm_states' => $states_to_check,
      );
    }
    return $cached_settings;
  }

  return array(
    'is_activate' => FALSE,
    'saving_blocking' => FALSE,
    'wbm_states' => array(),
  );
}

/**
 * Form callback for the settings form.
 *
 * @see system_settings_form()
 */
function nexteuropa_editorial_wysiwyg_tracking_settings_form($form, &$form_state) {

  $options = array();
  foreach (workbench_moderation_states() as $key => $state) {
    $options[$key] = $state->label;
  }

  $form['node_workflow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node tracking change workflow'),
    '#description' => t("Set when content with tracking change cannot be saved."),
  );

  $form['node_workflow']['nexteuropa_editorial_tracking_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Block if status is true'),
    '#default_value' => variable_get('nexteuropa_editorial_tracking_status'),
    '#description' => t('If checked, all content cannot be saved with tracked
       changes; except if the content type has a workbench moderation flow and
       the states are selected in the field below.'),
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
