<?php
/**
 * @file
 * Code specific to customization for the change tracking management.
 */

/**
 * Field widget form alter callback.
 *
 * It inject a specific validate callback in achrge of scanning field value.
 *
 * @see nexteuropa_editorial_field_widget_text_textarea_form_alter()
 * @see nexteuropa_editorial_field_widget_text_textarea_with_summary_form_alter()
 * @see nexteuropa_editorial_field_widget_text_textfield_form_alter()
 */
function _nexteuropa_editorial_field_widget_tracking_change_form_alter(&$element, &$form_state, $context) {
  // So far, only nodes are supported.
  $entity = FALSE;
  if (isset($element['#entity'])) {
    $entity = $element['#entity'];
    // Workaround for entities that do not use "entity_load" correctly
    // like "comment".
    if (!isset($entity->entity_type) && isset($element['#entity_type'])) {
      $entity->entity_type = $element['#entity_type'];
    }
  }
  $tracking_change_settings = _nexteuropa_editorial_wysiwyg_tracking_settings($entity);
  if ($tracking_change_settings['is_activate']) {
    $instance_settings = $context['instance']['settings'];
    if (isset($instance_settings['text_processing']) && $instance_settings['text_processing']) {
      // Tracking change is only possible on fields on which
      // a text format can be set.
      $element['#element_validate'][] = '_nexteuropa_editorial_tracking_change_field_validate';
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
function _nexteuropa_editorial_set_change_tracking_flags($entity, $type = 'node') {
  // Tracking changes are only present in these "fields type".
  $screened_field_types = array(
    'text_textarea',
    'text_textarea_with_summary',
    'text_textfield',
  );
  list(,, $bundle) = entity_extract_ids($type, $entity);
  $entity_language = entity_language($type, $entity);

  if (!isset($entity->tracking_activate)) {
    $entity->tracking_activate = array();
  }

  if (isset($entity->translations)) {
    // Entity translation case.
    $available_translations = $entity->translations;
    $available_translation_langs = array_keys($available_translations->data);
  }
  else {
    $available_translation_langs = array($entity_language);
  }

  $entity_field_instances = field_info_instances($type, $bundle);
  // Note: special field types like field collection or paragraphs
  // are not supported yet.
  foreach ($entity_field_instances as $field_name => $entity_field_instance) {
    $field_info = field_info_field($field_name);
    $widget_type = _nexteuropa_editorial_field_get_widget_type($entity_field_instance);
    if ($field_info['translatable']) {
      $field_languages = $available_translation_langs;
    }
    else {
      // To cover the case where a field is not translatable while
      // the entity is.
      $field_languages = array(LANGUAGE_NONE);
    }
    if (in_array($widget_type, $screened_field_types)) {
      $field_settings = $entity_field_instance['settings'];
      if ($field_settings['text_processing']) {

        foreach ($field_languages as $translation_lang) {
          $values = field_get_items($type, $entity, $field_name, $translation_lang);
          if ($values) {
            foreach ($values as $delta => $value) {
              if (preg_match('/<span[^>]+class="[^"]*ice-[^>]+>/', $value['value'])) {
                if (!in_array($translation_lang, $entity->tracking_activate)) {
                  $entity->tracking_activate[$translation_lang] = $translation_lang;
                }
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
function _nexteuropa_editorial_tracking_change_entity_validate($form, &$form_state) {
  $values = $form_state['values'];
  // So far, we only support "node" entity type.
  if (isset($form_state['node']) || isset($values['node'])) {
    $entity = isset($form_state['node']) ? $form_state['node'] : $values['node'];

    if (isset($values['workbench_moderation_state_new'])) {
      $current_wbm_state = $values['workbench_moderation_state_new'];
    }
    elseif (isset($values['state'])) {
      $current_wbm_state = $values['state'];
    }
    else {
      $current_wbm_state = FALSE;
    }
    $is_tracking_to_check = _nexteuropa_editorial_tracking_saving_to_block($entity, $current_wbm_state);
    // Generates errors only if required by WYSIWYG tracking workflow settings.
    if ($is_tracking_to_check) {
      $current_entity_language = $values['language'];
      $tracking_activate = $values['tracking_activate'];
      if (isset($form_state['tracked_changed_detected'])) {
        foreach ($form_state['tracked_changed_detected'] as $field_name => $field_path) {
          form_set_error($field_path, t('The field contains change tracking that cannot be saved.'));
        }
      }
      unset($tracking_activate[LANGUAGE_NONE]);
      if (!empty($tracking_activate)) {
        if (isset($tracking_activate[$current_entity_language])) {
          unset($tracking_activate[$current_entity_language]);
        }
        $language_names = array();
        $enabled_languages = locale_language_list('native');
        foreach ($tracking_activate as $lang) {
          $language_names[$lang] = '"' . $enabled_languages[$lang] . '"';
        }
        $message_param = array('@lang' => implode(', ', $language_names));
        $error_message = t('The form cannot be saved because of change tracking existing in the @lang version(s).', $message_param);
        form_set_error('tracking_activate', $error_message);
      }
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
 * @see _nexteuropa_editorial_tracking_change_entity_validate()
 */
function _nexteuropa_editorial_tracking_change_field_validate($element, &$form_state, $form) {
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

  if (preg_match('/<span[^>]+class="[^"]*ice-[^>]+>/', $value)) {
    // Storing field info in form_state to treat it later with the entity.
    $form_state['tracked_changed_detected'][$element['#field_name']] = $element['#name'];
  }
}

/**
 * Gets the widget type used by a specific field instance.
 *
 * @param array $field_instance
 *   The field instance for which the related widget type.
 *
 * @return bool|string
 *   Widget type; otherwise FALSE.
 */
function _nexteuropa_editorial_field_get_widget_type($field_instance) {
  $widget_info = _nexteuropa_editorial_field_get_widget_info($field_instance);

  if ($widget_info) {
    return $widget_info['type'];
  }

  return FALSE;
}

/**
 * Gets widget information for a specific field instance.
 *
 * @param array $field_instance
 *   The field instance for which we need information.
 *
 * @return bool|array
 *   Widget information; otherwise FALSE.
 */
function _nexteuropa_editorial_field_get_widget_info($field_instance) {
  if (isset($field_instance['widget'])) {
    return $field_instance['widget'];
  }

  return FALSE;
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
function _nexteuropa_editorial_tracking_saving_to_block($entity, $current_wbm_state = FALSE) {
  // So far, only nodes are support.
  if ($entity->entity_type == 'node') {
    $settings = _nexteuropa_editorial_wysiwyg_tracking_settings($entity);

    if ($settings['is_activate']) {
      if (empty($settings['wbm_states'])) {
        return $settings['saving_blocking'];
      }
      elseif (in_array($current_wbm_state, $settings['wbm_states'])) {
        return TRUE;
      }
    }
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
      $actual_states_to_check = array();
      foreach ($states as $state_name => $state_status) {
        if ($state_status) {
          $actual_states_to_check[] = $state_name;
        }
      }
      $cached_settings = array(
        'is_activate' => TRUE,
        'saving_blocking' => $status,
        'wbm_states' => $actual_states_to_check,
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
