<?php

/**
 * @file
 * Contains \Drupal\block\Config
 */

namespace Drupal\wysiwyg;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {


  /**
   * Add a button to a WYSIWYG profile.
   *
   * @param $profile
   *    Profile machine name. Ex. 'full_html', etc.
   * @param $group
   *    Button group name. Ex. 'default', 'drupal', etc.
   * @param $buttons
   *    Array of button names belonging to the $group button group.
   *    Ex. 'Anchor', 'BGColor', etc.
   */
  public function addButtonsToProfile($profile, $group, $buttons) {
    if (($profile = wysiwyg_profile_load('full_html'))) {
      foreach ($buttons as $button) {
        $profile->settings['buttons'][$group][$button] = 1;
      }
      $this->updateProfile($profile);
    }
  }

  /**
   * Remove a button from a WYSIWYG profile.
   *
   * @param $profile
   *    Profile machine name. Ex. 'full_html', etc.
   * @param $group
   *    Button group name. Ex. 'default', 'drupal', etc.
   * @param $buttons
   *    Array of button names belonging to the $group button group.
   *    Ex. 'Anchor', 'BGColor', etc.
   */
  public function removeButtonsFromProfile($profile, $group, $buttons) {
    if (($profile = wysiwyg_profile_load('full_html'))) {
      foreach ($buttons as $button) {
        unset($profile->settings['buttons'][$group][$button]);
      }
      $this->updateProfile($profile);
    }
  }

  /**
   * Update an existing WYSIWYG profile.
   *
   * @param $profile
   */
  private function updateProfile($profile) {
    db_merge('wysiwyg')
      ->key(array('format' => $profile->format))
      ->fields(array(
        'editor' => $profile->editor,
        'settings' => serialize($profile->settings),
      ))
      ->execute();
    wysiwyg_profile_cache_clear();
  }

} 
