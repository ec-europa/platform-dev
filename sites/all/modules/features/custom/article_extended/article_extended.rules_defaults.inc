<?php
/**
 * @file
 * article_extended.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function article_extended_default_rules_configuration() {
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
            "component" : "rules_publish_content_rule_",
            "date" : [ "node:field-article-publication-date" ],
            "identifier" : "node_id_[node:nid]",
            "param_node" : [ "node" ]
          }
        },
        { "schedule" : {
            "component" : "rules_unpublish_content_rule_",
            "date" : [ "node:field-article-unpublish-on" ],
            "identifier" : "unpub_node_id_[node:nid]",
            "param_node" : [ "node" ]
          }
        }
      ]
    }
  }');
  return $items;
}
