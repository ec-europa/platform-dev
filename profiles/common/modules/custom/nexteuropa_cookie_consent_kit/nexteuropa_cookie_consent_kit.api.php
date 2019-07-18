<?php

/**
 * @file
 * Hooks for nexteuropa_cookie_consent_kit module.
 */

/**
 * Alter the query of nexteuropa cookie consent iframe query.
 */
function hook_nexteuropa_cookie_consent_kit_iframe_query_alter(&$query) {
  // Add new parameter.
  $query['key'] = 'value';

  // Override existing parameter.
  $query['lang'] = 'fr';
}
