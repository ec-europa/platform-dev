<?php

/**
 * @file
 * Hooks for multisite_drupal_toolbox module.
 */

/**
 * Alter the default filter options for the Sanitize HTML text filter.
 */
function hook_multisite_drupal_toolbox_filter_options_alter(&$filter_options) {
  // Enable the <object> tag, strongly not advised of course.
  $filter_options['valid_elements']['object'] = array('*' => TRUE);
}
