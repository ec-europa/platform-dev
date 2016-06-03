<?php

/**
 * @file
 * Default implementation of the splash page content.
 *
 * Available variables:
 * - $close_button: unformatted close button.
 * - $languages_list: the language list.
 * - $languages_list_array: unformated array of languages.
 * - $languages_blacklist: unformated array of blacklisted language codes.
 *
 * @see template_preprocess()
 * @see template_preprocess_splash()
 * @see template_process()
 */
?>

<div class="row">
  <div class="col-md-8 col-md-offset-2">
    <nav class="site-level-language-selector">
      <?php print $icon; ?>
      <?php print $languages_list; ?>
      <?php if (isset($close_button)): ?>
        <?php print $close_button; ?>
      <?php endif; ?>
    </nav>
  </div>
</div>
