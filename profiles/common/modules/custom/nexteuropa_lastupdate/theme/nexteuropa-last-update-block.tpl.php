<?php

/**
 * @file
 * Default implementation of the last update block.
 *
 * Available variables:
 * - $label: the language list.
 * - $date: optional language icon.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 */
?>

<div class="last-update">
  <?php print $label; ?> : <?php print $date; ?>
</div>
