<?php

/**
 * @file
 * Definition of views_handler_area_communities_create_new_community_link.
 */

/**
 * Views area handler to display create a new community button.
 */
class views_handler_area_communities_create_new_community_link extends views_handler_area {

  /**
   * Return create a new community button.
   */
  public function render($empty = FALSE) {
    if (user_access('create community content')) {
      $options = array(
        'attributes' => array(
          'type' => 'add',
          'action_bar' => 'last',
          'btn_group' => 'single',
        ),
      );
      return l(t('Create a new community'), 'node/add/community', $options);
    }
  }

}
