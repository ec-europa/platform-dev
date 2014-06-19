<?php
/**
 * @file views-view-grid.tpl.php
 * Default simple view template to display a rows in a grid.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
 */
 
$nb_row = count($rows[0]);
if ($nb_row > 12) $nb_row = 12;
?>

<div class="<?php print $class; ?>">
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

  <div class="row <?php print $class; ?>"<?php print $attributes; ?>>
<?php 
$index = 0;

//get all views elements
foreach ($rows as $row_number => $columns): 
  foreach ($columns as $column_number => $item): 
    $grid_item[] = $item;
?>
    <div class="col-lg-<?php print $grid_col[$nb_row]['lg'][$index % count($grid_col[$nb_row]['lg'])]; ?> col-md-<?php print $grid_col[$nb_row]['md'][$index % count($grid_col[$nb_row]['md'])]; ?> col-sm-<?php print $grid_col[$nb_row]['sm'][$index % count($grid_col[$nb_row]['sm'])]; ?> col-xs-<?php print $grid_col[$nb_row]['xs'][$index % count($grid_col[$nb_row]['xs'])]; ?>">
      <?php print ec_resp_icon_type_classes($item); ?>
    </div>

    <?php if ((($index+1) % count($grid_col[$nb_row]['lg'])) == 0 || !isset($item[$index+1])): ?>
    <div class="clearfix visible-lg"></div>
    <?php endif; ?>

    <?php if ((($index+1) % count($grid_col[$nb_row]['md'])) == 0 || !isset($item[$index+1])): ?>
    <div class="clearfix visible-md"></div>
    <?php endif; ?>

    <?php if ((($index+1) % count($grid_col[$nb_row]['sm'])) == 0 || !isset($item[$index+1])): ?>
    <div class="clearfix visible-sm"></div>
    <?php endif; ?>

    <?php if ((($index+1) % count($grid_col[$nb_row]['xs'])) == 0 || !isset($item[$index+1])): ?>
    <div class="clearfix visible-xs"></div>
    <?php endif; ?>

    <?php $index++; ?>
<?php
  endforeach; 
endforeach;
?>
  </div>
</div>