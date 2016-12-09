<?php

/**
 * @file
 * Display Suite NE Bootstrap Three Columns Stacked.
 */

  // Add sidebar classes so that we can apply the correct width in css.
  // Second block is needed to activate display suite support on forms.
?>

<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes; ?>">
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  <div class="row">
    <<?php print $left_header_wrapper; ?> class="col-lg-9 <?php print $left_header_classes; ?>">
      <?php print $left_header; ?>
    </<?php print $left_header_wrapper; ?>>
    <<?php print $right_header_wrapper; ?> class="col-lg-3 <?php print $right_header_classes; ?>">
      <?php print $right_header; ?>
    </<?php print $right_header_wrapper; ?>>
  </div>
  <div class="row">
    <<?php print $top_wrapper; ?> class="col-lg-12 <?php print $top_classes; ?>">
      <?php print $top; ?>
    </<?php print $top_wrapper; ?>>

    <?php if (isset($left) && !empty($left)): ?>
      <<?php print $left_wrapper; ?> class="col-lg-3 <?php print $left_classes; ?>">
        <?php print $left; ?>
      </<?php print $left_wrapper; ?>>
    <?php endif; ?>

    <?php if (isset($left) && !empty($left)): ?>
      <<?php print $central_wrapper; ?> class="col-lg-9 <?php print $central_classes; ?>">
    <?php else: ?>
      <<?php print $central_wrapper; ?> class="col-lg-12 <?php print $central_classes; ?>">
    <?php endif; ?>
      <?php print $central; ?>
    </<?php print $central_wrapper; ?>>
  </div>
</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
