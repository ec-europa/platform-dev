<?php

namespace Drupal\nexteuropa_editorial;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\nexteuropa_editorial.
 */
class Config extends ConfigBase {

  /**
   * Return whereas a user is an editorial team member or not.
   *
   * @param mixed $account
   *   The user object or UID.
   *
   * @return bool
   *   TRUE if the user is an editorial team member, FALSE otherwise.
   */
  public function isEditorialTeamMember($account) {
    $uid = is_object($account) ? $account->uid : $account;
    if ($uid) {
      $query = db_select('og_membership', 'ogm')
        ->fields('ogm')
        ->condition('ogm.group_type', 'node')
        ->condition('ogm.state', OG_STATE_ACTIVE)
        ->condition('entity_type', 'user')
        ->condition('etid', $uid);
      // Filter on the editorial_team group bundle.
      $query->join('node', 'group_node', 'ogm.gid = group_node.nid');
      $query->condition('group_node.type', 'editorial_team');
      return (bool) $query->execute()->rowCount();
    }
    return FALSE;
  }

  /**
   * Create an Editorial Team.
   *
   * @param string $title
   *   Editorial team name.
   * @param string $group_content_access
   *   Define group content access public regardless of its group definition.
   *   Either OG_CONTENT_ACCESS_PUBLIC or OG_CONTENT_ACCESS_PRIVATE.
   *
   * @return int
   *   Newly created editorial team node NID.
   */
  public function createEditorialTeam($title, $group_content_access = OG_CONTENT_ACCESS_PUBLIC) {
    $properties = array(
      'type' => 'editorial_team',
      'uid' => 1,
      'status' => 1,
      'promote' => 0,
    );
    $entity = entity_create('node', $properties);
    $wrapper = entity_metadata_wrapper('node', $entity);
    $wrapper->title->set($title);
    $wrapper->comment = COMMENT_NODE_CLOSED;
    $wrapper->{OG_ACCESS_FIELD}->set($group_content_access);
    $wrapper->{OG_DEFAULT_ACCESS_FIELD}->set(0);
    $wrapper->save(TRUE);
    return $wrapper->getIdentifier();
  }

}
