<?php
/**
 * @file
 * Control access to subjobs.
 */

/**
 * Security access callbacks setup ().
 */
function _tmgmt_poetry_access_entity_info_alter(&$info) {
  if (!empty($info['tmgmt_job'])) {
    $info['tmgmt_job']['access callback'] = 'tmgmt_poetry_job_access';
  }
  if (!empty($info['tmgmt_job_item'])) {
    $info['tmgmt_job_item']['access callback'] = 'tmgmt_poetry_job_item_access';
  }
}

/**
 * Access callback for the job entity.
 *
 * @param string $op
 *   The operation being performed.
 * @param TMGMTJob $job
 *   (Optional) A TMGMTJob entity to check access for. If no entity is given, it
 *   will be determined whether access is allowed for all entities.
 * @param string $account
 *   (Optional) The user to check for. Leave it to NULL to check for the global
 *   user.
 *
 * @return bool
 *   TRUE if access is allowed, FALSE otherwise.
 */
function tmgmt_poetry_job_access($op, TMGMTJob $job = NULL, $account = NULL) {
  if ($GLOBALS['user']->uid == 1) {
    return TRUE;
  }
  elseif ($job !== NULL) {
    $items = $job->getItems();
    if (count($items) > 0) {
      $job_item = array_shift($items);
    }
    $translator = $job->getTranslator();
    if (
      $translator &&
      ($translator->plugin == 'poetry' && (strpos($job->reference, 'SUB_') !== FALSE || strpos($job->reference, 'MAIN_') !== FALSE)) &&
      isset($job_item) &&
      $job_item->state <= TMGMT_JOB_ITEM_STATE_ACTIVE
    ) {
      return FALSE;
    }
  }

  return tmgmt_job_access($op, $job, $account);
}

/**
 * Access callback for the job item entity.
 *
 * @param string $op
 *   The operation being performed.
 * @param TMGMTJobItem $item
 *   (Optional) A TMGMTJobItem entity to check access for. If no entity is
 *   given, it will be determined whether access is allowed for all entities.
 * @param string $account
 *   (Optional) The user to check for. Leave it to NULL to check for the global
 *   user.
 *
 * @return bool
 *   TRUE if access is allowed, FALSE otherwise.
 */
function tmgmt_poetry_job_item_access($op, TMGMTJobItem $item = NULL, $account = NULL) {
  if ($GLOBALS['user']->uid == 1) {
    return TRUE;
  }
  else {
    // There are no item specific permissions yet.
    return tmgmt_poetry_job_access($op, $item ? $item->getJob() : NULL, $account);
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
  }
}
