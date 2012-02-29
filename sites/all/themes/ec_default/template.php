<?php
// $Id: template.php,v 1.13 2010/12/14 01:04:27 dries Exp $

/**
 * Add body classes if certain regions have content.
 */
function ec_default_preprocess_html(&$variables) {
  /*drupal_set_message('message1');
  drupal_set_message('message2','warning');
  drupal_set_message('message3','error');
  drupal_set_message('message4','info');*/

  // Alter $variables to add bootstrap classes
  //messages
  /*$variables_table = explode('|',$variables['user']->session);
  $dsm = '';
  $dsm_serialized = '';

  foreach ($variables_table as $key => $item) {
    if ($messages = @unserialize($item)) {
      foreach ($messages as $type => $message) {
        switch ($type) {
          case 'status':
            $dsm['alert-message success'] = $messages[$type];
          break;

          case 'error':
            $dsm['alert-message error'] = $messages[$type];
          break;

          case 'warning':
            $dsm['alert-message warning'] = $messages[$type];
          break;

          case 'info':
            $dsm['alert-message info'] = $messages[$type];
          break;

          default :
            $dsm['alert-message'] = $messages[$type];
          break;
        }
      }
      $dsm_serialized[] .= serialize($dsm);
    } else {
      $dsm_serialized[] .= $item;
    }
  }
  $variables['user']->session = implode('|',$dsm_serialized);*/
  //end messages
  
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
  $variables['head_title'] = variable_get('site_name') . ' - ' . t('European Commission');

  // Add twitter bootsrap
  drupal_add_css(path_to_theme() . '/bootstrap/css/bootstrap.min.css', array('group' => CSS_THEME));
  /*drupal_add_js(path_to_theme() . '/bootstrap/js/bootstrap.min.js');
  drupal_add_js(path_to_theme() . '/bootstrap/js/bootstrap-dropdown.js');
  drupal_add_js(path_to_theme() . '/bootstrap/js/bootstrap-tab.js');*/
  
  // Add conditional stylesheets for IE
  drupal_add_css(path_to_theme() . '/css/ie.less', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 6', '!IE' => FALSE), 'preprocess' => FALSE));

  // Add EC stylesheets
  drupal_add_css('/wel/template-2012/stylesheets/ec.css', array('group' => CSS_THEME, 'type' => 'external'));
  drupal_add_css('/wel/template-2012/stylesheets/ec-ie.css', array('group' => CSS_THEME, 'browsers' => array('!IE' => FALSE), 'type' => 'external'));

  // Add hack stylesheet, to overide EC and bootstrap stylesheets if needed
  drupal_add_css(path_to_theme() . '/css/hack.css', array('group' => CSS_THEME));
  drupal_add_css(path_to_theme() . '/css/hack-ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE)));

  // Add Less stylesheets
  //drupal_add_css(path_to_theme() . '/bootstrap/bootstrap.less', array('group' => CSS_THEME));
  drupal_add_css(path_to_theme() . '/css/style.less', array('group' => CSS_THEME));
  drupal_add_css(path_to_theme() . '/css/colors.less', array('group' => CSS_THEME));

  // Add javascripts
	drupal_add_js('/wel/template-2012/scripts/ec.js', 'external');
	drupal_add_js(path_to_theme() . '/scripts/scripts.js');
  
  // Add hack javascript, to overide EC javascript if needed
  drupal_add_js(path_to_theme() . '/scripts/hack.js');  

}

/**
 * Override or insert variables into the page template for HTML output.
 */
function ec_default_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/**
 * Override or insert variables into the page template.
 */
function ec_default_process_page(&$variables) {
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
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
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
function ec_default_page_alter($page) {
  //Content-Language
  $meta_content_language = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'Content-Language',
      'content' =>  'en'    
    )
  );
  drupal_add_html_head( $meta_content_language, 'meta_content_language' );
  
  //description
  $meta_description = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'description',
      'content' =>  'Content should be a sentence that describes the content of the page'    
    )
  );
  drupal_add_html_head( $meta_description, 'meta_description' );  
  
  //reference
  $meta_reference = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'reference',
      'content' =>  'SITE_NAME'    
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
  
  //classification
  $meta_classification = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'classification',
      'content' =>  'Numeric code from the alphabetical classification list common to all the institutions'    
    )
  );
  drupal_add_html_head( $meta_classification, 'meta_classification' );      
  
  //keywords
  $meta_keywords = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'keywords',
      'content' =>  'One or more of the commission specific keywords + European Comission, European Union, EU'    
    )
  );
  drupal_add_html_head( $meta_keywords, 'meta_keywords' ); 

  //date
  $meta_date = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'date',
      'content' =>  'Date of creation of the page'    
    )
  );
  
  //compatibility
  /*$meta_date = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'X-UA-Compatible',
      'content' =>  'IE=edge'    
    )
  );*/

  drupal_add_html_head( $meta_date, 'meta_date' );   
}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function ec_default_preprocess_maintenance_page(&$variables) {
  if (!$variables['db_is_active']) {
    unset($variables['site_name']);
  }
  drupal_add_css(drupal_get_path('theme', 'ec_default') . '/css/maintenance-page.css');
}

/**
 * Override or insert variables into the maintenance page template.
 */
function ec_default_process_maintenance_page(&$variables) {
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
}

/**
 * Override or insert variables into the node template.
 */
function ec_default_preprocess_node(&$variables) {
  $variables['submitted'] = t('published by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $variables['date']));
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
}

/**
 * Override or insert variables into the block template.
 */
function ec_default_preprocess_block(&$variables) {
  // In the header region visually hide block titles.
  if ($variables['block']->region == 'header') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }
}

/**
 * Implements theme_menu_tree().
 */
function ec_default_menu_tree($variables) {
  return '<ul class="menu clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_field__field_type().
 */
function ec_default_field__taxonomy_term_reference($variables) {
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
function ec_default_menu_local_tasks(&$variables) {
  $output = '';

  /*if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<div class="subnav"><ul class="nav nav-pills">';
    $variables['secondary']['#suffix'] = '</ul></div>';
    $output .= drupal_render($variables['secondary']);
  }*/
  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<div class="subnav"><ul class="nav nav-pills">';
    $variables['primary']['#suffix'] = '</ul></div>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="nav nav-tabs">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  
  return $output;
}

/**
 * Hook form alter
 */
function ec_default_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'search_block_form':
      //print_r($form);
      $form['search_block_form']['#attributes']['class'][] = 'search-query';
      break;
    
    default:
      break;
  }
  $form['#after_build'][] = 'ec_default_cck_alter';
}

/**
 * #after_build function to modify CCK fields
 */
function ec_default_cck_alter($form, &$form_state) {
  if (!user_access('administer nodes')) {
    $form['comment_body']['und'][0]['format']['#access'] = 0;
  }
  return $form;
}

/**
 * Returns HTML for a link.
 * @param type $variables 
 */
function ec_default_link( $variables ){
  $decoration = '';
  $action_bar_before = '';
  $action_bar_after = '';
  $btn_group_before = '';
  $btn_group_after = '';  

  if (!isset($variables['options']['attributes']['class'])) {
    $variables['options']['attributes']['class'] = '';
  }
  
  if( isset($variables['options']['attributes']['action_bar']) ) {
    switch ( $variables['options']['attributes']['action_bar'] ) {
      case 'first':
        $action_bar_before .= '<div class="well btn-toolbar action_bar">';
        break;
      case 'last':
        $action_bar_after .= '</div>';
        break;
      case 'single':
        $action_bar_before .= '<div class="well btn-toolbar action_bar">';
        $action_bar_after .= '</div>';
        break;        
      default:
        break;
    }
  }
  
  if( isset($variables['options']['attributes']['btn_group']) ) {
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
  
  if( isset($variables['options']['attributes']['type']) ) {
    switch ( $variables['options']['attributes']['type'] ) {
      case 'add':
        $decoration .= '<i class="icon-plus icon-white"></i>';
        $variables['options']['attributes']['class'] .= ' btn btn-success';
        break;
      case 'expand':
        $decoration .= '<i class="icon-chevron-down"></i>';
        $variables['options']['attributes']['class'] .= ' btn btn-small';
        break;
      case 'collapse':
        $decoration .= '<i class="icon-chevron-up"></i>';
        $variables['options']['attributes']['class'] .= ' btn btn-small';
        break;
      case 'delete':
        $decoration .= '<i class="icon-trash icon-white"></i>';
        $variables['options']['attributes']['class'] .= ' btn btn-danger';
        break;
      case 'edit':
        $decoration .= '<i class="icon-pencil icon-white"></i>';
        $variables['options']['attributes']['class'] .= ' btn btn-warning';
        break;
      case 'message':
        $decoration .= '<i class="icon-envelope icon-white"></i>';
        $variables['options']['attributes']['class'] .= ' btn btn-info';
        break;        
      case 'neutral':
        $variables['options']['attributes']['class'] .= ' btn';
        break;   
      case 'small':
        $variables['options']['attributes']['class'] .= ' btn btn-small';
        break;         
      default:
        break;
    }
  }
  
  $output = $action_bar_before.$btn_group_before.'<a href="' . 
    check_plain(url($variables['path'], $variables['options'])) . '"' . 
    drupal_attributes($variables['options']['attributes']) . '>' . 
    $decoration . ($variables['options']['html'] ? 
      $variables['text'] : check_plain($variables['text'])) . 
    '</a>'.$btn_group_after.$action_bar_after;
  return $output;
}

/**
 * Returns HTML for a dropdown.
 * @param type $variables 
 */
function ec_default_dropdown($variables) {
   
  $items = $variables['items'];
  $attributes = array();

  $output="";
  if (!empty($items)) {
    $output .= "<ul class='dropdown-menu'>";
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
			//print_r($data);
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
function block_render($module, $block_id) {
  $block = block_load($module, $block_id);
  $block_content = _block_render_blocks(array($block));
  $build = _block_get_renderable_array($block_content);
  $block_rendered = drupal_render($build);
  return $block_rendered;
}


function icon_type_classes($subject) {
	$pattern = '@<i class="icon-(.+)"></i>@';
	$resexp = preg_replace_callback($pattern, 'class_replace', $subject);
  return $resexp;
}

function class_replace($match) {
  switch ($match[1]) {
    case "Article":
      return '<i class="icon-file"></i>';
    break;
    
    case "community":
      return '<i class="icon-home"></i>';
    break;
    
    case "Document":
      return '<i class="icon-book"></i>';
    break;
    
    case "Event":
      return '<i class="icon-calendar"></i>';
    break;
    
    case "Forum Room":
      return '<i class="icon-th-list"></i>';
    break;
    
    case "Forum Thread":
      return '<i class="icon-list"></i>';
    break;
    
    case "Links":
      return '<i class="icon-tag"></i>';
    break;
    
    case "News":
      return '<i class="icon-info-sign"></i>';
    break;
    
    case "Page":
      return '<i class="icon-file"></i>';
    break;
    
    case "Survey":
      return '<i class="icon-question-sign"></i>';
    break;
    
    case "Wiki":
      return '<i class="icon-th"></i>';
    break;
    
    default:
    break;
  }
}

?>