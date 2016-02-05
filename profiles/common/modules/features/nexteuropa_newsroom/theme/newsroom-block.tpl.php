<?php
/**
 * @file
 * Agenda.
 */
?>
<div class="newsroom_item_container <?php echo implode(' ', $css_classes) ?>" id="newsroom-block-<?php echo $type_url; ?>">
  <a name="newsroom-block-<?php echo $type_url; ?>"></a>
  
  <h3 class="newsroom_title"><?php echo l($title, $url); ?></h3>

  <?php echo $content; ?>

  <div class="newsroom_more">
    <a href="<?php echo $url; ?>"><span class="more">More</span> <span class="more_type"><em class="placeholder"><?php echo $title; ?></em></span></a>
  </div>
</div>