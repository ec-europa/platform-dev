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

  // Exported permission: 'administer email non-delivery report processing'.
  $permissions['administer email non-delivery report processing'] = array(
    'name' => 'administer email non-delivery report processing',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bounce',
  );

  // Exported permission: 'administer newsletter statistics'.
  $permissions['administer newsletter statistics'] = array(
    'name' => 'administer newsletter statistics',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplenews_statistics',
  );

  // Exported permission: 'administer newsletters'.
  $permissions['administer newsletters'] = array(
    'name' => 'administer newsletters',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'administer simplenews settings'.
  $permissions['administer simplenews settings'] = array(
    'name' => 'administer simplenews settings',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'administer simplenews subscriptions'.
  $permissions['administer simplenews subscriptions'] = array(
    'name' => 'administer simplenews subscriptions',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'create simplenews content'.
  $permissions['create simplenews content'] = array(
    'name' => 'create simplenews content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own simplenews content'.
  $permissions['delete own simplenews content'] = array(
    'name' => 'delete own simplenews content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own simplenews content'.
  $permissions['edit own simplenews content'] = array(
    'name' => 'edit own simplenews content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'send newsletter'.
  $permissions['send newsletter'] = array(
    'name' => 'send newsletter',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'subscribe to newsletters'.
  $permissions['subscribe to newsletters'] = array(
    'name' => 'subscribe to newsletters',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'view newsletter statistics'.
  $permissions['view newsletter statistics'] = array(
    'name' => 'view newsletter statistics',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplenews_statistics',
  );

  return $permissions;
}
