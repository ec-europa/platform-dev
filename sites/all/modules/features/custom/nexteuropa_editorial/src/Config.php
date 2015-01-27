<?php

/**
 * @file
 * Contains \Multisite\Config\Features\nexteuropa_editorial\Config
 */

namespace Drupal\nexteuropa_editorial;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Return whereas a user is an editorial team member or not.
   *
   * @param type $uid
   *    User UID
   * @return boolean
   *    TRUE if the user is a team member, FALSE otherwise.
   */
  public function isEditoralTeamMember($uid = 0) {
    $is_team_member = FALSE;
    $account = user_load($uid);
    $groups = og_get_groups_by_user($account, 'node');
    if ($groups) {
      $is_team_member = (bool) db_select('node', 'n')
        ->fields('n', array('nid'))
        ->condition('n.type', 'editorial_team')
        ->condition('n.nid', $groups)
        ->execute()
        ->fetchAll(\PDO::FETCH_COLUMN);
    }
    return $is_team_member;
  }

  /**
   * Create an Editorial Team.
   *
   * @param string $title
   *    Editorial team name.
   * @param const $group_content_access
   *     Define group content access public regardless of its group definition.
   * It could be either OG_CONTENT_ACCESS_PUBLIC or OG_CONTENT_ACCESS_PRIVATE.
   * @return type
   */
  public function createEditorialTeam($title, $group_content_access = OG_CONTENT_ACCESS_PUBLIC) {
    $properties = array('type' => 'editorial_team', 'uid' => 1, 'status' => 1, 'promote' => 0);
    $entity = entity_create('node', $properties);
    $wrapper = entity_metadata_wrapper('node', $entity);
    $wrapper->title->set($title);
    $wrapper->comment = COMMENT_NODE_CLOSED;
    $wrapper->{OG_ACCESS_FIELD}->set($group_content_access);
    $wrapper->{OG_DEFAULT_ACCESS_FIELD}->set(0);
    $wrapper->save(true);
    return $wrapper->getIdentifier();
  }
} 
