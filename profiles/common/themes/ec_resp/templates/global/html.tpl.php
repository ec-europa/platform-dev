<?php
/**
 * @file
 * Default theme implementation of main page.
 */
?>
<!DOCTYPE html>
<html lang="<?php print (isset($language) ? $language->language : '') ?>">
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <!-- HTML5 element support for IE6-8 -->
  <!--[if lt IE 9]>
    <script src="<?php print url(drupal_get_path('theme', 'ec_resp') . '/scripts/html5shiv.min.js', array('language' => (object) array('language' => FALSE))); ?>"></script>
    <script src="<?php print url(drupal_get_path('theme', 'ec_resp') . '/scripts/respond.min.js', array('language' => (object) array('language' => FALSE))); ?>"></script>
  <![endif]--> 
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
