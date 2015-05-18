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
 * - $menu_visible: Checking if the main menu is available in the region featured
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
 * - $page['sidebar_left']: Small sidebar displayed on left of the content, if not empty -> navigation, pictures, ... 
 * - $page['sidebar_right']: Small sidebar displayed on right of the content, if not empty -> latest content, calendar, ... 
 *
 * - $page['content_top']: Displayed in middle column, right before the page title -> carousel, important news, ...  
 * - $page['help']: Displayed between page title and content -> information about the page, contextual help, ... 
 * - $page['content']: The main content of the current page.
 * - $page['content_right']: Large sidebar displayed on right of the content, if not empty -> 2 column layout 
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

// format regions.
$region_header_right = (isset($page['header_right']) ? render($page['header_right']) : '');
$region_header_top = (isset($page['header_top']) ? render($page['header_top']) : '');
$region_featured = (isset($page['featured']) ? render($page['featured']) : '');
$region_sidebar_left = (isset($page['sidebar_left']) ? render($page['sidebar_left']) : '');
$region_tools = (isset($page['tools']) ? render($page['tools']) : '');
$region_content_top = (isset($page['content_top']) ? render($page['content_top']) : '');
$region_help = (isset($page['help']) ? render($page['help']) : '');
$region_content = (isset($page['content']) ? render($page['content']) : '');
$region_content_right = (isset($page['content_right']) ? render($page['content_right']) : '');
$region_content_bottom = (isset($page['content_bottom']) ? render($page['content_bottom']) : '');
$region_sidebar_right = (isset($page['sidebar_right']) ? render($page['sidebar_right']) : '');
$region_footer = (isset($page['footer']) ? render($page['footer']) : '');

// check if there is a responsive sidebar or not
$has_responsive_sidebar = ($region_header_right || $region_sidebar_left || $region_sidebar_right ? 1 : 0);

// calculate size of regions.
  // sidebars
  $col_sidebar_left = array(
    'lg' => (!empty($region_sidebar_left) ? 3 : 0),
    'md' => (!empty($region_sidebar_left) ? 4 : 0),
    'sm' => 0,
    'xs' => 0
  );
  $col_sidebar_right = array(
    'lg' => (!empty($region_sidebar_right) ? 3 : 0),
    'md' => (!empty($region_sidebar_right) ? (!empty($region_sidebar_left) ? 12 : 4) : 0),
    'sm' => 0,
    'xs' => 0
  );

  // content
  $col_content_main = array(
    'lg' => 12 - $col_sidebar_left['lg'] - $col_sidebar_right['lg'],
    'md' => ($col_sidebar_right['md'] == 4 ? 8 : 12 - $col_sidebar_left['md']),
    'sm' => 12,
    'xs' => 12
  );
  $col_content_right = array(
    'lg' => (!empty($region_content_right) ? 6 : 0),
    'md' => (!empty($region_content_right) ? 6 : 0),
    'sm' => (!empty($region_content_right) ? 12 : 0),
    'xs' => (!empty($region_content_right) ? 12 : 0)
  );
  $col_content = array(
    'lg' => 12 - $col_content_right['lg'],
    'md' => 12 - $col_content_right['md'],
    'sm' => 12,
    'xs' => 12
  );

  // tools
  $col_sidebar_button = array(
    'sm' => ($has_responsive_sidebar ? 2 : 0),
    'xs' => ($has_responsive_sidebar ? 2 : 0)
  );
  $col_tools = array(
    'lg' => ($title ? 4 : 12),
    'md' => ($title ? 4 : 12),
    'sm' => 12,
    'xs' => 12
  );

  // title
  $col_title = array(
    'lg' => 12 - $col_tools['lg'],
    'md' => 12 - $col_tools['md'],
    'sm' => 12,
    'xs' => 12
  );
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
      <img alt="European Commission logo" id="banner-flag" src="<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_16'); ?>/images/logo/logo_en.gif" />

      <span id="banner-image-right" class="hidden-sm hidden-xs">
        <?php print $region_header_right; ?>
      </span>
    
    <?php
      break;


      case 'europa':
    ?>
      <a class="banner-flag" href="http://europa.eu/index_en.htm" title="European Union homepage">
        <img id="banner-flag" src="<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_16'); ?>/wel/template-2011/images/europa-flag.gif" alt="European Union homepage. EU flag" width="67" height="60" border="0">
      </a>

      <p class="banner-title">
        <img src="<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_16'); ?>/wel/template-2011/images/title/title_en.gif" alt="Title of the site" width="450" height="46">
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
    </div>
  </div><!-- /#layout-header -->
  
  <div class="region-featured-wrapper <?php if ($has_responsive_sidebar) print 'sidebar-visible-sm'; ?>">
    <?php if ($menu_visible || $has_responsive_sidebar): ?>
      <div class="mobile-user-bar navbar navbar-default visible-xs" data-spy="affix" data-offset-top="82">
        <div class="container">

          <!-- Brand and toggle get grouped for better mobile display -->
          <div class="navbar-header" data-spy="affix" data-offset-top="165">
            <?php if ($menu_visible): ?>
              <button id="menu-button" type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
                <div class="arrow-down"></div>
              </button>
            <?php endif; ?>

            <?php if ($has_responsive_sidebar): ?>
              <div class="sidebar-button-wrapper">
                <button class="sidebar-button">
                  <span class="icon-bar"></span>
                  <span class="icon-bar"></span>
                  <span class="icon-bar"></span>
                </button>
              </div>
            <?php endif; ?>
          </div>
        </div><!-- /.container -->
      </div><!-- /.navbar -->
    <?php endif; ?>

    <?php print $region_featured; ?>

  </div>

  <?php if ($has_responsive_sidebar): ?>
    <div id="responsive-sidebar">
      <div id="responsive-header-right"></div>
      <div id="responsive-sidebar-left"></div>
      <div id="responsive-sidebar-right"></div>
    </div><!-- /#responsive-sidebar-->   
  <?php endif; ?>

  <div id="layout-body" class="container">
    <div class="row">
      <?php print render($title_prefix); ?>

      <?php if ($title): ?>
        <?php $title_image = (isset($node->field_thumbnail['und'][0]['uri']) && $node->type == 'community' ? image_style_url('communities_thumbnail', $node->field_thumbnail['und'][0]['uri']) : '');?>
        <h1 class="col-lg-<?php print $col_title['lg']; ?> col-md-<?php print $col_title['md']; ?> col-sm-<?php print $col_title['sm']; ?> col-xs-<?php print $col_title['xs']; ?>" id="page-title">
          <?php if ($title_image): ?>
            <img src="<?php print $title_image; ?>" alt="<?php print $title; ?>" />
          <?php endif; ?>
          <?php print $title; ?>
        </h1>
      <?php endif; ?>
      
      <?php print render($title_suffix); ?>

      <div class="col-lg-<?php print $col_tools['lg']; ?> col-md-<?php print $col_tools['md']; ?> col-sm-<?php print $col_tools['sm']; ?> col-xs-<?php print $col_tools['xs']; ?>">
        <?php print $region_tools; ?>
      </div>
    </div>

    <?php if ($messages): ?>
    <div id="messages">
        <?php print $messages; ?>
    </div><!-- /#messages -->
    <?php endif; ?>
        
    <div class="row">
      <?php if ($page['sidebar_left']): ?>
      <div id="sidebar-left" class="col-lg-<?php print ($col_sidebar_left['lg']); ?> col-md-<?php print ($col_sidebar_left['md']); ?> col-sm-<?php print ($col_sidebar_left['sm']); ?> col-xs-<?php print ($col_sidebar_left['xs']); ?> sidebar-left visible-lg visible-md">
        <?php print $region_sidebar_left; ?>
      </div>
      <?php endif; ?>     

      <div class="col-lg-<?php print $col_content_main['lg']; ?> col-md-<?php print $col_content_main['md']; ?> col-sm-<?php print $col_content_main['sm']; ?> col-md-<?php print $col_content_main['xs']; ?>">
        
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

        <div class="row">
          <div class="col-lg-<?php print $col_content['lg']; ?> col-md-<?php print $col_content['md']; ?> col-sm-<?php print $col_content['sm']; ?> col-xs-<?php print $col_content['xs']; ?>">
          <?php print $region_content; ?>
          </div>

          <div class="col-lg-<?php print $col_content_right['lg']; ?> col-md-<?php print $col_content_right['md']; ?> col-sm-<?php print $col_content_right['sm']; ?> col-xs-<?php print $col_content_right['xs']; ?>">
          <?php print $region_content_right; ?>
          </div>
        </div>
        
        <?php print $feed_icons; ?>

        <?php print $region_content_bottom; ?>
      </div>

      <div class="clearfix visible-sm visible-xs"></div>
      <?php if ($col_sidebar_right['md'] == 12): ?>
      <div class="clearfix visible-md"></div>
      <?php endif; ?>

      <?php if ($page['sidebar_right']): ?>
      <div id="sidebar-right" class="col-lg-<?php print ($col_sidebar_right['lg']); ?> col-md-<?php print ($col_sidebar_right['md']); ?> col-sm-<?php print ($col_sidebar_right['sm']); ?> col-xs-<?php print ($col_sidebar_right['xs']); ?> sidebar-right visible-lg visible-md">
        <?php print $region_sidebar_right; ?>
      </div>  
      <?php endif; ?>
    </div>
  </div><!-- /#layout-body -->

  <div id="layout-footer">
    <div class="container">
      <?php print $region_footer; ?>
    </div>
  </div><!-- /#layout-footer -->      

<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . drupal_get_path('theme', 'ec_resp_16'); ?>";
</script>