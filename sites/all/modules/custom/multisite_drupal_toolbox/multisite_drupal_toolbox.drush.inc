<?php
function drupal_multisite_toolbox_drush_command() {
  $items = array();

  $items['alert_message'] = array(
    'description' => "Put a permanent alert message.",
    'arguments' => array(
      'switch' => 'enable/disable : Enable or disable the alert message.',
    ),
    'examples' => array(
      'drush alert_message enable' => 'Display the alert message.',
    ),
    'aliases' => array('am'),
     'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );

  return $items;
}

function drush_drupal_multisite_toolbox($switch = "enable") {
  module_load_include('inc', 'multisite_drupal_toolbox', 'alert_message');
  $message = get_message();
  
  if($switch == "enable") {
    variable_set('alert_message_enable', TRUE);
    variable_set('alert_message_body', $message);
    print "alert message enabled\n";
  }
  else {
    variable_set('alert_message_enable', FALSE);
    print "alert message disabled\n";
  }
}
