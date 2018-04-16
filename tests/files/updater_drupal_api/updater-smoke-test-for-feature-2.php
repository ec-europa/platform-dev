<?php

/**
 * @file
 * Updater sample designed for Behat tests using Drupal API.
 */

/**
 * This updater enables the maintenance mode for the behat test via Drupal API.
 */
function updater_smoke_test_for_feature_2_update() {
  variable_set('maintenance_mode', 0);
  drupal_flush_all_caches();
}