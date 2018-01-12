<?php

/**
 * @file
 * multisite_translations.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function multisite_translations_user_default_roles() {
  $roles = array();

  // Exported role: translator.
  $roles['translator'] = array(
    'name' => 'translator',
    'weight' => 5,
  );

  return $roles;
}
