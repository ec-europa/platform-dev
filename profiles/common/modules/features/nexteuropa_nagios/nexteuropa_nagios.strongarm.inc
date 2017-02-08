<?php
/**
 * @file
 * nexteuropa_nagios.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nexteuropa_nagios_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nagios_enable_status_page';
  $strongarm->value = 1;
  $export['nagios_enable_status_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nagios_page_callback';
  $strongarm->value = '_nexteuropa_nagios_status_page';
  $export['nagios_page_callback'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nagios_page_path';
  $strongarm->value = 'nagios';
  $export['nagios_page_path'] = $strongarm;

  return $export;
}
