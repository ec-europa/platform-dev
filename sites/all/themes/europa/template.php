<?php
/**
 * @file
 * template.php
 */

/**
 * Implements hook_theme().
 */
function europa_theme() {
  return array(
    'node_form' => array(
      'render element' => 'form',
      'template' => 'node-form',
      'path' => drupal_get_path('module', 'europa') . '/theme',
    ),
  );
}

/**
 * Implements hook_form_BASE_FORM_ID_alter()
 */
function europa_form_node_form_alter(&$form, &$form_state, $form_id) {

  // Eventually remove field from vertical tabs or other similar groupings.
  $node_form_sidebar = theme_get_setting('node_form_sidebar');
  if ($node_form_sidebar) {
    foreach ($node_form_sidebar as $field_name) {
      $form[$field_name]['#group'] = NULL;
    }    
  }
}

/**
 * Preprocessor for theme('node_form').
 */
function europa_preprocess_node_form(&$variables) {
  
  $i = 100;  
  $variables['sidebar'] = array();
  $node_form_sidebar = theme_get_setting('node_form_sidebar');
  if ($node_form_sidebar) {
    foreach ($node_form_sidebar as $field_name) {
      if (isset($variables['form'][$field_name])) {
        $variables['form'][$field_name]['#weight'] = $i++;
        $variables['sidebar'][$field_name] = $variables['form'][$field_name];    
        hide($variables['form'][$field_name]);
      }
    }    
  }  
  // Extract the form buttons, and put them in independent variable.
  $variables['buttons'] = $variables['form']['actions'];
  hide($variables['form']['actions']);
}


/**
 * Overrides theme_form_required_marker()
 */
function europa_form_required_marker($variables) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  $attributes = array(
    'class' => 'form-required text-danger glyphicon glyphicon-asterisk',
    'title' => $t('This field is required.'),
  );
  return '<span' . drupal_attributes($attributes) . '></span>';
}

/**
 * Implementation of preprocess_node().
 */
function europa_preprocess_node(&$vars) {
  $vars['submitted'] = '';
  if (theme_get_setting('display_submitted')) {
    $vars['submitted'] = t('Submitted by !username on !datetime', array(
      '!username' => $vars['name'],
      '!datetime' => $vars['date'],
    ));
    
    // Display last update date
    $node = $vars['node'];
    $revision_account = user_load($node->revision_uid);
    $vars['revision_name'] = theme('username', array('account' => $revision_account));
    $vars['revision_date'] = format_date($node->changed);
    $vars['submitted'] .= "<br>".t('Last modified by !revision-name on !revision-date', array(
      '!name' => $vars['name'], '!date' => $vars['date'], '!revision-name' => $vars['revision_name'], '!revision-date' => $vars['revision_date'])
    );
  }
}

/**
 * Bootstrap theme wrapper function for the primary menu links.
 */
function europa_menu_tree__secondary(&$variables) {
  return '<ul class="menu nav navbar-nav secondary">' . $variables['tree'] . '</ul>';
  // global $user;
  // $username = format_username($user);
  // $toggle = t('Hello, !name', array('!name' => "<b>{$username}</b>"));
  // return '
  //    <ul class="nav navbar-nav navbar-right">
  //      <li class="dropdown">
  //        <a href="#" class="dropdown-toggle" data-toggle="dropdown">' . $toggle . ' <b class="caret"></b></a>
  //        <ul class="dropdown-menu">' . $variables['tree'] . '</ul>
  //      </li>
  //    </ul>'; 
}

/**
 * Implements preprocess for theme('easy_breadcrumb')
 */
function europa_preprocess_easy_breadcrumb(&$variables) {
  $variables['separator'] = '&raquo;';
}

/**
 * Overrides theme('easy_breadcrumb')
 */
function europa_easy_breadcrumb($variables) {

  $breadcrumb = $variables['breadcrumb'];
  $segments_quantity = $variables['segments_quantity'];
  $separator = $variables['separator'];

  $html = '';

  // We don't print out "Home" if it's the only breadcrumb component.
  if ($segments_quantity > 1) {

    $html .= '<ol class="breadcrumb">';

    for ($i = 0, $s = $segments_quantity - 1; $i < $segments_quantity; ++$i) {
      $it = $breadcrumb[$i];
      $content = decode_entities($it['content']);
      if (isset($it['url'])) {
        $html .= '<li>' . l($content, $it['url'], array('attributes' => array('class' => $it['class'])))  . '</li>';
      }
      else {
        $class = implode(' ', $it['class']);
        $html .= '<li class="active ' . $class . '">' . $content . '</li>';
      }
      if ($i < $s) {
        $html .= '<span class="active breadcrumb-separator"> ' . $separator . ' </span>';
      }
    }
    
    $html .= '</ol>';
  }

  return $html;
}

/**
 * Implements hook_preprocess_image().
*/
function europa_preprocess_image(&$variables) {
  // Fix issue between print module and bootstrap theme, print module put a string instead of an array in $variables['attributes']['class']
  if ($shape = theme_get_setting('bootstrap_image_responsive')) {
    if(isset($variables['attributes']['class'])) {
      if(is_array($variables['attributes']['class'])) {
        $variables['attributes']['class'][] = 'img-responsive';
      }
      else {
        $variables['attributes']['class'] = array($variables['attributes']['class'], 'img-responsive');
      }
    }
  }
}

/**
 * Implements hook_bootstrap_colorize_text_alter().
 */
function europa_bootstrap_colorize_text_alter(&$texts) {
  $texts['contains'][t('Save')] = 'primary';
}
