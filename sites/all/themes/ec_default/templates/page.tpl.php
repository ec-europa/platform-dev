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
 * - $page['header']: Items for the header region (right side of banner)
 * - $page['highlighted']: Items for the highlighted content region (language switcher)
 * - $page['featured']: Items for the featured region (main menu, global information)
 * - $page['help']: Dynamic help text, mostly for admin pages (between page title and content)
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the sidebar first region (left sidebar)
 * - $page['sidebar_second']: Items for the sidebar second region (right sidebar)
 * - $page['footer']: Items for the footer region.
 * - $page['tools']: Items for the tools region (top right of page)
 * - $page['tools_bottom']: Items for the bottom tools region (bottom right of page)
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see ec_default_process_page()
 */
?>

<?php
global $base_url;

?>

<div class="layout <?php if (isset($variables['no_right']) && $variables['no_right']) print ' layout-noright'; ?><?php if (isset($variables['no_left']) && $variables['no_left']) print ' layout-noleft'; ?>" id="layout">

  <a id="top-page"></a>
  <div id="header">
<?php
  switch ($variables['template']) {
    case 'ec':
?>
    <img alt="European Commission logo" id="banner-flag" src="<?php print $base_url . '/' . path_to_theme(); ?>/wel/template-2012/images/logo/logo_en.gif" />

    <p id="banner-title-text"><?php print $site_name; ?></p>
    <span class="title-en" id="banner-image-title"></span>

    <span id="banner-image-right">
  <?php if ($page['header']): ?><?php print render($page['header']); ?><?php endif; ?>
    </span>

  <?php
    break;

    case 'europa':
  ?>
    <a class="banner-flag" href="http://europa.eu/index_en.htm" title="European Union homepage">
      <img id="banner-flag" src="<?php print $base_url . '/' . path_to_theme(); ?>/wel/template-2011/images/europa-flag.gif" alt="European Union homepage. EU flag" width="67" height="60" border="0">
    </a>

    <p class="banner-title">
      <img src="<?php print $base_url . '/' . path_to_theme(); ?>/wel/template-2011/images/title/title_en.gif" alt="Title of the site" width="450" height="46">
    </p>

    <div class="banner-right">
  <?php if ($page['header']): ?><?php print render($page['header']); ?><?php endif; ?>
    </div>

  <?php
    break;

    default:
    break;
  }
  ?>

    <!--<div id="main_title">Service mutlisite</div>
    <div id="sub_title">Playground environment</div>-->

    <p class="off-screen">Accessibility tools</p>
    <ul class="reset-list" id="accessibility-menu">
      <li><a accesskey="1" href="#content"><?php print t('Go to content'); ?></a></li>
    </ul>

    <p class="off-screen">Service tools</p>
    <ul class="reset-list" id="services">
      <li><a class="first" accesskey="3" href="<?php print $base_url . '/contact'; ?>"><?php print t('Contact'); ?></a></li>
      <li><a accesskey="2" href="http://ec.europa.eu/geninfo/legal_notices_en.htm"><?php print t('Legal notice'); ?></a></li>
      <li><a accesskey="4" href="http://ec.europa.eu/geninfo/query/search_en.html"><?php print t('Search'); ?></a></li>
    </ul>

    <!-- language selector -->
    <?php print render($page['highlighted']); ?>

  </div><!-- /#header -->

  <div id="path">
    <p class="off-screen">Navigation path</p>
    <ul class="reset-list">
      <li class="first"><a href="http://ec.europa.eu/index_en.htm"><?php print t('European Commission'); ?></a></li>
      <li>
        <?php global $language; ?>
        <?php if (isset ($front_page)): ?>
          <?php print "<a href='$front_page'>$site_name</a>"; ?></li>
        <?php endif; ?>
        <?php print $breadcrumb; ?>
    </ul>
  </div><!-- /#path -->

  <div class="layout-body">
  <?php if ($page['featured']): ?>
    <?php print render($page['featured']); ?>
  <?php endif; ?>

    <div class="layout-wrapper">
      <div class="layout-wrapper-reset">

      <?php if ($messages): ?>
        <div id="messages">
          <?php print $messages; ?>
        </div><!-- /#messages -->
      <?php endif; ?>

        <div class="layout-left region region-sidebar-first">
        <?php if ($page['sidebar_first']): ?>
          <ul class="nav nav-list">
            <?php print render($page['sidebar_first']); ?>
          </ul>
        <?php endif; ?>
        </div><!-- /.layout-left -->

        <div class="layout-content">
          <div class="layout-content-reset"><a id="content"></a>

            <div class="region region-tools">
            <?php if ($page['tools']): ?>
              <ul class="links">
                <?php print render($page['tools']); ?>
              </ul>
            <?php endif; ?>
            </div>

            <?php if ($page['content_top']): ?>
              <?php print render($page['content_top']); ?>
            <?php endif; ?>

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

            <div class="region region-tools-bottom">
            <?php if ($page['tools_bottom']): ?>
              <ul class="links">
                <?php print render($page['tools_bottom']); ?>
              </ul>
            <?php endif; ?>
            </div>

          </div><!-- /.layout-content-reset -->
        </div><!-- /.layout-content -->
      </div><!-- /.layout-wrapper-reset -->
    </div><!-- /.layout-wrapper -->

    <div class="layout-right region region-sidebar-second">
    <?php if ($page['sidebar_second']): ?>
      <ul class="nav nav-list">
        <?php print render($page['sidebar_second']); ?>
      </ul>
    <?php endif; ?>
    </div><!-- /.layout-right -->

  </div><!-- /.layout-body -->

  <div class="layout-footer">
    <div class="layout-footer-wrapper navbar-inner">
      <?php if ($page['footer']): ?>
        <?php print render($page['footer']); ?>
      <?php endif; ?>
      <?php print t('Last update:') . ' ' . date('d/m/Y'); ?> | <a href="#top-page">Top</a>
    </div>
  </div><!-- /.layout-footer -->
</div><!-- /#layout -->

<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . path_to_theme(); ?>";
</script>