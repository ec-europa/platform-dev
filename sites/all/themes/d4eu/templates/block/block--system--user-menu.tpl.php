<?php
/**
 * @file
 * Sytem user menu.
 */
?>
<div class="utility-nav">
  <?php if (isset($user_welcome)): ?>
    <div class='username'><?php print $user_welcome; ?></div>
  <?php endif; ?>
  <?php global $base_url; ?>

  <div id="<?php echo $block_html_id; ?>" class="">
	<ul>
    <?php 
      $menu = menu_navigation_links('user-menu');
      $items = '';

      // Manage redirection after login.
      $status = drupal_get_http_header('status');
      if (strpos($status, '404') !== FALSE):
        $dest = 'home';
      elseif (strpos($_GET['q'], 'user/register') !== FALSE):
        $dest = 'home';
      elseif (strpos($_GET['q'], 'user/login') !== FALSE):
        $dest = 'home';
      else :
        $dest = drupal_get_path_alias();
      endif;

      foreach ($menu as $item_id):
        // Add redirection for login, logout and register.
        if ($item_id['href'] == 'user/login' || $item_id['href'] == 'user/register'):
          $attributes['query']['destination'] = $dest;
        endif;
        if ($item_id['href'] == 'user/logout'):
          $attributes['query']['destination'] = $base_url;
        endif;

        $items .= '<li>' . l($item_id['title'], $item_id['href'], array()) . '</li>';
      endforeach;

      echo $items;
    ?>
	</ul>
  </div>
</div>
