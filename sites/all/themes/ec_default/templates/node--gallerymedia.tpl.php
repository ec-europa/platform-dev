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

  global $base_url;
  
  $output = '';
 
  $fields = array(
    'picture' => array(),
    'body'  => array('body'),
    'hide'  => array('comments', 'links', 'print_links', 'field_picture_upload', 'field_video_upload'),
    'group' => array('group_audience', 'group_content_access')
  );        
  
  //set size of fields 
  if ($variables['no_left']) {
    $span_large = 'span11';
    $span_title = 'span2';
    $span_small = 'span9';
  } else {
    $span_large = 'span9';
    $span_title = 'span2';
    $span_small = 'span7';      
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
  
<?php  
// global $user;

  // /*Add Picture button*/
  // if ($uid == $user->uid) {
    // print l(t('Add a Picture'), 'node/'. $node->nid.'/addmedia', array(
          // 'attributes' => array(
                      // 'type' => 'add', 
                      // 'action_bar' => 'single',
                      // 'btn_group' => 'single',
                      // 'id' => 'add_picture'))); 
    // $add_form =  drupal_get_form('add_media_form');
    // print render($add_form);
  // }
?>
  
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
    
    //merge photos and videos
    if (isset($content['field_picture_upload']['#items']) && isset($content['field_video_upload']['#items'])) {
      $media_items = array_merge($content['field_picture_upload']['#items'],$content['field_video_upload']['#items']);
    } else if (isset($content['field_picture_upload']['#items'])) {
      $media_items = $content['field_picture_upload']['#items'];
    } else if (isset($content['field_video_upload']['#items'])) {
      $media_items = $content['field_video_upload']['#items'];
    } else {
      $media_items = array();
    }
    
    //sort table
    usort($media_items, "custom_sort");
    function custom_sort($a,$b) {
      return $a['timestamp']>$b['timestamp'];
    }    

    //display pager
    if(isset($content['field_picture_upload']['#cck_pager_pager'])){
      foreach ($content['field_picture_upload']['#cck_pager_pager'] as $key => $value) {
        $output .= ' '.$value['data'];
      }
    }
    
    //display media items
    if(!isset($media_items) || count($media_items) == 0) {
      global $base_url;
      $empty_pic = array(
        'type' => 'empty',
        'uri' => $base_url . '/' . path_to_theme() . '/images/empty_gallery.png',
        'filename' => t('empty gallery')
      );     
     
      $media_items[0] = $empty_pic;
    }
    
    foreach ($media_items as $key => $item) {
      if (($key % 4) == 0)
        $output .= '<div class="media_gallery row-fluid">';
        
      switch ($item['type']) {
        case 'image':
          $picture_square_thumbnail = image_style_url('square_thumbnail', $item['uri']);
          $picture_preview = image_style_url('preview', $item['uri']);
          $picture_original = file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . str_replace('public://','/',$item['uri']);        
          
          $output .= '<div class="span3 media_item">';
          $output .= '<div id="lightbox'.$key.'" class="lightbox" style="display: none;">';
          $output .= '<img src="'.$picture_preview.'" alt="'.$item['filename'].'" />';

          if (isset($item['field_picture_description']['und'][0]['value']))
            $output .= '<p>'.$item['field_picture_description']['und'][0]['value'].'</p>';

          $output .= '<p><a href="'.$base_url.'/'.$picture_original.'" title="'.$item['filename'].'" target="_blank">'.t('View full size picture').'</a></p>';
          $output .= '</div>';
          $output .= '<a href="#lightbox'.$key.'" class="fancybox" rel="gallery" title="'.$item['filename'].'">';
          $output .= '<img src="'.$picture_square_thumbnail.'" alt="'.$item['filename'].'" title="" />';
          $output .= '<p class="carousel-caption">'.$item['filename'].'</p>';
          $output .= '</a>';        
          $output .= '</div>';          
        break;
        
        case 'video':
          //$video_path = $base_url . '/' . variable_get('file_directory_path', $default = 'sites/default/files') . '/videos/original/' . $item['filename'];
				  
          $converted_fid = db_select('video_output', 'vd')
            ->fields('vd', array('output_fid'))
            ->condition('original_fid', $item['fid'],'=')
            ->execute()
            ->fetchAssoc();
          
          if (isset($converted_fid) && $converted_fid != null) {
            $converted_video = file_load($converted_fid['output_fid']);
            $video_path = $base_url . '/' . file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . str_replace('public://','/',$converted_video->uri);
          } else {
            $video_path = $base_url . '/' . variable_get('file_directory_path', $default = 'sites/default/files') . '/videos/original/' . $item['filename'];
          }
          $thumb = file_load($item['thumbnail']);
          $video_square_thumbnail = image_style_url('square_thumbnail', $thumb->uri);
          $video_preview = image_style_url('preview', $thumb->uri);
          $watermark = $base_url . '/' . path_to_theme() . '/images/video_icon.png';
          
          $output .= '<div class="span3 media_item">';
          $output .= '<div id="video_lightbox'.$key.'" class="lightbox" style="display: none;">';
          $output .= "<object classid='clsid:D27CDB6E-AE6D-11cf-96B8-444553540000' width='800' height='600' id='single1' name='single1'>
          <param name='movie' value='http://ec.europa.eu/wel/players/jwflvplayer/player.swf'>
          <param name='allowfullscreen' value='true'>
          <param name='allowscriptaccess' value='always'>
          <param name='wmode' value='transparent'>
          <param name='flashvars' value='file=".$video_path."&image=".$video_preview."&skin=http://ec.europa.eu/wel/players/jwflvplayer/skins/mainley.swf'>
          <embed
            type='application/x-shockwave-flash'
            id='single2'
            name='single2'
            src='http://ec.europa.eu/wel/players/jwflvplayer/player.swf'
            width='800'
            height='600'
            bgcolor='undefined'
            allowscriptaccess='always'
            allowfullscreen='true'
            wmode='transparent'
            flashvars='file=".$video_path."&image=".$video_preview."&skin=http://ec.europa.eu/wel/players/jwflvplayer/skins/mainley.swf'
          />
          </object>";
          $output .= '</div>';
          $output .= '<a href="#video_lightbox'.$key.'" class="fancybox" rel="gallery" title="'.$item['filename'].'">';
          $output .= '<img class="watermark" src="'.$watermark.'" alt="'.$item['filename'].'" title="" />';
          $output .= '<img src="'.$video_square_thumbnail.'" alt="'.$item['filename'].'" title="" />';
          $output .= '<p class="carousel-caption">'.$item['filename'].'</p>';
          $output .= '</a>';        
          $output .= '</div>';          
        break;
        
        case 'empty':
          $output .= '<div class="span3 media_item">';
          $output .= '<img src="'.$item['uri'].'" alt="'.$item['filename'].'" />';
          $output .= '</div>';           
        break;
        
        default:       
        break;
      }
        
      if ((($key+1) % 4) == 0 || !isset($media_items[$key+1]))
        $output .= '</div>';         
    }
    
    //display non hidden fields
    $display_other = FALSE;
    foreach ($content as $key => $value) {
      if (!in_array($key,$fields['picture']) &&
          !in_array($key,$fields['body']) &&
          !in_array($key,$fields['hide']) &&
          !in_array($key,$fields['group'])) {
        $display_other = TRUE;
        $fields['other'][$key] = $value['#weight'];
      }
    }    
    if ($display_other) {
      //sort fields by weight
      asort($fields['other']);

      $output .= '<blockquote class="f_left">';    
      foreach ($fields['other'] as $key => $value) {
        $field = '<div class="field c_left">';
        if (isset($content[$key]['#title'])) {
          $field .= '<div class="'.$span_title.' field-label">'.$content[$key]['#title'].'</div>';
          $field .= '<div class="'.$span_small.' no_label">'.render($content[$key]).'</div>';
          $field .= '</div>';
        } else {
          $field .= '<div class="'.$span_large.' no_label">'.render($content[$key]).'</div>';
          $field .= '</div>';
        }
        $output .= $field;      
      }
      $output .= '</blockquote>'; 
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