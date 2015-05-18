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

//set length of each column, depending of number of element on one line
$col = array();

$col[1]['lg'] = array(12); $col[1]['md'] = array(12); $col[1]['sm'] = array(12); $col[1]['xs'] = array(12);
$col[2]['lg'] = array(6,6); $col[2]['md'] = array(6,6); $col[2]['sm'] = array(12); $col[2]['xs'] = array(12);
$col[3]['lg'] = array(4,4,4); $col[3]['md'] = array(6,6); $col[3]['sm'] = array(6,6); $col[3]['xs'] = array(12);
$col[4]['lg'] = array(3,3,3,3); $col[4]['md'] = array(4,4,4); $col[4]['sm'] = array(4,4,4); $col[4]['xs'] = array(6,6);
$col[5]['lg'] = array(3,2,2,2,3); $col[5]['md'] = array(3,3,3,3); $col[5]['sm'] = array(4,4,4); $col[5]['xs'] = array(6,6);
$col[6]['lg'] = array(2,2,2,2,2,2); $col[6]['md'] = array(3,3,3,3); $col[6]['sm'] = array(4,4,4); $col[6]['xs'] = array(6,6);
$col[7]['lg'] = array(3,1,1,1,1,1,4); $col[7]['md'] = array(3,2,2,2,3); $col[7]['sm'] = array(3,3,3,3); $col[7]['xs'] = array(4,4,4);
$col[8]['lg'] = array(3,1,1,1,1,1,1,3); $col[8]['md'] = array(2,2,2,2,2,2); $col[8]['sm'] = array(3,3,3,3); $col[8]['xs'] = array(4,4,4);
$col[9]['lg'] = array(2,1,1,1,1,1,1,1,3); $col[9]['md'] = array(3,1,1,1,1,1,4); $col[9]['sm'] = array(3,2,2,2,3); $col[9]['xs'] = array(3,3,3,3);
$col[10]['lg'] = array(2,1,1,1,1,1,1,1,1,2); $col[10]['md'] = array(3,1,1,1,1,1,1,3); $col[10]['sm'] = array(2,2,2,2,2,2); $col[10]['xs'] = array(3,3,3,3);
$col[11]['lg'] = array(1,1,1,1,1,1,1,1,1,1,2); $col[11]['md'] = array(2,1,1,1,1,1,1,1,1,2); $col[11]['sm'] = array(3,1,1,1,1,1,1,3); $col[11]['xs'] = array(2,2,2,2,2,2);
$col[12]['lg'] = array(1,1,1,1,1,1,1,1,1,1,1,1); $col[12]['md'] = array(2,1,1,1,1,1,1,1,1,2); $col[12]['sm'] = array(3,1,1,1,1,1,1,3); $col[12]['xs'] = array(2,2,2,2,2,2);

$grid_item = array();
?>

<div class="<?php print $class; ?>">
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php 
//get all views elements
foreach ($rows as $row_number => $columns): 
  foreach ($columns as $column_number => $item): 
    $grid_item[] = $item;
  endforeach; 
endforeach; 

$index = 0;
?>

  <div class="row">
  <?php foreach ($grid_item as $item): ?>
    <div class="col-lg-<?php print $col[$nb_row]['lg'][$index % count($col[$nb_row]['lg'])]; ?> col-md-<?php print $col[$nb_row]['md'][$index % count($col[$nb_row]['md'])]; ?> col-sm-<?php print $col[$nb_row]['sm'][$index % count($col[$nb_row]['sm'])]; ?> col-xs-<?php print $col[$nb_row]['xs'][$index % count($col[$nb_row]['xs'])]; ?>">
      <?php print ec_resp_151_icon_type_classes($item); ?>
    </div>

    <?php if ((($index+1) % count($col[$nb_row]['lg'])) == 0 || !isset($grid_item[$index+1])): ?>
    <div class="clearfix visible-lg"></div>
    <?php endif; ?>

    <?php if ((($index+1) % count($col[$nb_row]['md'])) == 0 || !isset($grid_item[$index+1])): ?>
    <div class="clearfix visible-md"></div>
    <?php endif; ?>

    <?php if ((($index+1) % count($col[$nb_row]['sm'])) == 0 || !isset($grid_item[$index+1])): ?>
    <div class="clearfix visible-sm"></div>
    <?php endif; ?>

    <?php if ((($index+1) % count($col[$nb_row]['xs'])) == 0 || !isset($grid_item[$index+1])): ?>
    <div class="clearfix visible-xs"></div>
    <?php endif; ?>

    <?php $index++; ?>

  <?php endforeach; ?>
  </div>

</div>