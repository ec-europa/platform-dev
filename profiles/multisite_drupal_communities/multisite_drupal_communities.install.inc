<?php

/**
 * @file
 * Helper functions for the Multisite Drupal Standard installation profile.
 */

/**
 * Implements hook_install_tasks().
 */
function multisite_drupal_communities_install_tasks() {
  $tasks = array(
    'cce_basic_config_profile_theme_default_form' => array(
      'display_name' => st('Choose theme'),
      'type' => 'form',
    ),
  );
  return $tasks;
}
