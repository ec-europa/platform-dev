<?php
/**
 * @file
 * API documentation for the Nexteuropa Core Views module.
 */

/**
 * Returns all available row styles for the Europa theme component plugin.
 *
 * @return array
 *   An array of row styles.
 */
function hook_nexteuropa_core_views_row_styles_info() {
  return array(
    'banner',
    'card',
    'blockquote',
    'timelines',
    'expandable',
  );
}
