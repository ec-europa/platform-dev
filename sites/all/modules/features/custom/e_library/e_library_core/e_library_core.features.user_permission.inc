<?php

/**
 * @file
 * e_library_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function e_library_core_user_default_permissions() {
    $permissions = array();

    // Exported permission: create document content
    $permissions['create document content'] = array(
        'name' => 'create document content',
        'roles' => array(
            0 => 'contributor',
            1 => 'administrator',
            2 => 'editor',
        ),
        'module' => 'node',
    );

    // Exported permission: delete any document content
    $permissions['delete any document content'] = array(
        'module' => 'node',
        'name' => 'delete any document content',
        'roles' => array(
            0 => 'administrator',
            1 => 'editor',
        ),
    );

    // Exported permission: delete own document content
    $permissions['delete own document content'] = array(
        'name' => 'delete own document content',
        'roles' => array(
            0 => 'contributor',
            1 => 'administrator',
            2 => 'editor',
        ),
        'module' => 'node',
    );

    // Exported permission: edit any document content
    $permissions['edit any document content'] = array(
        'name' => 'edit any document content',
        'roles' => array(
            0 => 'administrator',
            1 => 'editor',
        ),
        'module' => 'node',
    );

    // Exported permission: edit own document content
    $permissions['edit own document content'] = array(
        'name' => 'edit own document content',
        'roles' => array(
            0 => 'contributor',
            1 => 'administrator',
            2 => 'editor',
        ),
        'module' => 'node',
    );




    // custom permissions
    // Add permissions to roles ----------------------------------------------------------------------------------------------------------------------------------------------
    // Administrator
    $adm_rid = get_rid('administrator');
    user_role_grant_permissions($adm_rid, array_keys(module_invoke_all('permission')));
    user_role_revoke_permissions($adm_rid, array(
        'administer modules',
        'administer features',
        'manage features',
		'show format selection for comment',
		'show format selection for file',
		'show format selection for node',
		'show format selection for rules_config',
		'show format selection for taxonomy_term',
		'show format selection for user',
		'show format tips',
		'show more format tips link',
    ));

    return $permissions;
}

