<?php
/**
 * @file
 * Main file defining Drush commands related to the Flexible Purge module.
 */

/**
 * Implements hook_drush_command().
 */
function flexible_purge_drush_command() {
  $items = array();
  $items['fp-info'] = array(
    'description' => 'Provide information about invalidation constraints like the minimum cache lifetime.',
    'drupal dependencies' => array('flexible_purge'),
    'aliases' => array('fpi'),
    'callback' => 'flexible_purge_drush_fpi',
  );
  $items['fp-purge-all'] = array(
    'description' => 'Purge everything cached by the frontend cache.',
    'drupal dependencies' => array('flexible_purge'),
    'aliases' => array('fpa'),
    'callback' => '_flexible_purge_force_invalidation',
  );
  return $items;
}

/**
 * Print a summary of the situation (with regards to minimum cache lifetime).
 */
function flexible_purge_drush_fpi() {
  drush_print(_flexible_purge_generate_description());
}
