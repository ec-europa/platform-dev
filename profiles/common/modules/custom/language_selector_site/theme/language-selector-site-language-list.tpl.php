<?php

/**
 * @file
 * Default implementation of the language selector.
 *
 * Available variables:
 * - $languages_list: the language list.
 * - $icon: optional language icon.
 * - $close_button: optional close button.
 *
 * @see template_preprocess()
 * @see template_preprocess_splash()
 * @see template_process()
 */
?>
<nav class="site-level-language-selector">
  <?php if ($icon): ?>
    <?php print $icon; ?>
  <?php endif; ?>

  <?php print $languages_list; ?>

  <?php if ($close_button): ?>
    <?php print $close_button; ?>
  <?php endif; ?>
</nav>
