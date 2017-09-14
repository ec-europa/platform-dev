<?php
/**
 * @file
 * Next Europa DGT Rules integration - Contains default rules elements.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ne_dgt_rules_default_rules_configuration() {
  // Rules component definition: Create main job and related job item.
  $data = '{
    "rules_ne_dgt_ftt_node_create_main_job_and_related_job_item" : {
    "LABEL" : "NE DGT FTT | Node | Create main job and related job item",
    "PLUGIN" : "action set",
    "OWNER" : "rules",
    "TAGS" : [ "NE DGT FTT" ],
    "REQUIRES" : [ "tmgmt", "rules" ],
    "USES VARIABLES" : {
      "node" : { "label" : "Node", "type" : "node" },
      "tmgmt_job" : { "label" : "Main job", "type" : "tmgmt_job", "parameter" : false }
    },
    "ACTION SET" : [
      { "tmgmt_rules_create_job" : {
          "USING" : { "source_language" : "en" },
          "PROVIDE" : { "job" : { "tmgmt_main_job" : "Main job" } }
        }
      },
      { "tmgmt_rules_job_add_item" : {
          "job" : [ "tmgmt-main-job" ],
          "plugin" : "node",
          "item_type" : "node",
          "item_id" : [ "node:nid" ]
        }
      },
      { "data_set" : { "data" : [ "tmgmt-job" ], "value" : [ "tmgmt-main-job" ] } }
    ],
      "PROVIDES VARIABLES" : [ "tmgmt_job" ]
    }
  }';
  $rule = rules_import($data);
  $configs[$rule->name] = $rule;

  return $configs;
}

