<?php
/**
 * @file
 * multisite_activity_og.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_activity_og_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function multisite_activity_og_default_message_type() {
  $items = array();
  $items['multisite_content_delete'] = entity_import('message_type', '{
    "name" : "multisite_content_delete",
    "description" : "content deletion",
    "argument_keys" : [ "!user-picture" ],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "en",
    "arguments" : [],
    "message_text" : {
      "en" : [
        {
          "value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-minus\\u0022\\u003E\\u003C\\/span\\u003E\\u0022@{message:field-node-ref:title}\\u0022 has been deleted by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-minus\\u0022\\u003E\\u003C\\/span\\u003E\\u0022@{message:field-node-ref:title}\\u0022 has been deleted by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E\\n"
        }
      ],
      "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "[message:field-node-ref:node-teaser]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-node-ref:node-teaser]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['multisite_content_update'] = entity_import('message_type', '{
    "name" : "multisite_content_update",
    "description" : "content update",
    "argument_keys" : [ "!user-picture" ],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "en",
    "arguments" : [],
    "message_text" : {
      "en" : [
        {
          "value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-pencil\\u0022\\u003E\\u003C\\/span\\u003E\\u0022@{message:field-node-ref:title}\\u0022 has been updated by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-pencil\\u0022\\u003E\\u003C\\/span\\u003E\\u0022@{message:field-node-ref:title}\\u0022 has been updated by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E\\n"
        }
      ],
      "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "[message:field-node-ref:node-teaser]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-node-ref:node-teaser]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['multisite_create_comment'] = entity_import('message_type', '{
    "name" : "multisite_create_comment",
    "description" : "new comment",
    "argument_keys" : [ "!teaser" ],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "en",
    "arguments" : null,
    "message_text" : {
      "en" : [
        {
          "value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-comment\\u0022\\u003E\\u003C\\/span\\u003EA new comment has been posted on \\u0022@{message:field-node-ref:title}\\u0022 by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-comment\\u0022\\u003E\\u003C\\/span\\u003EA new comment has been posted on \\u0022@{message:field-node-ref:title}\\u0022 by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E\\n"
        }
      ],
      "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E \\u003Ca href=\\u0022[message:field-comment-ref:url]\\u0022\\u003Ecommented\\u003C\\/a\\u003E on [message:field-node-ref:title]",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E \\u003Ca href=\\u0022[message:field-comment-ref:url]\\u0022\\u003Ecommented\\u003C\\/a\\u003E on [message:field-node-ref:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "[message:field-comment-ref:comment-teaser]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-comment-ref:comment-teaser]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['multisite_create_node'] = entity_import('message_type', '{
    "name" : "multisite_create_node",
    "description" : "new content creation",
    "argument_keys" : [ "!user-picture" ],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "en",
    "arguments" : [],
    "message_text" : {
      "en" : [
        {
          "value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-plus\\u0022\\u003E\\u003C\\/span\\u003EA new @{message:field-node-ref:content-type} \\u0022@{message:field-node-ref:title}\\u0022 has been created by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-plus\\u0022\\u003E\\u003C\\/span\\u003EA new @{message:field-node-ref:content-type} \\u0022@{message:field-node-ref:title}\\u0022 has been created by @{message:field-node-ref:author} in group [message:og-group-ref:title]\\u003C\\/p\\u003E\\n"
        }
      ],
      "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "[message:field-node-ref:node-teaser]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-node-ref:node-teaser]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['user_subscribe_to_group'] = entity_import('message_type', '{
    "name" : "user_subscribe_to_group",
    "description" : "user subscribe to group",
    "argument_keys" : [ "!user-picture" ],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "en",
    "arguments" : [],
    "message_text" : {
      "en" : [
        {
          "value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-user\\u0022\\u003E\\u003C\\/span\\u003EUser\\u0026nbsp;\\u003C\\/span\\u003E@{message:field-node-ref:author} is a new member of\\u0026nbsp;[message:og-group-ref:title]\\u003C\\/span\\u003E\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Cspan class=\\u0022glyphicon glyphicon-user\\u0022\\u003E\\u003C\\/span\\u003EUser\\u00a0@{message:field-node-ref:author} is a new member of\\u00a0[message:og-group-ref:title]\\u003C\\/p\\u003E\\n"
        }
      ],
      "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "[message:field-node-ref:node-teaser]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-node-ref:node-teaser]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
