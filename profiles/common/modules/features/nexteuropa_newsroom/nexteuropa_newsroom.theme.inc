<?php

/**
 * @file
 * Theme hooks.
 */

/**
 * Implements hook_theme().
 */
function nexteuropa_newsroom_theme($existing, $type, $theme, $path) {
  $theme_path = $path . '/theme';
  return array(
    'newsroom_services_page' => array(
      'variables' => array(
        'central_items' => NULL,
        'basic_items' => NULL,
        'privacy_statement' => NULL,
      ),
      'template' => 'newsroom-service-page',
      'path' => $theme_path,
    ),
    'newsroom_services_items' => array(
      'variables' => array(
        'items' => array(),
        'css_class' => NULL,
        'title' => NULL,
        'universe_id' => NULL,
      ),
      'template' => 'newsroom-service-items',
      'path' => $theme_path,
    ),
    'newsroom_related_content' => array(
      'variables' => array(
        'parent_item' => NULL,
        'current_item' => NULL,
        'children_items' => array(),
        'brother_items' => array(),
      ),
      'template' => 'newsroom-related-content',
      'path' => $theme_path,
    ),
    'newsroom_zoomable_image' => array(
      'variables' => array(
        'image_output' => NULL,
        'path' => NULL,
        'image_style' => NULL,
        'title' => NULL,
        'copyright' => NULL,
        'caption' => NULL,
        'path_to_original' => NULL,
        'zoomable' => FALSE,
        'display_title' => FALSE,
      ),
      'template' => 'newsroom-zoomable-image',
      'path' => $theme_path,
    ),
    'newsroom_summary_block' => array(
      'variables' => array(
        'content' => NULL,
        'rss' => NULL,
      ),
      'template' => 'newsroom-summary-block',
      'path' => $theme_path,
    ),
    'newsroom_summary_block_wrapper' => array(
      'variables' => array(
        'items' => array(),
        'title' => NULL,
        'classes' => array(),
        'type_url' => NULL,
        'url' => NULL,
      ),
      'template' => 'newsroom-summary-block-wrapper',
      'path' => $theme_path,
    ),
    'newsroom_summary_block_item' => array(
      'variables' => array(
        'items' => array(),
      ),
      'template' => 'newsroom-summary-block-item',
      'path' => $theme_path,
    ),
    'newsroom_agenda_page' => array(
      'variables' => array(
        'filter_form' => NULL,
        'date_form' => NULL,
        'next_event_items' => array(),
        'items' => array(),
        'navigation' => NULL,
        'is_block' => FALSE,
      ),
      'template' => 'newsroom-agenda-page',
      'path' => $theme_path,
    ),
    'newsroom_agenda_items' => array(
      'variables' => array(
        'items' => array(),
      ),
      'template' => 'newsroom-agenda-items',
      'path' => $theme_path,
    ),
    'newsroom_agenda_date' => array(
      'variables' => array(
        'day' => NULL,
        'month' => NULL,
        'year' => NULL,
      ),
      'template' => 'newsroom-agenda-date',
      'path' => $theme_path,
    ),
    'newsroom_page' => array(
      'variables' => array(
        'items' => NULL,
        'featured_item' => NULL,
      ),
      'template' => 'newsroom-page',
      'path' => $theme_path,
    ),
    'newsroom_page_item' => array(
      'variables' => array(
        'items' => NULL,
      ),
      'template' => 'newsroom-page-item',
      'path' => $theme_path,
    ),
    'newsroom_page_featured_item' => array(
      'variables' => array(
        'type' => NULL,
        'title' => NULL,
        'image' => NULL,
        'created' => NULL,
        'teaser' => NULL,
      ),
      'template' => 'newsroom-page-featured-item',
      'path' => $theme_path,
    ),
    'newsroom_page_rss' => array(
      'variables' => array(
        'title' => NULL,
        'namespaces' => NULL,
        'description' => NULL,
        'langcode' => NULL,
        'items' => NULL,
      ),
      'template' => 'newsroom-page-rss',
      'path' => $theme_path,
    ),
    'newsroom_page_rss_item' => array(
      'variables' => array(
        'title' => NULL,
        'link' => NULL,
        'description' => NULL,
        'url' => NULL,
      ),
      'template' => 'newsroom-page-rss-item',
      'path' => $theme_path,
    ),
  );
}
