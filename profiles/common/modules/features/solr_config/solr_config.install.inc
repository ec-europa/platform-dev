<?php
/**
 * @file
 * Solr_config.install.inc file, helper functions.
 */

/**
 * Custom function to add solr facet blocks to the search context.
 */
function _solr_config_place_facets() {
  global $theme_key;

  if ($theme_key == 'ec_resp') {
    $region = 'sidebar_left';
  }
  else {
    $region = 'sidebar_first';
  }

  multisite_drupal_toolbox_add_block_context('search', 'facetapi-8o8kdtP8CKjahDIu1Wy5LGxnDHg3ZYnT', 'facetapi', '8o8kdtP8CKjahDIu1Wy5LGxnDHg3ZYnT', $region, -14);
  multisite_drupal_toolbox_add_block_context('search', 'facetapi-wWWinJ0eOefOtAMbjo2yl86Mnf1rO12j', 'facetapi', 'wWWinJ0eOefOtAMbjo2yl86Mnf1rO12j', $region, -15);
  multisite_drupal_toolbox_add_block_context('search', 'facetapi-odQxTWyhGW1WU7Sl00ISAnQ21BCdJG3A', 'facetapi', 'odQxTWyhGW1WU7Sl00ISAnQ21BCdJG3A', $region, -17);
  multisite_drupal_toolbox_add_block_context('search', 'facetapi-GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu', 'facetapi', 'GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu', $region, -16);
  multisite_drupal_toolbox_add_block_context('search', 'apachesolr_search-sort', 'apachesolr_search', 'sort', $region, -10);
}
