<?php
/**
 * @file
 * Related content tree presentation.
 */
?>
<ul>  
  <?php $cnt = count($parent_items); ?>
  <?php $i = 1; ?>
  <?php if ($cnt > 0): ?>
    <?php foreach($parent_items as $parent_id => $item): ?>
    <li>  
      <?php echo l($item, 'node/' . $parent_id); ?>
      <?php if ($i == $cnt): ?>
        <ul>
          <li>
            <?php echo l($current_item->title, 'node/' . $current_item->nid); ?>
            
            <?php if (count($children_items) > 0): ?>
            <ul> 
              <?php foreach($children_items as $children_id => $item): ?>
                <li>
                  <?php echo l($item, 'node/' . $children_id); ?>
                </li>
              <?php endforeach; ?>
            </ul>
            <?php endif; ?>
          </li>
          <?php foreach($brother_items as $brother_id => $item): ?>
            <li>
              <?php if ($current_item->nid != $brother_id): ?>
              <?php echo l($item, 'node/' . $brother_id); ?>
              <?php endif; ?>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>
    </li>
    <?php $i++; ?>
    <?php endforeach; ?>
  <?php else : ?>
    <li>  
      <?php echo l($current_item->title, 'node/' . $current_item->nid); ?>
      <?php if (count($children_items) > 0): ?>
      <ul> 
        <?php foreach($children_items as $children_id => $item): ?>
          <li>
            <?php echo l($item, 'node/' . $children_id); ?>
          </li>
        <?php endforeach; ?>
      </ul>
      <?php endif; ?>
    </li>
    <?php foreach($brother_items as $brother_id => $item): ?>
      <li>
        <?php if ($current_item->nid != $brother_id): ?>
        <?php echo l($item, 'node/' . $brother_id); ?>
        <?php endif; ?>
      </li>
    <?php endforeach; ?>
  <?php endif; ?>
</ul>
