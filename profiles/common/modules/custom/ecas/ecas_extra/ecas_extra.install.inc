<?php

/**
 * @file
 * Helper functions for the instalation of the ecas_extra module.
 */

/**
* Returns the initial schema implementation.
*
* @return array
*   The initial schema implementation.
*/
function _ecas_extra_base_schema() {
$schema['denied_users'] = array(
'description' => 'Stores id of denied users.',
'fields' => array(
'uid' => array(
'type' => 'serial',
'unsigned' => TRUE,
'not null' => TRUE,
'description' => 'Primary Key: Unique user ID.',
),
'denied_by' => array(
'type' => 'int',
'unsigned' => TRUE,
'not null' => FALSE,
'description' => 'User ID who denied the other user.',
),
'denied' => array(
'type' => 'int',
'not null' => TRUE,
'default' => 0,
'description' => 'Timestamp for when user was denied.',
),
),
'primary key' => array('uid'),
);
return $schema;
}