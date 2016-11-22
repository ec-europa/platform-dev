<?php

/**
 * @file
 * Theme functions for layer.
 */

/**
 * Implements hook_theme().
 */
function ec_mapeditor_layer_theme($existing, $type, $theme, $path) {
  $theme = array();
  $theme['popup'] = array(
    'variables' => array(
      'title' => NULL,
      'description' => NULL,
      'url' => NULL,
    ),
  );
  return $theme;
}

/**
 * Defines markup for the map popup.
 */
function theme_popup(&$vars) {
  $output = "<div class='map_layer-popup'>";
  if (!empty($vars['url']) && !empty($vars['title'])) {
    $output .= "<h3 class='map-layer-popup-title'><a href='{$vars['url']}'>{$vars['title']}</a></h3>";
  }
  elseif (!empty($vars['title'])) {
    $output .= "<h3 class='map-layer-popup-title'>{$vars['title']}</h3>";
  }
  if (!empty($vars['description'])) {
    $output .= "<div class='map-layer-description'>{$vars['description']}</div>";
  }
  $output .= '</div>';
  return $output;
}
