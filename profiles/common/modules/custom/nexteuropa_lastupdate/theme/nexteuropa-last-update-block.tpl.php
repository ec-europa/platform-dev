<?php

/**
 * @file
 * Default implementation of the last update block.
 *
 * Available variables:
 * - $label: the language list.
 * - $date: optional language icon.
 * - $close_button: optional close button.
 *
 * @see template_preprocess()
 * @see template_preprocess_splash()
 * @see template_process()
 */
?>

<div class="last-update">
  <?php print $label; ?> : <?php print $date; ?>
</nav>
