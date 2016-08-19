<?php
/**
 * @file
 * Default theme functions.
 */

/**
 * Implements template_preprocess().
 */
function ec_resp_preprocess_feature_set_admin_form(&$variables) {
  // Add specific javascript.
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/feature-set.js', array('scope' => 'footer', 'weight' => 13));

  $categories_list = '';
  $features_list = '';

  foreach ($variables['feature_set_category']['category'] as $category => $features) {
    $table = array(
      'header' => NULL,
      'rows' => array(),
      'attributes' => array('class' => array('feature-set-content table table-striped table-hover')),
    );

    // Create category id.
    $category_id = preg_replace("/[^a-z0-9_\s-]/", "", strtolower($category));
    $category_id = preg_replace("/[\s-]+/", " ", $category_id);
    $category_id = preg_replace("/[\s_]/", "-", $category_id);

    // Format categories.
    $categories_list .= theme('html_tag', array(
      'element' => array(
        '#tag' => 'li',
        '#attributes' => array(
          'class' => 'feature-set__category',
          'role' => 'presentation',
        ),
        '#value' => l(
          $category . ' (' . count($features) . ')',
          '',
          array(
            'fragment' => $category_id,
            'external' => TRUE,
          )
        ),
      ),
    ));

    // Format features.
    $feature_full = '';
    foreach ($features as $key => $item) {
      // Get the icon if available.
      if (!empty($item['#featuresetinfo']['font'])) {
        $feature_icon = theme('html_tag', array(
          'element' => array(
            '#tag' => 'div',
            '#attributes' => array(
              'class' => array(
                'feature-set__icon',
                $item['#featuresetinfo']['font'],
              ),
            ),
            '#value' => '',
          ),
        ));
      }
      elseif (!empty($item['#featuresetinfo']['icon'])) {
        $image = array(
          'path' => $item['#featuresetinfo']['icon'],
          'alt' => t('@feature-set icon', array('@feature-set' => $item['#featuresetinfo']['featureset'])),
          'attributes' => array(
            'class' => 'feature-set__icon',
          ),
        );
        $feature_icon = theme_image($image);
      }
      else {
        $feature_icon = '';
      }

      // Format feature name.
      $feature_name = theme('html_tag', array(
        'element' => array(
          '#tag' => 'div',
          '#attributes' => array(
            'class' => 'feature-set__name',
          ),
          '#value' => $item['#featuresetinfo']['featureset'],
        ),
      ));

      // Format feature documentation.
      $feature_documentation = !empty($item['#featuresetinfo']['documentation'])
        ? l(
          t('See @name documentation', array('@name' => $item['#featuresetinfo']['featureset'])),
          $item['#featuresetinfo']['documentation'],
          array('attributes' => array('target' => '_blank')))
        : '';

      // Format feature description.
      $feature_description_value = '';
      $feature_description_value .= !empty($item['#featuresetinfo']['description'])
        ? $item['#featuresetinfo']['description']
        : '';
      $feature_description_value .= !empty($feature_documentation)
        ? theme('html_tag', array(
          'element' => array(
            '#tag' => 'footer',
            '#attributes' => array(
              'class' => 'feature-set__doc',
            ),
            '#value' => $feature_documentation,
          ),
        ))
        : '';

      $feature_description = theme('html_tag', array(
        'element' => array(
          '#tag' => 'blockquote',
          '#attributes' => array(
            'class' => 'feature-set__desc',
          ),
          '#value' => $feature_description_value,
        ),
      ));

      // Format feature requirements.
      $feature_require = theme('html_tag', array(
        'element' => array(
          '#tag' => 'div',
          '#attributes' => array(
            'class' => 'feature-set__doc',
          ),
          '#value' => !empty($item['#featuresetinfo']['require'])
          ? $item['#featuresetinfo']['require']
          : '',
        ),
      ));

      // Format switcher.
      $feature_switcher = theme('html_tag', array(
        'element' => array(
          '#tag' => 'div',
          '#attributes' => array(
            'class' => 'feature-set__switch',
          ),
          '#value' => render($item),
        ),
      ));

      // Group content.
      $feature_header = theme('html_tag', array(
        'element' => array(
          '#tag' => 'div',
          '#attributes' => array(
            'class' => 'feature-set__header',
          ),
          '#value' => $feature_icon . $feature_name . $feature_switcher,
        ),
      ));
      $feature_content = theme('html_tag', array(
        'element' => array(
          '#tag' => 'div',
          '#attributes' => array(
            'class' => 'feature-set__content',
          ),
          '#value' => $feature_description . $feature_require,
        ),
      ));
      $feature_full .= theme('html_tag', array(
        'element' => array(
          '#tag' => 'div',
          '#attributes' => array(
            'class' => 'feature-set__feature',
          ),
          '#value' => $feature_header . $feature_content,
        ),
      ));
    }

    // Update feature list.
    $features_list .= theme('html_tag', array(
      'element' => array(
        '#tag' => 'div',
        '#attributes' => array(
          'id' => $category_id,
          'class' => 'feature-set__feature-group',
        ),
        '#value' => $feature_full,
      ),
    ));
  }

  $variables['feature_set_categories_list'] = $categories_list;
  $variables['feature_set_features_list'] = $features_list;
}

/**
 * Implements template_preprocess_page().
 */
function ec_resp_preprocess_page(&$variables) {
  $title = drupal_get_title();
  // Format regions.
  $regions = array();
  $regions['header_right'] = (isset($variables['page']['header_right']) ? render($variables['page']['header_right']) : '');
  $regions['header_top'] = (isset($variables['page']['header_top']) ? render($variables['page']['header_top']) : '');
  $regions['featured'] = (isset($variables['page']['featured']) ? render($variables['page']['featured']) : '');
  $regions['sidebar_left'] = (isset($variables['page']['sidebar_left']) ? render($variables['page']['sidebar_left']) : '');
  $regions['tools'] = (isset($variables['page']['tools']) ? render($variables['page']['tools']) : '');
  $regions['content_top'] = (isset($variables['page']['content_top']) ? render($variables['page']['content_top']) : '');
  $regions['help'] = (isset($variables['page']['help']) ? render($variables['page']['help']) : '');
  $regions['content'] = (isset($variables['page']['content']) ? render($variables['page']['content']) : '');
  $regions['content_right'] = (isset($variables['page']['content_right']) ? render($variables['page']['content_right']) : '');
  $regions['content_bottom'] = (isset($variables['page']['content_bottom']) ? render($variables['page']['content_bottom']) : '');
  $regions['sidebar_right'] = (isset($variables['page']['sidebar_right']) ? render($variables['page']['sidebar_right']) : '');
  $regions['footer'] = (isset($variables['page']['footer']) ? render($variables['page']['footer']) : '');

  // Check if there is a responsive sidebar or not.
  $has_responsive_sidebar = ($regions['header_right'] || $regions['sidebar_left'] || $regions['sidebar_right'] ? 1 : 0);

  // Calculate size of regions.
  $cols = array();
  // Sidebars.
  $cols['sidebar_left'] = array(
    'lg' => (!empty($regions['sidebar_left']) ? 3 : 0),
    'md' => (!empty($regions['sidebar_left']) ? 4 : 0),
    'sm' => 0,
    'xs' => 0,
  );
  $cols['sidebar_right'] = array(
    'lg' => (!empty($regions['sidebar_right']) ? 3 : 0),
    'md' => (!empty($regions['sidebar_right']) ? (!empty($regions['sidebar_left']) ? 12 : 4) : 0),
    'sm' => 0,
    'xs' => 0,
  );

  // Content.
  $cols['content_main'] = array(
    'lg' => 12 - $cols['sidebar_left']['lg'] - $cols['sidebar_right']['lg'],
    'md' => ($cols['sidebar_right']['md'] == 4 ? 8 : 12 - $cols['sidebar_left']['md']),
    'sm' => 12,
    'xs' => 12,
  );
  $cols['content_right'] = array(
    'lg' => (!empty($regions['content_right']) ? 6 : 0),
    'md' => (!empty($regions['content_right']) ? 6 : 0),
    'sm' => (!empty($regions['content_right']) ? 12 : 0),
    'xs' => (!empty($regions['content_right']) ? 12 : 0),
  );
  $cols['content'] = array(
    'lg' => 12 - $cols['content_right']['lg'],
    'md' => 12 - $cols['content_right']['md'],
    'sm' => 12,
    'xs' => 12,
  );

  // Tools.
  $cols['sidebar_button'] = array(
    'sm' => ($has_responsive_sidebar ? 2 : 0),
    'xs' => ($has_responsive_sidebar ? 2 : 0),
  );
  $cols['tools'] = array(
    'lg' => (empty($title) ? 12 : 4),
    'md' => (empty($title) ? 12 : 4),
    'sm' => 12,
    'xs' => 12,
  );

  // Title.
  $cols['title'] = array(
    'lg' => 12 - $cols['tools']['lg'],
    'md' => 12 - $cols['tools']['md'],
    'sm' => 12,
    'xs' => 12,
  );

  // Add variables to template file.
  $variables['regions'] = $regions;
  $variables['cols'] = $cols;
  $variables['has_responsive_sidebar'] = $has_responsive_sidebar;

  $variables['menu_visible'] = FALSE;
  if (!empty($variables['page']['featured'])) {
    foreach ($variables['page']['featured'] as $key => $value) {
      if ($key == 'system_main-menu' ||
        strpos($key, 'om_maximenu') !== FALSE) {
        $variables['menu_visible'] = TRUE;
      }
    }
  }
  // Update logo for interinstitutional theme option.
  if (theme_get_setting('enable_interinstitutional_theme')) {
    $variables['logo'] = file_create_url(drupal_get_path('theme', 'ec_resp') . '/logo_europa.png');
  }
  elseif (theme_get_setting('default_logo')) {
    $variables['svg_logo'] = file_create_url(drupal_get_path('theme', 'ec_resp') . '/logo.svg');
  }

  // Adding pathToTheme for Drupal.settings to be used in js files.
  $base_theme = multisite_drupal_toolbox_get_base_theme();
  drupal_add_js('jQuery.extend(Drupal.settings, { "pathToTheme": "' . drupal_get_path('theme', $base_theme) . '" });', 'inline');
}

/**
 * Implements template_preprocess_node().
 */
function ec_resp_preprocess_node(&$variables) {
  $variables['prefix_display'] = FALSE;
  $variables['suffix_display'] = FALSE;

  if (isset($variables['group_content_access']) && isset($variables['group_content_access'][LANGUAGE_NONE]) && $variables['group_content_access'][LANGUAGE_NONE][0]['value'] == 2) {
    $variables['prefix_display'] = TRUE;
  }

  if ($variables['display_submitted']) {
    $variables['suffix_display'] = TRUE;
  }

  // Alter date format.
  $custom_date = format_date($variables['created'], 'custom', 'l, d/m/Y');
  $variables['submitted'] = t('Published by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $custom_date));

  // Add classes.
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
  if ($variables['teaser'] || !empty($variables['content']['comments']['comment_form'])) {
    unset($variables['content']['links']['comment']['#links']['comment-add']);
  }

  switch ($variables['type']) {
    case 'idea':
      $variables['watched'] = $variables['field_watching'][0]['value'];
      break;

    case 'gallerymedia':
      unset($variables['content']['field_picture_upload']);
      unset($variables['content']['field_video_upload']);
      break;
  }

  // Display last update date.
  if ($variables['display_submitted']) {
    $node = $variables['node'];

    // Append the revision information to the submitted by text.
    $revision_account = user_load($node->revision_uid);
    $variables['revision_name'] = theme('username', array('account' => $revision_account));
    $variables['revision_date'] = format_date($node->changed);
    $variables['submitted'] .= "<br />" . t('Last modified by !revision-name on !revision-date',
      array(
        '!revision-name' => $variables['revision_name'],
        '!revision-date' => $variables['revision_date'],
      )
    );
  }

}

/**
 * Implements template_preprocess_file_entity().
 */
function ec_resp_preprocess_file_entity(&$variables) {
  if ($variables['view_mode'] == "media_gallery_colorbox") {
    $variables['classes_array'][] = "col-lg-2 col-md-3 col-xs-6";
  }
}

/**
 * Implements template_preprocess_user_profile().
 */
function ec_resp_preprocess_user_profile(&$variables) {
  // Format profile page.
  $identity = '';
  if (isset($variables['field_firstname'][0]['safe_value'])) {
    $identity .= $variables['field_firstname'][0]['safe_value'];
  }
  if (isset($variables['field_lastname'][0]['safe_value'])) {
    if ($identity != '') {
      $identity .= ' ';
    }
    $identity .= $variables['field_lastname'][0]['safe_value'];
  }

  $date = '';
  if ($user = user_load(arg(1))) {
    $date_string = format_date($user->created, 'custom', 'd/m/Y');
    $args = array('@date' => $date_string);
    $date .= t('Member since @date', $args);
  }

  $variables['user_info']['name'] = $identity;
  $variables['user_info']['date'] = $date;

  // Add contact form link on user profile page.
  if (module_exists('contact')) {
    $account = $variables['elements']['#account'];
    $menu_item = menu_get_item("user/$account->uid/contact");
    if (isset($menu_item['access']) && $menu_item['access'] == TRUE) {
      $variables['contact_form'] = l(t('Contact this user'), 'user/' . $account->uid . '/contact', array('attributes' => array('type' => 'message')));
    }
  }
}

/**
 * Implements template_preprocess_field().
 */
function ec_resp_preprocess_field(&$variables, $hook) {
  switch ($variables['element']['#field_name']) {
    case 'group_group':
      if (isset($variables['items'][0]['#type']) && $variables['items'][0]['#type'] == 'link') {
        $variables['classes_array'][] = 'btn';
        $variables['classes_array'][] = 'btn-info';
      }
      break;

  }
}

/**
 * Custom implementation for select element of Form API.
 */
function ec_resp_preprocess_select(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}

/**
 * Custom implementation for textfield element of Form API.
 */
function ec_resp_preprocess_textfield(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}

/**
 * Custom implementation for password element of Form API.
 */
function ec_resp_preprocess_password(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}

/**
 * Custom implementation for textarea element of Form API.
 */
function ec_resp_preprocess_textarea(&$variables) {
  $variables['element']['#attributes']['class'][] = 'form-control';
}

/**
 * Implements template_preprocess_maintenance_page().
 */
function ec_resp_preprocess_maintenance_page(&$variables) {
  if (!$variables['db_is_active']) {
    unset($variables['site_name']);
  }
}

/**
 * Implements hook_css_alter().
 */
function ec_resp_css_alter(&$css) {
  // Loads eu_resp.css instead of ec_resp, if checked in theme settings.
  if (theme_get_setting('enable_interinstitutional_theme')) {
    $css = drupal_add_css(drupal_get_path('theme', 'ec_resp') . '/css/eu_resp.min.css');
    unset($css[drupal_get_path('theme', 'ec_resp') . '/css/ec_resp.css']);
  }
}

/**
 * Implements template_preprocess_html().
 */
function ec_resp_preprocess_html(&$variables) {
  // Update page title.
  // If nexteuropa_metatags is enabled, it should manage
  // the metatags instead of ec_resp.
  if (!module_exists('nexteuropa_metatags')) {
    if (arg(0) == 'node' && is_numeric(arg(1))) {
      $node = node_load(arg(1));
      // If the metatag title exists, it must be used
      // to construct the title page.
      if ($node && isset($node->field_meta_title) && !empty($node->field_meta_title)) {
        $title = strip_tags($node->field_meta_title['und'][0]['value']);
      }
      else {
        $title = strip_tags($node->title);
      }
    }
    else {
      // For all no-node page, keep the default drupal behavior.
      $title = strip_tags(drupal_get_title());
    }

    if (theme_get_setting('enable_interinstitutional_theme')) {
      $variables['head_title'] = t('EUROPA - !title', array('!title' => $title));
    }
    else {
      $variables['head_title'] = t('!title - European Commission', array('!title' => $title));
    }
  }

  // Add javascripts to the footer scope.
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/ec.js', array('scope' => 'footer', 'weight' => 10));
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/jquery.mousewheel.min.js', array('scope' => 'footer', 'weight' => 11));
  drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/ec_resp.js', array('scope' => 'footer', 'weight' => 12));
}

/**
 * Implements template_preprocess_menu_link().
 */
function ec_resp_preprocess_menu_link(&$variables) {
  // Get icon links to menu item.
  $icon = (isset($variables['element']['#localized_options']['attributes']['data-image']) ? $variables['element']['#localized_options']['attributes']['data-image'] : '');

  // Get display title option.
  $display_title = (isset($variables['element']['#localized_options']['attributes']['data-display-title']) ? $variables['element']['#localized_options']['attributes']['data-display-title'] : 1);

  // Add the icon.
  if ($icon) {
    if ($display_title) {
      $variables['element']['#title'] = '<span class="glyphicon glyphicon-' . $icon . '"></span> ' . $variables['element']['#title'];
    }
    else {
      $variables['element']['#title'] = '<span class="glyphicon glyphicon-' . $icon . ' menu-no-title"></span>';
    }
  }

  // Manage CSS class.
  $remove_default_classes = (isset($variables['element']['#localized_options']['attributes']['data-remove-class']) ? $variables['element']['#localized_options']['attributes']['data-remove-class'] : 0);
  if (!$remove_default_classes) {
    $variables['element']['#localized_options']['attributes']['class'][] = 'list-group-item';
  }

  // Add CSS class property to the <front> item.
  if ($variables['element']['#href'] == '<front>' && $variables['element']['#original_link']['menu_name'] == 'main-menu' && $variables['element']['#original_link']['has_children'] == 0) {
    $variables['element']['#attributes']['class'][] = 'resp-main-menu-frontpage';
  }
}

/**
 * Implements template_preprocess_views_view().
 */
function ec_resp_preprocess_views_view(&$variables) {
  $view = $variables['view'];

  switch ($view->name) {
    case 'galleries':
      if ($view->current_display == 'medias_block') {
        drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/view-medias-block.js');
      }
      else {
        drupal_add_js(drupal_get_path('theme', 'ec_resp') . '/scripts/view-galleries.js');
      }

      // Get empty gallery picture, if needed.
      $empty_pic = db_select('file_managed', 'fm')
        ->fields('fm', array('uri'))
        ->condition('filename', 'empty_gallery.png', '=')
        ->execute()
        ->fetchAssoc();

      $empty_img = theme('image_style', array(
        'style_name' => 'square_thumbnail',
        'path' => $empty_pic['uri'],
        'alt' => t('There is no content in this gallery, or it has not been validated yet.'),
      ));

      // Check if the galleries are actually empty.
      $rows = str_replace('[Empty_gallery][Empty_gallery]', $empty_img, $variables['rows']);
      // Check if there is only one picture.
      $rows = str_replace('[Empty_gallery]', '', $rows);
      // Replace nid by number of items in gallery.
      $variables['rows'] = preg_replace_callback('#<div id="nb_items">([0-9]+)</div>#', "_ec_resp_media_gallery_count", $rows);

      break;
  }
}

/**
 * Implements template_preprocess_views_view_grid().
 */
function ec_resp_preprocess_views_view_grid(&$variables) {

  // Set length of each column, depending of number of element on one line.
  $grid_col = array();

  $grid_col[1]['lg'] = array(12);
  $grid_col[1]['md'] = array(12);
  $grid_col[1]['sm'] = array(12);
  $grid_col[1]['xs'] = array(12);
  $grid_col[2]['lg'] = array(6, 6);
  $grid_col[2]['md'] = array(6, 6);
  $grid_col[2]['sm'] = array(12);
  $grid_col[2]['xs'] = array(12);
  $grid_col[3]['lg'] = array(4, 4, 4);
  $grid_col[3]['md'] = array(4, 4, 4);
  $grid_col[3]['sm'] = array(6, 6);
  $grid_col[3]['xs'] = array(12);
  $grid_col[4]['lg'] = array(3, 3, 3, 3);
  $grid_col[4]['md'] = array(4, 4, 4);
  $grid_col[4]['sm'] = array(4, 4, 4);
  $grid_col[4]['xs'] = array(6, 6);
  $grid_col[5]['lg'] = array(3, 2, 2, 2, 3);
  $grid_col[5]['md'] = array(3, 3, 3, 3);
  $grid_col[5]['sm'] = array(4, 4, 4);
  $grid_col[5]['xs'] = array(6, 6);
  $grid_col[6]['lg'] = array(2, 2, 2, 2, 2, 2);
  $grid_col[6]['md'] = array(3, 3, 3, 3);
  $grid_col[6]['sm'] = array(4, 4, 4);
  $grid_col[6]['xs'] = array(6, 6);
  $grid_col[7]['lg'] = array(3, 1, 1, 1, 1, 1, 4);
  $grid_col[7]['md'] = array(3, 2, 2, 2, 3);
  $grid_col[7]['sm'] = array(3, 3, 3, 3);
  $grid_col[7]['xs'] = array(4, 4, 4);
  $grid_col[8]['lg'] = array(3, 1, 1, 1, 1, 1, 1, 3);
  $grid_col[8]['md'] = array(2, 2, 2, 2, 2, 2);
  $grid_col[8]['sm'] = array(3, 3, 3, 3);
  $grid_col[8]['xs'] = array(4, 4, 4);
  $grid_col[9]['lg'] = array(2, 1, 1, 1, 1, 1, 1, 1, 3);
  $grid_col[9]['md'] = array(3, 1, 1, 1, 1, 1, 4);
  $grid_col[9]['sm'] = array(3, 2, 2, 2, 3);
  $grid_col[9]['xs'] = array(3, 3, 3, 3);
  $grid_col[10]['lg'] = array(2, 1, 1, 1, 1, 1, 1, 1, 1, 2);
  $grid_col[10]['md'] = array(3, 1, 1, 1, 1, 1, 1, 3);
  $grid_col[10]['sm'] = array(2, 2, 2, 2, 2, 2);
  $grid_col[10]['xs'] = array(3, 3, 3, 3);
  $grid_col[11]['lg'] = array(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2);
  $grid_col[11]['md'] = array(2, 1, 1, 1, 1, 1, 1, 1, 1, 2);
  $grid_col[11]['sm'] = array(3, 1, 1, 1, 1, 1, 1, 3);
  $grid_col[11]['xs'] = array(2, 2, 2, 2, 2, 2);
  $grid_col[12]['lg'] = array(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
  $grid_col[12]['md'] = array(2, 1, 1, 1, 1, 1, 1, 1, 1, 2);
  $grid_col[12]['sm'] = array(3, 1, 1, 1, 1, 1, 1, 3);
  $grid_col[12]['xs'] = array(2, 2, 2, 2, 2, 2);

  $variables['nb_col'] = $variables['view']->style_plugin->options['columns'];
  $variables['grid_col'] = $grid_col;
}

/**
 * Count items in media gallery.
 */
function _ec_resp_media_gallery_count($matches) {
  $node = node_load($matches[1]);
  $nb_pictures = 0;
  $nb_video = 0;

  if (isset($node->field_picture_upload[LANGUAGE_NONE])) :
    $nb_pictures = count($node->field_picture_upload[LANGUAGE_NONE]);
  endif;

  if (isset($node->field_video_upload[LANGUAGE_NONE])) :
    $nb_video = count($node->field_video_upload[LANGUAGE_NONE]);
  endif;

  return '<div class="meta">' . ($nb_pictures + $nb_video) . ' ' . t('items') . '</div>';
}

/**
 * Implements hook_page_alter().
 */
function ec_resp_page_alter(&$page) {

  global $language;
  if (arg(0) == 'node') {
    $node = node_load(arg(1));
    if (isset($node->title)) {
      $node_title = filter_xss($node->title);
    }
  }

  $description = filter_xss(variable_get('site_slogan'));
  if (empty($description)) {
    $description = filter_xss(variable_get('site_name'));
  }
  if (!empty($node)) {
    $description = $node_title . ' - ' . $description;
  }

  if (theme_get_setting('enable_interinstitutional_theme')) {
    $title = t('EUROPA - !title', array('!title' => filter_xss(variable_get('site_name'))));
  }
  else {
    $title = t('!title - European Commission', array('!title' => filter_xss(variable_get('site_name'))));
  }
  if (!empty($node)) {
    // If the metatag title exists, it must be used to construct the title page.
    if (isset($node->field_meta_title) && !empty($node->field_meta_title)) {
      $title = filter_xss($node->field_meta_title['und'][0]['value']);
    }
    else {
      $title = $node_title . ' - ' . $title;
    }
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
  $keywords .= filter_xss(variable_get('site_name')) . ', ';
  $keywords .= t('European Commission, European Union, EU');

  $type = 'website';
  if (!empty($node)) {
    $type = $node->type;
  }

  if (!module_exists('nexteuropa_metatags')) {
    // Content-Language.
    $meta_content_language = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'Content-Language',
        'content' => $language->prefix,
      ),
    );
    drupal_add_html_head($meta_content_language, 'meta_content_language');

    // Description.
    $meta_description = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'description',
        'content' => $description,
      ),
    );
    drupal_add_html_head($meta_description, 'meta_description');

    // Reference.
    $meta_reference = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'reference',
        'content' => filter_xss(variable_get('site_name')),
      ),
    );
    drupal_add_html_head($meta_reference, 'meta_reference');

    // Creator.
    $meta_creator = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'creator',
        'content' => 'COMM/DG/UNIT',
      ),
    );
    drupal_add_html_head($meta_creator, 'meta_creator');
  }

  // IPG classification.
  $classification = variable_get('meta_configuration', 'none');
  if ($classification != 'none') {
    if (!module_exists('nexteuropa_metatags')) {
      $meta_classification = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'classification',
          'content' => variable_get('meta_configuration', 'none'),
        ),
      );
      drupal_add_html_head($meta_classification, 'meta_classification');
    }
  }
  else {
    if (user_access('administer site configuration')) {
      $link = l(t('here'), 'admin/config/system/site-information');
      $args = array('!link' => $link);
      drupal_set_message(t('Please select the IPG classification of your site !link.', $args), 'warning');
    }
  }

  if (!module_exists('nexteuropa_metatags')) {
    // Keywords.
    $meta_keywords = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'keywords',
        'content' => $keywords,
      ),
    );
    drupal_add_html_head($meta_keywords, 'meta_keywords');

    // Date.
    $meta_date = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'date',
        'content' => format_date(time(), 'custom', 'd/m/Y'),
      ),
    );
    drupal_add_html_head($meta_date, 'meta_date');

    // Og title.
    $meta_og_title = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:title',
        'content' => $title,
      ),
    );
    drupal_add_html_head($meta_og_title, 'meta_og_title');

    // Og type.
    $meta_og_type = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:type',
        'content' => $type,
      ),
    );
    drupal_add_html_head($meta_og_type, 'meta_og_type');

    // Og site name.
    $meta_og_site_name = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:site_name',
        'content' => filter_xss(variable_get('site_name')),
      ),
    );

    drupal_add_html_head($meta_og_site_name, 'meta_og_site_name');

    // Og description.
    $meta_og_description = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:description',
        'content' => $description,
      ),
    );
    drupal_add_html_head($meta_og_description, 'meta_og_description');

    // Fb admins.
    $meta_fb_admins = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'fb:admins',
        'content' => 'USER_ID',
      ),
    );
    drupal_add_html_head($meta_fb_admins, 'meta_fb_admins');

    // Robots.
    $meta_robots = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'robots',
        'content' => 'follow,index',
      ),
    );
    drupal_add_html_head($meta_robots, 'meta_robots');

    // Revisit after.
    $revisit_after = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'revisit-after',
        'content' => '15 Days',
      ),
    );
    drupal_add_html_head($revisit_after, 'revisit-after');

    // Viewport.
    $viewport = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width, initial-scale=1.0',
      ),
    );
    drupal_add_html_head($viewport, 'viewport');
  }
}

/**
 * Implements hook_block_view_alter().
 */
function ec_resp_block_view_alter(&$data, $block) {

  if ($block->region == 'sidebar_left' || $block->region == 'sidebar_right') {
    // Add classes to list.
    $data['content'] = (isset($data['content']) ? str_replace('<ul>', '<ul class="list-group list-group-flush list-unstyled">', $data['content']) : '');

    // Add classes to list items.
    if (!is_array($data['content'])) {
      preg_match_all('/<a(.*?)>/s', $data['content'], $matches);

      if (isset($matches[0])) {
        foreach ($matches[0] as $link) {
          if (strpos($link, ' class="') !== FALSE) {
            $new_link = str_replace(' class="', ' class="list-group-item ', $link);
          }
          elseif (strpos($link, " class='") !== FALSE) {
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
function ec_resp_form_element($variables) {
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
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(
      ' ' => '-',
      '_' => '-',
      '[' => '-',
      ']' => '',
    ));
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
function ec_resp_button($variables) {
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
function ec_resp_menu_tree($variables) {
  $classes = 'menu clearfix list-group list-group-flush list-unstyled';

  return '<ul class="' . $classes . '">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree_main_menu().
 */
function ec_resp_menu_tree__main_menu($variables) {
  if (strpos($variables['tree'], 'dropdown-menu')) {
    // There is a dropdown in this tree.
    $variables['tree'] = str_replace('nav navbar-nav', 'list-group list-group-flush list-unstyled', $variables['tree']);
    return '<ul class="menu clearfix nav navbar-nav">' . $variables['tree'] . '</ul>';
  }
  else {
    // There is no dropdown in this tree, simply return it in a <ul>.
    return '<ul class="menu clearfix nav navbar-nav">' . $variables['tree'] . '</ul>';
  }
}

/**
 * Implements theme_menu_tree__menu_breadcrumb_menu().
 */
function ec_resp_menu_tree__menu_breadcrumb_menu($variables) {
  return '<div class="menu menu-breadcrumb">' . $variables['tree'] . '</div>';
}

/**
 * Implements theme_menu_link().
 */
function ec_resp_menu_link($variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $hide_children = (isset($variables['element']['#localized_options']['attributes']['data-hide-children']) ? $variables['element']['#localized_options']['attributes']['data-hide-children'] : 0);

  // Test if there is a sub menu and if it has to be displayed.
  if ($element['#below'] && !$hide_children) {
    // Render sub menu.
    $sub_menu = drupal_render($element['#below']);

    if (!theme_get_setting('disable_dropdown_menu') && !in_array('dropdown', $element['#attributes']['class'])) {
      // Add carret and class.
      $element['#title'] .= '<b class="caret"></b>';
      $element['#attributes']['class'][] = 'dropdown';

      // Add attributes to children items.
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'][] = 'dropdown';

      // Add CSS class to ul tag
      // Dirty, but I see no better way to do it.
      $sub_menu = str_replace('<ul class="', '<ul class="dropdown-menu ', $sub_menu);
    }
  }

  $element['#localized_options']['html'] = TRUE;
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_menu_link__menu_breadcrumb_menu().
 */
function ec_resp_menu_link__menu_breadcrumb_menu(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $separator = variable_get('easy_breadcrumb-segments_separator');

  // Check sub menu items.
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  // Check CSS classes.
  $last = FALSE;
  foreach ($element['#attributes']['class'] as $key => $class) {
    if ($class == 'last') {
      $last = TRUE;
      break;
    }
  }

  if (theme_get_setting('enable_interinstitutional_theme') && $element['#title'] == 'European Commission') {
    global $language;
    $element['#title'] = t('Europa');
    $element['#href'] = 'http://europa.eu/index_' . $language->language . '.htm';
  }

  // Format output.
  $element['#localized_options']['html'] = TRUE;
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  $suffix = ($last ? '' : '<span class="easy-breadcrumb_segment-separator"> ' . $separator . ' </span>');
  return $output . $sub_menu . $suffix;
}

/**
 * Implements theme_field__field_type().
 */
function ec_resp_field__taxonomy_term_reference($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label">' . $variables['label'] . ': </div>';
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
 * Alter tabs.
 */
function ec_resp_menu_local_tasks(&$variables) {
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
 * Implements hook_form_alter().
 */
function ec_resp_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'nexteuropa_europa_search_search_form':
      if (theme_get_setting('enable_interinstitutional_theme')) {
        $form['search_input_group']['europa_search_submit']['#type'] = 'image_button';
        $form['search_input_group']['europa_search_submit']['#src'] = drupal_get_path('theme', 'ec_resp') . '/images/search-button.gif';
        $form['search_input_group']['europa_search_submit']['#attributes']['class'] = array_merge($form['search_input_group']['europa_search_submit']['#attributes']['class'], array('btn', 'btn-default'));
        $form['search_input_group']['europa_search_submit']['#attributes']['alt'] = t('Search');
      }
      break;

    case 'search_block_form':
      $form['search_block_form']['#attributes']['placeholder'][] = t('Search');

      $form['actions']['submit']['#type'] = 'image_button';

      if (theme_get_setting('enable_interinstitutional_theme')) {
        $form['actions']['submit']['#src'] = drupal_get_path('theme', 'ec_resp') . '/images/search-button.gif';
      }
      else {
        $form['actions']['submit']['#src'] = drupal_get_path('theme', 'ec_resp') . '/images/search-button.png';
      }
      $form['actions']['submit']['#attributes']['class'][] = 'btn btn-default btn-small';
      $form['actions']['submit']['#attributes']['alt'] = t('Search');
      break;

    case 'apachesolr_search_custom_page_search_form':
    case 'search_form':
      $form['basic']['#attributes']['class'][] = 'input-group';
      $form['basic']['keys']['#title'] = '';
      $form['basic']['keys']['#attributes']['placeholder'][] = t('Search');
      $form['basic']['submit']['#type'] = 'image_button';
      $form['basic']['submit']['#src'] = drupal_get_path('theme', 'ec_resp') . '/images/search-button.png';
      $form['basic']['submit']['#attributes']['class'][] = 'btn btn-default btn-small';
      break;

    case 'add_media_form':
      $form['submit']['#attributes']['class'][] = 'btn btn-default';
      break;

    case 'comment_admin_overview':
      $form['options']['submit']['#attributes']['class'][] = 'btn-small';
      $form['comments']['#prefix'] = '<div class="table-responsive">';
      $form['comments']['#suffix'] = '</div>';
      break;

    case 'views_exposed_form':
      if (isset($form['submit'])) {
        $form['submit']['#attributes']['class'][] = 'btn-small';
      }
      break;

    case 'feature_set_admin_form':
      if (isset($form['submit']) && $form['submit']['#type'] == "submit") {
        $form['submit']['#value'] = t('Validate');
        $form['submit']['#attributes']['class'][] = 'btn';
        $form['submit']['#attributes']['class'][] = 'btn-lg';
        $form['submit']['#attributes']['class'][] = 'btn-success';
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

  // Hide format field.
  if (!user_access('administer nodes')) {
    $form['#after_build'][] = 'ec_resp_after_build';
  }
}

/**
 * Implements the afterbuild function.
 */
function ec_resp_after_build($form) {
  $form['comment_body'][LANGUAGE_NONE][0]['format']['#prefix'] = "<div class='hide'>";
  $form['comment_body'][LANGUAGE_NONE][0]['format']['#suffix'] = "</div>";
  $form['body'][LANGUAGE_NONE][0]['format']['#prefix'] = "<div class='hide'>";
  $form['body'][LANGUAGE_NONE][0]['format']['#suffix'] = "</div>";
  return $form;
}

/**
 * Returns HTML for a link.
 */
function ec_resp_link($variables) {
  $decoration = '';
  $action_bar_before = '';
  $action_bar_after = '';
  $btn_group_before = '';
  $btn_group_after = '';

  if (!isset($variables['options']['attributes']['class'])) {
    $variables['options']['attributes']['class'] = '';
  }

  if (isset($variables['options']['attributes']['action_bar'])) {
    switch ($variables['options']['attributes']['action_bar']) {
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
    switch ($variables['options']['attributes']['btn_group']) {
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
        $decoration .= '<span class="glyphicon glyphicon-plus"></span> ';
        $classes = array('btn', 'btn-success');
        break;

      case 'expand':
        $decoration .= '<span class="glyphicon glyphicon-chevron-down"></span> ';
        $classes = array('btn', 'btn-default', 'btn-sm');
        break;

      case 'collapse':
        $decoration .= '<span class="glyphicon glyphicon-chevron-up"></span> ';
        $classes = array('btn', 'btn-default', 'btn-sm');
        break;

      case 'delete':
        $decoration .= '<span class="glyphicon glyphicon-trash"></span> ';
        $classes = array('btn', 'btn-danger');
        break;

      case 'edit':
        $decoration .= '<span class="glyphicon glyphicon-pencil"></span> ';
        $classes = array('btn', 'btn-info');
        break;

      case 'message':
        $decoration .= '<span class="glyphicon glyphicon-envelope"></span> ';
        $classes = array('btn', 'btn-primary');
        break;

      case 'small':
        $classes = array('btn', 'btn-default', 'btn-sm');
        break;

      default:
        $classes = array();
        break;
    }

    if (is_array($variables['options']['attributes']['class'])) {
      $variables['options']['attributes']['class'] = array_merge($variables['options']['attributes']['class'], $classes);
    }
    else {
      $variables['options']['attributes']['class'] = $classes;
    }
  }
  $path = ($variables['path'] == '<nolink>') ? '#' : check_plain(url($variables['path'], $variables['options']));
  $output = $action_bar_before . $btn_group_before .
    '<a href="' . $path . '"' .
    drupal_attributes($variables['options']['attributes']) . '>' . $decoration .
    ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) .
    '</a>' . $btn_group_after . $action_bar_after;
  return $output;
}

/**
 * Render a block (to be displayed in a template file).
 */
function ec_resp_block_render($module, $block_id) {
  $block = block_load($module, $block_id);
  $block_content = _block_render_blocks(array($block));
  $build = _block_get_renderable_array($block_content);
  $block_rendered = drupal_render($build);
  return $block_rendered;
}

/**
 * Add an icon corresponding to content type.
 */
function ec_resp_icon_type_classes($subject) {
  $pattern = '@<i class="icon-(.+)"></i>@';
  $resexp = preg_replace_callback($pattern, 'ec_resp_class_replace', $subject);
  return $resexp;
}

/**
 * Add html markup for icons.
 */
function ec_resp_class_replace($match) {
  $output = '';

  switch ($match[1]) {
    case "Article":
      $output = '<i class="multisite-icon-file"></i>';
      break;

    case "community":
      $output = '<i class="multisite-icon-group"></i>';
      break;

    case "Document":
      $output = '<i class="multisite-icon-newspaper"></i>';
      break;

    case "Event":
      $output = '<i class="multisite-icon-calendar"></i>';
      break;

    case "Links":
      $output = '<i class="multisite-icon-link"></i>';
      break;

    case "News":
      $output = '<i class="multisite-icon-megaphone"></i>';
      break;

    case "Page":
      $output = '<i class="multisite-icon-file"></i>';
      break;

    case "Survey":
      $output = '<i class="multisite-icon-check"></i>';
      break;

    case "Wiki":
      $output = '<i class="multisite-icon-edit"></i>';
      break;

    case "F.A.Q":
      $output = '<i class="multisite-icon-question"></i>';
      break;

    case "GalleryMedia":
      $output = '<i class="multisite-icon-pictures"></i>';
      break;

    case "Blog post":
      $output = '<i class="multisite-icon-book"></i>';
      break;

    case "idea":
      $output = '<i class="multisite-icon-light-bulb"></i>';
      break;

    case "Simplenews newsletter":
      $output = '<i class="multisite-icon-paperplane"></i>';
      break;

    default:
      break;
  }
  return $output;
}

/**
 * Put Breadcrumbs in a li structure.
 */
function ec_resp_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  $crumbs = '';
  if (!empty($breadcrumb)) {
    foreach ($breadcrumb as $key => $value) {
      if ($key != 0) {
        $crumbs .= '<li>' . $value . '</li>';
      }
    }
  }
  return $crumbs;
}

/**
 * Implementation of theme_preproces_admin_menu_icon.
 *
 * Preprocesses variables for theme_admin_menu_icon().
 */
function ec_resp_preprocess_admin_menu_icon(&$variables) {
  $theme_path = drupal_get_path('theme', 'ec_resp');
  $logo_url = file_create_url($theme_path . '/images/favicon.png');
  $variables['src'] = preg_replace('@^https?:@', '', $logo_url);
}

/**
 * Implements template_preprocess_block().
 */
function ec_resp_preprocess_block(&$variables) {
  global $user, $language;

  $block_no_panel = array(
    'search' => 'form',
    'print' => 'print-links',
    'print_ui' => 'print-links',
    'workbench' => 'block',
    'social_bookmark' => 'social-bookmark',
    'views' => 'view_ec_content_slider-block',
    'om_maximenu' => array('om-maximenu-1', 'om-maximenu-2'),
    'menu' => 'menu-service-tools',
    'cce_basic_config' => 'footer_ipg',
  );

  // List of all blocks that don't need their title to be displayed.
  $block_no_title = array(
    'fat_footer' => 'fat-footer',
    'om_maximenu' => array('om-maximenu-1', 'om-maximenu-2'),
    'menu' => 'menu-service-tools',
    'cce_basic_config' => 'footer_ipg',
  );

  $block_no_body_class = array();

  $panel = TRUE;
  foreach ($block_no_panel as $key => $value) {
    if ($variables['block']->module == $key) {
      if (is_array($value)) {
        foreach ($value as $delta) {
          if ($variables['block']->delta == $delta) {
            $panel = FALSE;
            break;
          }
        }
      }
      else {
        if ($variables['block']->delta == $value) {
          $panel = FALSE;
          break;
        }
      }
    }
  }

  $title = TRUE;
  foreach ($block_no_title as $key => $value) {
    if ($variables['block']->module == $key) {
      if (is_array($value)) {
        foreach ($value as $delta) {
          if ($variables['block']->delta == $delta) {
            $title = FALSE;
            break;
          }
        }
      }
      else {
        if ($variables['block']->delta == $value) {
          $title = FALSE;
          break;
        }
      }
    }
  }

  $body_class = TRUE;
  foreach ($block_no_body_class as $key => $value) {
    if ($variables['block']->module == $key && $variables['block']->delta == $value) {
      $body_class = FALSE;
    }
  }

  $variables['panel'] = $panel;
  $variables['title'] = $title;
  $variables['body_class'] = $body_class;

  if (isset($variables['block']->bid)) {
    switch ($variables['block']->bid) {
      case 'locale-language':
        $languages = language_list();

        $items = array();
        $items[] = array(
          'data' => '<span class="off-screen">' . t("Current language") . ':</span> ' . $language->language,
          'class' => array('selected'),
          'title' => $language->native,
          'lang' => $language->language,
        );
        // Get path of translated content.
        $translations = translation_path_get_translations(current_path());
        $language_default = language_default();

        foreach ($languages as $language_object) {
          $prefix = $language_object->language;
          $language_name = $language_object->name;

          if (isset($translations[$prefix])) {
            $path = $translations[$prefix];
          }
          else {
            $path = current_path();
          }

          // Get the related url alias
          // Check if the multisite language negotiation
          // with suffix url is enabled.
          $language_negociation = variable_get('language_negotiation_language');
          if (isset($language_negociation['locale-url-suffix'])) {
            $delimiter = variable_get('language_suffix_delimiter', '_');
            $alias = drupal_get_path_alias($path, $prefix);

            if ($alias == variable_get('site_frontpage', 'node')) {
              $path = ($prefix == 'en') ? '' : 'index';
            }
            else {
              if ($alias != $path) {
                $path = $alias;
              }
              else {
                $path = drupal_get_path_alias(isset($translations[$language_name]) ? $translations[$language_name] : $path, $language_name);
              }
            }
          }
          else {
            $path = drupal_get_path_alias($path, $prefix);
          }

          // Add enabled languages.
          if ($language_name != $language->name) {
            $items[] = array(
              'data' => l($language_name, filter_xss($path), array(
                'attributes' => array(
                  'hreflang' => $prefix,
                  'lang' => $prefix,
                  'title' => $language_name,
                ),
                'language' => $language_object,
              )),
            );
          }
        }

        $variables['language_list'] = theme('item_list', array('items' => $items));
        break;

      case 'system-user-menu':
        if ($user->uid) {
          $name = theme('username', array('account' => $user, 'nolink' => TRUE));
          $variables['welcome_message'] = "<div class='username'>" . t('Welcome,') . ' <strong>' . ($name) . '</strong></div>';

        }
        $menu = menu_navigation_links("user-menu");
        $items = array();

        // Manage redirection after login.
        $status = drupal_get_http_header('status');
        if (strpos($status, '404') !== FALSE) {
          $dest = 'home';
        }
        elseif (strpos(current_path(), 'user/register') !== FALSE) {
          $dest = 'home';
        }
        elseif (strpos(current_path(), 'user/login') !== FALSE) {
          $dest = 'home';
        }
        else {
          $dest = drupal_get_path_alias();
        }

        foreach ($menu as $item_id) {
          // Get icon links to menu item.
          $icon = (isset($item_id['attributes']['data-image']) ? $item_id['attributes']['data-image'] : '');

          // Get display title option.
          $display_title = (isset($item_id['attributes']['data-display-title']) ? $item_id['attributes']['data-display-title'] : 1);

          // Add the icon.
          if ($icon) {
            if ($display_title) {
              $item_id['title'] = '<span class="glyphicon glyphicon-' . $icon . '" aria-hidden="true"></span> ' . $item_id['title'];
            }
            else {
              // If the title is not supposed to be displayed, add a visually
              // hidden title that is accessible for screen readers.
              $item_id['title'] = '<span class="glyphicon glyphicon-' . $icon . ' menu-no-title" aria-hidden="true"></span><span class="sr-only">' . $item_id['title'] . '</span>';
            }
          }

          // Add redirection for login, logout and register.
          if ($item_id['href'] == 'user/login' || $item_id['href'] == 'user/register') {
            $item_id['query']['destination'] = $dest;
          }
          if ($item_id['href'] == 'user/logout') {
            $item_id['query']['destination'] = '<front>';
          }

          // Add icon before menu item
          // TODO: make it editable in administration.
          switch ($item_id['href']) {
            case 'user':
              $item_id['attributes']['type'] = 'user';
              break;

            case 'user/login':
              $item_id['attributes']['type'] = 'login';
              break;

            case 'user/logout':
              $item_id['attributes']['type'] = 'logout';
              break;

            case 'admin/workbench':
              $item_id['attributes']['type'] = 'workbench';
              break;

          }

          $item_id['html'] = TRUE;

          $items[] = l($item_id['title'], $item_id['href'], $item_id);
        }

        $variables['menu_items'] = implode('', $items);
        break;

      case 'easy_breadcrumb-easy_breadcrumb':
        $variables['menu_breadcrumb'] = menu_tree('menu-breadcrumb-menu');
        break;

    }
  }
}

/**
 * Preprocesses variables for theme_username().
 */
function ec_resp_preprocess_username(&$vars) {
  if (isset($vars['link_path']) && isset($vars['nolink']) && $vars['nolink']) {
    unset($vars['link_path']);
  }
}

/**
 * Returns HTML for a dropdown.
 */
function ec_resp_dropdown($variables) {
  $items = $variables['items'];
  $attributes = array();
  $output = "";

  if (!empty($items)) {
    if (theme_get_setting('disable_dropdown_menu')) {
      $output .= "<ul>";
    }
    else {
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
  }
  return $output;
}

/**
 * Implements theme_table().
 */
function ec_resp_table($variables) {
  $header = $variables['header'];
  $rows = $variables['rows'];
  $attributes = $variables['attributes'];
  $caption = $variables['caption'];
  $colgroups = $variables['colgroups'];
  $sticky = $variables['sticky'];
  $empty = $variables['empty'];

  // Add sticky headers, if applicable.
  if (count($header) && $sticky) {
    drupal_add_js('misc/tableheader.js');
    // Add 'sticky-enabled' class to the table to identify it for JS.
    // This is needed to target tables constructed by this function.
    $attributes['class'][] = 'sticky-enabled table table-striped';
  }

  $output = '<table' . drupal_attributes($attributes) . ">\n";

  if (isset($caption)) {
    $output .= '<caption>' . $caption . "</caption>\n";
  }

  // Format the table columns:
  if (count($colgroups)) {
    foreach ($colgroups as $number => $colgroup) {
      $attributes = array();

      // Check if we're dealing with a simple or complex column.
      if (isset($colgroup['data'])) {
        foreach ($colgroup as $key => $value) {
          if ($key == 'data') {
            $cols = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cols = $colgroup;
      }

      // Build colgroup.
      if (is_array($cols) && count($cols)) {
        $output .= ' <colgroup' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cols as $col) {
          $output .= ' <col' . drupal_attributes($col) . ' />';
        }
        $output .= " </colgroup>\n";
      }
      else {
        $output .= ' <colgroup' . drupal_attributes($attributes) . " />\n";
      }
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $empty) {
    $header_count = 0;
    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }
    $rows[] = array(
      array(
        'data' => $empty,
        'colspan' => $header_count,
        'class' => array('empty', 'message'),
      ),
    );
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    // HTML requires that the thead tag has tr tags in it followed by tbody
    // tags. Using ternary operator to check and see if we have any rows.
    $output .= (count($rows) ? ' <thead><tr>' : ' <tr>');
    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }
    // Using ternary operator to close the tags based on whether
    // or not there are rows.
    $output .= (count($rows) ? " </tr></thead>\n" : "</tr>\n");
  }
  else {
    $ts = array();
  }

  // Format the table rows:
  if (count($rows)) {
    $output .= "<tbody>\n";
    $flip = array(
      'even' => 'odd',
      'odd' => 'even',
    );
    $class = 'even';
    foreach ($rows as $number => $row) {
      // Check if we're dealing with a simple or complex row.
      if (isset($row['data'])) {
        foreach ($row as $key => $value) {
          if ($key == 'data') {
            $cells = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cells = $row;
      }
      if (count($cells)) {
        // Add odd/even class.
        if (empty($row['no_striping'])) {
          $class = $flip[$class];
          $attributes['class'][] = $class;
        }

        // Build row.
        $output .= ' <tr' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cells as $cell) {
          $cell = tablesort_cell($cell, $header, $ts, $i++);
          $output .= _theme_table_cell($cell);
        }
        $output .= " </tr>\n";
      }
    }
    $output .= "</tbody>\n";
  }

  $output .= "</table>\n";
  return $output;
}

/**
 * Implements template_preprocess_comment().
 */
function ec_resp_preprocess_comment(&$variables) {
  $variables['comment_created'] = format_date($variables['elements']['#comment']->created, 'custom', 'd/m/Y H:i');
}

/**
 * Implements template_preprocess_comment_wrapper().
 */
function ec_resp_preprocess_comment_wrapper(&$variables) {
  $variables['title_text'] = $variables['content']['#node']->type != 'forum' ? t('Comments') : t('Replies');
}

/**
 * Implements theme_nexteuropa_multilingual_language_list().
 */
function ec_resp_nexteuropa_multilingual_language_list(array $variables) {
  // Provide defaults.
  $options = !empty($variables['options']) ? $variables['options'] : [];

  $content = '<div class="row">';

  $half = ceil(count($variables['languages']) / 2);
  $first_half = array_slice($variables['languages'], 0, $half);
  $second_half = array_slice($variables['languages'], $half);

  $content .= _ec_resp_nexteuropa_multilingual_language_list_column($first_half, $variables['path'], $options);
  $content .= _ec_resp_nexteuropa_multilingual_language_list_column($second_half, $variables['path'], $options);

  $content .= '</div>';

  return $content;
}

/**
 * Helper function to display splash page language list column.
 *
 * @param array $languages
 *   An associative array of languages to link to.
 * @param string $path
 *   The internal path being linked to.
 * @param array $options
 *   An associative array of additional options.
 *
 * @return string
 *   Formatted HTML column displaying the list of provided languages.
 */
function _ec_resp_nexteuropa_multilingual_language_list_column($languages, $path, $options) {
  $content = '<div class="col-sm-6">';
  foreach ($languages as $language) {
    $options['attributes']['lang'] = $language->language;
    $options['attributes']['hreflang'] = $language->language;
    $options['attributes']['class'] = 'btn splash-page__btn-language';
    $options['language'] = $language;
    $content .= l($language->native, $path, $options);
  }
  $content .= '</div>';

  return $content;
}
