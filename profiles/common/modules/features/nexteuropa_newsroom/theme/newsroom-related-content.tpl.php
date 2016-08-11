<?php

/**
 * @file
 * Related content tree presentation.
 */
?>
<?php $cnt_children = count($children_items); ?>
<?php $cnt_brother = count($brother_items); ?>
<?php if ($parent_item || $cnt_children > 0 || $cnt_brother > 0): ?>
  <ul>  
      <?php if ($parent_item): ?>
      <li>
        <?php echo l($parent_item->title, 'node/' . $parent_item->id); ?>
        <?php if ($cnt_children > 0 || $cnt_brother > 0): ?>
        <ul>
        <?php endif; ?>
      <?php endif; ?>


      <?php if ($cnt_children > 0): ?>
      <li>  
        <?php echo l($current_item->title, 'node/' . $current_item->nid); ?>
        <ul> 
          <?php foreach ($children_items as $item): ?>
            <li>
              <?php echo l($item->title, 'node/' . $item->id); ?>
            </li>
          <?php endforeach; ?>
        </ul>
      </li>
      <?php endif; ?>

      <?php if ($cnt_brother > 0): ?>
        <?php foreach ($brother_items as $brother_id => $item): ?>
          <li>
            <?php echo l($item->title, 'node/' . $item->id); ?>
          </li>
        <?php endforeach; ?>
      <?php endif; ?>

  <?php if ($parent_item): ?>
    <?php if ($cnt_children > 0 || $cnt_brother > 0): ?>
    </ul>
    <?php endif; ?>
  </li>
  <?php endif; ?>
</ul>
<?php endif; ?>
