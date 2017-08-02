<?php

/**
 * @file
 * Default implementation of the last update block.
 *
 * Available variables:
 * - $label: the language label.
 * - $date: the date.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 */
?>
<?php if (!empty($label) && !empty($date)) : ?>
  <div class="last-update">
    <?php print $label; ?> : <?php print $date; ?>
  </div>
<?php endif; ?>
