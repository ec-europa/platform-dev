<?php

/**
 * @file
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
  <?php
  foreach ($rows as $id => $row):
    print '<div class="' . $classes_array[$id] . ($first ? ' active' : '') . '">' . $row . '</div>';
    $first = FALSE;
  endforeach;
  ?>
  </div>
  <a class="left carousel-control" href="#media-gallery-carousel" data-slide="prev"><span class="glyphicon glyphicon-chevron-left"></span></a>
  <a class="right carousel-control" href="#media-gallery-carousel" data-slide="next"><span class="glyphicon glyphicon-chevron-right"></span></a>    
</div>
