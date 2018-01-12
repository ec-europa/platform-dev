<?php

/**
 * @file
 * nexteuropa_webtools.bean.inc
 */

/**
 * Implements hook_bean_admin_ui_types().
 */
function nexteuropa_webtools_bean_admin_ui_types() {
  $export = array();

  $bean_type = new stdClass();
  $bean_type->disabled = FALSE; /* Edit this to true to make a default bean_type disabled initially */
  $bean_type->api_version = 5;
  $bean_type->name = 'webtools';
  $bean_type->label = 'webtools';
  $bean_type->options = '';
  $bean_type->description = '';
  $export['webtools'] = $bean_type;

  return $export;
}
