<?php
// $Id: page.tpl.php,v 1.9 2010/11/07 21:48:56 dries Exp $

/**
 * @file
 * ec_default's theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template normally located in the
 * modules/system folder.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/ec_default.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['featured']: Items for the featured region.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['triptych_first']: Items for the first triptych.
 * - $page['triptych_middle']: Items for the middle triptych.
 * - $page['triptych_last']: Items for the last triptych.
 * - $page['footer_firstcolumn']: Items for the first footer column.
 * - $page['footer_secondcolumn']: Items for the second footer column.
 * - $page['footer_thirdcolumn']: Items for the third footer column.
 * - $page['footer_fourthcolumn']: Items for the fourth footer column.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see ec_default_process_page()
 */
?>

<?php
$no_left = FALSE;
if (arg(0) == 'admin' ||
    arg(2) == 'edit') {
  $no_left = TRUE;
}
?>

<a id="top-page" name="top-page"></a>

<!--<ul class="nav nav-pills">
        <li class="active"><a href="#">Home</a></li>
        <li><a href="#">Profile</a></li>
        <li class="dropdown">
          <a href="#" data-toggle="dropdown" class="dropdown-toggle">Dropdown <b class="caret"></b></a>
          <ul class="dropdown-menu">
            <li><a href="#">Action</a></li>
            <li><a href="#">Another action</a></li>
            <li><a href="#">Something else here</a></li>
            <li class="divider"></li>
            <li><a href="#">Separated link</a></li>
          </ul>
        </li>
      </ul>-->
      
<div class="layout layout-noright<?php if ($no_left) print ' layout-noleft'; ?>" id="layout">
  
  <div id="header">
    <a href="<?php print $front_page; ?>">

      <img alt="European Commission logo" id="banner-flag" src="http://ec.europa.eu/wel/template-2012/images/logo/logo_en.gif">
      
      <p id="banner-title-text"><?php print $site_name; ?></p>
      <span class="title-en" id="banner-image-title"></span>
      
      <p class="off-screen">Accessibility tools</p>
      <ul class="reset-list" id="accessibility-menu">
        <li><a accesskey="1" href="#content"><?php print t('Go to content'); ?></a></li>
      </ul>

      <p class="off-screen">Service tools</p>
      <ul class="reset-list" id="services">
        <li><a class="first" href="http://ec.europa.eu/atoz_en.htm"><?php print t('A-Z Index'); ?></a></li>
        <li><a href="http://ec.europa.eu/sitemap/index_en.htm"><?php print t('Sitemap'); ?></a></li>
        <li><a href="http://ec.europa.eu/abouteuropa/index_en.htm"><?php print t('About this site'); ?></a></li>
        <li><a href="http://ec.europa.eu/abouteuropa/faq/index_en.htm"><?php print t('FAQ'); ?></a></li>
        <li><a href="http://ec.europa.eu/geninfo/whatsnew_en.htm"><?php print t("What's New"); ?></a></li>
        <li><a accesskey="2" href="http://ec.europa.eu/geninfo/legal_notices_en.htm"><?php print t('Legal notice'); ?></a></li>
        <li><a accesskey="3" href="http://ec.europa.eu/contact/index_en.htm"><?php print t('Contact'); ?></a></li>
        <li><a accesskey="4" href="http://ec.europa.eu/geninfo/query/search_en.html"><?php print t('Search'); ?></a></li>
      </ul>
    </a>
    
    <!-- language selector -->
    <?php print render($page['highlighted']); ?>    
  </div><!-- /#header -->

  <div id="path">
    <p class="off-screen">Navigation path</p>
    <ul class="reset-list">
      <li class="first"><a href="http://ec.europa.eu/index_en.htm"><?php print t('European Commission'); ?></a></li>
      <li><?php print $site_name; ?></li>
    </ul>
  </div><!-- /#path -->
  
  <div class="layout-body">
    <div class="layout-wrapper">
      <div class="layout-wrapper-reset">

      <?php if ($messages): ?>
        <div id="messages">
          <?php print $messages; ?>
        </div><!-- /#messages -->
      <?php endif; ?>

        <div class="layout-left">
        <ul class="nav nav-list">
      <?php if ($page['sidebar_first']): ?>
        <?php print render($page['sidebar_first']); ?>
      <?php endif; ?>
        </ul>
        </div><!-- /.layout-left -->	

        <div class="layout-content">
          <div class="layout-content-reset"><a id="content" name="content"></a>
          
            <?php if ($main_menu): ?>
              <div id="main-menu" class="navigation">
                <?php print theme('links__system_main_menu', array(
                  'links' => $main_menu,
                  'attributes' => array(
                    'id' => 'main-menu-links',
                    'class' => array('clearfix', 'nav', 'nav-pills'),
                  ),
                  'heading' => array(
                    'text' => t('Main menu'),
                    'level' => 'h2',
                    'class' => array('element-invisible'),
                  ),
                )); ?>
              </div><!-- /#main-menu -->
            <?php endif; ?>    

            <?php if ($secondary_menu): ?>
              <div id="secondary-menu" class="navigation">
                <?php print theme('links__system_secondary_menu', array(
                  'links' => $secondary_menu,
                  'attributes' => array(
                    'id' => 'secondary-menu-links',
                    'class' => array('links', 'inline', 'clearfix'),
                  ),
                  'heading' => array(
                    'text' => t('Secondary menu'),
                    'level' => 'h2',
                    'class' => array('element-invisible'),
                  ),
                )); ?>
              </div><!-- /#secondary-menu -->
            <?php endif; ?>             
            
            <p class="off-screen">Additional tools</p>
            <ul class="reset-list" id="additional-tools">
              <li class="print"> <a class="link-components" href="javascript:tools.printPage();" title="Print version"><img alt="Print version" src="http://ec.europa.eu/wel/template-2012/images/print.gif"><span class="s">&nbsp;</span></a> </li>
              <li class="font-decrease"> <a class="link-components" href="javascript:tools.decreaseFontSize();" title="Decrease text"><img alt="Decrease text" src="http://ec.europa.eu/wel/template-2012/images/font-decrease.gif"><span class="s">&nbsp;</span></a> </li>
              <li class="font-increase"> <a class="link-components" href="javascript:tools.increaseFontSize();" title="Increase text"><img alt="Increase text" src="http://ec.europa.eu/wel/template-2012/images/font-increase.gif"><span class="s">&nbsp;</span></a> </li>
            </ul>

            <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
            <a id="main-content"></a>
            <?php print render($title_prefix); ?>
            <?php if ($title): ?>
              <h1 class="title" id="page-title">
                <?php print $title; ?>
              </h1>
            <?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php if ($tabs): ?>
                <?php print render($tabs); ?>
            <?php endif; ?>
            <?php print render($page['help']); ?>
            <?php if ($action_links): ?>
              <ul class="action-links">
                <?php print render($action_links); ?>
              </ul>
            <?php endif; ?>
            <?php print render($page['content']); ?>
            <?php print $feed_icons; ?>

          </div><!-- /.layout-content-reset -->
        </div><!-- /.layout-content -->
      </div><!-- /.layout-wrapper-reset -->
    </div><!-- /.layout-wrapper -->

    <div class="layout-right">
      <p>Right navigation</p>
    </div><!-- /.layout-right -->
  </div><!-- /.layout-body -->
  
  <div class="layout-footer"> Last update: DD/MM/YYYY | <a href="#top-page">Top</a>
  </div><!-- /.layout-footer -->
</div><!-- /#layout -->




