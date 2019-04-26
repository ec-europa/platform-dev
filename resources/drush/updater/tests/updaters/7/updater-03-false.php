<?php

/**
 * @file
 * Basic updater.
 */

/**
 * Basic updater which returns false.
 */
function updater_03_false_update() {
  drush_print(dt('This updater does nothing and returns false.'));
  return FALSE;
}
