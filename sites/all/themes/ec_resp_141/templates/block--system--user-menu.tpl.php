<?php

/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 *
 * @ingroup themeable
 */

?>
  <li>
  <?php 
  global $user;

  if (!empty($user) && 0 != $user->uid) {
    $full_user = user_load($user->uid);
    $name = (isset($full_user->field_firstname['und'][0]['value']) && isset($full_user->field_lastname['und'][0]['value']) ? $full_user->field_firstname['und'][0]['value'] . ' ' . $full_user->field_lastname['und'][0]['value'] : $user->name);

    print ("<div class='username'>" . t('Welcome, ') . '<strong>' . $name . '</strong></div>');
  }
  ?>
    
  <ul id="<?php print $block_html_id; ?>" class="unstyled inline">
  <?php 
    $menu = menu_navigation_links("user-menu");
    $items = "";

    // Manage redirection after login
    $status = drupal_get_http_header('status');
    if (strpos($status, '404') !== FALSE) {
      $dest = 'home';
    }
    elseif (strpos($_GET['q'], 'user/register') !== FALSE) {
      $dest = 'home';
    }
    elseif (strpos($_GET['q'], 'user/login') !== FALSE) {
      $dest = 'home';
    }
    else {
      $dest = drupal_get_path_alias();
    }

    $attributes = array(
      'attributes' => array(
        'type' => '',
        'class' => array('btn')
      )
    );
    
    foreach ($menu as $item_id) {
      // Add redirection for login, logout and register
      if ($item_id['href'] == 'user/login' || $item_id['href'] == 'user/register') {
        $attributes['query']['destination'] = $dest;
      }

      $items .= '<li>'.l($item_id['title'],$item_id['href'], $attributes).'</li>';
    }
    
    print $items;
  ?>    
  </ul>  
  </li>
