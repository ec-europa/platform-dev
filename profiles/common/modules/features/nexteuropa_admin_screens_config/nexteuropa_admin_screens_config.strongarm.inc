<?php
/**
 * @file
 * nexteuropa_admin_screens_config.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nexteuropa_admin_screens_config_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_force_cli';
  $strongarm->value = '1';
  $export['admin_language_force_cli'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_force_default';
  $strongarm->value = '0';
  $export['admin_language_force_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_force_neutral';
  $strongarm->value = '0';
  $export['admin_language_force_neutral'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_hide_node';
  $strongarm->value = '1';
  $export['admin_language_hide_node'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_hide_user';
  $strongarm->value = '1';
  $export['admin_language_hide_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_pages';
  $strongarm->value = 'admin admin/* admin_menu/* node/add/* node/*/edit node/*/devel node/*/translate file/ajax/* media/ajax/* system/ajax';
  $export['admin_language_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_path_is_admin_paths';
  $strongarm->value = array(
    'admin' => 'file/add
file/add/*
file/*/edit
file/*/usage
file/*/delete
fpa_modal/*/permissions
user/*/linkchecker
linkchecker/*/edit
media/*/edit/*
media/*/format-form
media/browser
media/browser/*
node/*/group
group/*/*/admin/*
admin
admin/*
batch
taxonomy/term/*/edit
user/*/cancel
user/*/edit
user/*/edit/*
taxonomy/*/translate
taxonomy/*/translate/*
node/*/revisions/view/*/*',
    'non_admin' => 'admin/structure/block/demo/*
admin/reports/status/php',
  );
  $export['admin_language_path_is_admin_paths'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_translate_admin_menu';
  $strongarm->value = '1';
  $export['admin_language_translate_admin_menu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_translate_local_tasks';
  $strongarm->value = '1';
  $export['admin_language_translate_local_tasks'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_use_path_is_admin';
  $strongarm->value = 1;
  $export['admin_language_use_path_is_admin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_language_visibility';
  $strongarm->value = '1';
  $export['admin_language_visibility'] = $strongarm;

  return $export;
}
