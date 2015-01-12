<?php
/**
 * @file
 * multisite_translations.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function multisite_translations_default_rules_configuration() {
  $items = array();
  $items['rules_job_notification'] = entity_import('rules_config', '{ "rules_job_notification" : {
      "LABEL" : "job translation notification",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "job translation" ],
      "REQUIRES" : [ "rules", "multisite_translations", "tmgmt" ],
      "ON" : { "tmgmt_job_update" : [] },
      "IF" : [ { "data_is" : { "data" : [ "tmgmt-job:state" ], "value" : "1" } } ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "job_translation_log",
              "param_user" : [ "tmgmt-job:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-job-reference" ],
            "value" : [ "tmgmt-job" ]
          }
        },
        { "mail_to_related_translation_role" : {
            "subject" : "translation request : [tmgmt-job:source-language] to [tmgmt-job:target-language]",
            "message" : "A new translation request has been made.\\r\\n[tmgmt-job:source-language] to [tmgmt-job:target-language]\\r\\nSee the request : [tmgmt-job:url]\\r\\n\\r\\n[entity-created:text]"
          }
        }
      ]
    }
  }');
  return $items;
}
