<?php
/**
 * @file
 * nexteuropa_integration.features.inc
 */

/**
 * Implements hook_default_integration_backend().
 */
function nexteuropa_integration_default_integration_backend() {
  $items = array();
  $items['couchdb'] = entity_import('integration_backend', '{
    "formatter" : "json_formatter",
    "authentication" : "cookie_authentication",
    "name" : "CouchDB",
    "machine_name" : "couchdb",
    "plugin" : "couchdb_backend",
    "enabled" : "1",
    "settings" : {
      "plugin" : {
        "resource_schemas" : [ "department" ],
        "backend" : {
          "base_url" : "https:\\/\\/webgate.acceptance.ec.europa.eu\\/fpfis\\/ilayer\\/beta",
          "id_endpoint" : "\\/uuid"
        },
        "resource_schema" : { "department" : {
            "endpoint" : "\\/docs\\/type\\/department",
            "all_docs_endpoint" : "\\/docs\\/type\\/department\\/producer\\/prd",
            "changes_endpoint" : "\\/changes\\/type\\/department\\/producer\\/prd"
          }
        }
      },
      "components" : { "authentication_handler" : { "username" : "", "password" : "", "loginpath" : "\\/login" } }
    },
    "description" : null,
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_integration_resource_schema().
 */
function nexteuropa_integration_default_integration_resource_schema() {
  $items = array();
  $items['department'] = entity_import('integration_resource_schema', '{
    "name" : "Department",
    "machine_name" : "department",
    "plugin" : "raw_resource_schema",
    "enabled" : "1",
    "settings" : { "plugin" : { "fields" : {
          "title" : "Title",
          "department_type" : "Department type",
          "directorate_type" : "Directorate type",
          "main_task" : "Main task",
          "description" : "Description",
          "introduction" : "Introduction",
          "abbreviation" : "Abbreviation",
          "canonical_url" : "Canonical URL"
        }
      }
    },
    "description" : null,
    "rdf_mapping" : []
  }');
  return $items;
}
