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
 * - $base_url: the base_url of the site instance.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see ec_default_process_page()
 */
?>

<a id="top-page" name="top-page"></a>

<div class="splash container-fluid">
  <div class="row">
    <!-- picture and title -->
    <div class="col-lg-3 offset2 center">
      <div id="logo"></div>
      <h1><?php print $site_name; ?></h1>
    </div>

    <!-- language list -->
    <div class="col-lg-5">
      <ul class="well languages">
        <li><h2 id="label_language"><?php print t('Please choose a language'); ?></h2></li>
        <?php print $languages_list; ?>
      </ul>
    </div>
  </div>
</div>
<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . path_to_theme(); ?>";
</script>