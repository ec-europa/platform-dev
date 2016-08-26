<?php

/**
 * @file
 * Contains default rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function nexteuropa_varnish_default_rules_configuration() {
  $config = [];
  // Invalidate cache after create and update of published nodes.
  $data = '
    { "rules_fp_invalidate_cache_after_create_update" : {
        "LABEL" : "NE Flexible Purge: Invalidate cache after create or update published content",
        "PLUGIN" : "reaction rule",
        "WEIGHT" : "10",
        "ACTIVE" : false,
        "OWNER" : "rules",
        "TAGS" : [ "NE Flexible Purge" ],
        "REQUIRES" : [ "workbench_moderation", "flexible_purge", "rules" ],
        "ON" : { "node_insert" : [], "node_update" : [] },
        "IF" : [
          { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } }
        ],
        "DO" : [ { "nexteuropa_varnish_invalidate_website_cache" : [] } ]
      }
    }
  ';
  $rule = rules_import($data);
  $config[$rule->name] = $rule;

  // Invalidate cache after delete.
  $data = '
    { "rules_fp_invalidate_cache_after_deleting" : {
        "LABEL" : "NE Flexible Purge: Invalidate cache after deleting content",
        "PLUGIN" : "reaction rule",
        "WEIGHT" : "10",
        "ACTIVE" : false,
        "OWNER" : "rules",
        "TAGS" : [ "NE Flexible Purge" ],
        "REQUIRES" : [ "flexible_purge", "rules" ],
        "ON" : { "node_delete" : [] },
        "DO" : [ { "nexteuropa_varnish_invalidate_website_cache" : [] } ]
      }
    }
  ';
  $rule = rules_import($data);
  $config[$rule->name] = $rule;

  return $config;

}
