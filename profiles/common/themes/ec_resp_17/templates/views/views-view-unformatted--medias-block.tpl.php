<?php
/**
 * @file
 * Views-view-unformatted.tpl.php.
 *
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

$first = TRUE;
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

  <div id="media-gallery-carousel" class="carousel slide">

    <ol class="carousel-indicators">
    <?php
    foreach ($rows as $id => $row):
      print '<li data-target="#media-gallery-carousel" data-slide-to="' . $id . '" class="' . ($first ? "active" : "") . '"></li>';

      $first = FALSE;
    endforeach; ?>
    </ol>

    <?php $first = TRUE; ?>

    <div class="carousel-inner">
<?php foreach ($rows as $id => $row): ?>
  <div class="<?php print $classes_array[$id]; ?> <?php print ($first ? 'active' : '') ?>">
    <?php

      // Check if the galleries are actually empty.
      $row = str_replace('[Empty_gallery][Empty_gallery]', '', $row);
      // Check if there is only one picture.
      $row = str_replace('[Empty_gallery]', '', $row);

      print $row;
      $first = FALSE;
    ?>
  </div>
<?php endforeach; ?>
    </div>
    <a class="left carousel-control" href="#media-gallery-carousel" data-slide="prev"><span class="glyphicon glyphicon-chevron-left"></span></a>
    <a class="right carousel-control" href="#media-gallery-carousel" data-slide="next"><span class="glyphicon glyphicon-chevron-right"></span></a>    
  </div>
