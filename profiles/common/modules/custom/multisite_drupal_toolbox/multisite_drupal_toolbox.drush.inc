<?php

/**
 * @file
 * Multisite Toolbox drush commands to activate an update warning message.
 */

/**
 * Drush commands.
 */
function multisite_drupal_toolbox_drush_command() {
  $items = array();

  $items['alert_message'] = array(
    'description' => "Put a permanent alert message.",
    'arguments' => array(
      'switch' => 'enable/disable : Enable or disable the alert message.',
    ),
    'examples' => array(
      'drush alert_message enable' => 'Display the alert message on the current instance.',
      'drush @sites alert_message enable' => 'Display the alert message on all the subsites and master site.',
    ),
    'aliases' => array('am'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['theme_info'] = array(
    'description' => "Get current theme info.",
    'aliases' => array('ti'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  return $items;
}

/**
 * Alert message.
 */
function drush_multisite_drupal_toolbox_alert_message($switch = "enable") {
  module_load_include('inc', 'multisite_drupal_toolbox', 'alert_message');
  $message = get_message();

  if ($switch == "enable") {
    variable_set('alert_message_enable', TRUE);
    variable_set('alert_message_body', $message);
    print "alert message enabled\n";
  }
  else {
    variable_set('alert_message_enable', FALSE);
    print "alert message disabled\n";
  }
}

/**
 * Theme info.
 */
function drush_multisite_drupal_toolbox_theme_info() {
  global $theme_info, $base_theme_info;
  echo "current theme : " . $theme_info->name . "\n";
  if (count($base_theme_info) > 0) {
    echo "base theme : " . $base_theme_info[0]->name . "\n";
  }
}
