<?php
// $Id: page.tpl.php,v 1.9 2010/11/07 21:48:56 dries Exp $

/**
 * @file
 * ec_resp_150's theme implementation to display a single Drupal page.
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
 *   or themes/ec_resp_150.
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
 * @see ec_resp_150_process_page()
 */
?>

<?php
global $base_url;

//calculate size of regions
$col_sidebar_left_lg    = ($page['sidebar_left'] ? 3 : 0);
$col_sidebar_left_md    = ($page['sidebar_left'] ? 4 : 0);
$col_sidebar_right_lg   = ($page['sidebar_right'] ? 3 : 0);
$col_sidebar_right_md   = ($page['sidebar_right'] ? ($page['sidebar_left'] ? 12 : 4) : 0);
$col_content_lg         = 12 - $col_sidebar_left_lg - $col_sidebar_right_lg;
$col_content_md         = ($page['sidebar_left'] ? 12 - $col_sidebar_left_md : ($page['sidebar_right'] ? 12 - $col_sidebar_right_md : 12));
$col_tools_lg           = ($title ? 4 : 12);
$col_tools_md           = ($title ? 4 : 12);
$col_title_lg           = 12 - $col_tools_lg;
$col_title_md           = 12 - $col_tools_md;

//format regions
$region_header_right = $page['header_right'] ? render($page['header_right']) : '';
$region_header_top = $page['header_top'] ? render($page['header_top']) : '';
$region_featured = $page['featured'] ? render($page['featured']) : '';
$region_sidebar_left = $page['sidebar_left'] ? render($page['sidebar_left']) : '';
$region_tools = $page['tools'] ? render($page['tools']) : '';
$region_content_top = $page['content_top'] ? render($page['content_top']) : '';
$region_help = $page['help'] ? render($page['help']) : '';
$region_content = $page['content'] ? render($page['content']) : '';
$region_content_bottom = $page['content_bottom'] ? render($page['content_bottom']) : '';
$region_sidebar_right = $page['sidebar_right'] ? render($page['sidebar_right']) : '';
$region_footer = $page['footer'] ? render($page['footer']) : '';
?>

  <a id="top-page"></a>

  <div class="container">
    <?php print $region_header_top; ?>
  </div>

  <div id="layout-header">
    <div class="container">
  <?php
    switch ($variables['template']) {
      case 'ec':
  ?>
      <img alt="European Commission logo" id="banner-flag" src="<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_150'); ?>/images/logo/logo_en.gif" />

      <span id="banner-image-right" class="hidden-sm hidden-xs">
        <?php print $region_header_right; ?>
      </span>
    
    <?php
      break;

      case 'europa':
    ?>
      <a class="banner-flag" href="http://europa.eu/index_en.htm" title="European Union homepage">
        <img id="banner-flag" src="<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_150'); ?>/wel/template-2011/images/europa-flag.gif" alt="European Union homepage. EU flag" width="67" height="60" border="0">
      </a>

      <p class="banner-title">
        <img src="<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_150'); ?>/wel/template-2011/images/title/title_en.gif" alt="Title of the site" width="450" height="46">
      </p>

      <div class="banner-right">
        <?php print $region_header_right; ?>
      </div>
      
    <?php
      break;

      default:
      break;
    }
    ?>

      <div id="main-title"><?php print $site_name; ?></div>
      <div id="sub-title"><?php print $site_slogan; ?></div>

      <p class="off-screen">Service tools</p>
      <ul class="reset-list hidden-sm hidden-xs" id="services">
        <li><?php print l(t('About this site'), 'http://ec.europa.eu/about_en.htm', array('attributes' => array('class' => array('first'), 'accesskey' => array('1')))); ?></li>
        <li><?php print l(t('Legal notice'), 'http://ec.europa.eu/geninfo/legal_notices_en.htm', array('attributes' => array('accesskey' => array('2')))); ?></li>
        <li><?php print l(t('Contact'), 'http://ec.europa.eu/contact/index_en.htm', array('attributes' => array('accesskey' => array('3')))); ?></li>
        <li><?php print l(t('Search'), 'http://ec.europa.eu/geninfo/query/search_en.html', array('attributes' => array('class' => array('last'), 'accesskey' => array('4')))); ?></li>
      </ul>
    </div>
  </div><!-- /#layout-header -->  

  <div id="path" class="hidden-xs">
    <div class="container">
      <p class="off-screen">Navigation path</p>
      <ul class="reset-list">
        <li class="first"><a href="http://ec.europa.eu/index_en.htm"><?php print t('European Commission'); ?></a></li>
          <?php global $language; ?>
          <?php if (isset ($front_page)): ?>
            <li class="home"><?php print "<a href='" . filter_xss($front_page) . "'>$site_name</a>"; ?></li>
          <?php endif; ?>
          <?php print $breadcrumb; ?>
      </ul>
    </div>
  </div><!-- /#path --> 

  <?php print $region_featured; ?>

  <?php
    switch ($variables['responsive_sidebar']) {
      case 'left':
  ?>
  <?php if ($page['sidebar_left']): ?>
    <div id="responsive-sidebar" class="visible-sm visible-xs">
      <div>
        <?php 
        $region_sidebar_left_responsive = str_replace('"share-tool"','"share-tool-responsive"',$region_sidebar_left);
        $region_sidebar_left_responsive = str_replace('"tb_browser_tree"','"tb_browser_tree-responsive"',$region_sidebar_left);

        print $region_sidebar_left_responsive; 
        ?>
      </div>
    </div><!-- /#responsive-sidebar-->   
  <?php endif; ?>
    <?php
      break;

      case 'right':
    ?>
  <?php if ($page['sidebar_right']): ?>
    <div id="responsive-sidebar" class="visible-sm visible-xs">
      <div>
        <?php 
        $region_sidebar_right_responsive = str_replace('"share-tool"','"share-tool-responsive"',$region_sidebar_right);
        $region_sidebar_left_responsive = str_replace('"tb_browser_tree"','"tb_browser_tree-responsive"',$region_sidebar_left);

        print $region_sidebar_right_responsive; 
        ?>
      </div>
    </div><!-- /#responsive-sidebar-->   
  <?php endif; ?>
    <?php
      break;

      case 'both':
    ?>
  <?php if ($page['sidebar_left'] || $page['sidebar_right']): ?>
    <div id="responsive-sidebar" class="visible-sm visible-xs">
      <div>
    <?php if ($page['sidebar_left']): ?>
      <?php 
      $region_sidebar_left_responsive = str_replace('"share-tool"','"share-tool-responsive"',$region_sidebar_left);
      $region_sidebar_left_responsive = str_replace('"tb_browser_tree"','"tb_browser_tree-responsive"',$region_sidebar_left);

      print $region_sidebar_left_responsive; 
      ?>
    <?php endif; ?>
    <?php if ($page['sidebar_right']): ?>
      <?php 
      $region_sidebar_right_responsive = str_replace('"share-tool"','"share-tool-responsive"',$region_sidebar_right);
      $region_sidebar_left_responsive = str_replace('"tb_browser_tree"','"tb_browser_tree-responsive"',$region_sidebar_left);

      print $region_sidebar_right_responsive; 
      ?>
    <?php endif; ?>
        </div>
      </div><!-- /#responsive-sidebar-->       
  <?php endif; ?>
    <?php
      break;      

      default:
      break;
    }
    ?>      


  <div id="layout-body" class="container">
    <div class="row">
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="col-lg-<?php print $col_title_lg; ?> col-md-<?php print $col_title_md; ?>" id="page-title">
          <?php print $title; ?>
        </h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($page['tools']): ?>
      <div class="col-lg-<?php print $col_tools_lg; ?> col-md-<?php print $col_tools_md; ?>">
        <?php print $region_tools; ?>
      </div>
      <?php endif; ?>
    </div>

    <?php if ($messages): ?>
    <div id="messages">
        <?php print $messages; ?>
    </div><!-- /#messages -->
    <?php endif; ?>
        
    <div class="row">
      <?php if ($page['sidebar_left']): ?>
      <div class="col-lg-<?php print ($col_sidebar_left_lg); ?> col-md-<?php print ($col_sidebar_left_md); ?> sidebar-left hidden-sm hidden-xs">
        <?php print $region_sidebar_left; ?>
      </div>
      <?php endif; ?>     

      <div class="col-lg-<?php print $col_content_lg; ?> col-md-<?php print $col_content_md; ?>">
        
        <a id="content"></a>

        <?php if ($title): ?>
          <h1 class="title" id="content-title">
            <?php print $title; ?>
          </h1>
        <?php endif; ?>

        <?php print $region_content_top; ?>

        <a id="main-content"></a>

        <?php if ($tabs): ?>
          <div class="tabs">
            <?php print render($tabs); ?>
          </div>
        <?php endif; ?>

        <?php print $region_help; ?>
        
        <?php if ($action_links): ?>
          <ul class="action-links">
            <?php print render($action_links); ?>
          </ul>
        <?php endif; ?>

        <?php print $region_content; ?>
        
        <?php print $feed_icons; ?>

        <?php if ($page['content_bottom']): ?>
          <?php print $region_content_bottom; ?>
        <?php endif; ?>
      </div>

      <div class="clearfix visible-sm visible-xs visible-md"></div>

      <?php if ($page['sidebar_right']): ?>
      <div class="col-lg-<?php print ($col_sidebar_right_lg); ?> col-md-<?php print ($col_sidebar_right_md); ?> hidden-sm hidden-xs sidebar-right">
        <?php print $region_sidebar_right; ?>
      </div>  
      <?php endif; ?>
    </div>

    <?php if ($col_sidebar_right_md == 12): ?>

    <?php endif; ?>

  </div><!-- /#layout-body -->

  <div id="layout-footer">
    <div class="container">
      <?php print $region_footer; ?>      
      <?php print t('Last update:') . ' ' . date('d/m/Y'); ?> | <a href="#top-page">Top</a>
    </div>
  </div><!-- /#layout-footer -->      

<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_150'); ?>";
</script>