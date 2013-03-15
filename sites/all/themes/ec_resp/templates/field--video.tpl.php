<?php
/**
 * @file field.tpl.php
 * Default template implementation to display the value of a field.
 *
 * This file is not used and is here as a starting point for customization only.
 * @see theme_field()
 *
 * Available variables:
 * - $items: An array of field values. Use render() to output them.
 * - $label: The item label.
 * - $label_hidden: Whether the label display is set to 'hidden'.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - field: The current template type, i.e., "theming hook".
 *   - field-name-[field_name]: The current field name. For example, if the
 *     field name is "field_description" it would result in
 *     "field-name-field-description".
 *   - field-type-[field_type]: The current field type. For example, if the
 *     field type is "text" it would result in "field-type-text".
 *   - field-label-[label_display]: The current label position. For example, if
 *     the label position is "above" it would result in "field-label-above".
 *
 * Other variables:
 * - $element['#object']: The entity to which the field is attached.
 * - $element['#view_mode']: View mode, e.g. 'full', 'teaser'...
 * - $element['#field_name']: The field name.
 * - $element['#field_type']: The field type.
 * - $element['#field_language']: The field language.
 * - $element['#field_translatable']: Whether the field is translatable or not.
 * - $element['#label_display']: Position of label display, inline, above, or
 *   hidden.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 */
global $base_url, $theme;
$themepath = drupal_get_path('theme', $theme);
?>
<!--
THIS FILE IS NOT USED AND IS HERE AS A STARTING POINT FOR CUSTOMIZATION ONLY.
See http://api.drupal.org/api/function/theme_field/7 for details.
After copying this file to your theme's folder and customizing it, remove this
HTML comment.
-->
<div class="media_gallery row-fluid">
  <ul class="thumbnails">

    <?php foreach ($items as $delta => $item): ?>

      <?php
      $converted_fid = db_select('video_output', 'vd')
              ->fields('vd', array('output_fid'))
              ->condition('original_fid', $item['#item']['fid'], '=')
              ->execute()
              ->fetchAssoc();

      if (isset($converted_fid) && $converted_fid != NULL) {
        $converted_video = file_load($converted_fid['output_fid']); //very useful object

        $video_path = $base_url . '/' . file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . str_replace('public://', '/', $converted_video->uri);
      } else {
        $video_path = $base_url . '/' . file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . '/videos/original/' . $item['#item']['filename'];
      }


      //REPLACE $localdata with $item['#item']
      $thumb = file_load($item['#item']['thumbnail']);

      if (!empty($thumb)) {
        $video_square_thumbnail = image_style_url('square_thumbnail', $thumb->uri);
        $video_preview = image_style_url('preview', $thumb->uri);
      }



      $short_name = (strlen(filter_xss($item['#item']['filename'])) > 35) ? substr(filter_xss($item['#item']['filename']), 0, 30) . '[...]' : filter_xss($item['#item']['filename']);
      ?>


       <?php
//activate it if necessary
//print render($item);
      ?>
        <li class="span3">
          <!-- $key replace by $element['#field_name']-->
          <div id="video_lightbox<?php print $delta; ?>" class="lightbox" style="display: none;">


            <object classid='clsid:D27CDB6E-AE6D-11cf-96B8-444553540000' width='800' height='600' id='<?php print $element['#field_name']; ?>' name='<?php print $element['#field_name']; ?>'>
              <param name='movie' value='http://ec.europa.eu/wel/players/jwflvplayer/player.swf'>
              <param name='allowfullscreen' value='true'>
              <param name='allowscriptaccess' value='always'>
              <param name='flashvars' value='file=<?php print $video_path; ?>&fullscreen=true&image=<?php print $video_preview; ?>&skin=http://ec.europa.eu/wel/players/jwflvplayer/skins/mainley.swf'>
              <!--<param name='flashvars' value='file=playlist.xml'>
              inside embed will be
              flashvars="file=playlist.xml"
              -->
              <embed id='<?php print $element['#field_name']; ?>'
                     name='<?php print $element['#field_name']; ?>'
                     src='http://ec.europa.eu/wel/players/jwflvplayer/player.swf'
                     width='800'
                     height='600'
                     allowscriptaccess='always'
                     allowfullscreen='true'
                     flashvars="file=<?php print $video_path; ?>&fullscreen=true&image=<?php print $video_preview; ?>&skin=http://ec.europa.eu/wel/players/jwflvplayer/skins/mainley.swf"
                     />
            </object>

          </div>

          <a href="#video_lightbox<?php print $delta; ?>" class="fancybox thumbnail" rel="gallery" title="<?php $item['#item']['filename']; ?>">
            <img class="watermark" src="<?php print $base_url . '/' . $themepath; ?>/images/video_icon.png" alt="<?php $item['#item']['filename']; ?>" title="<?php $item['#item']['filename']; ?>" />
            <img src="<?php print $video_square_thumbnail; ?>" alt="<?php $item['#item']['filename']; ?>" title="<?php $item['#item']['filename']; ?>" />
            <p class="carousel-caption"><?php print $short_name; ?></p>
          </a>



        </li>

<?php endforeach; ?>

  </ul>
</div>
