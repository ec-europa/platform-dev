<?php
/**
 * @file
 * Default theme functions.
 */

// $Id: template.php,v 1.13 2010/12/14 01:04:27 dries Exp $

/**
 * Preprocess hooks
 */

function ec_resp_150_preprocess(&$variables) {
  //select template
  $variables['template'] = 'ec'; //'ec' or 'europa'

  //select responsive sidebar
  $variables['responsive_sidebar'] = 'both'; //'left', 'right' or 'both'
}

function ec_resp_150_preprocess_node(&$variables) {
  $custom_date = format_date($variables['created'], 'custom', 'l, d/m/Y');
  $variables['submitted'] = t('Published by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $custom_date));
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
}

function ec_resp_150_preprocess_block(&$variables) {
  // In the header region visually hide block titles.
  if ($variables['block']->region == 'header') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }
}

function ec_resp_150_preprocess_select(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}
function ec_resp_150_preprocess_textfield(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}
function ec_resp_150_preprocess_password(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}
function ec_resp_150_preprocess_textarea(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}

function ec_resp_150_preprocess_username(&$variables) {
  //$variables['attributes_array']['class'][] = 'list-group-item';
}

function ec_resp_150_preprocess_maintenance_page(&$variables) {
  if (!$variables['db_is_active']) {
    unset($variables['site_name']);
  }
  drupal_add_css(drupal_get_path('theme', 'ec_resp_150') . '/css/maintenance-page.css');
}

function ec_resp_150_preprocess_html(&$variables) {
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
      'href' => $base_url . '/' . drupal_get_path('theme', 'ec_resp_150') . '/css/text_size_small.css', 
      'rel' => 'stylesheet',
      'type' => 'text/css',
      'data-name' => 'switcher',
    )
  );
  drupal_add_html_head($element, 'font_size_switcher');

  // Add conditional stylesheets for IE
  drupal_add_css(drupal_get_path('theme', 'ec_resp_150') . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));

  // Add javascripts
  drupal_add_js(drupal_get_path('theme', 'ec_resp_150') . '/scripts/ec.js', array('scope' => 'footer', 'weight' => 10));
  drupal_add_js(drupal_get_path('theme', 'ec_resp_150') . '/scripts/jquery.mousewheel-3.0.6.pack.js', array('scope' => 'footer', 'weight' => 11));
  drupal_add_js(drupal_get_path('theme', 'ec_resp_150') . '/scripts/scripts.js', array('scope' => 'footer', 'weight' => 12));
  drupal_add_js(drupal_get_path('theme', 'ec_resp_150') . '/scripts/hack.js', array('scope' => 'footer', 'weight' => 13));  
}


/**
 * Process hooks
 */
function ec_resp_150_process_maintenance_page(&$variables) {
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss(variable_get('site_slogan', ''));
  }
}

function ec_resp_150_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

function ec_resp_150_process_page(&$variables) {
  
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss(variable_get('site_slogan', ''));
  }
  // Since the title and the shortcut link are both block level elements,
  // positioning them next to each other is much simpler with a wrapper div.
  if (!empty($variables['title_suffix']['add_or_remove_shortcut']) && $variables['title']) {
    // Add a wrapper div using the title_prefix and title_suffix render elements.
    $variables['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $variables['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
    );
    // Make sure the shortcut link is the first item in title_suffix.
    $variables['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }
}


/**
 * Alter page header 
 */
function ec_resp_150_page_alter($page) {
  global $language;
  if (arg(0) == 'node') {
    $node = node_load(arg(1));
    if(isset($node->title))
      $node_title = filter_xss($node->title);
  }
  
  $description = variable_get('site_slogan');
  if (empty($description)) {
    $description = filter_xss(variable_get('site_name'));
  }  
  if (!empty($node)) {
    $description = $node_title . ' - ' . $description;
  }
  
  $title = filter_xss(variable_get('site_name')) . ' - ' . t('European Commission');
  if (!empty($node)) {
    $title = $node_title . ' - ' . $title;
  }  
  
  $keywords = '';
  if (!empty($node) && !empty($node->field_tags)) {
    $tags = field_view_field('node', $node, 'field_tags');
    if (isset($tags['#items'])) {
      foreach ($tags['#items'] as $key => $value) {
        $keywords .= $value['taxonomy_term']->name . ', ';
      }
    }
  }  
  $keywords .=  filter_xss(variable_get('site_name')).', ';
  $keywords .= 'European Commission, European Union, EU';
  
  $type = 'website';
  if (!empty($node)) {
    $type = $node->type;
  }  
  
  //Content-Language
  $meta_content_language = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'Content-Language',
      'content' =>  $language->language    
    )
  );
  drupal_add_html_head( $meta_content_language, 'meta_content_language' );
  
  //description
  $meta_description = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'description',
      'content' => $description   
    )
  );
  drupal_add_html_head( $meta_description, 'meta_description' );  
  
  //reference
  $meta_reference = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'reference',
      'content' =>  filter_xss(variable_get('site_name'))    
    )
  );
  drupal_add_html_head( $meta_reference, 'meta_reference' );    
  
  //creator
  $meta_creator = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'creator',
      'content' =>  'COMM/DG/UNIT'    
    )
  );
  drupal_add_html_head( $meta_creator, 'meta_creator' );      
  
  //IPG classification
  $classification = variable_get('meta_configuration', 'none');
    if ($classification != 'none') {
    $meta_classification = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'classification',
        'content' =>  variable_get('meta_configuration', 'none')
      )
    );
    drupal_add_html_head($meta_classification, 'meta_classification');      
  } 
  else {
    if (user_access('administer site configuration')) {
      drupal_set_message(t('Please select the IPG classification of your site') . ' ' . l(t('here.'), 'admin/config/system/site-information'), 'warning');
    }
  }
  
  //keywords
  $meta_keywords = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'keywords',
      'content' =>  $keywords  
    )

  );
  drupal_add_html_head( $meta_keywords, 'meta_keywords' ); 

  //date
  $meta_date = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'date',
      'content' =>  date('d/m/Y')   
    )
  );
  drupal_add_html_head( $meta_date, 'meta_date' );     
  
  //og title
  $meta_og_title = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'property' => 'og:title',

      'content' =>  $title
    )
  );
  drupal_add_html_head( $meta_og_title, 'meta_og_title' ); 

  //og type
  $meta_og_type = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'property' => 'og:type',
      'content' =>  $type
    )
  );
  drupal_add_html_head( $meta_og_type, 'meta_og_type' );
  
  //og site name
  $meta_og_site_name = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'property' => 'og:site_name',
      'content' =>  filter_xss(variable_get('site_name'))
    )
  );
  drupal_add_html_head( $meta_og_site_name, 'meta_og_site_name' );
  
  //og description
  $meta_og_description = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'property' => 'og:description',
      'content' =>  $description
    )
  );
  drupal_add_html_head( $meta_og_description, 'meta_og_description' );  
  
  //fb admins
  $meta_fb_admins = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'property' => 'fb:admins',
      'content' =>  'USER_ID'
    )
  );
  drupal_add_html_head( $meta_fb_admins, 'meta_fb_admins' );  
  
  //robots
  $meta_robots = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'property' => 'robots',
      'content' =>  'follow,index'
    )
  );
  drupal_add_html_head( $meta_robots, 'meta_robots' );  
  
  //revisit after
  $revisit_after = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'property' => 'revisit-after',
      'content' =>  '15 Days'
    )
  );
  drupal_add_html_head( $revisit_after, 'revisit-after' );  

  //viewport
  $viewport = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' =>  'width=device-width, initial-scale=1.0'
    )
  );
  drupal_add_html_head( $viewport, 'viewport' );    
}

/**
 * Implements hook_block_view_alter().
 */
function ec_resp_150_block_view_alter(&$data, $block) {

  if ($block->region == 'sidebar_left' || $block->region == 'sidebar_right') { 
    // add classes to list 
    $data['content'] = (isset($data['content']) ? str_replace('<ul>','<ul class="list-group list-group-flush list-unstyled">',$data['content']) : '');

    // add classes to list items
    if (!is_array($data['content'])) {
      preg_match_all('/<a(.*?)>/s', $data['content'], $matches);

      if (isset($matches[0])) {
        foreach ($matches[0] as $link) {
          if (strpos($link,' class="') !== false) {
            $new_link = str_replace(' class="', ' class="list-group-item ', $link);
          }
          else if (strpos($link," class='") !== false) {
            $new_link = str_replace(" class='", " class='list-group-item ", $link);
          }
          else {
            $new_link = str_replace(' href=', ' class="list-group-item" href=', $link);
          }
          $data['content'] = str_replace($link, $new_link, $data['content']);
        }
      }   
    }
  }
}

/**
 * Implements theme_form_element().
 */
function ec_resp_150_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $type_clean = strtr($element['#type'], '_', '-');
    $attributes['class'][] = 'form-type-' . $type_clean;
    if ($type_clean === 'radio' || $type_clean === 'checkbox') {
      $attributes['class'][] = $type_clean;
    }
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Implements theme_button().
 */
function ec_resp_150_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  $element['#attributes']['class'][] = 'btn btn-default';
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Implements theme_menu_tree().
 */
function ec_resp_150_menu_tree($variables) {
  return '<ul class="menu clearfix">' . $variables['tree'] . '</ul>';
}

function ec_resp_150_menu_tree__main_menu($variables) {
  if (strpos($variables['tree'], 'main_menu_dropdown')) {
  //there is a dropdown in this tree (using a specific term "main_menu_dropdown" to avoid mistakes)
    $variables['tree'] = str_replace('<ul class="nav navbar-nav">', '<ul class="dropdown-menu">', $variables['tree']);
    return '<ul class="nav navbar-nav">' . $variables['tree'] . '</ul>';  
  } 
  else {
  //there is no dropdown in this tree, simply return it in a <ul>
    return '<ul class="nav navbar-nav">' . $variables['tree'] . '</ul>';
  }
}

/**
 * Implements theme_menu_link().
 */
function ec_resp_150_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $element['#localized_options']['html'] = TRUE;
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function ec_resp_150_menu_link__main_menu(array $variables) {
  $element = $variables['element'];
  $dropdown = '';
  $name_id = strtolower(strip_tags(str_replace(' ', '', $element['#title'])));
// remove colons and anything past colons
  if (strpos($name_id, ':')) $name_id = substr ($name_id, 0, strpos($name_id, ':'));
//Preserve alphanumerics and numbers, everything else goes away
  $pattern = '/([^a-z]+)([^0-9]+)/';
  $name_id = preg_replace($pattern, '', $name_id);  
  $element['#attributes']['class'][] = 'item' . $element['#original_link']['mlid'];

  if ($element['#below'] && !theme_get_setting('disable_dropdown_menu')) {
  //Menu item has dropdown
    if (!in_array('dropdown-submenu', $element['#attributes']['class'])) {
      $element['#title'] .= '<b class="caret"></b>';
    }

    //get first child item (we only need to add a class to the first item)
    $current = current($element['#below']);
    $id = $current['#original_link']['mlid'];
    
    //add class to specify it is a dropdown
    $element['#below'][$id]['#attributes']['class'][] = 'main_menu_dropdown';
    if (!in_array('dropdown-submenu', $element['#attributes']['class'])) {
      $element['#attributes']['class'][] = 'dropdown';
    }
    
    //test if there is a sub-dropdown
    foreach ($element['#below'] as $key => $value) {
      if (is_numeric($key) && $value['#below']) {
        $sub_current = current($value['#below']);
        $sub_id = $sub_current['#original_link']['mlid'];      
        //add class to specify it is a sub-dropdown
        $element['#below'][$key]['#below'][$sub_id]['#attributes']['class'][] = 'main_menu_sub_dropdown';
        $element['#below'][$key]['#attributes']['class'][] = 'dropdown-submenu';
      }
    }   
    
    $element['#attributes']['id'][] = $name_id;   
    $element['#localized_options']['fragment'] = $name_id;
    $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    $element['#localized_options']['attributes']['data-toggle'][] = 'dropdown';
    $element['#localized_options']['html'] = TRUE;    
    $output = l($element['#title'], '', $element['#localized_options']);
    
    $dropdown = drupal_render($element['#below']);

  } 
  else {
  //No dropdown
    $element['#localized_options']['html'] = TRUE;
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  }

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $dropdown . "</li>\n";
}


/**
 * Implements theme_field__field_type().
 */
function ec_resp_150_field__taxonomy_term_reference($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h3 class="field-label">' . $variables['label'] . ': </h3>';
  }

  // Render the items.
  $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }
  $output .= '</ul>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '">' . $output . '</div>';

  return $output;
}

/**
 * Alter tabs
 */
function ec_resp_150_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs nav-justified tabs-primary">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="nav nav-pills tabs-secondary">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  
  return $output;
}

/**
 * Hook form alter
 */
function ec_resp_150_form_alter(&$form, &$form_state, $form_id) { //print $form_id;
  switch ($form_id) {
    case 'search_block_form':
      $form['search_block_form']['#attributes']['placeholder'][] = t('Search');

      $form['actions']['submit']['#type'] = 'image_button';
      $form['actions']['submit']['#src'] = drupal_get_path('theme', 'ec_resp_150') . '/images/search-button.png';
      $form['actions']['submit']['#attributes']['class'][] = 'btn btn-default btn-small';
      break;

    case 'apachesolr_search_custom_page_search_form':
    case 'search_form':
      $form['basic']['#attributes']['class'][] = 'input-group';
      $form['basic']['keys']['#title'] = '';
      $form['basic']['keys']['#attributes']['placeholder'][] = t('Search');
      $form['basic']['submit']['#type'] = 'image_button';
      $form['basic']['submit']['#src'] = drupal_get_path('theme', 'ec_resp_150') . '/images/search-button.png';
      $form['basic']['submit']['#attributes']['class'][] = 'btn btn-default btn-small';
      break;

    case 'add_media_form':
      $form['submit']['#attributes']['class'][] = 'btn btn-default';
      break;
      
    case 'comment_admin_overview':
      $form['options']['submit']['#attributes']['class'][] = 'btn-small';
      break;

    case 'views_exposed_form':
      if (isset($form['submit'])) {
        $form['submit']['#attributes']['class'][] = 'btn-small';
      }
      break;

    default:
      break;
  }

  $content_types = node_type_get_types();
  foreach ($content_types as $content_type) {
    if ($form_id === $content_type->type . "_node_form") {
      $form['actions']['submit']['#attributes']['class'][] = 'btn btn-default';
      $form['actions']['preview']['#attributes']['class'][] = 'btn btn-default';
    }
  }
  $form['#after_build'][] = 'ec_resp_150_cck_alter';
}

/**
 * #after_build function to modify CCK fields
 */
function ec_resp_150_cck_alter($form, &$form_state) {
  //hide format field
  if (!user_access('administer nodes')) {
    $form['comment_body']['und'][0]['format']['#prefix'] = "<div class='hide'>";
    $form['comment_body']['und'][0]['format']['#suffix'] = "</div>";

    $form['body']['und'][0]['format']['#prefix'] = "<div class='hide'>";
    $form['body']['und'][0]['format']['#suffix'] = "</div>";
  }
  
  return $form;
}

/**
 * Returns HTML for a link.
 * @param type $variables 
 */
function ec_resp_150_link( $variables ) {
  $decoration = '';
  $action_bar_before = '';
  $action_bar_after = '';
  $btn_group_before = '';
  $btn_group_after = '';  

  if (!isset($variables['options']['attributes']['class'])) {
    $variables['options']['attributes']['class'] = '';
  }
  
  if (isset($variables['options']['attributes']['action_bar'])) {
    switch ( $variables['options']['attributes']['action_bar'] ) {
      case 'first':
        $action_bar_before .= '<div class="form-actions btn-toolbar action_bar">';
        break;
      case 'last':
        $action_bar_after .= '</div>';
        break;
      case 'single':
        $action_bar_before .= '<div class="form-actions btn-toolbar action_bar">';
        $action_bar_after .= '</div>';
        break;        
      default:
        break;
    }
  }
  
  if (isset($variables['options']['attributes']['btn_group'])) {
    switch ( $variables['options']['attributes']['btn_group'] ) {
      case 'first':
        $btn_group_before .= '<div class="btn-group">';
        break;
      case 'last':
        $btn_group_after .= '</div>';
        break;
      case 'single':
        $btn_group_before .= '<div class="btn-group">';
        $btn_group_after .= '</div>';
        break;  
      default:
        break;
    }
  }  
  
  if (isset($variables['options']['attributes']['type'])) {
    switch ($variables['options']['attributes']['type']) {
      case 'add':
        $decoration .= '<span class="glyphicon glyphicon-plus"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-success';
        break;
      case 'expand':
        $decoration .= '<span class="glyphicon glyphicon-chevron-down"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-default btn-sm';
        break;
      case 'collapse':
        $decoration .= '<span class="glyphicon glyphicon-chevron-up"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-default btn-sm';
        break;
      case 'delete':
        $decoration .= '<span class="glyphicon glyphicon-trash"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-danger';
        break;
      case 'edit':
        $decoration .= '<span class="glyphicon glyphicon-pencil"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-info';
        break;
      case 'message':
        $decoration .= '<span class="glyphicon glyphicon-envelope"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-primary';
        break;        
      case 'login':
        $decoration .= '<span class="glyphicon glyphicon-log-in"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-default';
        break;
      case 'logout':
        $decoration .= '<span class="glyphicon glyphicon-log-out"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-default btn-xs';
        break;
      case 'user':
        $decoration .= '<span class="glyphicon glyphicon-user"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-default btn-xs';
        break;
      case 'workbench':
        $decoration .= '<span class="glyphicon glyphicon-list-alt"></span>';
        $variables['options']['attributes']['class'] .= ' btn btn-info btn-xs';
        break;
      case 'small':
        $variables['options']['attributes']['class'] .= ' btn btn-default btn-sm';
        break;        
      default:
        break;
    }
  }
  
  $output = $action_bar_before . $btn_group_before . '<a href="' . 
    check_plain(url($variables['path'], $variables['options'])) . '"' . 
    drupal_attributes($variables['options']['attributes']) . '>' . 
    $decoration . ($variables['options']['html'] ? 
      $variables['text'] : check_plain($variables['text'])) . 
    '</a>' . $btn_group_after . $action_bar_after;
  return $output;
}

/**
 * Returns HTML for a dropdown.
 * @param type $variables 
 */
function ec_resp_150_dropdown($variables) {
  
  $items = $variables['items'];
  $attributes = array();

  $output="";
  if (!empty($items)) {
  if (theme_get_setting('disable_dropdown_menu'))
    $output .= "<ul>";
    else
    $output .= "<ul class='dropdown-menu'>";
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      $output .= '<li>' . $data . "</li>\n";
    }
    $output .= "</ul>";
  }
  return $output;  
}

/**
 * render a block (to be displayed in a template file)
 */
function ec_resp_150_block_render($module, $block_id) {
  $block = block_load($module, $block_id);
  $block_content = _block_render_blocks(array($block));
  $build = _block_get_renderable_array($block_content);
  $block_rendered = drupal_render($build);
  return $block_rendered;
}


function ec_resp_150_icon_type_classes($subject) {
  $pattern = '@<i class="icon-(.+)"></i>@';
  $resexp = preg_replace_callback($pattern, 'ec_resp_150_class_replace', $subject);
  return $resexp;
}

function ec_resp_150_class_replace($match) {
  switch ($match[1]) {
    case "Article":
      return '<i class="multisite-icon-file"></i>';
    break;
    
    case "community":
      return '<i class="multisite-icon-group"></i>';
    break;
    
    case "Document":

      return '<i class="multisite-icon-newspaper"></i>';
    break;
    
    case "Event":
      return '<i class="multisite-icon-calendar"></i>';
    break;
    
    case "Links":
      return '<i class="multisite-icon-link"></i>';
    break;
    
    case "News":
      return '<i class="multisite-icon-megaphone"></i>';
    break;
    
    case "Page":
      return '<i class="multisite-icon-file"></i>';
    break;
    
    case "Survey":
      return '<i class="multisite-icon-check"></i>';
    break;
    
    case "Wiki":
      return '<i class="multisite-icon-edit"></i>';
    break;
    
    case "F.A.Q":
      return '<i class="multisite-icon-question"></i>';
    break;
    
    case "GalleryMedia":
      return '<i class="multisite-icon-pictures"></i>';
    break;

    case "Blog post":
      return '<i class="multisite-icon-book"></i>';
    break;

    case "idea":
      return '<i class="multisite-icon-light-bulb"></i>';
    break;

    case "Simplenews newsletter":
      return '<i class="multisite-icon-paperplane"></i>';
    break;
    
    default:
    break;
  }
}

/* Put Breadcrumbs in a  li structure */
function ec_resp_150_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  $crumbs = '';
  if (!empty($breadcrumb)) {
    foreach ($breadcrumb as $key => $value) {
      if ($key!=0) {
        $crumbs .= '<li>' . $value . '</li>';
      }
    }
  }
  return $crumbs;
}  
