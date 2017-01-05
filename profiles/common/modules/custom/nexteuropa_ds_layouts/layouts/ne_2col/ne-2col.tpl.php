<?php

/**
 * @file
 * Display Suite NE Bootstrap Two Columns Stacked.
 */

  // Add sidebar classes so that we can apply the correct width in css.
  // Second block is needed to activate display suite support on forms.
?>

<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes; ?>">
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  <a href="<?php print $node_url; ?>">
    <?php if (!empty($second)): ?>
      <<?php print $second_wrapper; ?> class="column-second <?php print $second_classes; ?>">
        <?php print $second; ?>
      </<?php print $second_wrapper; ?>>
    <?php endif; ?>
    <<?php print $main_wrapper; ?> class="column-main <?php print $main_classes; ?>">
      <?php print $main; ?>
    </<?php print $main_wrapper; ?>>
  </a>
</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
