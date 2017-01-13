<?php

/**
 * @file
 * Agenda items.
 */
?>
<div class="date-row">
  <?php echo $date; ?>
  <div class="date-events">
    <?php if (count($items) > 0): ?>
      <?php foreach ($items as $item): ?>
        <div class="views-row clearfix">      
          <span class="newsroom_type"><?php echo $item->name; ?>: </span>
          <div class="newsroom_title">
            <?php $prefix = $item->new ? '<span class="itemFlag flagHot newItem">New</span> ' : NULL; ?>
            <?php echo l($prefix . $item->title, $item->url, array('html' => TRUE, 'absolute' => TRUE)); ?>
          </div>
          <div class="newsroom_item_metadata">
            <?php echo t('From @start_date', array('@start_date' => $item->prepared_start_date)); ?>
            <?php if (!empty($item->end_date)): ?>
               <?php echo t('to @end_date', array('@end_date' => $item->prepared_end_date)); ?>
            <?php endif; ?>
          </div>
        </div>
      <?php endforeach; ?>
    <?php else: ?>
      <div class="nothing-found"><?php echo t('None'); ?></div>
    <?php endif; ?>
  </div>
</div>
