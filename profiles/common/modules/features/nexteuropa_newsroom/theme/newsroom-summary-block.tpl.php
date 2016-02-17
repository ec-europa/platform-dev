<?php
/**
 * @file
 * Block summary template.
 */
?>
<div class="block-nexteuropa-newsroom" >
  <div class="newsroom_rss">
    <?php echo $rss; ?>
  </div>
  <?php foreach ($items as $item) : ?>
    <?php echo $item->generateContent(); ?>
  <?php endforeach; ?>
</div>
