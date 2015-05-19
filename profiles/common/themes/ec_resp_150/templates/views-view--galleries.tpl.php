<?php
/**
 * @file views-view.tpl.php
 * Main view template
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>

  <?php 
  //Replace nid by number of items in gallery  
  function nb_items_count($matches) {
    $node = node_load($matches[1]);
    $nb_pictures = 0;
    $nb_video = 0;

    if (isset($node->field_picture_upload['und'])):
      $nb_pictures = sizeof($node->field_picture_upload['und']);
    endif;

    if (isset($node->field_video_upload['und'])):
      $nb_video = sizeof($node->field_video_upload['und']);
    endif;  

    return '<div class="meta">' . ($nb_pictures + $nb_video) . ' ' . t('items') . '</div>';
  }

    if (user_access('create gallerymedia content') && strpos($classes, "medias_block") == false ) {
      print l(t('Create a Gallery'), 'node/add/gallerymedia', array('attributes' => array('type' => 'add', 'action_bar' => 'single', 'btn_group' => 'single'))); 
    }
  ?>
  
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <?php     
          $empty_pic = db_select('file_managed', 'fm')
            ->fields('fm')
            ->condition('filename', 'empty_gallery.png','=')
            ->execute()
            ->fetchAssoc();
          $picture_square_thumbnail = image_style_url('square_thumbnail', $empty_pic['uri']);
          $empty_img = '<img src="'.$picture_square_thumbnail.'" alt="There is no content in this gallery, or it has not been validated yet." />';

          //Check if the galleries are actually empty
          $rows = str_replace('[Empty_gallery][Empty_gallery]', $empty_img, $rows );
          //Check if there is only one picture
          $rows = str_replace('[Empty_gallery]', '', $rows );
          //Replace nid by number of items in gallery
          $rows = preg_replace_callback('#<div id="nb_items">([0-9]+)</div>#', "nb_items_count" , $rows);

          print $rows;

      ?>
    </div>

  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>


<!-- Small bits of jquery to make it clean -->
<script type="text/javascript">
  //use jQuery 1.7.1
  (function($){
    $(document).ready(function() {  //Once the page elements are fully loaded
      $row=$('div.galleries-item-wrapper');
      //hide the video thumbnails in galleries with pictur thumbnails
      $row.each(function() {
       if($(this).find('a').size()>1){
        $(this).find('a:last').hide();
        }
      });
    });
  })(jq171); 
</script>
