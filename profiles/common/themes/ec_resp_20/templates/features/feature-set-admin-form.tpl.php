<?php

/**
 * @file
 * theme implementation to display feature set.
 *
 * Available variables:
 * - $feature_set_category: list of features, grouped by category
 * - $feature_set_row: raw list of features, ungrouped
 * - $feature_set_input: rendered form input (submit and hidden fields) 
 */

?>

<div class="row">
  <div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">
    <ul class="list-group nav nav-tabs nav-stacked">
      <?php print $feature_set_output_left; ?>
    </ul>
  </div>

  <div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">
    <ul class="list-group nav nav-tabs nav-stacked">
      <?php print $feature_set_output_right; ?>
    </ul>
  </div>
</div>

<?php 
  print $feature_set_input;
?>
