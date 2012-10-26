<?php
/**
 * @file
 * cce_basic_config.default_password_policy.inc
 */

/**
 * Implements hook_default_password_policy().
 */
function cce_basic_config_default_password_policy() {
  $export = array();

  $password_policy = new stdClass();
  $password_policy->disabled = FALSE; /* Edit this to true to make a default password_policy disabled initially */
  $password_policy->api_version = 1;
  $password_policy->name = 'Min 10 chars';
  $password_policy->description = 'Your password must contain at least 1 digit and be 10 characters long';
  $password_policy->enabled = TRUE;
  $password_policy->policy = array(
    'length' => '10',
  );
  $password_policy->created = 1351233511;
  $password_policy->expiration = 0;
  $password_policy->warning = '';
  $password_policy->weight = FALSE;
  $export['Min 10 chars'] = $password_policy;

  return $export;
}
