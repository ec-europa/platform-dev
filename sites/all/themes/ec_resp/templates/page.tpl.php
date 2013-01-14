<?php
// $Id: page.tpl.php,v 1.9 2010/11/07 21:48:56 dries Exp $

/**
 * @file
 * ec_resp's theme implementation to display a single Drupal page.
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
 *   or themes/ec_resp.
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
 * - $page['header_top']: Displayed at the top line of the header -> language switcher, links, ...
 * - $page['header_right']: Displayed in the right part of the header -> logo, search box, ...
 *
 * - $page['featured']: Displayed below the header, take full width of screen -> main menu, global information, ...
 * - $page['tools']: Displayed on top right of content area, before the page title -> login/logout buttons, author information, ...
 *
 * - $page['sidebar_left']: Displayed on left of the content, if not empty -> navigation, pictures, ... 
 * - $page['sidebar_right']: Displayed on right of the content, if not empty -> latest content, calendar, ... 
 *
 * - $page['content_top']: Displayed in middle column, right before the page title -> carousel, important news, ...  
 * - $page['help']: Displayed between page title and content -> information about the page, contextual help, ... 
 * - $page['content']: The main content of the current page.
 * - $page['content_bottom']: Displayed below the content, in middle column -> print button, share tools, ...
 *
 * - $page['footer']: Displayed at bottom of the page, on full width -> latest update, copyright, ...
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see ec_resp_process_page()
 */
?>

<?php
global $base_url;

//calculate size of regions
$nb_column            = 1;
if ($page['sidebar_left']) $nb_column++;
if ($page['sidebar_right']) $nb_column++;

$span_sidebar_left    = ($page['sidebar_left'] ? 5 - $nb_column : 0);
$span_sidebar_right   = ($page['sidebar_right'] ? 5 - $nb_column : 0);
$span_content         = 12 - $span_sidebar_left - $span_sidebar_right;
$span_tools           = 4;
$span_messages        = 12 - $span_tools;
?>

  <a id="top-page"></a>

  <div id="layout-header" class="visible-desktop">
    <div class="container">
  <?php
    switch ($variables['template']) {
      case 'ec':
  ?>
      <img alt="European Commission logo" id="banner-flag" src="<?php print $base_url . '/' . path_to_theme(); ?>/images/logo/logo_en.gif" />

      <span id="banner-image-right">
        <?php if ($page['header_right']): ?>
        <div class="region region-header_right">
          <?php print render($page['header_right']); ?>
        </div><!-- /.region-header_right -->
        <?php endif; ?>
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
        <?php if ($page['header_right']): ?>
        <div class="region region-header_right">
          <ul class="links unstyled">
            <?php print render($page['header_right']); ?>
          </ul>
        </div><!-- /.region-header_right -->
        <?php endif; ?>
      </div>
      
    <?php
      break;

      default:
      break;
    }
    ?>

      <div id="main-title"><?php print $site_name; ?></div>
      <div id="sub-title"><?php print $site_slogan; ?></div>

      <div class="region region-header_top">
        <p class="off-screen">Service tools</p>
        <ul class="reset-list" id="services">
          <li><a class="first" accesskey="3" href="<?php print $base_url . '/contact'; ?>"><?php print t('Contact'); ?></a></li>
          <li><a accesskey="2" href="http://ec.europa.eu/geninfo/legal_notices_en.htm"><?php print t('Legal notice'); ?></a></li>
          <li><a accesskey="4" href="http://ec.europa.eu/geninfo/query/search_en.html"><?php print t('Search'); ?></a></li>
        </ul>
        <?php if ($page['header_top']): ?>
          <?php print render($page['header_top']); ?>
        <?php endif; ?>
      </div><!-- /.region-header_top -->

    </div>
  </div><!-- /#layout-header -->  

  <div id="path" class="visible-desktop">
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

  <?php if ($page['featured']): ?>
  <div class="region region-featured">
    <?php print render($page['featured']); ?>  
  </div><!-- /.region-featured -->
  <?php endif; ?> 

  <?php if ($page['sidebar_left']): ?>
    <div id="responsive-sidebar" class="region region-sidebar_left visible-phone">
      <ul class="nav nav-list">
        <?php print render($page['sidebar_left']); ?>
      </ul>
    </div><!-- /#responsive-sidebar-->   
  <?php endif; ?>

  <div id="layout-body" class="container">
    <div class="row-fluid">
      <div id="messages" class="span<?php print $span_messages; ?>">
        <?php if ($messages): ?>
          <?php print $messages; ?>
        <?php endif; ?>
      </div><!-- /#messages -->

      <?php if ($page['tools']): ?>
      <div class="region region-tools span<?php print $span_tools; ?>">
        <ul class="links unstyled">
          <?php print render($page['tools']); ?>
        </ul>
      </div><!-- /.region-tools -->
      <?php endif; ?>
    </div>

    <div class="row-fluid">
      <?php if ($page['sidebar_left']): ?>
      <div class="region region-sidebar_left span<?php print ($span_sidebar_left); ?> hidden-phone">
        <ul class="nav nav-list">
          <?php print render($page['sidebar_left']); ?>
        </ul>
      </div><!-- /.region-sidebar_left -->     
      <?php endif; ?>     

      <div class="span<?php print $span_content; ?>">
        
        <a id="content"></a>

        <div class="region region-content_top">
        <?php if ($page['content_top']): ?>
          <?php print render($page['content_top']); ?>
        <?php endif; ?>
        </div><!-- /.region-content_top -->

        <a id="main-content"></a>

        <?php print render($title_prefix); ?>
        <?php if ($title): ?>
          <h1 class="title" id="page-title">
            <?php print $title; ?>
          </h1>
        <?php endif; ?>
        <?php print render($title_suffix); ?>

        <?php if ($tabs): ?>
          <div class="tabs">
            <?php print render($tabs); ?>
          </div>
        <?php endif; ?>

        <?php print render($page['help']); ?>
        
        <?php if ($action_links): ?>
          <ul class="action-links">
            <?php print render($action_links); ?>
          </ul>
        <?php endif; ?>

        <?php print render($page['content']); ?>
        
        <?php print $feed_icons; ?>

        <div class="region region-content_bottom">
        <?php if ($page['content_bottom']): ?>
          <ul class="links">
            <?php print render($page['content_bottom']); ?>
          </ul>
        <?php endif; ?>
        </div><!-- /.region-content_bottom -->
      </div>

      <?php if ($page['sidebar_right']): ?>
      <div class="region region-sidebar_right span<?php print ($span_sidebar_right); ?> hidden-phone">
        <ul class="nav nav-list">
          <?php print render($page['sidebar_right']); ?>
        </ul>
      </div><!-- /.region-sidebar_right -->  
      <?php endif; ?> 
    </div>
  </div><!-- /#layout-body -->    

  <div id="layout-footer" class="navbar navbar-static-top">
    <div class="navbar-inner">
      <div class="container">
        <?php if ($page['footer']): ?>
          <?php print render($page['footer']); ?>
        <?php endif; ?>
        <?php print t('Last update:') . ' ' . date('d/m/Y'); ?> | <a href="#top-page">Top</a>
      </div>
    </div>
  </div><!-- /#layout-footer -->      

<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . path_to_theme(); ?>";
</script>