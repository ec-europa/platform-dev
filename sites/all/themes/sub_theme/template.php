<?php
/**
 * @file
 * Default theme functions.
 */

// $Id: template.php,v 1.13 2010/12/14 01:04:27 dries Exp $

/**
 * Add body classes if certain regions have content.
 */
function eacea_preprocess_html(&$variables) {
  if (!empty($variables['page']['featured'])) {
    $variables['classes_array'][] = 'featured';
  }

  if (!empty($variables['page']['triptych_first'])
    || !empty($variables['page']['triptych_middle'])
    || !empty($variables['page']['triptych_last'])) {
    $variables['classes_array'][] = 'triptych';
  }

  if (!empty($variables['page']['footer_firstcolumn'])
    || !empty($variables['page']['footer_secondcolumn'])
    || !empty($variables['page']['footer_thirdcolumn'])
    || !empty($variables['page']['footer_fourthcolumn'])) {
    $variables['classes_array'][] = 'footer-columns';
  }

  // display left sidebar, or not
  if (empty($variables['page']['sidebar_left'])) {
    variable_set('has_left_sidebar', 0);
  } 
  else {
    variable_set('has_left_sidebar', 1);
  }

  // display right sidebar, or not
  if (empty($variables['page']['sidebar_right'])) {
    variable_set('has_right_sidebar', 0);
  } 
  else {
    variable_set('has_right_sidebar', 1);
  }

  // Update page title
  if (arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
    $variables['head_title'] = filter_xss($node->title) . ' - ' . t('European Commission');
  } 
  else {
    $variables['head_title'] = filter_xss(variable_get('site_name')) . ' - ' . t('European Commission');
  }  
  
  // Add specific css for font size switcher
  // it has to be done here, to add custom data
  global $base_url;
  $element = array(
    '#tag' => 'link', 
    '#attributes' => array( 
      'href' => $base_url . '/' . drupal_get_path('theme', 'ec_resp') . '/css/text_size_small.css', 
      'rel' => 'stylesheet',
      'type' => 'text/css',
      'data-name' => 'switcher',
    )
  );
  drupal_add_html_head($element, 'font_size_switcher');

  // Add conditional stylesheets for IE
  drupal_add_css(drupal_get_path('theme', 'ec_resp') . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));

  // Add javascripts
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/ec.js', array('scope' => 'footer', 'weight' => 10));
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/jquery.mousewheel-3.0.6.pack.js', array('scope' => 'footer', 'weight' => 11));
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/scripts.js', array('scope' => 'footer', 'weight' => 12));
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/hack.js', array('scope' => 'footer', 'weight' => 13));
  drupal_add_js(drupal_get_path('theme', 'eacea') . '/scripts/eacea.js', array('scope' => 'footer', 'weight' => 14));

}
