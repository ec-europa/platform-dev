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
$span = array();

//set length of each column, depending of number of element on one line
$span[1]  = array(12);
$span[2]  = array(6,6);
$span[3]  = array(4,4,4);
$span[4]  = array(3,3,3,3);
$span[5]  = array(3,2,2,2,3);
$span[6]  = array(2,2,2,2,2,2);
$span[7]  = array(3,1,1,1,1,1,4);
$span[8]  = array(3,1,1,1,1,1,1,3);
$span[9]  = array(2,1,1,1,1,1,1,1,3);
$span[10] = array(2,1,1,1,1,1,1,1,1,2);
$span[11] = array(1,1,1,1,1,1,1,1,1,1,2);
$span[12] = array(1,1,1,1,1,1,1,1,1,1,1,1);
?>

<div class="<?php print $class; ?>">
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php foreach ($rows as $row_number => $columns): ?>
  <div class="<?php print $row_classes[$row_number]; ?> row-fluid"> 
    <?php foreach ($columns as $column_number => $item): ?>
      <div class="span<?php print $span[$nb_row][$column_number]; ?>">
        <?php print icon_type_classes($item); ?>
      </div>
    <?php endforeach; ?>
  </div>
<?php endforeach; ?>
</div>