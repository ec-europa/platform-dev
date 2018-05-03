<?php

/**
 * @file
 * Helper file for the TMGMT DGT connector.
 */

/**
 * Calculate the total length of the translatable strings of a content.
 *
 * @param object $entity
 *   The entity to translate.
 *
 * @return int
 *   Length of all translatable content.
 */
function _tmgmt_dgt_connector_get_content_length($entity) {
  $length = 0;

  $fields = field_read_fields(array(
    'entity_type' => $entity->entity_type,
    'bundle' => $entity->type,
    'module' => 'text',
    'translatable' => TRUE,
  ));

  foreach ($fields as $field) {
    if ($field['translatable']) {
      $field_name = $field['field_name'];
      $values = $entity->$field_name;
      if (!empty($values[$entity->language])) {
        foreach ($values[$entity->language] as $value) {
          $length += drupal_strlen(strip_tags($value['value']));
        }
      }
    }
  }

  return $length;
}

/**
 * Loads the structured source data array from the source.
 *
 * @param string $plugin_type
 *   The TMGMT Job item plugin type.
 * @param string $entity_type
 *   The entity type.
 * @param string $entity_id
 *   The entity ID.
 *
 * @return array
 *   Returns an array of structured data.
 */
function _tmgmt_dgt_connector_get_source_data($plugin_type, $entity_type, $entity_id) {
  $data = array();
  $data_collector_func = sprintf('_tmgmt_dgt_connector_get_%s_data', $plugin_type);

  if (function_exists($data_collector_func)) {
    $data = call_user_func($data_collector_func, $entity_type, $entity_id);
  }

  return $data;
}

/**
 * Parse all data items recursively and sums up all the characters in them.
 *
 * @param array $item
 *   The current data item.
 * @param int $count
 *   The total count of characters.
 *
 * @return int
 *   Returns the count of the characters.
 */
function _tmgmt_dgt_connector_count_source_data(array $item, &$count = 0) {
  if (!empty($item['#text'])) {
    if (_tmgmt_filter_data($item)) {
      // Count characters of the data item.
      $count += drupal_strlen(strip_tags($item['#text']));
    }
  }
  elseif (is_array($item)) {
    foreach (element_children($item) as $key) {
      _tmgmt_dgt_connector_count_source_data($item[$key], $count);
    }
  }

  return $count;
}

/**
 * Returns the translatable data from a workbench moderated entity.
 *
 * Used by _tmgmt_dgt_connector_get_source_data().
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $entity_id
 *   The entity id.
 *
 * @return array
 *   Returns an array of structured data
 */
function _tmgmt_dgt_connector_get_workbench_moderation_data($entity_type, $entity_id) {
  return _tmgmt_dgt_connector_get_entity_data($entity_type, $entity_id);
}

/**
 * Returns the translatable data from an entity.
 *
 * Used by _tmgmt_dgt_connector_get_source_data().
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $entity_id
 *   The entity id.
 *
 * @throws \TMGMTException
 *
 * @return array
 *   Returns an array of structured data
 */
function _tmgmt_dgt_connector_get_entity_data($entity_type, $entity_id) {
  $entities = entity_load($entity_type, array($entity_id));

  $entity = $entities ? reset($entities) : FALSE;
  if (!$entity) {
    throw new TMGMTException(t('Unable to load entity %type with id %id', array('%type' => $entity_type, $entity_id)));
  }

  $langcode = isset($entity->language) ? $entity->language : NULL;

  return tmgmt_field_get_source_data($entity_type, $entity, $langcode, TRUE);
}

/**
 * Get data for string.
 *
 * Used by _tmgmt_dgt_connector_get_source_data().
 *
 * @param string $item_type
 *   The type of the item to be checked.
 * @param string $item_id
 *   The id of the item to be checked.
 *
 * @return array
 *   Returns an array with data of the string.
 */
function _tmgmt_dgt_connector_get_i18n_string_data($item_type, $item_id) {

  // Get i18n object from id.
  list(, $type, $object_id) = explode(':', $item_id, 3);
  $i18n_object = tmgmt_i18n_string_get_wrapper($item_type, (object) array('type' => $type, 'objectid' => $object_id));
  $structure = array();

  if ($i18n_object instanceof i18n_string_object_wrapper) {
    $i18n_strings = $i18n_object->get_strings();
    foreach ($i18n_strings as $string_id => $string) {
      // If '#label' is empty theme_tmgmt_ui_translator_review_form() fails.
      $structure[$string_id] = array(
        '#label' => !empty($string->title) ? $string->title : $string->property,
        '#text' => $string->string,
        '#translate' => TRUE,
      );
    }
  }

  return $structure;
}

/**
 * Get data for locale string.
 *
 * Used by _tmgmt_dgt_connector_get_source_data().
 *
 * @param string $item_type
 *   The type of the item to be checked.
 * @param string $item_id
 *   The id of the item to be checked.
 *
 * @return array
 *   Returns an array with data of the string.
 */
function _tmgmt_dgt_connector_get_locale_data($item_type, $item_id) {
  $query = db_select('locales_source', 'ls');
  $query
    ->fields('ls')
    ->condition('ls.lid', $item_id);
  $locale_object = $query
    ->execute()
    ->fetchObject();

  // Check existence of the string.
  if (!$locale_object) {
    drupal_set_message(t('Unable to load locale with id %id', array('%id' => $item_id)), 'error');
    return array();
  }

  $text = $locale_object->source;
  // Identify placeholders that need to be escaped. Assume that placeholders
  // consist of alphanumeric characters and _,- only and are delimited by
  // non-alphanumeric characters. There are cases that don't match, for
  // example appended SI units like "@valuems", there only @value is the
  // actual placeholder.
  $escape = array();
  if (preg_match_all('/([@!%][a-zA-Z0-9_-]+)/', $text, $matches, PREG_OFFSET_CAPTURE)) {
    foreach ($matches[0] as $match) {
      $escape[$match[1]]['string'] = $match[0];
    }
  }
  $structure['singular'] = array(
    '#label' => t('Singular'),
    '#text' => (string) $text,
    '#translate' => TRUE,
    '#escape' => $escape,
  );
  return $structure;
}

/**
 * Change the #cart submit logic.
 *
 * @see tmgmt_ui_cart_request_translation_form_submit()
 */
function _tmgmt_dgt_connector_workbench_store_request_languages_callback(&$form, &$form_state) {
  global $user;

  $target_languages = array_filter($form_state['values']['target_language']);
  $job_items_by_source_language = array();

  // Group the selected items by source language.
  foreach (tmgmt_job_item_load_multiple(array_filter($form_state['values']['items'])) as $job_item) {
    $source_language = $job_item->getSourceLangCode();
    if (in_array($source_language, $job_item->getExistingLangCodes())) {
      $job_items_by_source_language[$source_language][$job_item->tjiid] = $job_item;
    }
  }

  $jobs = $remove_job_item_ids = $reference = array();
  // Loop over all target languages, create a job for each source and target
  // language combination add add the relevant job items to it.
  foreach ($target_languages as $target_language) {
    foreach ($job_items_by_source_language as $source_language => $job_items) {
      // Skip in case the source language is the same as the target language.
      if ($source_language == $target_language) {
        continue;
      }

      if (!empty($reference)) {
        // Poetry: We need the reference to identify related jobs.
        $job = tmgmt_job_create($source_language, $target_language, $user->uid, $reference);
      }
      else {
        $job = tmgmt_job_create($source_language, $target_language, $user->uid);
      }

      $job_empty = TRUE;
      /** @var TMGMTJobItem $job_item */
      foreach ($job_items as $id => $job_item) {
        try {
          // As the same item might be added to multiple jobs, we need to
          // re-create them and delete the old ones, after removing them from
          // the cart.
          $job->addItem($job_item->plugin, $job_item->item_type, $job_item->item_id);
          $remove_job_item_ids[$job_item->tjiid] = $job_item->tjiid;
          $job_empty = FALSE;
        }
        catch (Exception $e) {
          // If an item fails for one target language, then it is also going
          // to fail for others, so remove it from the array.
          unset($job_items_by_source_language[$source_language][$id]);
          drupal_set_message($e->getMessage(), 'error');
        }
      }

      if (!$job_empty) {
        $jobs[] = $job;

        // Set reference to be based on main job ID.
        if (empty($reference)) {
          $reference = array('reference' => 'SUB_' . $job->tjid);
        }
      }

    }
  }

  // Remove job items from the cart.
  if ($remove_job_item_ids) {
    tmgmt_ui_cart_get()->removeJobItems($remove_job_item_ids);
    entity_delete_multiple('tmgmt_job_item', $remove_job_item_ids);
  }

  // Start the checkout process if any jobs were created.
  if ($jobs) {
    tmgmt_ui_job_checkout_and_redirect($form_state, $jobs);
  }
  else {
    drupal_set_message(t('It is not possible to create a translation job from the selection you made.'), 'error');
  }

  // Store chosen translation request languages for further processing.
  _tmgmt_poetry_workbench_store_request_languages($target_languages);

  // Empty redirection queue, Poetry doesn't work with that.
  tmgmt_ui_redirect_queue_set(array());
}

/**
 * Custom function to manage permissions of the tmgmt_dgt_connector translator.
 *
 * @param string $op
 *   Which operation is performed.
 * @param TMGMTTranslator $translator
 *   The translator the operation is performed on.
 * @param array $account
 *   The account which is performing the update.
 *
 * @return bool
 *   Boolean
 */
function _tmgmt_dgt_connector_translator_access($op, TMGMTTranslator $translator, array $account) {
  if ('tmgmt_dgt_connector' === $translator->plugin) {
    if ('delete' === $op) {
      return FALSE;
    }
    else {
      return user_access('manage feature nexteuropa_dgt_connector');
    }
  }

  return tmgmt_translator_access($op, $translator, $account);
}

/**
 * Check if 'Send to cart' is possible.
 *
 * @param string $plugin_type
 *   The cart plugin type.
 * @param string $item_type
 *   The type of the item to be checked.
 * @param string $item_id
 *   The id of the item to be checked.
 *
 * @return bool
 *   Returns true if 'Send to cart' is possible, false otherwise.
 */
function _tmgmt_dgt_connector_smalljob_translation_possible($plugin_type, $item_type, $item_id) {

  $source_data = _tmgmt_dgt_connector_get_source_data($plugin_type, $item_type, $item_id);
  if (empty($source_data)) {
    return FALSE;
  }
  $length = _tmgmt_dgt_connector_count_source_data($source_data);

  return $length <= variable_get('tmgmt_dgt_connector_max_lenght', TMGMT_DGT_CONNECTOR_MAX_LENGTH);
}
