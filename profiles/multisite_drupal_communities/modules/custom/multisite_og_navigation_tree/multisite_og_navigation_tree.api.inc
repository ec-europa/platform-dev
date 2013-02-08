<?php

/**
 * @file
 * Common (api) functions
 */

/*
 * Get all term children in an easy array
 */
function _mont_group_taxonomy_get_allchildren($tid, $vid = 0, $key = 'tid') {
  $c = taxonomy_get_children($tid, $vid, $key);
  $result = array();
  foreach ($c as $t => $d) {
    $result[$t] = $d;
    $below = _mont_group_taxonomy_get_allchildren($t, $vid, $key);
    if (!empty($below)) {
      foreach ($below as $nt => $nd) {
        $result[$nt] = $nd;
      }
    }
  }
  return $result;
}

function _mont_get_groups_by_user($account = NULL) {
  if (empty($account)) {
    global $user;
    $account = $user;
  }

  $gids = array();

  // Get all active OG membership that belong to the user.
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'og_membership')->propertyCondition('entity_type', 'user')->propertyCondition('etid', $account->uid)->propertyCondition('state', OG_STATE_ACTIVE)->execute();

  if (!empty($result['og_membership'])) {
    $memberships = og_membership_load_multiple(array_keys($result['og_membership']));
    foreach ($memberships as &$membership) {
      $gids[] = $membership->gid;
    }
  }

  return $gids;
}

/*
 *   Weird : og_is_group is not in og 
 *   But actually exists on http://drupalcontrib.org/api/drupal/contributions%21og%21og.module/function/og_is_group/7
 */
function _mont_og_is_group($entity_type, $entity) {
  $wrapper = entity_metadata_wrapper($entity_type, $entity);
  return !empty($wrapper->{OG_GROUP_FIELD}) && $wrapper->{OG_GROUP_FIELD}->value();
}


/*
 * Check if group checkbox is ticked
 */
function _mont_is_group($node) {
  if (!og_is_group_type('node', $node->type)) {
    return FALSE;
  }
  if (_mont_og_is_group('node', $node)) {
    return TRUE;
  }
  return FALSE;
}

/*
 * Check if a content type is a group type and if group taxonomy is enabled
 */
function _mont_group_taxonomy_enabled($node) {
  $group_taxonomy_settings = variable_get('_mont_taxonomy_enabled', array());
  if (array_key_exists($node->type, $group_taxonomy_settings)) {
    $group_taxonomy_vid = variable_get('multisite_og_navigation_tree_vid', FALSE);
    if ($group_taxonomy_vid) {
      return $group_taxonomy_vid;
    }
  }
  return FALSE;
}

/*
 * Load the group taxonomy term for a node
 */
function _mont_group_taxonomy_load($nid) {
  $group_taxonomy = db_select('multisite_og_navigation_tree_grouptaxonomy', 'gtr')->fields('gtr')->condition('nid', $nid, '=')->range(0, 1)->execute()->fetchObject();
  return $group_taxonomy;
}

/*
 * Get the group node id from a term id;
 */
function _mont_group_taxonomy_load_by_term($tid = 0) {
  $group_taxonomy = db_select('multisite_og_navigation_tree_grouptaxonomy', 'gtr')->fields('gtr')->condition('tid', $tid, '=')->range(0, 1)->execute()->fetchObject();
  return $group_taxonomy;
}

/*
 * Insert taxonomy term on node insert
 */
function _mont_group_taxonomy_insert($node, $vid) {
  $nid = $node->nid;
  $node_type = $node->type;
  $term = new stdClass;
  $term->name = $node->title;
  $term->vid = $vid;
  $status = taxonomy_term_save($term);
  if ($status == SAVED_NEW) {
    db_insert(TBL_GROUP_TAXONOMY_RELATION)->fields(array(
      'nid' => $nid,
      'tid' => $term->tid,
      'vid' => $vid,
      'node_type' => $node_type
    ))->execute();
  }
  else {
    watchdog('multisite_og_navigation_tree', 'Unable to save taxonomy term for @node_title' , array('@name' => $node->title));
  }
}

/*
 * Update taxonomy term on node update
 */
function _mont_group_taxonomy_update($node, $vid) {
  $nid = $node->nid;
  $node_type = $node->type;
  $term = new stdClass;
  $term->name = $node->title;
  $term->vid = $vid;
  $status = taxonomy_term_save($term);
  if ($status == SAVED_NEW) {
    db_insert(TBL_GROUP_TAXONOMY_RELATION)->fields(array(
      'nid' => $nid,
      'tid' => $term->tid,
      'vid' => $vid,
      'node_type' => $node_type
    ))->execute();
  }
  else {
    watchdog('multisite_og_navigation_tree', 'Unable to save taxonomy term for @node_title' , array('@name' => $node->title));
  }
}

