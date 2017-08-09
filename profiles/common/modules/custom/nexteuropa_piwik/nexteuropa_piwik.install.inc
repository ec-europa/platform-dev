<?php
/**
 * @file
 * Helper functions for the installation file.
 */

/**
 * Returns the schema array.
 */
function _nexteuropa_piwik_get_schema_array() {
  return array(
    'description' => 'Next Europa PIWIK rules',
    'fields' => array(
      'id' => array(
        'type' => 'serial',
        'not null' => TRUE,
        'description' => 'Primary Key: Unique PIWIK rule ID.',
      ),
      'rule_language' => array(
        'type' => 'varchar',
        'length' => 12,
        'not null' => TRUE,
        'description' => 'The language for which a given rule applies.',
      ),
      'rule_path' => array(
        'type' => 'text',
        'description' => 'Path where a given rule applies.',
      ),
      'rule_path_type' => array(
        'type' => 'varchar',
        'length' => 16,
        'not null' => TRUE,
        'description' => 'The rule path type.',
      ),
      'rule_section' => array(
        'type' => 'varchar',
        'length' => 128,
        'not null' => TRUE,
        'description' => 'The name of the site section where a given rule applies.',
      ),
    ),
    'primary key' => array('id'),
  );
}
