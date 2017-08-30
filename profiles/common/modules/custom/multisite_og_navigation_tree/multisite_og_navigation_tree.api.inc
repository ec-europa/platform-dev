<?php
/**
 * @file
 * API documentation for the Multisite OG Navigation Tree module.
 */

/**
 * Returns all term children in an easy array.
 *
 * @param int $tid
 *   The taxonomy term ID for which to return the children.
 * @param int $vid
 *   An optional vocabulary ID to restrict the child search.
 * @param string $key
 *   Unused.
 *
 * @return array
 *   An associative array of terms, keyed by term ID.
 *
 * @todo Remove the $key parameter, it is unused.
 */
function _mont_group_taxonomy_get_allchildren($tid, $vid = 0, $key = 'tid') {
  // @todo taxonomy_get_children() only accepts two parameters.
  $children = taxonomy_get_children($tid, $vid, $key);
  $result = array();
  foreach ($children as $child_tid => $term) {
    $result[$child_tid] = $term;
    $below = _mont_group_taxonomy_get_allchildren($child_tid, $vid, $key);
    if (!empty($below)) {
      foreach ($below as $below_tid => $below_term) {
        $result[$below_tid] = $below_term;
      }
    }
  }
  return $result;
}

/**
 * Returns a list of group IDs that belong to the given user.
 *
 * @param object $account
 *   Optional user object for which to return group IDs.
 *
 * @return array
 *   An array of group IDs.
 *
 * @deprecated Use og_get_groups_by_user() instead.
 *
 * @see og_get_groups_by_user()
 */
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

/**
 * Returns whether the given entity is a group entity.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to check.
 *
 * @return bool
 *   TRUE if the entity is a group entity, FALSE otherwise.
 *
 * @deprecated Use og_is_group() instead.
 *
 * @see og_is_group()
 */
function _mont_og_is_group($entity_type, $entity) {
  $wrapper = entity_metadata_wrapper($entity_type, $entity);
  return !empty($wrapper->{OG_GROUP_FIELD}) && $wrapper->{OG_GROUP_FIELD}->value();
}


/**
 * Check if group checkbox is ticked.
 *
 * @param object $node
 *   A node to check.
 *
 * @return bool
 *   TRUE if the group checkbox is ticked (?).
 *
 * @todo The purpose of this function is unclear. Should be clarified.
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

/**
 * Check if a content type is a group type and if group taxonomy is enabled.
 *
 * @param object $node
 *   A node to check.
 *
 * @return bool
 *   TRUE if the node is a group type and group taxonomy is enabled.
 */
function _mont_group_taxonomy_enabled($node) {
  $group_taxonomy_settings = variable_get('multisite_og_navigation_tree_mont_taxonomy_enabled', array());
  if (array_key_exists($node->type, $group_taxonomy_settings)) {
    $group_taxonomy_vid = variable_get('multisite_og_navigation_tree_vid', FALSE);
    if ($group_taxonomy_vid) {
      return $group_taxonomy_vid;
    }
  }
  return FALSE;
}

/**
 * Load the group taxonomy term for a node.
 *
 * @param int $nid
 *   The node ID of the node for which to load the group taxonomy term.
 *
 * @return object
 *   A database record containing the group taxonomy terms.
 */
function _mont_group_taxonomy_load($nid) {
  $group_taxonomy = db_select('multisite_og_navigation_tree_grouptaxonomy', 'gtr')->fields('gtr')->condition('nid', $nid, '=')->range(0, 1)->execute()->fetchObject();
  return $group_taxonomy;
}

/**
 * Get the group node id from a term id.
 *
 * @param int $tid
 *   The term ID of the taxonomy term for which to load the node ID.
 *
 * @return object
 *   A database record containing the node ID.
 */
function _mont_group_taxonomy_load_by_term($tid = 0) {
  $group_taxonomy = db_select('multisite_og_navigation_tree_grouptaxonomy', 'gtr')->fields('gtr')->condition('tid', $tid, '=')->range(0, 1)->execute()->fetchObject();
  return $group_taxonomy;
}

/**
 * Insert taxonomy term on node insert.
 *
 * @param object $node
 *   The node for which the taxonomy term should be saved.
 * @param int $vid
 *   The vocabulary ID to which the taxonomy term belongs.
 */
function _mont_group_taxonomy_insert($node, $vid) {
  $nid = $node->nid;
  $node_type = $node->type;
  $term = new stdClass();
  $term->name = $node->title;
  $term->vid = $vid;
  $status = taxonomy_term_save($term);
  if ($status == SAVED_NEW) {
    db_insert(MULTISITE_OG_NAVIGATION_TREE_TBL_GROUP_TAXONOMY_RELATION)->fields(array(
      'nid' => $nid,
      'tid' => $term->tid,
      'vid' => $vid,
      'node_type' => $node_type,
    ))->execute();
  }
  else {
    watchdog('multisite_og_navigation_tree', 'Unable to save taxonomy term for @node_title', array('@name' => filter_xss($node->title)));
  }
}

/**
 * Update taxonomy term on node update.
 *
 * @param object $node
 *   The node for which the taxonomy term should be saved.
 * @param int $vid
 *   The vocabulary ID to which the taxonomy term belongs.
 */
function _mont_group_taxonomy_update($node, $vid) {
  $nid = $node->nid;
  $node_type = $node->type;
  $term = new stdClass();
  $term->name = $node->title;
  $term->vid = $vid;
  $status = taxonomy_term_save($term);
  if ($status == SAVED_NEW) {
    db_insert(MULTISITE_OG_NAVIGATION_TREE_TBL_GROUP_TAXONOMY_RELATION)->fields(array(
      'nid' => $nid,
      'tid' => $term->tid,
      'vid' => $vid,
      'node_type' => $node_type,
    ))->execute();
  }
  else {
    watchdog('multisite_og_navigation_tree', 'Unable to save taxonomy term for @node_title', array('@name' => filter_xss($node->title)));
  }
}
