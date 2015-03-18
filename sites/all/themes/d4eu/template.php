<?php
/**
 * @file
 * Contains custom theme functionality.
 */

/**
 * Implements theme_menu_tree__MENU_NAME().
 */
function d4eu_menu_tree__main_menu($variables) {
  if (strpos($variables['tree'], 'main_menu_dropdown') && !strpos($variables['tree'], '<ul') && !theme_get_setting('disable_dropdown_menu')) {
    return '<ul class="dropdown-menu">' . $variables['tree'] . '</ul>';
  }
  else {
    $variables['tree'] = str_replace('<ul class="nav nav-pills">', '<ul class="dropdown-menu">', $variables['tree']);
    return '<ul class="nav nav-pills">' . $variables['tree'] . '</ul>';
  }
}

/**
 * Builds main menu.
 */
function d4eu_menu_link__main_menu(array $variables) {

  // Remove title attribute for links with the same Title.
  if (isset($variables['element']['#localized_options']['attributes']['title']) && $variables['element']['#title'] == $variables['element']['#localized_options']['attributes']['title']) {
    unset($variables['element']['#localized_options']['attributes']['title']);
  }

  // Set Home title for the link.
  if (isset($variables['element']['#href']) && $variables['element']['#href'] == '<front>') {
    $variables['element']['#localized_options']['attributes']['title'] = t('Home');
  }
  $variables['element']['#localized_options']['html'] = TRUE;
  return theme_menu_link($variables);
}

/**
 * Implements hook_preprocess_block().
 */
function d4eu_preprocess_block(&$variables) {
  $block = $variables['block'];

  // Constructs a block ID based on module, region and delta.
  $block_id = $variables['elements']['#block']->region . '-' . $variables['elements']['#block']->module . '-' . $variables['elements']['#block']->delta;

  switch ($block_id) {
    case 'header_top-system-user-menu':

      // Constructs the name of the user for display in top toolbar.
      if ($variables['user']->uid) {
        $name = format_username($variables['user']);
        $options = array();
        $options['attributes']['class'][] = 'user-link';
        $variables['user_welcome'] = t('Welcome, <strong class="user-link">!name</strong>',
            array(
              '!name' => l($name, 'user/' . $variables['user']->uid, $options))
            );
      }

      break;
  }
}


/**
 * Implements hook_menu_block_view_alter().
 */
function d4eu_block_view_alter(&$data, $block) {
  // Remove from the list items.
  if (isset($data['content'])) {
    if (!is_array($data['content'])) {
      preg_match_all('/<a(.*?)>/s', $data['content'], $matches);

      if (isset($matches[0])) {
        foreach ($matches[0] as $link) {
          if (strpos($link, ' class="') !== FALSE) {
            $new_link = str_replace(' class="list-group-item', ' class="', $link);
            $data['content'] = str_replace($link, $new_link, $data['content']);
          }
        }
      }
    }
  }
}
