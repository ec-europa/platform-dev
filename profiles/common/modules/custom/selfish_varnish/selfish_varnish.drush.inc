<?php
/**
 * @file
 * Provide Drush integration for selfish_varnish.
 */

/**
 * Implements hook_drush_help().
 */
function selfish_varnish_drush_help($section) {
  switch ($section) {
    case 'drush:selfish-purge-all':
      return dt('Instruct Selfish Varnish to purge the frontend cache completely.');
  }
}

/**
 * Implements hook_drush_command().
 */
function selfish_varnish_drush_command() {

  $items = array();

  $items['selfish-purge-all'] = array(
    'description' => 'Purge the frontend cache completely.',
    'callback' => 'drush_selfish_purge_all',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}

/**
 * Trigger total frontend cache invalidation.
 *
 * Before calling this we need to be bootstrapped to DRUPAL_BOOTSTRAP_DATABASE.
 */
function drush_selfish_purge_all() {
  if (!drush_bootstrap_to_phase(DRUSH_BOOTSTRAP_DRUPAL_FULL)) {
    return drush_set_error('DRUPAL_SITE_NOT_FOUND', dt('You need to specify an alias or run this command within a drupal site.'));
  }
  _selfish_varnish_force_invalidation(TRUE);
}
