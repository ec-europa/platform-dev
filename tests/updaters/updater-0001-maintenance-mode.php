<?php

/**
 * @file
 * Test Updater Drush command.
 */

/**
 * This updater puts the site in maintenance mode, then back live.
 */
function updater_0001_maintenance_mode_update() {
  drush_invoke_process('@self', 'vset', array('maintenance_mode', '1'));
  drush_invoke_process('@self', 'vset', array('maintenance_mode', '0'));
}
