<?php

/**
 * @file
 * Varnish drush commands.
 */

/**
 * Drush commands.
 */
function nexteuropa_varnish_drush_command() {
  $items = array();

  $items['varnish_flush_cache'] = array(
    'description' => "Varnish clear cache.",
    'examples' => array(
      'drush varnish-flush-cache' => 'Varnish clear cache.',
    ),
    'aliases' => array('vcc'),
  );

  return $items;
}

/**
 * Varnish clear cache.
 */
function drush_nexteuropa_varnish_varnish_flush_cache() {
  _nexteuropa_varnish_varnish_requests_send();
}
