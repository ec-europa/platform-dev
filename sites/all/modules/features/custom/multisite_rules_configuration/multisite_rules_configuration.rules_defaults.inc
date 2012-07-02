<?php
/**
 * @file
 * article_core.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cce_basic_config_default_rules_configuration() {
  $items = array();
  $items['rules_manage_article_node_publication'] = entity_import('rules_config', '{ "rules_manage_article_node_publication" : {
      "LABEL" : "Manage Article Node Publication",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Publication" ],
      "REQUIRES" : [ "rules", "rules_scheduler", "workbench_moderation" ],
      "ON" : [
        "node_insert",
        "node_update",
        "workbench_moderation_after_moderation_transition"
      ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } }
      ],
      "DO" : [
        { "schedule" : {
            "component" : "rules_publish_article_content_rule_",
            "date" : [ "node:field-article-publication-date" ],
            "identifier" : "node_id_[node:nid]",
            "param_node" : [ "node" ]
          }
        },
        { "schedule" : {
            "component" : "rules_unpublish_article_content_rule_",
            "date" : [ "node:field-article-unpublication-date" ],
            "identifier" : "unpub_node_id_[node:nid]",
            "param_node" : [ "node" ]
          }
        }
      ]
    }
  }');
  $items['rules_publish_article_content_rule_'] = entity_import('rules_config', '{ "rules_publish_article_content_rule_" : {
      "LABEL" : "Publish Article content {rule}",
      "PLUGIN" : "rule",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-article-publication-date" ] } },
        { "data_is" : {
            "data" : [ "node:field-article-publication-date" ],
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
  $items['rules_unpublish_article_content_rule_'] = entity_import('rules_config', '{ "rules_unpublish_article_content_rule_" : {
      "LABEL" : "UNpublish Article content {rule}",
      "PLUGIN" : "rule",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-article-unpublication-date" ] } },
        { "data_is" : {
            "data" : [ "node:field-article-unpublication-date" ],
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
