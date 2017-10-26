<?php

/**
 * @file
 * nexteuropa_notices.bean.inc
 */

/**
 * Implements hook_bean_admin_ui_types().
 */
function nexteuropa_notices_bean_admin_ui_types() {
  $export = array();

  $bean_type = new stdClass();
  $bean_type->disabled = FALSE; /* Edit this to true to make a default bean_type disabled initially */
  $bean_type->api_version = 5;
  $bean_type->name = 'notice';
  $bean_type->label = 'Notice';
  $bean_type->options = '';
  $bean_type->description = '';
  $export['notice'] = $bean_type;

  return $export;
}
