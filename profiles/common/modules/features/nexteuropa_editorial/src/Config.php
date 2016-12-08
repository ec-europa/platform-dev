<?php

/**
 * @file
 * Contains \Multisite\Config\Features\nexteuropa_editorial\Config.
 */

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
   * @param int $uid
   *    User UID.
   *
   * @return bool
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
   * Return whereas a group is an editorial team group or not.
   *
   * @param int $nid
   *    Node NID.
   *
   * @return bool
   *    TRUE if the node is a team group, FALSE otherwise.
   */
  public function isEditoralTeamGroup($nid = 0) {
    $is_team_member = FALSE;
    $node = node_load($nid);
    if ($node && ($node->type == "editorial_team")) {
      $is_team_member = TRUE;
    }
    return $is_team_member;
  }

  /**
   * Create an Editorial Team.
   *
   * @param string $title
   *    Editorial team name.
   * @param string $group_content_access
   *    Define group content access public regardless of its group definition.
   *    Either OG_CONTENT_ACCESS_PUBLIC or OG_CONTENT_ACCESS_PRIVATE.
   *
   * @return int
   *    Newly created editorial team node NID.
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
