<?php
/**
 * @file splash.tpl.php
 *
 * Default implementation of the splash page content.
 *
 * Available variables:
 *
 * - $site_name: the site name.
 * - $languages_list: the language list.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see ec_default_process_page()
 */
?>

<a id="top-page" name="top-page"></a>

<div class="splash container-fluid">
  <div class="row-fluid">
    <div class="span2">&nbsp;</div>
    <div class="span10">
      <div class="row-fluid">

        <!-- picture and title -->
        <div class="span4 center">
          <div id="logo"></div>
          <h1><?php print $site_name; ?></h1>
        </div>

        <!-- language list -->
        <div class="span4">
          <ul class="well languages nav nav-list">
            <li><h2 id="label_language"><?php print t('Please choose a language'); ?></h2></li>
            <?php print $languages_list; ?>
          </ul>
        </div>
      </div>
    </div>
  </div>
</div>
