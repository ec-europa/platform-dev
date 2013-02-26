<?php
/**
 * @file
 * cce_basic_config.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cce_basic_config_default_rules_configuration() {
  $items = array();
  $items['rules_manage_article_node_publication'] = entity_import('rules_config', '{ "rules_manage_article_node_publication" : {
      "LABEL" : "Manage Article Node Publication",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
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
            "component" : "rules_publish_article",
            "date" : [ "node:field-article-publication-date" ],
            "identifier" : "publish_nid_[node:nid]_rev_id_[node:vid]"
          }
        },
        { "schedule" : {
            "component" : "rules_unpublish_article",
            "date" : [ "node:field-article-unpublish-on" ],
            "identifier" : "unpublish_nid_[node:nid]_rev_id_[node:vid]"
          }
        }
      ]
    }
  }');
  return $items;
}
