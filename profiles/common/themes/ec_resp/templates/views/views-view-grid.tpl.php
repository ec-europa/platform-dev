<?php

/**
 * @file
 * Default simple view template to display a rows in a grid.
 *
 * Available variables:
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
 */

if ($nb_col > 12):
  $nb_col = 12;
endif;
?>

<div class="<?php print $class; ?>">
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

  <div class="row <?php print $class; ?>"<?php print $attributes; ?>>
<?php
$index = 0;

// Get all views elements.
foreach ($rows as $row_number => $columns):
  foreach ($columns as $column_number => $item):
    if (!empty($item)):
?>
    <div class="col-lg-<?php print $grid_col[$nb_col]['lg'][$index % count($grid_col[$nb_col]['lg'])]; ?> col-md-<?php print $grid_col[$nb_col]['md'][$index % count($grid_col[$nb_col]['md'])]; ?> col-sm-<?php print $grid_col[$nb_col]['sm'][$index % count($grid_col[$nb_col]['sm'])]; ?> col-xs-<?php print $grid_col[$nb_col]['xs'][$index % count($grid_col[$nb_col]['xs'])]; ?>">
      <div class="grid-item">
        <?php print ec_resp_icon_type_classes($item); ?>
      </div>
    </div>

    <?php if ((($index + 1) % count($grid_col[$nb_col]['lg'])) == 0): ?>
    <div class="clearfix visible-lg"></div>
    <?php endif; ?>

    <?php if ((($index + 1) % count($grid_col[$nb_col]['md'])) == 0): ?>
    <div class="clearfix visible-md"></div>
    <?php endif; ?>

    <?php if ((($index + 1) % count($grid_col[$nb_col]['sm'])) == 0): ?>
    <div class="clearfix visible-sm"></div>
    <?php endif; ?>

    <?php if ((($index + 1) % count($grid_col[$nb_col]['xs'])) == 0): ?>
    <div class="clearfix visible-xs"></div>
    <?php endif; ?>

    <?php $index++; ?>
<?php
    endif;
  endforeach;
endforeach;
?>
  </div>
</div>
