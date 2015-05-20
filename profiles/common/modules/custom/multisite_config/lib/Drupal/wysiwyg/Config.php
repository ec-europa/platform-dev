<?php
/**
 * @file
 * Contains \\Drupal\\block\\Config.
 */

namespace Drupal\wysiwyg;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\wysiwyg.
 *
 * @example example_wysiwyg.cpp
 * This is an example of how to use the wysiwyg class.
 */

/**
 * You can find below some <strong>example of use</strong>.
 *
 * @brief Helper functions to manage WYSIWYG
 *
 * @details @include example_wysiwyg.cpp
 */
class Config extends ConfigBase {

  /**
   * Add a button to a WYSIWYG profile.
   *
   * @param string $profile
   *   Profile machine name. Ex. 'full_html', etc.
   * @param string $group
   *   Button group name. Ex. 'default', 'drupal', etc.
   * @param mixed $buttons
   *   Array of button names belonging to the $group button group.
   *   Ex. 'Anchor', 'BGColor', etc.
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
   * @param string $profile
   *   Profile machine name. Ex. 'full_html', etc.
   * @param string $group
   *   Button group name. Ex. 'default', 'drupal', etc.
   * @param mixed $buttons
   *   Array of button names belonging to the $group button group.
   *   Ex. 'Anchor', 'BGColor', etc.
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
   * @param string $profile
   *   Profile machine name. Ex. 'full_html', etc.
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
