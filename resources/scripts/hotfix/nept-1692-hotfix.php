<?php
/**
 * @file
 * Hook_update to include in the next hotfix release of the info site.
 */

/**
 * Delete TMGMT-POETRY references 'WEB-2017-40025-1-13-TRA' for the nid 50188.
 */
function my_module_update_xxxx() {
  // We have to delete all DB table rows linked to the
  // "How to present your skills and qualifications" content
  // with the nid 50188 and use the reference "WEB/2017/40025/1/13/TRA".
  $implied_nid = 50188;
  $implied_annee = 2017;
  $implied_numero = 40025;
  $implied_version = 1;
  $implied_partie = 13;
  $implied_reference = sprintf('WEB/%d/%d/%d/%d/TRA', $implied_annee, $implied_numero, $implied_version, $implied_partie);

  // Clean "poetry_status" table.
  $tjiid_list_query = db_select('tmgmt_job_item', 'tji');
  $tjiid_list_query->join('tmgmt_job', 'tj', 'tji.tjid = tj.tjid');
  $tjiid_list_query->condition('tj.reference', '%' . $implied_reference, 'LIKE')
    ->fields('tji', array('tjiid'));
  $tjiids = $tjiid_list_query->execute()->fetchCol();

  db_delete('poetry_status')->condition('tjiid', $tjiids, 'IN')->execute();

  watchdog('NextEuropa DGT Connector Cleaning', 'All rows related to one of these tjiid have been deleted 
  from "poetry_status" tables: @list.', array('@list' => implode(' ,', $tjiids)));

  // Clean "tmgmt_job_item" table.
  $tjid_list_query = db_select('tmgmt_job', 'tj')
    ->condition('reference', '%' . $implied_reference, 'LIKE')
    ->fields('tj', array('tjid'));
  $tjids = $tjid_list_query->execute()->fetchCol();

  db_delete('tmgmt_job_item')->condition('tjid', $tjids, 'IN')->execute();

  // Clean "tmgmt_message" table.
  db_delete('tmgmt_message')->condition('tjid', $tjids, 'IN')->execute();

  watchdog('NextEuropa DGT Connector Cleaning', 'All rows related to one of these tjid have been deleted 
  from "tmgmt_job_item" and "tmgmt_message" tables: @list.', array('@list' => implode(' ,', $tjids)));

  // Clean "poetry_map" table.
  db_delete('poetry_map')
    ->condition('entity_type', 'node', '=')
    ->condition('entity_id', $implied_nid, '=')
    ->condition('annee', $implied_annee, '=')
    ->condition('numero', $implied_numero, '=')
    ->condition('version', $implied_version, '=')
    ->condition('partie', $implied_partie, '=')->execute();

  watchdog('NextEuropa DGT Connector Cleaning', 'The row that concerns the node with the nid @nid and the "partie" @partie is deleted  
  from "poetry_map" tables: @list.', array('@nid' => $implied_nid, '@partie' => $implied_partie));

  // Clean "tmgmt_job" table.
  db_delete('tmgmt_job')->condition('reference', '%' . $implied_reference, 'LIKE')->execute();

  watchdog('NextEuropa DGT Connector Cleaning', 'All rows related to one of these tjid are supposed to be deleted 
  from "tmgmt_job" table: @list.', array('@list' => implode(' ,', $tjids)));

  return t(
    'Poetry job clean done for the reference @ref and the node @nid, please check the watchdog logs for more information.',
    array('@ref' => $implied_reference, '@nid' => $implied_nid));
}
