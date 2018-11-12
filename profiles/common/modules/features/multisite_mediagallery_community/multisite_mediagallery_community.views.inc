<?php

/**
 * @file
 * Provides support for the views module.
 */

/**
 * Implements hook_views_data().
 */
function multisite_mediagallery_community_views_data() {
  $data = array();
  $data['views']['multisite_mediagallery_link'] = array(
    'title' => t('Create Media Gallery'),
    'help' => t('Link to create Media Gallery'),
    'area' => array(
      'handler' => 'views_handler_area_media_link',
    ),
  );
  return $data;
}
