<?php

/**
 * @file
 * Default implementation of the splash page content.
 *
 * Available variables:
 * - $site_name: the site name.
 * - $languages_list: the language list.
 * - $languages_list_array: unformated array of languages. 
 * - $languages_blacklist: unformated array of blacklisted language codes.
 * - $base_url: the base_url of the site instance.
 *
 * @see template_preprocess()
 * @see template_preprocess_splash()
 * @see template_process()
 */
?>

<nav class="site-level-language-selector">
  <h1 class="icon-language"><?php print t('Select language'); ?>:</h1>
  <?php print $languages_list; ?>
</nav>
