<?php
/**
 * @file
 * sitemap.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sitemap_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_categories_depth';
  $strongarm->value = 'all';
  $export['site_map_categories_depth'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_css';
  $strongarm->value = 0;
  $export['site_map_css'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_forum_threshold';
  $strongarm->value = '-1';
  $export['site_map_forum_threshold'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_message';
  $strongarm->value = array(
    'value' => '',
    'format' => 'filtered_html',
  );
  $export['site_map_message'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_page_title';
  $strongarm->value = 'Site map';
  $export['site_map_page_title'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_rss_depth';
  $strongarm->value = 'all';
  $export['site_map_rss_depth'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_rss_front';
  $strongarm->value = 'rss.xml';
  $export['site_map_rss_front'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_show_count';
  $strongarm->value = 1;
  $export['site_map_show_count'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_show_front';
  $strongarm->value = 1;
  $export['site_map_show_front'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_show_menus';
  $strongarm->value = array(
    'main-menu' => 'main-menu',
    'management' => 0,
    'navigation' => 0,
    'user-menu' => 0,
  );
  $export['site_map_show_menus'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_show_rss_links';
  $strongarm->value = '1';
  $export['site_map_show_rss_links'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_show_vocabularies';
  $strongarm->value = array(
    1 => '1',
  );
  $export['site_map_show_vocabularies'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_map_term_threshold';
  $strongarm->value = '0';
  $export['site_map_term_threshold'] = $strongarm;

  return $export;
}
