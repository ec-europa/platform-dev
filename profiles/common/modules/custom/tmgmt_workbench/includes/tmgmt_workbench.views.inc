<?php
/**
 * @file
 * Alter view data for tmgmt_workbench related entities.
 */

/**
 * Implements hook_views_data_alter().
 *
 * Allow relationship with node based in nid,
 * TMGMTNodeSourceViewsController only gives this relationship based in vid.
 */
function tmgmt_workbench_views_data_alter(&$data) {

  // Relationship between job items and nodes.
  $data['tmgmt_job_item']['job_item_to_node_by_nid'] = array(
    'title' => t('Content'),
    'help' => t('Content that is associated with this job item by NID.'),
    'real field' => 'item_id',
    'relationship' => array(
      'label' => t('Content by NID'),
      'base' => 'node',
      'base field' => 'nid',
      'relationship field' => 'item_id',
      'extra' => array(
        array(
          'table' => 'tmgmt_job_item',
          'field' => 'item_type',
          'operator' => '=',
          'value' => 'node',
        ),
      ),
    ),
  );
}
