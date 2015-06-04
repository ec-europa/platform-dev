<?php
/**
 * @file
 * Theme implementation to display feature set.
 *
 * Available variables:
 * - $feature_set_category: list of features, grouped by category
 * - $feature_set_row: raw list of features, ungrouped
 * - $feature_set_input: rendered form input (submit and hidden fields)
 */
?>

<div class="row">
  <div class="col-lg-3 col-sm-4 col-xs-12">
    <ul class="nav nav-pills nav-stacked feature-set__categories">
      <?php print $feature_set_categories_list; ?>
    </ul>
  </div>

  <div class="col-lg-9 col-sm-8 col-xs-12">
    <div class="tab-content feature-set__features">
      <?php print $feature_set_features_list; ?>
    </div>
  </div>
</div>

<div class="feature-set__input">
  <?php 
    print $feature_set_input;
  ?>
</div>
