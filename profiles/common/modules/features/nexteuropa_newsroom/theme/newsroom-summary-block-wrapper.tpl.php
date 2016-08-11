<?php

/**
 * @file
 * Summary block wrapper.
 */
?>
<?php if ($content): ?>
<div class="newsroom_item_container <?php echo implode(' ', $css_classes) ?>" id="newsroom-block-<?php echo $type_url; ?>">
  <a name="newsroom-block-<?php echo $type_url; ?>"></a>
  <h3 class="newsroom_title"><?php echo l($title, $url); ?></h3>
  <?php echo $content; ?>
  <div class="newsroom_more">
    <?php $title = '<span class="more">More</span> <span class="more_type"><em class="placeholder">' . $title . '</em></span>'; ?>
    <?php echo l($title, $url, array('html' => TRUE)); ?>
  </div>
</div>
<?php endif; ?>
