<?php

/**
 * @file
 * Hooks provided by the nexteuropa_json_field module.
 */

/**
 * Returns the list of javascript url variables to be inslude on JSON field.
 *
 * @return array $options
 *   The array of javascript url variables name.
 */
function hook_json_field_js_to_load() {
  $options = array('nexteuropa_webtools_smarloader_url' => t('Webtools load.js'));

  return $options;
}
