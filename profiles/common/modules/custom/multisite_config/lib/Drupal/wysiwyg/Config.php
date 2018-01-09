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
   * @param string $format_name
   *   Text format machine name, for example: "full_html".
   * @param string $group
   *   Button group name. Ex. 'default', 'drupal', etc.
   * @param mixed $buttons
   *   Array of button names belonging to the $group button group.
   *   Ex. 'Anchor', 'BGColor', etc.
   */
  public function addButtonsToProfile($format_name, $group, $buttons) {
    if (($profile = $this->getProfile($format_name))) {
      foreach ($buttons as $button) {
        $profile->settings['buttons'][$group][$button] = 1;
      }
      $this->updateProfile($profile);
    }
  }

  /**
   * Remove a button from a WYSIWYG profile.
   *
   * @param string $format_name
   *   Text format machine name, for example: "full_html".
   * @param string $group
   *   Button group name. Ex. 'default', 'drupal', etc.
   * @param mixed $buttons
   *   Array of button names belonging to the $group button group.
   *   Ex. 'Anchor', 'BGColor', etc.
   */
  public function removeButtonsFromProfile($format_name, $group, $buttons) {
    if (($profile = $this->getProfile($format_name))) {
      foreach ($buttons as $button) {
        unset($profile->settings['buttons'][$group][$button]);
      }
      $this->updateProfile($profile);
    }
  }

  /**
   * Get WYSIWYG profile object.
   *
   * @param string $format_name
   *   Text format machine name, for example: "full_html".
   *
   * @return object
   *   WYSIWYG profile object.
   */
  public function getProfile($format_name) {
    wysiwyg_profile_cache_clear();
    if ($profile = wysiwyg_profile_load($format_name)) {
      return $profile;
    }
  }

  /**
   * Create a new WYSIWYG profile.
   *
   * @param string $format_name
   *   Text format machine name, for example: "full_html".
   * @param string $editor
   *   WYSIWYG JavaScript plugin machine name, for example: "ckeditor".
   * @param array $settings
   *   Profile settings array.
   *
   * @return object
   *   WYSIWYG profile object.
   */
  public function createProfile($format_name, $editor, $settings = array()) {
    $settings += $this->defaultSettings();

    // Insert new profile data.
    db_merge('wysiwyg')
      ->key(array('format' => $format_name))
      ->fields(array(
        'editor' => $editor,
        'settings' => serialize($settings),
      ))
      ->execute();
    wysiwyg_profile_cache_clear();
    return $this->getProfile($format_name);
  }

  /**
   * Remove a WYSIWYG profile.
   *
   * @param string $format_name
   *   Text format machine name, for example: "full_html".
   */
  public function deleteProfile($format_name) {
    wysiwyg_profile_delete($format_name);
    wysiwyg_profile_cache_clear();
  }

  /**
   * Update an existing WYSIWYG profile.
   *
   * @param string $profile
   *   Text format machine name, for example: "full_html".
   */
  public function updateProfile($profile) {
    db_merge('wysiwyg')
      ->key(array('format' => $profile->format))
      ->fields(array(
        'editor' => $profile->editor,
        'settings' => serialize($profile->settings),
      ))->execute();
    wysiwyg_profile_cache_clear();
  }

  /**
   * Return default settings, useful when creating a new WYSIWYG profile.
   *
   * @see: wysiwyg_profile_form().
   *
   * @return array
   *   Array of default profile settings.
   */
  private function defaultSettings() {
    return array(
      'default' => TRUE,
      'user_choose' => FALSE,
      'show_toggle' => TRUE,
      'theme' => 'advanced',
      'language' => 'en',
      'access' => 1,
      'access_pages' => "node/*\nuser/*\ncomment/*",
      'buttons' => array(),
      'toolbar_loc' => 'top',
      'toolbar_align' => 'left',
      'path_loc' => 'bottom',
      'resizing' => TRUE,
      // Also available, but buggy in TinyMCE 2.x: blockquote,code,dt,dd,samp.
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'verify_html' => TRUE,
      'preformatted' => FALSE,
      'convert_fonts_to_spans' => TRUE,
      'remove_linebreaks' => TRUE,
      'apply_source_formatting' => TRUE,
      'paste_auto_cleanup_on_paste' => FALSE,
      'css_setting' => 'theme',
      'css_path' => NULL,
      'css_classes' => NULL,
    );
  }

}
