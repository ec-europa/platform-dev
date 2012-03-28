<?php
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php print $wrapper_prefix; ?>
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>

  <div class="carrousel">
  <?php print $list_type_prefix; ?>
    <?php foreach ($rows as $id => $row): ?>
      <li class="<?php print $classes_array[$id]; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
  <?php print $list_type_suffix; ?>
    <p class="wrapper"></p>    
  </div>
  <p class="carrousel_buttons">
    <a class="btn" id="previous"><i class='icon-chevron-left'></i></a>
    <a class="btn" id="next"><i class='icon-chevron-right'></i></a>
  </p>
  
<?php print $wrapper_suffix; ?>
