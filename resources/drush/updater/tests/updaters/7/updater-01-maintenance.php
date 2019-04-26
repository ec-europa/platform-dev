<?php

/**
 * @file
 * Basic updater.
 */

/**
 * Basic updater which puts the website in maintenance mode.
 */
function updater_01_maintenance_update() {
  drush_invoke_process('@self', 'vset', array('maintenance_mode', '1'));
}
