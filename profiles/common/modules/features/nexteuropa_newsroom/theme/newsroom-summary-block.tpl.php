<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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