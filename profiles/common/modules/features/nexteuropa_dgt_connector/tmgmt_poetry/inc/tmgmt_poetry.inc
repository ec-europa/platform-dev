<?php

/**
 * @file
 * Include file for module TMGMT Poetry.
 */

/**
 * Given a Poetry status, get information if job is aborted.
 *
 * Returns TRUE for Poetry status REF and CNL.
 *
 * @param string $poetry_status
 *   The Poetry status.
 *
 * @return bool
 *   True if job is aborted, false otherwise.
 */
function _tmgmt_poetry_is_mapped_job_status_aborted($poetry_status) {
  return _tmgmt_poetry_get_mapped_job_status($poetry_status) === TMGMT_JOB_STATE_ABORTED;
}

/**
 * Given a Poetry status, get the mapped TMGMT job status.
 *
 * @param string $poetry_status
 *   The Poetry status.
 * @param string $default
 *   The default value in case Poetry status is not mapped.
 *
 * @return string
 *   Job status
 */
function _tmgmt_poetry_get_mapped_job_status($poetry_status, $default = '') {
  $status = _tmgmt_poetry_status_mapping();

  return isset($status[$poetry_status]) ? $status[$poetry_status] : $default;
}

/**
 * Get the mapping between Poetry and TMGMT job status.
 *
 * @return array
 *   Status mapping.
 */
function _tmgmt_poetry_status_mapping() {
  return array(
    'SUS' => TMGMT_JOB_STATE_ACTIVE,
    'ONG' => TMGMT_JOB_STATE_ACTIVE,
    'LCK' => TMGMT_JOB_STATE_ACTIVE,
    'EXE' => TMGMT_JOB_STATE_ACTIVE,
    'REF' => TMGMT_JOB_STATE_ABORTED,
    'CNL' => TMGMT_JOB_STATE_ABORTED,
  );
}

/**
 * Custom function to manage permissions of the poetry translator.
 *
 * @param string $op
 *   Which operation is performed.
 * @param array|null $translator
 *   The translator the operation is performed on.
 * @param array|null $account
 *   The account which is performing the update.
 *
 * @return bool
 *   Boolean
 */
function _tmgmt_poetry_translator_access($op, $translator, $account) {
  if (!empty($translator) && $translator->plugin == 'poetry') {
    if ($op == 'delete'  && $translator->name != 'tmgmt_poetry_test_translator') {
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

/**
 * Helper function to retrive a Job based on its reference.
 */
function _tmgmt_poetry_load_job_by_reference($reference) {
  $job = NULL;
  $result = db_select('tmgmt_job', 'job')
    ->fields('job', array('tjid'))
    ->condition('reference', $reference, '=')
    ->execute()
    ->fetchAssoc();

  if (isset($result['tjid']) && !empty($result['tjid'])) {
    $job = tmgmt_job_load($result['tjid']);
  }

  return $job;
}

/**
 * Helper function to force translator contacts to be lowercase.
 */
function _tmgmt_poetry_process_translator_contacts(&$form, &$form_state) {
  if (!empty($form_state['values']['settings']['contacts'])) {
    foreach ($form_state['values']['settings']['contacts'] as $key => $contact) {
      $form_state['values']['settings']['contacts'][$key] = drupal_strtolower($contact);
    }
  }
}

/**
 * Custom validator to add a server validation step for dates in the past.
 */
function _tmgmt_poetry_validate_job_mandatory_fields($form, &$form_state) {
  // This function also runs when changing the Translator Combo box,
  // we need to check if the form was really submitted.
  if (empty($form_state['submitted'])) {
    return;
  }

  if (empty($form_state['values']['settings'])) {
    return;
  }

  // Delivery date is mandatory.
  $delai = $form_state['values']['settings']['delai'];
  if (is_string($delai)) {
    $date = strtotime($delai);
    $today = time();
    if ($date < $today) {
      form_set_error('delai', t('The expected requested delivery date cannot be in the past.'));
    }
  }

  // At least one language is mandatory.
  $languages_empty = TRUE;
  $languages = $form_state['values']['settings']['languages'];
  if (!empty($languages)) {
    foreach ($languages as $language) {
      if ($language) {
        $languages_empty = FALSE;
      }
    }
  }

  if ($languages_empty) {
    form_set_error('languages', t('You have to select a language for requesting a translation.'));
  }
}

/**
 * Sets up TMGMT translator settings for given parameters.
 */
function _tmgmt_poetry_form_load_translator_settings(&$form_state, &$form, $job) {
  $settings = tmgmt_ui_checkout_settings_form($form_state, $job);

  if (!is_array($settings)) {
    $settings = array();
  }

  $form['translator_wrapper']['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure translation request'),
    '#prefix' => '<div id="tmgmt-ui-translator-settings">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  ) + $settings;
}

/**
 * Job Form Callback.
 */
function _tmgmt_poetry_form_tmgmt_job_submit($form, &$form_state) {
  // Current implementation part.
  $origin_job = $form_state['tmgmt_job'];

  // Get list of job_items and main job_item.
  $origin_job_items = $origin_job->getItems();
  if ($origin_job_items === NULL) {
    return;
  }
  $origin_job_item = array_shift($origin_job_items);

  // NEXTEUROPA-7719 - Simplifying Poetry UI.
  // Checking if main language has been changed and picking another one if so
  // and saving it in to the job to keep the current implementation way.
  $target_lg = $form_state['values']['target_language'];
  if (isset($form_state['values']['settings']['languages'])) {

    if ($form_state['values']['settings']['languages'][$target_lg] === 0) {
      foreach ($form_state['values']['settings']['languages'] as $language) {
        if ($language !== 0) {
          $new_main_lg = $language;
          break;
        }
      }

      // There are other submit callbacks after this, that's why changes of
      // $form_state variable are needed.
      $form_state['values']['target_language'] = $new_main_lg;
      $form_state['tmgmt_job']->target_language = $new_main_lg;
      $form_state['tmgmt_job']->save();

      // If there was already a job item for new target language, delete it.
      // This is usefull for the #cart.
      $result = tmgmt_poetry_obtain_related_translation_jobs(array($new_main_lg), 'SUB_' . $origin_job->tjid);

      if ($row = $result->fetchAssoc()) {
        entity_get_controller('tmgmt_job')->delete(array($row['tjid']));
        entity_get_controller('tmgmt_job_item')->delete(array($row['tjiid']));
      }
    }

    // Clearing chosen request languages from the session.
    _tmgmt_poetry_workbench_clear_request_languages();
  }

  // Checking translator plugin type.
  if (!$origin_job->hasPoetryTranslator()) {
    // The translator has benn changed,
    // proceed to clear the settings of origin job and the main reference.
    if (isset($origin_job->settings['languages'])) {
      $origin_job->settings = NULL;
      $origin_job->reference = NULL;
      $origin_job->save();
    }
  }

  // In case if a translation request is already sent,
  // check if there was added or removed additionnal languages.
  if (($form_state['triggering_element']['#value'] != $form['actions']['checkout']['#value']) && $origin_job->state == TMGMT_JOB_STATE_ACTIVE && $origin_job_item->state < TMGMT_JOB_ITEM_STATE_REVIEW) {

    if ($form_state['values']['languages'] !== $origin_job->settings['languages']) {
      unset($origin_job->settings['translations']);
      foreach ($form_state['values']['languages'] as $key_lang => $value_lang) {
        // A LANGUAGE IS ADDED TO ALREADY SENT TRANSLATION REQUEST.
        if (empty($origin_job->settings['languages'][$key_lang]) && !empty($value_lang)) {
          $origin_job->settings['translations']['added'][] = $key_lang;
          // A LANGUAGE IS REMOVED FROM ALREADY SENT TRANSLATION REQUEST.
        }
        elseif (!empty($origin_job->settings['languages'][$key_lang]) && empty($value_lang)) {
          $origin_job->settings['translations']['removed'][] = $key_lang;
        }
      }

      $origin_job_languages = $origin_job->settings['languages'];
      $origin_job->settings['languages'] = $form_state['values']['languages'];
      $origin_job->save();

      // If new request is failed,
      // reset the main job translation languages to old value and save.
      if (!tmgmt_ui_job_request_translation($origin_job)) {
        $origin_job->settings['languages'] = $origin_job_languages;
        $origin_job->state = TMGMT_JOB_STATE_ACTIVE;
        $origin_job->save();

        return;
      }
    }
    else {
      drupal_set_message(t('No changes was detected to resubmit the request'));
    }
  }

  // Find unchecked translations to be removed.
  // This is usefull for the #cart (but it was here before).
  $active_languages = array();
  // Checking if job already has been submit to translator at least once.
  if (!is_null($origin_job->settings) && isset($origin_job->settings['languages'])) {
    $active_languages = $origin_job->settings['languages'];
  }
  // Getting requested languages from the $form_state submitted values.
  elseif (isset($form_state['values']['settings']['languages'])) {
    $active_languages = $form_state['values']['settings']['languages'];
  }

  $active_languages = array_merge(array($origin_job->source_language), $active_languages);
  $languages = language_list('language');
  // Remove old translations in case that they are not available
  // in the settings of the main translation.
  $language_targets_to_remove = array();

  foreach ($languages as $language) {
    // If a language is not in the requested translation.
    if (!in_array($language->language, $active_languages, TRUE)) {
      $language_targets_to_remove[] = $language->language;
    }
  }

  if (!empty($language_targets_to_remove)) {
    $result = tmgmt_poetry_obtain_related_translation_jobs($language_targets_to_remove, 'SUB_' . $origin_job->tjid);

    // If any, removed found translations.
    if ($result) {
      foreach ($result as $row) {
        // Remove if the target language is the same as the main translation.
        if ($origin_job->tjid !== $row->tjid && $origin_job_item->tjiid !== $row->tjiid) {
          entity_get_controller('tmgmt_job')->delete(array($row->tjid));
          entity_get_controller('tmgmt_job_item')->delete(array($row->tjiid));
        }
      }
    }
  }

  // Cancel all old activate jobs associated to this entity.
  $jobs_canceled = _tmgmt_poetry_get_active_translation_jobs_by_entity_id($origin_job_item->item_id);
  $jobs_canceled_id = array();

  foreach ($jobs_canceled as $job_item) {
    $jobs_canceled_id[] = $job_item->tjid;
  }

  foreach (tmgmt_job_load_multiple($jobs_canceled_id, array()) as $job_canceled) {
    if (!empty($job_canceled)) {
      $job_canceled->aborted();
    }
  }
}

/**
 * Return related translations by the translated entity id.
 *
 * @param array|null $languages
 *   Target languages.
 * @param string $reference
 *   Reference to look for.
 * @param bool $not_poetry
 *   Job does not belong to poetry.
 *
 * @return mixed
 *   mixed.
 */
function tmgmt_poetry_obtain_related_translation_jobs($languages, $reference = '', $not_poetry = FALSE) {
  $query = db_select('tmgmt_job', 'job');
  $query->join('tmgmt_job_item', 'job_item', 'job.tjid = job_item.tjid');
  $query->fields('job', array('tjid'));
  $query->fields('job_item', array('tjiid'));

  if (count($languages) > 0) {
    $query->condition('job.target_language', $languages, 'IN');
  }

  $query->condition('job.reference', '%' . $reference . '%', 'LIKE');

  if ($not_poetry) {
    $query->condition('job.reference', $reference . '_POETRY_%', 'NOT LIKE');
  }

  return $query->execute();
}

/**
 * Helper function to reject a TMGMT job and its related sub jobs.
 */
function _tmgmt_poetry_tmgmt_job_reject($job, $status_message, $internal_message, $message) {
  // Reject the main Job.
  $job->rejected(
    $internal_message . " Message error: @error",
    array('@error' => $message),
    'error'
  );

  $results = db_select('tmgmt_job_item', 'job_item')
    ->fields('job_item', array('tjiid'))
    ->condition('tjid', $job->tjid, '=')
    ->execute();

  if ($results) {
    foreach ($results as $result) {
      _tmgmt_poetry_update_item_status($result->tjiid, "", $status_message, "");
    }
  }

  // Reject the related sub Job.
  $related_jobs = tmgmt_poetry_obtain_related_translation_jobs($job->settings['languages'], 'SUB_' . $job->tjid);

  foreach ($related_jobs as $related_job) {
    $job_rejected = tmgmt_job_load($related_job->tjid);
    $job_rejected->rejected(
      $internal_message . " Message error: @error",
     array('@error' => $message),
      'error');
    _tmgmt_poetry_update_item_status($related_job->tjiid, "", $status_message, "");
  }

  drupal_set_message($internal_message, 'error');
}

/**
 * Fetches active translation jobs based on a given entity id.
 *
 * @param int $entity_id
 *   Entity id.
 *
 * @return mixed
 *   An array of results with active translation jobs for given entity id.
 */
function _tmgmt_poetry_get_active_translation_jobs_by_entity_id($entity_id) {
  $query = db_select('tmgmt_job_item', 'item');
  $query->join('tmgmt_job', 'job', 'item.tjid = job.tjid');
  $query->groupBy('job.tjid');
  $query->condition('item.item_id', $entity_id, '=');
  $query->condition('job.state', TMGMT_JOB_STATE_ACTIVE, '=');

  // List of available fields form tmgmt_job_item column.
  $query->fields('item', array(
    'tjiid',
    'item_type',
    'item_id',
    'state',
  ));

  // List of available fields form tmgmt_job column.
  $query->fields('job', array(
    'tjid',
    'reference',
    'source_language',
    'target_language',
    'state',
    'changed',
  ));

  $result = $query->execute()->fetchAllAssoc('tjid');

  return $result;
}

/**
 * Insert a row on the item status table.
 *
 * @param int $tjiid
 *   Job item identifier.
 * @param string $target_language
 *   Target language.
 * @param string $status
 *   Item status.
 * @param string $delai
 *   Item delay.
 */
function _tmgmt_poetry_insert_item_status($tjiid, $target_language, $status, $delai) {
  // Converting date format.
  if (strtotime($delai)) {
    $delai = format_date(strtotime($delai), 'custom', 'd/m/Y');
  }

  db_insert('poetry_status')
    ->fields(array(
      'tjiid' => $tjiid,
      'target_language' => $target_language,
      'status' => $status,
      'delai' => $delai,
    ))
    ->execute();
}

/**
 * Update a row on the item status table.
 *
 * @param int $tjiid
 *   Job item identifier.
 * @param string $target_language
 *   Target language.
 * @param string $status
 *   Item status.
 * @param string $delai
 *   Item delay.
 */
function _tmgmt_poetry_update_item_status($tjiid, $target_language, $status, $delai) {
  if (empty($target_language) && empty($status) && empty($delai)) {
    return;
  }

  $query = db_update('poetry_status');
  if (!empty($target_language)) {
    $query->fields(array('target_language' => $target_language));
  }

  if (!empty($status)) {
    $query->fields(array('status' => $status));
  }

  if (!empty($delai)) {
    $query->fields(array('delai' => $delai));
  }

  $query->condition('tjiid', $tjiid, '=')->execute();
}

/**
 * Loads an array with the word and status statistics of a job.
 *
 * @param array $tjids
 *   An array of job ids.
 *
 * @return array
 *   An array of objects with the keys word_count, count_pending,
 *   count_accepted, count_reviewed and count_translated.
 */
function tmgmt_poetry_job_statistics_load(array $tjids) {
  $statistics = &drupal_static(__FUNCTION__, array());
  // First try to get the values from the cache.
  $return = array();
  $tjids_to_load = array();

  foreach ($tjids as $tjid) {
    if (isset($statistics[$tjid])) {
      // Info exists in cache, get it from there.
      $return[$tjid] = $statistics[$tjid];
    }
    else {
      // Info doesn't exist in cache, add job to the list that needs to be
      // fetched.
      $tjids_to_load[] = $tjid;
    }
  }

  // If there are remaining jobs, build a query to fetch them.
  if (!empty($tjids_to_load)) {
    foreach ($tjids_to_load as $tjid_to_load) {
      // Build the query to fetch the statistics.
      $query = db_select('tmgmt_job_item', 'tji_item');
      $query->join('tmgmt_job', 'tji_job', 'tji_item.tjid = tji_job.tjid');
      $query->addExpression($tjid_to_load, 'tjid');
      $query->addExpression('SUM(word_count)', 'word_count');
      $query->addExpression('SUM(count_accepted)', 'count_accepted');
      $query->addExpression('SUM(count_reviewed)', 'count_reviewed');
      $query->addExpression('SUM(count_pending)', 'count_pending');
      $query->addExpression('SUM(count_translated)', 'count_translated');
      $query->condition('reference', "^(MAIN|SUB)_" . $tjid_to_load . "_", "REGEXP");

      $result = $query->execute();

      foreach ($result as $row) {
        $return[$row->tjid] = $statistics[$row->tjid] = $row;
      }
    }
  }

  return $return;
}

/**
 * Returns a specific statistic of a task.
 *
 * @param TMGMTJob $job
 *   The translation task entity.
 * @param string $key
 *   One of word_count, loop_count, count_pending, count_accepted and
 *   count_translated.
 *
 * @return int
 *   The requested information as an integer.
 */
function tmgmt_poetry_job_statistics(TMGMTJob $job, $key) {
  $statistics = tmgmt_poetry_job_statistics_load(array($job->tjid));

  if (isset($statistics[$job->tjid]->$key)) {
    return $statistics[$job->tjid]->$key;
  }

  return 0;
}

/**
 * Returns the list of possible translations.
 *
 * @param array $form_state
 *   The $form_state variable from form.
 *
 * @return array
 *   Returns an array with the possible translation.
 */
function _tmgmt_poetry_translations_possible(array $form_state) {
  $translations_possible = array();

  // Checking if we have a node with the appropriate moderation state.
  // Getting the moderation states which allows to request the translation.
  $states = array_values(_tmgmt_workbench_available_states());
  $state = $form_state['entity']->workbench_moderation['current']->state;

  if (in_array($state, $states, 'strict')) {
    $translations_possible = array('regular');
  }

  // If Cart translation is possible, Regular translation shouldn't be possible.
  $test_cart = function_exists('_tmgmt_dgt_connector_smalljob_translation_possible');
  if ($test_cart && isset($form_state['tmgmt_cart'])) {
    $cart_info = $form_state['tmgmt_cart'];
    if (_tmgmt_dgt_connector_smalljob_translation_possible($cart_info['plugin'], $cart_info['item_type'], $cart_info['item_id'])) {
      $translations_possible = array('cart');
    }
  }

  return $translations_possible;
}

/**
 * Checks if translation request was at least accepted by the Poetry service.
 *
 * @param int $entity_id
 *   Entity id.
 *
 * @return bool
 *   TRUE if sending a request is possible otherwise FALSE.
 */
function _tmgmt_poetry_check_translatability($entity_id) {
  // Getting the main TMGMT job based on the given entity id.
  $query = db_select('tmgmt_job_item', 'tji');
  $query->join('tmgmt_job', 'tj', 'tji.tjid = tj.tjid');
  $query->fields('tj', array('tjid'));
  $query->condition('tji.item_id', $entity_id, '=');
  $query->condition('reference', "^(MAIN)_", "REGEXP");

  $result = $query->execute()->fetchAssoc();

  if ($result) {
    $main_job = tmgmt_job_load($result['tjid']);
    $translator = $main_job->getTranslator();

    return $translator->canTranslate($main_job);
  }

  return FALSE;
}

/**
 * Checks if passed job items are in the state which allows translation.
 *
 * @param array $existing_jobs_items
 *   An array with the TMGMT job items.
 *
 * @return bool
 *   Returns TRUE/FALSE.
 */
function _tmgmt_poetry_check_jobs_translatability(array $existing_jobs_items) {
  foreach ($existing_jobs_items as $existing_job_item) {
    // Check if it's a poetry job.
    $job = $existing_job_item->getJob();

    if (!$job->hasPoetryTranslator()) {
      continue;
    }

    $status = _tmgmt_poetry_get_job_item_status($existing_job_item->tjiid);
    if (isset($status) && $status == TMGMT_POETRY_STATUS_MSG_PEN) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Get Poetry status of Job Item.
 *
 * @param int $tjiid
 *   TMGMT job item id.
 *
 * @return string
 *   Poetry status of the Job Item.
 */
function _tmgmt_poetry_get_job_item_status($tjiid) {

  $result = db_select('poetry_status', 'ps')
    ->fields('ps')
    ->condition('tjiid', $tjiid, '=')
    ->execute()
    ->fetchAssoc();

  return $result['status'];
}

/**
 * Storing chosen translation request languages for further processing.
 *
 * @param array|null $languages
 *   An array with languages.
 *
 * @return array
 *   An array with language codes.
 *
 * @see TMGMTPoetryTranslatorUIController
 */
function _tmgmt_poetry_workbench_store_request_languages($languages) {
  foreach ($languages as $key => $language) {
    if ($language === 0) {
      unset($languages[$key]);
    }
  }

  // Pick first language to be a main translation request language.
  $langcode = reset($languages);
  $languages['main'] = $langcode;

  $_SESSION['tmgmt_workbench']['languages'] = $languages;

  return $langcode;
}

/**
 * Get chosen translation request languages from session.
 *
 * @return array
 *   An array with languages.
 */
function _tmgmt_poetry_workbench_get_request_languages() {
  $languages = array();

  if (isset($_SESSION['tmgmt_workbench']['languages'])) {
    $languages = $_SESSION['tmgmt_workbench']['languages'];
  }

  return $languages;
}

/**
 * Clearing session for chosen translation request languages.
 */
function _tmgmt_poetry_workbench_clear_request_languages() {
  if (isset($_SESSION['tmgmt_workbench']['languages'])) {
    unset($_SESSION['tmgmt_workbench']['languages']);
  }
}

/**
 * Disable form elements.
 */
function _tmgmt_poetry_disable_form_elements(&$form) {
  // Disable all actions.
  unset($form['actions']);

  $lang_codes = array_keys($form['languages']['#options']);
  foreach ($lang_codes as $lang_code) {
    $form['languages'][$lang_code] = array(
      '#type' => 'checkbox',
      '#disabled' => TRUE,
    );
  }
}

/**
 * Provides translatable language codes.
 *
 * Function omits languages which are:
 *  - in ongoing translation request (present in $existing_jobs),
 *  - already translated,
 *  - source language.
 *
 * @param array|null $existing_jobs
 *   An array with existing TMGMT jobs.
 * @param array|null $form
 *   Reference to the $form variable.
 * @param array|null $form_state
 *   Reference to the $form_state variable.
 *
 * @return array
 *   An empty array or an array with translatable language codes.
 */
function _tmgmt_poetry_get_translatable_languages($existing_jobs, &$form, &$form_state) {
  $existing_lg = array_keys($existing_jobs);
  $translatable_lg = array();
  $languages = language_list();

  foreach ($form['languages']['#options'] as $lg_code => $language) {
    if (!in_array($lg_code, $existing_lg) &&
      !in_array($lg_code, array_keys($form_state['entity']->translations->data)) &&
      $language[TMGMT_WORKBENCH_REQUEST_SOURCE_LG_INDEX] != '(original content)'
    ) {
      $translatable_lg[$lg_code] = $languages[$lg_code]->name;
    }
  }

  return $translatable_lg;
}

/**
 * Injects 'request additional languages' functionality form elements.
 *
 * @param array|null $form
 *   Reference to the main form array.
 * @param array $trans_langs
 *   An array with translatable languages.
 */
function _tmgmt_poetry_inject_add_new_languages_elements(&$form, array $trans_langs) {
  // Setting up header for the additional languages.
  $trans_lang_header = array(
    'language' => t('Language'),
  );

  // Setting up $options for the additional languages.
  foreach ($trans_langs as $lg_code => $trans_lang) {
    $trans_langs_options[$lg_code]['language'] = $trans_lang;
  }

  $form['add_new_languages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Request addition of new languages'),
    '#prefix' => '<div class="tmgmt-poetry-ui-add-new-languages">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );

  $form['add_new_languages']['translatable_languages'] = array(
    '#title' => t('Additional languages'),
    '#type' => 'tableselect',
    '#header' => $trans_lang_header,
    '#options' => $trans_langs_options,
    '#empty' => t('No content available.'),
    '#prefix' => '<div class="col-lg-4, col-md-4">',
    '#suffix' => '</div>',
  );

  $form['add_new_languages']['delai'] = array(
    '#type' => 'date_popup',
    '#title' => t('Expected delivery time'),
    '#default_value' => '',
    '#date_format' => 'd/m/Y',
    '#date_year_range' => '-0:+1',
    '#required' => TRUE,
  );

  $form['add_new_languages']['actions']['#type'] = 'actions';
  $form['add_new_languages']['actions']['add_langs'] = array(
    '#type' => 'submit',
    '#value' => t('Add languages'),
    '#submit' => array('_tmgmt_poetry_add_target_languages_form_submit'),
    '#validate' => array('_tmgmt_poetry_add_target_languages_form_validate'),
  );
}

/**
 * Submit callback for the addition of new target languages request.
 */
function _tmgmt_poetry_add_target_languages_form_submit($form, &$form_state) {
  // Getting main job based on the $entity ID.
  $entity_id = $form_state['tmgmt_cart']['item_id'];
  $main_job = _tmgmt_poetry_get_main_job_by_entity_id($entity_id);

  // Getting TMGMT Job controller to perform custom request.
  $ctrl = $main_job->getTranslatorController();

  // Getting selected languages.
  $selected_languages = array_diff($form_state['values']['translatable_languages'], array(0));
  $selected_languages = array_keys($selected_languages);

  $delivery_date = strtotime($form_state['values']['delai']);
  // Performing request for addition of new languages.
  $ctrl->addNewTargetLanguages($main_job, $selected_languages, $delivery_date);
}

/**
 * Validation callback of the addition of languages to the ongoing translation.
 */
function _tmgmt_poetry_add_target_languages_form_validate($form, &$form_state) {
  if (isset($form_state['values']['translatable_languages'])) {
    foreach ($form_state['values']['translatable_languages'] as $language) {
      if (!empty($language)) {
        return;
      }

      form_set_error('languages', t('You have to select at least one language to add it to the ongoing translation request.'));
    }
  }
}

/**
 * Provides main TMGMT job based on the given entity id.
 *
 * @param int $entity_id
 *   Entity id.
 *
 * @return \TMGMTJob|bool
 *   TMGMT Job object or FALSE.
 */
function _tmgmt_poetry_get_main_job_by_entity_id($entity_id) {
  $query = db_select('tmgmt_job_item', 'tji');
  $query->join('tmgmt_job', 'tj', 'tji.tjid = tj.tjid');
  $query->fields('tj', array('tjid', 'reference'));
  $query->condition('tji.item_id', $entity_id, '=');
  $query->condition('reference', "^(MAIN)_", "REGEXP");
  $result = $query->execute()->fetchAssoc();

  if ($result) {
    return tmgmt_job_load($result['tjid']);
  }

  return FALSE;
}

/**
 * Creates 'sub' job and related job item based on the 'main' job and language.
 *
 * @param string $lg_code
 *   Language code.
 * @param \TMGMTPoetryJob $main_job
 *   Main TMGMT Poetry job.
 * @param int $delivery_date
 *   Delivery date timestamp ('delai') set for the translation request.
 */
function _tmgmt_poetry_create_job_and_item($lg_code, TMGMTPoetryJob $main_job, $delivery_date) {
  $languages = language_list('language');
  $job = tmgmt_job_create($main_job->source_language, $lg_code, $main_job->uid);
  $main_job_items = $main_job->getItems();
  $main_job_item = array_shift($main_job_items);

  $job->translator = $main_job->translator;
  $job->reference = str_replace(
    'MAIN_' . $main_job->tjid . '_POETRY_',
    'SUB_' . $main_job->tjid . '_POETRY_',
    $main_job->reference
  );
  $job->label = $main_job->label . ' ' . $languages[$lg_code]->name;
  $job->save();
  $job->submitted();

  $job_item = tmgmt_job_item_create($main_job_item->plugin, $main_job_item->item_type, $main_job_item->item_id);
  $job_item->tjid = $job->tjid;

  $job->state = TMGMT_JOB_STATE_ACTIVE;
  $job_item->save();
  _tmgmt_poetry_insert_item_status($job_item->tjiid, $job->target_language, "Pending", date('d/m/Y', $delivery_date));
}

/**
 * Checks if the plugin is one of poetry or tmgmt_dgt_connector.
 *
 * @param string $plugin
 *   Name of the plugin to check.
 *
 * @return bool
 *   Returns TRUE if the plugin is one of poetry or tmgmt_dgt_connector.
 */
function _tmgmt_poetry_has_poetry_plugin($plugin) {
  if (in_array($plugin, array('poetry', 'tmgmt_dgt_connector'))) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Replace job id in received content.
 *
 * @param string $content
 *   The formatted content.
 * @param TMGMTJob $job
 *   The TMGMT Job.
 * @param TMGMTJobItem $job_item
 *   The TMGMT Job Item.
 *
 * @return mixed
 *   The content with replaced data or FALSE if some problem happened.
 */
function _tmgmt_poetry_replace_job_in_content($content, TMGMTJob $job, TMGMTJobItem $job_item) {
  switch ($job->getSetting('export_format')) {
    case 'html_poetry':
    case 'xml_dgt':
      $dom = new DOMDocument();
      if (!multisite_drupal_toolbox_load_html($dom, $content)) {
        return FALSE;
      }

      // Workaround for saveXML() generating two xmlns attributes.
      // See https://bugs.php.net/bug.php?id=47666.
      if ($dom->documentElement->hasAttributeNS(NULL, 'xmlns')) {
        $dom->documentElement->removeAttributeNS(NULL, 'xmlns');
      }

      $xml = simplexml_import_dom($dom);

      if (count($xml->head->meta) > 0) {
        foreach ($xml->head->meta as $meta_tag) {
          if (isset($meta_tag['name'])) {
            switch ($meta_tag['name']) {
              case 'JobID':
                $meta_tag['content'] = $job->tjid;
                break;

              case 'languageSource':
                $meta_tag['content'] = $job->getTranslator()
                  ->mapToRemoteLanguage($job->source_language);
                break;

              case 'languageTarget':
                $meta_tag['content'] = $job->getTranslator()
                  ->mapToRemoteLanguage($job->target_language);
                break;
            }
          }
        }
      }
      if (isset($xml->head->title)) {
        $xml->head->title = "Job ID " . $job->tjid;
      }
      foreach ($xml->body->div as $parent_div) {
        if ($parent_div['class'] == 'meta' && $parent_div['id'] == 'languageTarget') {
          $parent_div[0] = $job->target_language;
        }
        if ($parent_div['class'] == 'asset') {
          $parent_div['id'] = $job_item->tjiid;

          /** @var SimpleXMLElement $div */
          foreach ($parent_div->div as $div) {
            if ($div['class'] == 'atom') {
              $data = drupal_substr($div['id'], 1);
              $data = base64_decode(str_pad(strtr($data, '-_', '+/'), drupal_strlen($data) % 4, '=', STR_PAD_RIGHT));
              $data = explode(']', $data);
              $data[0] = $job_item->tjiid;
              $data = implode(']', $data);
              $div['id'] = 'b' . rtrim(strtr(base64_encode($data), '+/', '-_'), '=');
            }
          }
        }
      }

      $result = $xml->saveXML();
      break;

    case 'xliff_xsl_xml_poetry':
      $xml = simplexml_load_string($content);

      // Register the XLIFF namespace, required for xpath.
      $xml->registerXPathNamespace('xliff', 'urn:oasis:names:tc:xliff:document:1.2');
      // Check if the job has a valid job reference.
      $phase = $xml->xpath("//xliff:phase[@phase-name='extraction']");
      $phase = reset($phase);
      $phase['job-id'] = $job->tjid;
      $xml->file['target-language'] = $job->target_language;

      $xml->file->body->group['id'] = $job_item->tjiid;

      /** @var SimpleXMLElement $transunit */
      foreach ($xml->file->body->group->{'trans-unit'} as $transunit) {
        $data = explode(']', $transunit['id']);
        $old_tjiid = $data[0];
        $data[0] = $job_item->tjiid;
        $data = implode(']', $data);
        $transunit['id'] = $data;
        $transunit['resname'] = $data;

        $target = dom_import_simplexml($transunit->target);
        $target->setAttribute('xml:lang', $job->target_language);

        /** @var SimpleXMLElement $transunit */
        foreach ($transunit->source->children() as $tag) {
          $tag['id'] = str_replace('tjiid' . $old_tjiid . '-', 'tjiid' . $job_item->tjiid . '-', $tag['id']);
        }
      }
      $result = $xml->asXML();
      break;
  }
  return $result;
}

/**
 * Replace [language] with given replacement.
 *
 * @param string $label
 *   Initial label.
 * @param string $replacement
 *   Replacement for [language].
 *
 * @return string
 *   The new label
 */
function tmgmt_poetry_change_label($label, $replacement = '') {
  return preg_replace('/ \[(.*)\]$/', $replacement, $label);
}
