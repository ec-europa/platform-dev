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
  $password_policy->name = 'Example policy';
  $password_policy->config = 'a:9:{s:11:"alpha_count";a:1:{s:11:"alpha_count";s:1:"6";}s:10:"char_count";a:1:{s:10:"char_count";s:2:"10";}s:11:"consecutive";a:1:{s:22:"consecutive_char_count";s:0:"";}s:9:"int_count";a:1:{s:9:"int_count";s:1:"2";}s:14:"past_passwords";a:1:{s:14:"past_passwords";s:0:"";}s:12:"symbol_count";a:2:{s:12:"symbol_count";s:0:"";s:20:"symbol_count_symbols";s:30:"!@#$%^&*()_+=-|}{"?:><,./;\'\\[]";}s:8:"username";a:1:{s:7:"enabled";b:0;}s:4:"role";a:1:{s:5:"roles";a:4:{i:2;i:0;i:3;i:0;i:4;i:0;i:5;i:0;}}s:6:"expire";a:4:{s:12:"expire_limit";s:1:"0";s:25:"expire_warning_email_sent";s:8:"-14 days";s:28:"expire_warning_email_message";s:0:"";s:28:"expire_warning_email_subject";s:92:"[user:name] you password on [site:name] shall expire in [password_expiration_date:interval] ";}}';
  $export['Example policy'] = $password_policy;

  return $export;
}
