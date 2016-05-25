<?php
/**
 * @file
 * Control access to subjobs.
 */

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
}
