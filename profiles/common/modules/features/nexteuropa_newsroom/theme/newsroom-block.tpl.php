<?php
/**
 * @file
 * Agenda.
 */
?>
<div class="newsroom_item_container <?php echo ($highlighted) ? 'featured highlighted' : NULL; ?>" id="newsroom-block-<?php echo $type_url; ?>">
  <a name="newsroom-block-<?php echo $type_url; ?>"></a>
  
  <h3 class="newsroom_title"><?php echo l($title, $url); ?></h3>
  
  <?php if (count($items) > 0) : ?>
  <div class="view view-newsroom-page-content">
    <div class="view-content">
      <?php foreach($items as $item) : ?>
      <div class="views-row">
        <span class="newsroom_type"><?php echo $item->name; ?>: </span>
        <div class="newsroom_title">
          <?php echo l($item->title, 'node/' . $item->nid); ?>
        </div>
        <span class="newsroom_date">
          <?php $date = new DateTime($item->date); ?>
          <span content="2012-07-20T02:00:00+02:00" datatype="xsd:dateTime" property="dc:date" class="date-display-single"><?php echo $date->format('d/m/Y'); ?></span>            
        </span>
      </div>
      <?php endforeach; ?>
    </div>
  </div>
  <?php endif; ?>
  <div class="newsroom_more">
    <a href="<?php echo $url; ?>"><span class="more">More</span> <span class="more_type"><em class="placeholder"><?php echo $title; ?></em></span></a>
  </div>
</div>