<?php
/**
 * @file
 * Page wrapper.
 */
?>
<div class="newsroomPage-filterForm">
  <h3><?php echo t('filter by');?></h3>
  <?php echo $filter_form; ?>
</div>
<div class="newsroom-page view-content">
  <?php echo $featured_item; ?>
  <?php echo $items; ?>
</div>
