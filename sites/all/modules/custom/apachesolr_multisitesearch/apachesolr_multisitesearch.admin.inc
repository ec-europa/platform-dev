<?php

/**
 * Creates the form that allows the user to select which facets will be enabled.
 *
 * Only enabled facets are sent to solr.  Fewer enabled facets can reduce the
 * load on the search server.  Blocks are only offered for enabled facets, so
 * this also reduces the clutter on the blocks admin page.
 */
function apachesolr_multisitesearch_settings() {
  module_load_include('inc', 'apachesolr_multisitesearch', 'apachesolr_multisitesearch.index');
  $form = array();
  $form['#tree'] = TRUE;
  $form['submit_message'] = array(
    '#type' => 'value',
    '#value' => t('The Apache Solr Multisite Search filter settings were changed. To arrange the blocks for your enabled filters, visit the <a href="@url">blocks administration page</a>.', array('@url' => url('admin/structure/block'))),
  );
  $form['admin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Administrative functions'),
  );
  $form['admin']['refresh'] = array(
    '#type' => 'submit',
    '#value' => t('Refresh metadata now'),
    '#prefix' => '<p>' . t('Multisite metadata is used to communicate between all of the sites in a multisite setup. If site names are not showing properly in the search results and facet blocks try refreshing the metadata. Metadata is also refreshed periodically on cron runs.') . '</p>',
    '#submit' => array('apachesolr_multisitesearch_refresh_metadata_now'),
  );

  // Use the metadata and a list of all the hashes in the index
  // to build up checkboxes for deleting site indexes.
  // This is only necessary because sometimes hashes get
  // stranded in the index and deleting the index from the normal
  // admin screen doesn't rectify the problem.
  $metadata = variable_get('apachesolr_multisitesearch_metadata', array());
  $hashes = apachesolr_multisitesearch_get_site_hashes();
  $options = array();
  foreach ($hashes as $hash => $count) {
    if ($hash == apachesolr_site_hash()) {
      $options[$hash] = t('This site (!site, !count documents)', array('!site' => variable_get('site_name', 'Drupal'), '!count' => $count));
    }
    elseif (!empty($metadata[$hash])) {
      $options[$hash] = $metadata[$hash]['site'] . ' ' . t('(!count documents)', array('!count' => $count));
    }
    else {
      $options[$hash] = $hash . ' ' . t('(!count documents)', array('!count' => $count));
    }
  }

  if (count($options) > 0) {
    $form['admin']['delete']['hashes'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Delete data from sites using this index'),
      '#options' => $options,
      '#description' => t('If you end up in a situation where the index has hashes that no longer map to real active sites, use this option to delete the outdated data. If you delete another site\'s index from this site, that site will have to first trigger a re-index, and then run cron until the index is rebuilt.'),
    );
    $form['admin']['delete']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Delete selected indexes'),
      '#submit' => array('apachesolr_multisitesearch_delete_indexes'),
    );
  }
  return $form;
}

/**
 * Submit handler for the "Delete selected indexes" button.
 */
function apachesolr_multisitesearch_delete_indexes($form, &$form_state) {
  module_load_include('inc', 'apachesolr_multisitesearch', 'apachesolr_multisitesearch.index');
  // Instantiate a new Solr object.
  $solr = apachesolr_get_solr();
  $env_id = apachesolr_default_environment();
  foreach ($form_state['values']['admin']['delete']['hashes'] as $hash) {
    if ($hash) {
      $query = "hash:$hash";
      $solr->deleteByQuery($query);
      drupal_set_message(t('The index for !hash has been deleted.', array('!hash' => $hash)));
      if (apachesolr_site_hash() == $hash) {
        //Todo : we might want to execute apachesolr_node_check_index_table();
        apachesolr_set_last_index_updated($env_id, time());
      }
    }
  }
  $solr->commit();
  apachesolr_multisitesearch_retrieve_metadata();
}

/**
 * Submit handler for the "Refresh metadata now" button.
 */
function apachesolr_multisitesearch_refresh_metadata_now() {
  module_load_include('inc', 'apachesolr_multisitesearch', 'apachesolr_multisitesearch.index');
  // Delete all current variables and refresh them
  variable_del('apachesolr_multisitesearch_last_metadata_update');
  variable_del('apachesolr_multisitesearch_last_metadata_fetch');
  apachesolr_multisitesearch_refresh_metadata();
  drupal_set_message(t('The metadata has been refreshed.'));
}
