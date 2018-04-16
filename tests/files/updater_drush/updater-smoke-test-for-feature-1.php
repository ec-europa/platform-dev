<?php

/**
 * @file
 * Updater sample designed for Behat tests using drush.
 */

/**
 * This updater enables the maintenance mode for the behat test via drush.
 */
function updater_smoke_test_for_feature_1_update() {
  drush_invoke_process('@self', 'vset', array('maintenance_mode', 1));
  watchdog('test', 'updater_smoke_test_for_feature_1_update');
  drush_invoke_process('@self', 'cc', array('all'));
}