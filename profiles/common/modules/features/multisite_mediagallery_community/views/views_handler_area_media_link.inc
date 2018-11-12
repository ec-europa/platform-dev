<?php

/**
 * @file
 * Definition of multisite_mediagallery_community.
 */

/**
 * Views area handler to display glossary for the list of communities.
 */
class views_handler_area_media_link extends views_handler_area {

  /**
   * Return the glossary.
   */
  public function render($empty = FALSE) {
    $output = '';
    $og = og_context();
    if ($og) {
      $gid = $og['gid'];
      // Check if user has permissions to create content for the community and
      // render the button 'Create content'.
      if (og_is_member('node', $gid) && og_user_access('node', $gid, 'create gallerymedia content') && user_access('create gallerymedia content')) {
        $output .= l(t('Create a Media Gallery'), 'node/add/gallerymedia', array(
          'attributes' => array(
            'type' => 'add',
            'action_bar' => 'single',
            'btn_group' => 'single',
          ),
          'query' => array(
            'og_group_ref' => $og['gid'],
          ),
        ));
      }
    }

    return $output;
  }

}
