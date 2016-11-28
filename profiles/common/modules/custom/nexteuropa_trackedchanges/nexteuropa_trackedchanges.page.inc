<?php
/**
 * @file
 * Callback for the Entitires list page.
 */

/**
 * Page Callback of the List of entities containing tracked changes.
 *
 * @return string
 *   Page display.
 */
function nexteuropa_trackedchanges_list() {
  $rebuild_required = _nexteuropa_trackedchanges_table_rebuild();
  if ($rebuild_required) {
    drupal_goto('admin/content/tracked_changes/table_rebuild');
  }
  else {
    drupal_set_message(t('Table is populate'));
  }
  return 'Under construction';
}

/**
 * Menu callback triggering the nexteuropa_trackedchanges_info rebuild.
 */
function nexteuropa_trackedchanges_table_rebuilt() {

  // Empty the table and "lock" it.
  variable_set('nexteuropa_trackedchanges_rebuild_lock', 1);
  // It is a rebuild, then we flush the table.
  db_truncate('nexteuropa_trackedchanges_info')->execute();

  $operations = array();
  // The 2nd argument is useless in this case because the default Batch API
  // process fulfils function requirements.
  $operations[] = array('_nexteuropa_trackedchanges_revisions_scanning_process', array());
  $operations[] = array('_nexteuropa_trackedchanges_entity_scanning_process', array());
  $operations[] = array('_nexteuropa_trackedchanges_table_rebuilt_process', array());

  $batch = array(
    'operations' => $operations,
    'finished' => '_nexteuropa_trackedchanges_table_rebuilt_finished',
    'title' => t('Processing the rebuild of the tracked change table'),
    'init_message' => t('Content scanning is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('The rebuild has encountered an error.'),
  );
  batch_set($batch);
  batch_process('admin/content/tracked_changes/entities_list');
}

/**
 * Batch operation saving info on entity in the DB.
 *
 * @see nexteuropa_trackedchanges_table_rebuilt()
 */
function _nexteuropa_trackedchanges_table_rebuilt_process(&$context) {
  if (!isset($context['sandbox']['saving_progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['saving_progress'] = 1;

    $context['sandbox']['detected_entities'] = $context['results']['detected_entities'];
    $context['sandbox']['max'] = count($context['sandbox']['detected_entities']);
  }

  $message['message'] = t('No info related to detected tracked changes in any entities to save.');
  if (!empty($context['sandbox']['detected_entities'])) {
    $detected_entity = array_shift($context['sandbox']['detected_entities']);
    $t_args = array('@type' => $detected_entity['entity_type'], '@id' => $detected_entity['entity_id']);
    $context['message'] = t('Info on the "@type" entity with @id is saved', $t_args);

    $entity = entity_create('nexteuropa_trackedchanges_info', $detected_entity);
    entity_save('nexteuropa_trackedchanges_info', $entity);
  }
  $context['sandbox']['progress']++;

  if (empty($context['sandbox']['detected_entities'])) {
    $context['finished'] = 1;
  }
  elseif ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finished callback of the batch rebuilding the "Info" table.
 *
 * The "Info" table is "nexteuropa_trackedchanges_info".
 *
 * @see nexteuropa_trackedchanges_table_rebuilt()
 */
function _nexteuropa_trackedchanges_table_rebuilt_finished($success, $results, $operations) {
  // Unlock the table to allow a new rebuild if it failed.
  variable_set('nexteuropa_trackedchanges_rebuild_lock', 0);
  variable_set('nexteuropa_trackedchanges_last_rebuild_time', REQUEST_TIME);
  if ($success) {
    drupal_set_message(t('the tracked change table is rebuilt'));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message_args = array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    );
    $message = t('An error occurred during the rebuild process on the 
      %error_operation with arguments: @arguments', $message_args);
    drupal_set_message($message, 'error');
  }
}

/**
 * Check if the nexteuropa_trackedchanges_info must be rebuilt.
 *
 * @return bool
 *   True if it requested; otherwise FALSE.
 */
function _nexteuropa_trackedchanges_table_rebuild() {
  $is_lock = variable_get('nexteuropa_trackedchanges_rebuild_lock');

  if ($is_lock) {
    return FALSE;
  }
  $rebuild_time = variable_get('nexteuropa_trackedchanges_last_rebuild_time');
  if ($rebuild_time) {
    $now = REQUEST_TIME;
    $ellapse_time = ($now - $rebuild_time);
    // @todo parametrise 300.
    return ($ellapse_time > 300);
  }

  return TRUE;
}
