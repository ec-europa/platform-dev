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
          <?php 
          global $language;
          $languages = language_list('enabled');
          $li = "";

          foreach($languages[1] as $lang) {
            //add enabled languages
            $li .= '<li><a href="'.base_path().$lang->prefix.'" data-label="('.$lang->prefix.') '.t(variable_get("splash_screen_language_msg")).'"><span>'.$lang->language.'</span>'.$lang->native.'</a></li>';
          }
           ?>
          <ul class="well languages nav nav-list">
            <li><h2 id="label_language"><?php print variable_get("splash_screen_language_msg"); ?></h2></li>
          <?php print $li; ?>
          </ul>
        </div>
      </div>
    </div>
  </div>
</div>

<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . path_to_theme(); ?>";
  
  jQuery(function($){
    $(document).ready(function() {
      $('ul.languages li a').hover(function() {
        $('#label_language').text($(this).attr('data-label'));
      });
      
    });
  }); 
</script>
