<?php
/**
 * @file
 * Provides support for the views module.
 */

/**
 * Implements hook_views_data().
 */
function communities_views_data() {
  $data = array();
  $data['views']['communities_glossary'] = array(
    'title' => t('Communities Glossary'),
    'help' => t('Display glossary'),
    'area' => array(
      'handler' => 'views_handler_area_communities_glossary',
    ),
  );

  $data['views']['communities_create_new_community'] = array(
    'title' => t('Create a new community link'),
    'help' => t('Display a button to create a new community'),
    'area' => array(
      'handler' => 'views_handler_area_communities_create_new_community_link',
    ),
  );

  return $data;
}
