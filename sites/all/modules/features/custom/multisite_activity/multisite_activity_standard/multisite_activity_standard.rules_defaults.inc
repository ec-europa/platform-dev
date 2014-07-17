<?php
/**
 * @file
 * multisite_activity_standard.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function multisite_activity_standard_default_rules_configuration() {
  $items = array();
  $items['rules_log_comments'] = entity_import('rules_config', '{ "rules_log_comments" : {
      "LABEL" : "Log comments",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : { "comment_insert" : [] },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "multisite_create_comment",
              "param_user" : [ "comment:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-node-ref" ],
            "value" : [ "comment:node" ]
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-published" ], "value" : 1 } }
      ]
    }
  }');
  $items['rules_log_deleted_content'] = entity_import('rules_config', '{ "rules_log_deleted_content" : {
      "LABEL" : "Log deleted content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_delete" : [] },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "multisite_content_delete",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-node-ref" ], "value" : [ "node" ] } },
        { "data_set" : { "data" : [ "entity-created:field-published" ], "value" : 1 } }
      ]
    }
  }');
  $items['rules_log_new_content'] = entity_import('rules_config', '{ "rules_log_new_content" : {
      "LABEL" : "Log new content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "OR" : [
            { "NOT content_is_using_workbench_moderation" : { "node" : [ "node" ] } },
            { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } }
          ]
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "multisite_create_node",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-node-ref" ], "value" : [ "node" ] } },
        { "data_set" : { "data" : [ "entity-created:field-published" ], "value" : 1 } }
      ]
    }
  }');
  $items['rules_log_new_revision'] = entity_import('rules_config', '{ "rules_log_new_revision" : {
      "LABEL" : "Log first published revision",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "AND" : [
            { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } },
            { "NOT node_is_published" : { "node" : [ "node" ] } }
          ]
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "multisite_create_node",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-node-ref" ], "value" : [ "node" ] } },
        { "data_set" : { "data" : [ "entity-created:field-published" ], "value" : 1 } }
      ]
    }
  }');
  $items['rules_log_nth_published_revision'] = entity_import('rules_config', '{ "rules_log_nth_published_revision" : {
      "LABEL" : "Log nth published revision",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } },
        { "node_is_published" : { "node" : [ "node" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "multisite_content_update",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-node-ref" ], "value" : [ "node" ] } },
        { "data_set" : { "data" : [ "entity-created:field-published" ], "value" : 1 } }
      ]
    }
  }');
  $items['rules_log_updated_content'] = entity_import('rules_config', '{ "rules_log_updated_content" : {
      "LABEL" : "Log updated content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : { "node_update" : [] },
      "IF" : [
        { "NOT content_is_using_workbench_moderation" : { "node" : [ "node" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "multisite_content_update",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-node-ref" ], "value" : [ "node" ] } },
        { "data_set" : { "data" : [ "entity-created:field-published" ], "value" : 1 } }
      ]
    }
  }');
  return $items;
}
