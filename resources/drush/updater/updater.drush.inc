<?php

/**
 * @file
 * Main Drush Updater command file.
 */

use Drush\updater\Controller;

/**
 * Implements hook_drush_command().
 */
function updater_drush_command() {
  $items = array();

  $items['update-website'] = array(
    'description' => 'Updates the website instance by executing available updaters.',
    'bootstrap'   => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'drupal dependencies' => array(),
    'options' => array(
      'path' => 'Directory path where updaters are located, relative to Drupal root if not absolute. Defaults to sites/all/drush/updaters.',
      'test' => 'Execute updates but do not set them as executed. Defaults to FALSE.',
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_init().
 */
function updater_drush_init() {
  drush_autoload(__FILE__);
}

/**
 * Call-back function for update_website command.
 */
function drush_updater_update_website() {
  $args = func_get_args();
  unset($args[0]);
  $testing = drush_get_option('test', FALSE) ? TRUE : FALSE;
  $path = drush_get_option('path', DRUPAL_ROOT . '/sites/all/drush/updaters');
  $result = Controller::executeUpdaters($path, $args, $testing);
  drush_log(dt('All available updaters executed.'), 'success');
  return $result;
}
