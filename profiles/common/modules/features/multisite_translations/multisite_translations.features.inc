<?php
/**
 * @file
 * multisite_translations.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_translations_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function multisite_translations_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function multisite_translations_default_message_type() {
  $items = array();
  $items['job_translation_log'] = entity_import('message_type', '{
    "name" : "job_translation_log",
    "description" : "job translation log",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "en",
    "arguments" : null,
    "message_text" : { "en" : [
        {
          "value" : "A new translation request has been made.\\r\\n[message:field-job-reference:source-language] to [message:field-job-reference:target-language]\\r\\nSee the request : [message:field-job-reference:url]\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EA new translation request has been made.\\u003Cbr \\/\\u003E\\n[message:field-job-reference:source-language] to [message:field-job-reference:target-language]\\u003Cbr \\/\\u003E\\nSee the request : [message:field-job-reference:url]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
