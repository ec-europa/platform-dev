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
 * Change the #cart submit logic.
 *
 * @see tmgmt_ui_cart_request_translation_form_submit()
 */
function _tmgmt_dgt_connector_workbench_store_request_languages_callback(&$form, &$form_state) {
  global $user;

  $target_languages = array_filter($form_state['values']['target_language']);
  $enforced_source_language = NULL;
  if ($form_state['values']['enforced_source_language']) {
    $enforced_source_language = $form_state['values']['source_language'];
  }

  $skipped_count = 0;
  $job_items_by_source_language = array();
  // Group the selected items by source language.
  foreach (tmgmt_job_item_load_multiple(array_filter($form_state['values']['items'])) as $job_item) {
    $source_language = $enforced_source_language ? $enforced_source_language : $job_item->getSourceLangCode();
    if (in_array($source_language, $job_item->getExistingLangCodes())) {
      $job_items_by_source_language[$source_language][$job_item->tjiid] = $job_item;
    }
    else {
      $skipped_count++;
    }
  }

  $jobs = array();
  $remove_job_item_ids = array();
  $reference = NULL;
  // Loop over all target languages, create a job for each source and target
  // language combination add add the relevant job items to it.
  foreach ($target_languages as $target_language) {
    foreach ($job_items_by_source_language as $source_language => $job_items) {
      // Skip in case the source language is the same as the target language.
      if ($source_language == $target_language) {
        continue;
      }

      if (is_null($reference)) {
        // Poetry: we need the reference to identify related jobs.
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
        if (is_null($reference)) {
          $reference = ['reference' => 'SUB_' . $job->tjid];
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
    if ($enforced_source_language) {
      if ($skipped_count) {
        $languages = language_list();
        drupal_set_message(format_plural($skipped_count, 'One item skipped. @language translation unavailable.',
          '@count items skipped. @language translation unavailable.', array('@language' => $languages[$enforced_source_language]->name)), 'warning');
      }
    }

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
 * @param array $translator
 *   The translator the operation is performed on.
 * @param array $account
 *   The account which is performing the update.
 *
 * @return bool
 *   Boolean
 */
function _tmgmt_dgt_connector_translator_access($op, array $translator, array $account) {
  if (!empty($translator) && $translator->plugin == 'tmgmt_dgt_connector') {
    if ($op == 'delete') {
      return FALSE;
    }
    else {
      return user_access('manage feature nexteuropa_dgt_connector');
    }
  }
  else {
    return tmgmt_translator_access($op, $translator, $account);
  }

}
