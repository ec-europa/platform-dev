<?php
// $Id: node.tpl.php,v 1.2 2010/12/01 00:18:15 webchick Exp $

/**
 * @file
 * ec_resp's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $display_user_picture: Whether node author's picture should be displayed.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */

  $output = '';
  $display_user_picture = TRUE;
  $prefixe = '';
  $suffixe = '';
  $display_label = FALSE;
  //get node type
  switch ($type) {
    case 'links':
      $fields = array(
        'picture' => array(),
        'body'    => array(),
        'hidden'  => array('comments', 'links', 'print_links'),
        'group' => array('group_audience', 'group_content_access')
      );
      $display_user_picture = FALSE;
      break;

    case 'news':
      $fields = array(
        'picture' => array('field_news_picture'),
        'body'    => array('body'),
        'hidden'    => array('comments', 'links', 'print_links'),
        'group'   => array('group_audience', 'group_content_access')
      );
      $display_user_picture = FALSE;
      break;

    case 'community':
      $fields = array(
        'picture' => array('field_thumbnail'),
        'body'  => array('body'),
        'hidden'  => array('comments', 'links', 'print_links', 'field_thumbnail','og_roles_permissions'),
        'group' => array('group_group', 'group_access')
      );
      $display_submitted = FALSE;

      break;

    case 'blog_post':
      $fields = array(
        'picture' => array(),
        'body'  => array('body'),
        'hidden'  => array('comments', 'links', 'print_links'),
        'group' => array('group_audience', 'group_content_access')
      );
      break;

    case 'idea':
      $fields = array(
        'picture' => array(),
        'body'  => array('body'),
        'hidden'  => array('comments', 'links', 'field_watching', 'print_links'),
        'group' => array('group_audience', 'group_content_access')
      );
      $display_submitted = FALSE;
      if ($content['field_watching']['#object']->field_watching['und'][0]['value']) {
        $suffixe .= '<div class="no_label">';
        $suffixe .= '<span class="label label-success t_upper f_right"><i class="icon-eye-open icon-white"></i>'.t('watched').'</span>';
        $suffixe .= '</div>';
      }
      break;

    case 'webform':
      $fields = array(
        'picture' => array(),
        'body'  => array('body'),
        'hidden'  => array('comments', 'links', 'print_links'),
        'group' => array('group_audience', 'group_content_access')
      );
      $display_user_picture = FALSE;
      $display_label = TRUE;
      break;

    case 'gallerymedia':
      $fields = array(
        'picture' => array(),
        'body'  => array('body'),
        'hidden'  => array('field_video_upload', 'field_picture_upload', 'comments', 'links', 'print_links'),
        'group' => array('group_audience', 'group_content_access')
      );
      $suffixe = $gallerymedia_items;
      break;

      case 'page':
      $fields = array(
        'picture' => array(),
        'body'  => array('body'),
        'hidden'  => array('field_picture_upload', 'comments', 'links', 'print_links'),
        'group' => array('group_audience', 'group_content_access')
      );
      break;

    default:
      $fields = array(
        'picture' => array(),
        'body'  => array('body'),
        'hidden'  => array('comments', 'links', 'print_links'),
        'group' => array('group_audience', 'group_content_access')
      );
      //$suffixe = $video_items;
      break;
  }

  //set size of fields
  $span_large = 'span12';
  $span_title = 'span2';
  $span_small = 'span10';
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print filter_xss($node_url); ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="meta submitted">
      <?php if ($display_user_picture): ?>
        <?php print $user_picture; ?>
      <?php endif; ?>
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content clearfix"<?php print $content_attributes; ?>>

    <?php
      // We hide several elements now so that we can render them later.
      foreach ($fields as $key => $value) {
        foreach ($value as $id) {
          hide($content[$id]);
        }
      }

      $output .= $prefixe;

      //display non hidden fields
      $display_content = FALSE;
      foreach ($content as $key => $value) {
        if (!in_array($key,$fields['hidden']) &&
            !in_array($key,$fields['group'])) {
          $display_content = TRUE;
          if (isset($value['#weight'])) {
            $fields['content'][$key] = $value['#weight'];
          }
        }
      }
      if ($display_content && !empty($fields['content'])) {
        //sort fields by weight
        asort($fields['content']);

        foreach ($fields['content'] as $key => $value) {
          $field = '';
          if (isset($content[$key]['#label_display'])) {
            $field .= '<div class="row-fluid field c_left">';

            switch ($content[$key]['#label_display']) {
              case 'hidden':
                $field .= '<div class="'.$span_large.'">'.render($content[$key]).'</div>';
              break;

              case 'above':
                if (isset($content[$key]['#title'])) {
                  $content[$key]['#label_display'] = 'hidden';
                  $field .= '<div class="'.$span_large.' field-label">'.$content[$key]['#title'].'</div></div>';
                  $field .= '<div class="row-fluid"><div class="'.$span_large.' no_label">'.render($content[$key]).'</div>';
                } else {
                  $field .= '<div class="'.$span_large.' no_label">'.render($content[$key]).'</div>';
                }
              break;

              case 'inline':
              default:
                if (isset($content[$key]['#title'])) {
                  $content[$key]['#label_display'] = 'hidden';
                  $field .= '<div class="'.$span_title.' field-label">'.$content[$key]['#title'].'</div>';
                  $field .= '<div class="'.$span_small.' no_label">'.render($content[$key]).'</div>';
                } else {
                  $field .= '<div class="'.$span_large.' no_label">'.render($content[$key]).'</div>';
                }
              break;
            }

            $field .= '</div>';
          } else if ($display_label) {
            $field .= '<div class="row-fluid"><div class="'.$span_large.'">'.render($content[$key]).'</div></div>';
          } else  {
            $field .= '<div class="row-fluid"><div class="'.$span_large.' no_label">'.render($content[$key]).'</div></div>';
          }

          if (isset($content[$key]['#field_name']) && in_array($content[$key]['#field_name'],$fields['body'])) {
            $output .= '<fieldset>'.$field.'</fieldset>';
          } else if (isset($content[$key]['#field_name']) && in_array($content[$key]['#field_name'],$fields['picture'])) {
            $output .= '<div class="no_label center">'.$field.'</div>';
          } else {
            $output .= $field;
          }
        }
      }

      $output .= $suffixe;

      //display groups & workbench blocks
      $display_group = false;
      if (isset($fields['group'])) {
        foreach ($fields['group'] as $id) {
          if (isset($content[$id]['#access'])) {
            $display_group = true;
            break;
          }
        }
      }
      $display_workbench = ec_resp_141_block_render('workbench', 'block');

      if ($display_group || $display_workbench) {
        $output .= '<div class="row-fluid">';
        if ($display_group) {
          if ($display_workbench) {
            $group_span = 6;
          }
          else {
            $group_span = 12;
          }

          $output .= '<div class="span' . $group_span . ' well well-small">';
          foreach ($fields['group'] as $id) {
            $output .=  render($content[$id]);
          }
          $output .= '</div>';
        }

        if ($display_workbench) {
          $workbench_class = '';
          if ($display_group) {
            $workbench_span = 6;
          }
          else {
            $workbench_span = 6;
            $workbench_class .= 'offset6 ';
          }
          $workbench_class .= 'span' . $workbench_span . ' well well-small';

          $output .= '<div class="' . $workbench_class . '">';
          $output .= $display_workbench;
          $output .= '</div>';
        }
        $output .= '</div>';
      }

      print $output;
    ?>

  </div>

  <?php
    // Remove the "Add new comment" link on the teaser page or if the comment
    // form is being displayed on the same page.
    if ($teaser || !empty($content['comments']['comment_form'])) {
      unset($content['links']['comment']['#links']['comment-add']);
    }
    // Only display the wrapper div if there are links.
    $links = render($content['links']);
    if ($links):
  ?>
    <div class="link-wrapper right">
      <?php print $links; ?>
    </div>
  <?php endif; ?>

  <?php print render($content['comments']); ?>

</div>
