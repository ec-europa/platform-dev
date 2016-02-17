<?php
/**
 * @file
 * Agenda.
 */
?>
<?php if (count($items) > 0) : ?>
  <div class="view view-newsroom-page-content">
    <div class="view-content">
      <?php foreach ($items as $item) : ?>
        <div class="views-row">
          <span class="newsroom_type"><?php echo $item->name; ?>: </span>
          <div class="newsroom_title">
            <?php $prefix = $item->new ? '<span class="itemFlag flagHot newItem">New</span> ' : NULL; ?>
            <?php echo l($prefix . $item->title, 'node/' . $item->nid, array('html' => TRUE)); ?>
          </div>
          <span class="newsroom_date">
            <?php $date = date('d/m/Y', $item->created); ?>
            <span content="<?php echo $date ?>" datatype="xsd:dateTime" property="dc:date" class="date-display-single"><?php echo $date; ?></span>            
          </span>
        </div>
      <?php endforeach; ?>
    </div>
  </div>
<?php endif; ?>
