<?php
/**
 * @file
 * Menu top services.
 */
global $user, $base_url;

$menu = menu_navigation_links('menu-service-tools');
$items = '';

foreach ($menu as $item_id):
  $items .= '<li>' . l($item_id['title'], $item_id['href'], array()) . '</li>';
endforeach;

if (!empty($items)):
  ?>
  <div class="administrative-nav">
    <div id="<?php echo $block_html_id; ?>" class="">
      <?php echo '<ul>' . $items . '</ul>'; ?>
    </div>
  </div>
<?php endif; ?>
