<?php
/**
 * @file
 * Provides support for the Views module.
 */

/**
 * Implements hook_views_plugins().
 */
function e_library_og_views_plugins() {
  return array(
    'argument default' => array(
      'e_library_og_context_session_groups' => array(
        'title' => t("The user's session group context"),
        'handler' => 'e_library_og_plugin_argument_default_og_context_session',
      ),
    ),
  );
}
