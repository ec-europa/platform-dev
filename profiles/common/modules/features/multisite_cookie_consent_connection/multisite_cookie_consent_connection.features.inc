<?php
/**
 * @file
 * multisite_cookie_consent_connection.features.inc
 */

/**
 * Implements hook_clients_default_connections().
 */
function multisite_cookie_consent_connection_clients_default_connections() {
  $items = array();
  $items['csr'] = entity_import('clients_connection', '{
    "name" : "csr",
    "endpoint" : "http:\\/\\/csr.deglise.com",
    "configuration" : {
      "debug" : 0,
      "credentials_storage" : "connection_configuration",
      "username" : "x",
      "password" : "x"
    },
    "label" : "csr",
    "type" : "multisite_cookie_rest",
    "rdf_mapping" : []
  }');
  return $items;
}
