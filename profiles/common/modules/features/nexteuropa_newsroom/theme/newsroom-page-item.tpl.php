<?php
/**
 * @file
 * Page item.
 */
?>
<div class="views-row clearfix">
  <div class="views-field views-field-field-newsroom-item-type">
    <?php echo l($type_title, $type_url); ?>
  </div>
  <div class="views-field-field-newsroom-item-short-title">
    <?php echo l($title, $node_url); ?>
  </div>

  <?php if ($image): ?>
  <div class="views-field-field-newsroom-illustrative-img">
    <?php echo $image; ?>
  </div>
  <?php endif; ?>

  <?php if (!empty($start_date) || !empty($end_date)): ?>
    <div class="views-field-field-newsroom-item-date">        
      <?php if (!empty($start_date)): ?>
      <?php if (!empty($end_date)): ?>
      <?php echo t('From'); ?> 
      <?php endif; ?>
      <span class="date-display-single" property="dc:date" datatype="xsd:dateTime" content="<?php echo $start_date; ?>"><?php echo $start_date; ?></span>
      <?php endif; ?>
      <?php if (!empty($end_date)): ?>
       <?php echo t('to'); ?>
      <span class="date-display-single" property="dc:date" datatype="xsd:dateTime" content="<?php echo $end_date; ?>"><?php echo $end_date; ?></span>
      <?php endif; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($venue)): ?>
  <div class="views-field-field-newsroom-item-venue">
    <?php echo $venue; ?>
  </div>  
  <?php endif; ?>
  <div class="views-field-field-newsroom-teaser">        
    <?php echo $teaser; ?>
    <?php echo l(t('Read more'), $node_url); ?>
  </div>  
</div>