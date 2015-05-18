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

<nav class="site-level-language-selector">
  <img src="<?php print drupal_get_path('module', 'splash_screen'); ?>/theme/icon_language.png" width="64" height="64" alt="Select language" title="Select language" />
  <?php print $languages_list; ?>
  <?php print $close_button; ?>
</nav>
