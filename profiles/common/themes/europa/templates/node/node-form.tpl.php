<?php 
/**
 * @file
 * Customize the display of a node form.
 */
?>

<div class="row">
  <div class="col-md-8">
    <?php print drupal_render_children($form); ?>    
    <div class="visible-md visible-lg">
      <?php print render($buttons); ?>
    </div>    
  </div>
  <div class="col-md-4 node-form-sidebar">
    <div class="visible-md visible-lg">
      <?php print render($buttons); ?>
    </div>    
    <?php print render($sidebar); ?>
    <div class="visible-sm visible-xs">
      <?php print render($buttons); ?>
    </div>    
  </div>
</div>
