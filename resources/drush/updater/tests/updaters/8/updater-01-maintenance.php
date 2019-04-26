<?php

/**
 * @file
 * Basic updater.
 */

/**
 * Basic updater which puts the website in maintenance mode.
 */
function updater_01_maintenance_update() {
  drush_invoke_process('@self', 'sset', array('system.maintenance_mode', 1));
}
