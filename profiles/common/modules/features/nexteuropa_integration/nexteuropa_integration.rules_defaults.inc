<?php

/**
 * @file
 * Contains NextEuropa Integration default Rules configuration.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function nexteuropa_integration_default_rules_configuration() {
  $config = [];

  if (module_exists('nexteuropa_varnish') && module_exists('flexible_purge')) {
    // Invalidate Varnish cache after migration.
    $data = '
      { "rules_ne_ilayer_cache_invalidation_after_data_consumption" : {
          "LABEL" : "NE Integration: Cache Invalidation after data consumption",
          "PLUGIN" : "reaction rule",
          "WEIGHT" : "10",
          "ACTIVE" : false,
          "OWNER" : "rules",
          "TAGS" : [ "NE Integration" ],
          "REQUIRES" : [ "flexible_purge", "integration", "nexteuropa_varnish" ],
          "ON" : { "integration_consumer_post_import" : [] },
          "DO" : [ { "nexteuropa_varnish_invalidate_website_cache" : [] } ]
        }
      }
    ';
    $rule = rules_import($data);
    $config[$rule->name] = $rule;
  }

  return $config;
}
