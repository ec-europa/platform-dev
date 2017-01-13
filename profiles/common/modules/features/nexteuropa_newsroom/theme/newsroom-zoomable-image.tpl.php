<?php

/**
 * @file
 * Zoomable image HTML markup.
 */
?>
<figure class="newsroom-image">
  <?php if ($zoomable): ?>
    <div class="picContainer zoomable">
      <?php echo l($image_output . "<span class='zoomIcon'></span>", $path_to_original, array('html' => TRUE, 'attributes' => array('class' => 'fancybox'))); ?>
    </div>
  <?php else: ?>
    <div class="picContainer">
      <?php echo $image_output; ?>
    </div>
  <?php endif; ?>
  <?php if ($caption || $copyright): ?>
    <figcaption>
      <?php if ($caption): ?>
      <div class="legend">
          <?php echo $caption; ?>
      </div>
      <?php endif; ?>
      <?php if ($copyright): ?>
        <div class="copyright">&copy;
          <?php echo $copyright; ?>
        </div>
      <?php endif; ?>
    </figcaption>
  <?php endif; ?>
</figure>
