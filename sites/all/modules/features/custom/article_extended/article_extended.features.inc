<?php
/**
 * @file
 * article_extended.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function article_extended_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
