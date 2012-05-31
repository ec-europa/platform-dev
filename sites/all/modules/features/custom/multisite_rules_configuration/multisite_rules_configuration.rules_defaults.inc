<?php
/**
 * @file
 * rules_pubication.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rules_pubication_default_rules_configuration() {
  $items = array();
  $items['rules_manage_node_publication'] = entity_import('rules_config', '{ "rules_manage_node_publication" : {
      "LABEL" : "Manage Node Publication",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Publication" ],
      "REQUIRES" : [ "rules", "rules_scheduler" ],
      "ON" : [ "node_insert", "node_update" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } }
      ],
      "DO" : [
        { "schedule" : {
            "component" : "rules_publish_content_rule_",
            "date" : [ "node:field-date-publication" ],
            "identifier" : "node_id_[node:nid]",
            "param_node" : [ "node" ]
          }
        },
        { "schedule" : {
            "component" : "rules_unpublish_content_rule_",
            "date" : [ "node:field-date-unpublication" ],
            "identifier" : "unpub_node_id_[node:nid]",
            "param_node" : [ "node" ]
          }
        }
      ]
    }
  }');
  $items['rules_publish_content_rule_'] = entity_import('rules_config', '{ "rules_publish_content_rule_" : {
      "LABEL" : "Publish content {rule}",
      "PLUGIN" : "rule",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "news" : "news" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-date-publication" ] } },
        { "data_is" : {
            "data" : [ "node:field-date-publication" ],
            "op" : "\\u003C",
            "value" : "now"
          }
        },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "validated" } }
      ],
      "DO" : [
        { "workbench_moderation_set_state" : {
            "node" : [ "node" ],
            "moderation_state" : "published",
            "force_transition" : 1
          }
        }
      ]
    }
  }');
  $items['rules_unpublish_content_rule_'] = entity_import('rules_config', '{ "rules_unpublish_content_rule_" : {
      "LABEL" : "UNpublish content {rule}",
      "PLUGIN" : "rule",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "news" : "news" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-date-unpublication" ] } },
        { "data_is" : {
            "data" : [ "node:field-date-unpublication" ],
            "op" : "\\u003C",
            "value" : "now"
          }
        },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } }
      ],
      "DO" : [
        { "workbench_moderation_set_state" : {
            "node" : [ "node" ],
            "moderation_state" : "archived",
            "force_transition" : 1
          }
        }
      ]
    }
  }');
  return $items;
}
