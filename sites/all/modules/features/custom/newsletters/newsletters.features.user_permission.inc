<?php
/**
 * @file
 * newsletters.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function newsletters_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer newsletters
  $permissions['administer newsletters'] = array(
    'name' => 'administer newsletters',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: administer simplenews settings
  $permissions['administer simplenews settings'] = array(
    'name' => 'administer simplenews settings',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: administer simplenews subscriptions
  $permissions['administer simplenews subscriptions'] = array(
    'name' => 'administer simplenews subscriptions',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'contributor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: create simplenews content
  $permissions['create simplenews content'] = array(
    'name' => 'create simplenews content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own simplenews content
  $permissions['delete own simplenews content'] = array(
    'name' => 'delete own simplenews content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own simplenews content
  $permissions['edit own simplenews content'] = array(
    'name' => 'edit own simplenews content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: send newsletter
  $permissions['send newsletter'] = array(
    'name' => 'send newsletter',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: subscribe to newsletters
  $permissions['subscribe to newsletters'] = array(
    'name' => 'subscribe to newsletters',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'contributor',
    ),
    'module' => 'simplenews',
  );

  return $permissions;
}
