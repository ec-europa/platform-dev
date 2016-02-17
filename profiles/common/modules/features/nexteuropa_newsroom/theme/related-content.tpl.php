<?php
/**
 * @file
 * Related content tree presentation.
 */
?>
<?php $cnt_parent = count($parent_items); ?>
<?php $cnt_children = count($children_items); ?>
<?php $cnt_brother = count($brother_items); ?>
<?php if ($cnt_parent > 0 || $cnt_children > 0 || $cnt_brother > 0): ?>
<ul>  
  <?php $i = 1; ?>
  <?php if ($cnt_parent > 0): ?>
    <?php foreach ($parent_items as $parent_id => $item): ?>
      <li>  
        <?php echo l($item, 'node/' . $parent_id); ?>
        <?php if ($i == $cnt_parent): ?>
          <ul>
            <li>
              <?php echo l($current_item->title, 'node/' . $current_item->nid); ?>

              <?php if (count($children_items) > 0): ?>
                <ul> 
                  <?php foreach ($children_items as $children_id => $item): ?>
                    <li>
                      <?php echo l($item, 'node/' . $children_id); ?>
                    </li>
                  <?php endforeach; ?>
                </ul>
              <?php endif; ?>
            </li>
            <?php if ($cnt_brother > 0): ?>
              <?php foreach ($brother_items as $brother_id => $item): ?>
                <li>
                  <?php if ($current_item->nid != $brother_id): ?>
                    <?php echo l($item, 'node/' . $brother_id); ?>
                  <?php endif; ?>
                </li>
              <?php endforeach; ?>
            <?php endif; ?>
          </ul>
        <?php endif; ?>
      </li>
      <?php $i++; ?>
    <?php endforeach; ?>
  <?php else : ?>
    <li>  
      <?php if ($cnt_children > 0): ?>
        <?php echo l($current_item->title, 'node/' . $current_item->nid); ?>
        <ul> 
          <?php foreach ($children_items as $children_id => $item): ?>
            <li>
              <?php echo l($item, 'node/' . $children_id); ?>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>
    </li>
    <?php if ($cnt_brother > 0): ?>
      <?php foreach ($brother_items as $brother_id => $item): ?>
        <li>
          <?php if ($current_item->nid != $brother_id): ?>
            <?php echo l($item, 'node/' . $brother_id); ?>
          <?php endif; ?>
        </li>
      <?php endforeach; ?>
    <?php endif; ?>
  <?php endif; ?>
</ul>
<?php endif; ?>
