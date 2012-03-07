<?php
// $Id: node.tpl.php,v 1.2 2010/12/01 00:18:15 webchick Exp $

/**
 * @file
 * ec_default's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
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
 
  switch ($type) {
    case 'links':
      $fields = array(
        'picture' => array(),
        'body'    => array(),
        'hide'  => array('comments', 'links'),
        'group' => array('group_audience', 'group_content_access')
      );        
      break;
      
    case 'news':
      $fields = array(
        'picture' => array('field_news_picture'),
        'body'    => array('body'),
        'hide'    => array('comments', 'links'),
        'group'   => array('group_audience', 'group_content_access')
      );        
      break;
      
    case 'community':
      $display_submitted = FALSE;
      $fields = array(
        'picture' => array('field_thumbnail'),
        'body'  => array('body'),
        'hide'  => array('comments', 'links', 'field_thumbnail'),
        'group' => array('group_group', 'group_access')
      );
      break;

    default:
      $fields = array(
        'picture' => array(),
        'body'  => array('body'),
        'hide'  => array('comments', 'links'),
        'group' => array('group_audience', 'group_content_access')
      );        
      break;
  }
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  
  
  <?php if ($display_submitted): ?>
    <div class="meta submitted">
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

    //display picture
    $display_picture = false;
    if (isset($fields['picture'])) {
      foreach ($fields['picture'] as $id) {
        if (isset($content[$id]['#access'])) {
          $display_picture = true;
          break;
        }
      }
    }
    if ($display_picture) { 
      foreach ($fields['picture'] as $id) {
        $output .= '<div class="no_label center">' . render($content[$id]) . '</div>';
      }     
    } 
    
    //display body
    $display_body = false;
    if (isset($fields['body'])) {
      foreach ($fields['body'] as $id) {
        if (isset($content[$id]['#access'])) {
          $display_body = true;
          break;
        }
      }
    }
    if ($display_body) {
      $output .= '<fieldset>';
      foreach ($fields['body'] as $id) {
        $output .= render($content[$id]);
      }       
      $output .= '</fieldset>';
    }
    
    //display non hidden fields
    foreach ($content as $key => $value) {
      if (!in_array($key,$fields['picture']) &&
          !in_array($key,$fields['body']) &&
          !in_array($key,$fields['hide']) &&
          !in_array($key,$fields['group'])) {
        $field = '<div class="field clerfix">';
        $field .= '<div class="span2 field-label">'.$value['#title'].'</div>';
        if ($variables['no_left']) {
          $field .= '<div class="span9 no_label">'.render($value).'</div>';
        } else {
          $field .= '<div class="span7 no_label">'.render($value).'</div>';
        }
        $field .= '</div>';
        
        $output .= $field;
      }
    }
    
    //display groups
    $display_group = false;
    if (isset($fields['group'])) {
      foreach ($fields['group'] as $id) {
        if (isset($content[$id]['#access'])) {
          $display_group = true;
          break;
        }
      }
    }
    if ($display_group) { 
      $output .= '<div class="meta submitted group well">';
        foreach ($fields['group'] as $id) {
          $output .=  render($content[$id]);
        }        
      $output .= '</div>';
    } 
    
    //display workbench block
    $display_workbench = block_render('workbench', 'block');
    if ($display_workbench) {
      $output .= '<div class="f_left meta submitted well alt workbench">';
      $output .= $display_workbench;
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
