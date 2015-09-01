<?php

/**
 * @file
 * Theme functions for mapeditor.
 */

/**
 * Implements hook_theme().
 */
function mapeditor_theme($existing, $type, $theme, $path) {
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
  $output = "<div class='mapeditor-popup'>";
  if (!empty($vars['url']) && !empty($vars['title'])) {
    $output .= "<h3 class='mapeditor-popup-title'><a href='{$vars['url']}'>{$vars['title']}</a></h3>";
  }
  elseif (!empty($vars['title'])) {
    $output .= "<h3 class='mapeditor-popup-title'>{$vars['title']}</h3>";
  }
  if (!empty($vars['description'])) {
    $output .= "<div class='mapeditor-description'>{$vars['description']}</div>";
  }
  $output .= '</div>';
  return $output;
}
