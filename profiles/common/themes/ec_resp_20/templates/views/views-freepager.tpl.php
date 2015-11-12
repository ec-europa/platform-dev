<?php

/**
 * @file
 * Default view template to display Free Pager.
 *
 * Available variables:
 *
 * $previous
 *   The rendered field used for the row before the viewed one. May be empty.
 * $previous_linked
 *   The 'previous' field, linking to the previous page.
 * $current
 *   The rendered field used for the currently viewed row.
 * $current_linked
 *   The 'current' field, linking to the current page. Not highly useful.
 * $next
 *   The rendered field used for the row after the viewed one. May be empty.
 * $next_linked
 *   The 'next' field, linking to the next page.
 * $row_number
 *   The number of the viewed row.
 * $total_rows
 *   The total number of rows in the list from Views.
 *
 * @ingroup views_templates
 */
?>

<?php if (!empty($previous)): ?>
  <span class="freepager-previous">
    <?php print $previous_linked; ?>
  </span>
<?php endif; ?>
<?php if (!empty($next)): ?>
  <span class="freepager-next">
    <?php print $next_linked; ?>
  </span>
<?php endif; ?>
<?php if (!empty($current)): ?>
  <div class="freepager-current">
    <?php print $current; ?>
  </div>
<?php endif; ?>
