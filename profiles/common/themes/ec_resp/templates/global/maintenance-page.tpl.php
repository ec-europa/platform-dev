<?php

/**
 * @file
 * Implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in page.tpl.php.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 * @see ec_resp_process_maintenance_page()
 */
?><!DOCTYPE html>
<html lang="<?php print (isset($language) ? $language->language : "") ?>">
<head>
  <meta http-equiv="X-UA-Compatible" content="IE=edge" />
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $classes; ?>" <?php print $attributes;?>>

  <div id="layout-header">
    <div class="container">
      <img alt="European Commission logo" id="banner-flag" src="<?php print $logo; ?>" />

      <div id="main-title"><?php print (isset($site_name) ? $site_name : '') ?></div>
      <div id="sub-title"><?php print (isset($site_slogan) ? $site_slogan : '') ?></div>
    </div>
  </div><!-- /#layout-header -->

  <div class="panel panel-default">
    <div class="container">
      <div class="page-header">
        <?php if ($title): ?>
        <h1><?php print filter_xss($title); ?></h1>
        <?php endif; ?>
      </div>

      <div class="jumbotron">
        <p><?php print $content; ?></p>
      </div>

      <p class="text-right">
        <?php print t('Allowed users (ie: Administrators) can !login', array('!login' => l(t('log in here'), 'user/login'))); ?>
      </p>

      <?php if ($messages): ?>
        <div id="messages">
          <div class="section">
            <?php print filter_xss_admin($messages); ?>
          </div>
        </div>
      <?php endif; ?>
    </div>
  </div>

</body>
</html>
