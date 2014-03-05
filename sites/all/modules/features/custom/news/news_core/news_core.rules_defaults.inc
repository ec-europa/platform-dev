<?php
/**
 * @file
 * news_core.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function news_core_default_rules_configuration() {
  $items = array();
  $items['rules_manage_node_publication'] = entity_import('rules_config', '{ "rules_manage_node_publication" : {
      "LABEL" : "Manage Node Publication",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Publication" ],
      "REQUIRES" : [ "rules", "rules_scheduler", "workbench_moderation" ],
      "ON" : {
        "node_insert" : [],
        "node_update" : [],
        "workbench_moderation_after_moderation_transition" : []
      },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "news" : "news" } } } }
      ],
      "DO" : [
        { "schedule" : {
            "component" : "rules_publish_content_rule_",
            "date" : [ "node:field-news-publication-date" ],
            "identifier" : "publish_nid_[node:nid]_rev_id_[node:vid]",
            "param_node" : [ "node" ]
          }
        },
        { "schedule" : {
            "component" : "rules_unpublish_content_rule_",
            "date" : [ "node:field-news-unpublication-date" ],
            "identifier" : "unpublish_nid_[node:nid]_rev_id_[node:vid]",
            "param_node" : [ "node" ]
          }
        }
      ]
    }
  }');
  $items['rules_publish_content_rule_'] = entity_import('rules_config', '{ "rules_publish_content_rule_" : {
      "LABEL" : "Publish content {rule}",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "news" : "news" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-news-publication-date" ] } },
        { "data_is" : {
            "data" : [ "node:field-news-publication-date" ],
            "op" : "\\u003C",
            "value" : "now"
          }
        },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "validated" } }
      ],
      "DO" : [
        { "workbench_moderation_load_current_revision" : {
            "USING" : { "node" : [ "node" ] },
            "PROVIDE" : { "node_revision" : { "node_revision" : "Current node revision" } }
          }
        },
        { "workbench_moderation_set_state" : {
            "node" : [ "node-revision" ],
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
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "news" : "news" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-news-unpublication-date" ] } },
        { "data_is" : {
            "data" : [ "node:field-news-unpublication-date" ],
            "op" : "\\u003C",
            "value" : "now"
          }
        },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } }
      ],
      "DO" : [
        { "workbench_moderation_set_state_and_unpublish" : {
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
