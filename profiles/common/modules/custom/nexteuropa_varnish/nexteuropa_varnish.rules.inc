<?php

/**
 * @file
 * Rules integration.
 */

module_load_include('inc', 'flexible_purge', 'flexible_purge.cache');

/**
 * Implements hook_rules_action_info().
 */
function nexteuropa_varnish_rules_action_info() {
  $actions = array(
    'nexteuropa_varnish_invalidate_website_cache' => array(
      'label' => t('Invalidate Varnish cache for the website'),
      'group' => t('Flexible Purge'),
    ),
  );

  return $actions;
}

/**
 * Invalidation of the Varnish cache for the whole website.
 */
function nexteuropa_varnish_invalidate_website_cache() {
  if (!class_exists('FlexiblePurgeCache')) {
    return;
  }
  $cache = new FlexiblePurgeCache('cache_page');

  // First trigger a clear operation on the actual backend cache, if any.
  $backend = $cache->keepCachingObject();
  if (!is_null($backend)) {
    $backend->clear(NULL, FALSE);
  }

  $cache->emitRequests(NULL, FALSE);
}
