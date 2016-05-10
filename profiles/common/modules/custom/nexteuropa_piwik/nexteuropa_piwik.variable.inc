<?php

/**
 * @file
 * Definition of variables for Variable API module.
 */

/**
 * Implements hook_variable_info().
 */
function nexteuropa_piwik_variable_info($options) {
  $variables['nexteuropa_piwik_site_id'] = array(
    'type' => 'string',
    'title' => t('Piwik site ID', array(), $options),
    'default' => '',
    'description' => t('The user account number is unique to the websites domain. Click the <strong>Settings</strong> link in your Piwik account, then the <strong>Websites</strong> tab and enter the appropriate site <strong>ID</strong> into this field.'),
    'required' => TRUE,
    'group' => 'nexteuropa_piwik',
    'localize' => TRUE,
    'multidomain' => TRUE,
    'validate callback' => 'nexteuropa_piwik_validate_piwik_site_id',
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function nexteuropa_piwik_variable_group_info() {
  $groups['nexteuropa_piwik'] = array(
    'title' => t('Piwik'),
    'description' => t('Configure tracking behavior to get insights into your website traffic and marketing effectiveness.'),
    'access' => 'administer nexteuropa_piwik',
    'path' => array('admin/config/system/webtools/piwik'),
  );

  return $groups;
}

/**
 * Validate Piwik site ID variable.
 */
function nexteuropa_piwik_validate_piwik_site_id($variable) {
  if (!preg_match('/^\d{1,}$/', $variable['value'])) {
    return t('A valid Piwik site ID is an integer only.');
  }
}
