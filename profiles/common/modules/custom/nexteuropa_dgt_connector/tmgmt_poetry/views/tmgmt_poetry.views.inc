<?php

/**
 * @file
 * Views specific hooks implementations.
 *
 * According to views hooks documentation below hooks should be stored in
 * dedicated file modulename.views.inc.
 */

/**
 * Implements hook_views_data_alter().
 */
function tmgmt_poetry_views_data_alter(&$data) {
  // This is how you can change views handlers for specific fields.
  // It runs only once after clearing the cache,
  // keep it in mind when running a debugger.
  if (isset($data['tmgmt_job']['reference']['field'])) {
    $data['tmgmt_job']['reference']['field']['handler'] = 'tmgmt_poetry_handler_field_tmgmt_job_reference';
  }
  if (isset($data['tmgmt_job_item']['operations']['field'])) {
    $data['tmgmt_job_item']['operations']['field']['handler'] = 'tmgmt_poetry_handler_field_tmgmt_job_item_operations';
  }
  if (isset($data['tmgmt_job']['progress']['field'])) {
    $data['tmgmt_job']['progress']['field']['handler'] = 'tmgmt_poetry_handler_field_progress';
  }

  if (isset($data['tmgmt_job_item']['progress']['field']['handler'])) {
    $data['tmgmt_job_item']['progress']['field']['handler'] = 'tmgmt_poetry_handler_field_progress';
  }
}

/**
 * Implements hook_views_query_alter().
 */
function tmgmt_poetry_views_query_alter(&$view, &$query) {
  // Hide the sub translation jobs from the job overview page.
  if ($view->name == 'tmgmt_ui_job_overview') {
    $join = new views_join();
    $join->table = 'tmgmt_job_item';
    $join->field = 'tjid';
    $join->left_table = 'tmgmt_job';
    $join->left_field = 'tjid';
    $join->type = 'inner';
    $query->add_relationship('tmgmt_job_item', $join, 'tmgmt_job');

    $query->add_where(isset($query->options['group']),
      db_or()
        ->condition(
          db_or()
            ->condition('reference', 'SUB_%', 'NOT LIKE')
            ->isNull('reference')
        )
    );
    $query->add_field('tmgmt_job', 'reference', 'reference');
  }

  // Show the translation jobs from the detail job view.
  if ($view->name == 'tmgmt_poetry_translation_job_items') {
    $query->where[0]['type'] = "OR";
    if (isset($query->where[0]['conditions'][0])) {
      $query->add_where(isset($query->options['group']),
        db_or()
          ->condition('reference', '^(MAIN|SUB)_' . reset($query->where[0]['conditions'][0]['value']) . "_", 'REGEXP')
      );
    }
    $query->add_field('', 'reference', 'reference');
  }
}
