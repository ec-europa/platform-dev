<?php

/**
 * @file
 * Helper functions for installing the feature social bookmark.
 */

/**
 * Returns all custom global variables.
 */
function _social_bookmark_get_global_var() {
  $global_var = array(
    'type_socialbookmark',
    'icon_size_socialbookmark',
    'override_socialbookmark',
    'label_socialbookmark',
    'display_socialbookmark',
    'least_socialbookmark',
    'orientation_socialbookmark',
    'statistics_socialbookmark',
    'language_socialbookmark',
    'language_selector_socialbookmark',
    'data_table',
    'type_socialbar',
    'icon_size_socialbar',
    'text_socialbar',
    'statistics_socialbar',
    'language_socialbar',
    'language_selector_socialbar',
    'user_value_socialbookmark',
  );

  return $global_var;
}
