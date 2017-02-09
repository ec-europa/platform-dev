<?php
/**
 * @file
 * Alter template file for theme('media_vimeo_video').
 *
 * Variables available:
 *  $uri - The media uri for the Vimeo video (e.g., vimeo://v/xsy7x8c9).
 *  $video_id - The unique identifier of the Vimeo video (e.g., xsy7x8c9).
 *  $id - The file entity ID (fid).
 *  $url - The full url including query options for the Vimeo iframe.
 *  $options - An array containing the Media Vimeo formatter options.
 *  $api_id_attribute - An id attribute if the Javascript API is enabled;
 *  otherwise NULL.
 *  $width - The width value set in Media: Vimeo file display options.
 *  $height - The height value set in Media: Vimeo file display options.
 *  $title - The Media: YouTube file's title.
 *  $alternative_content - Text to display for browsers that don't support
 *  iframes.
 *  $no_wrapper - Flag deterining if the video related tags must be embedded in
 *  the container.
 */
?>
<?php if (!$no_wrapper): ?>
 <div class="<?php print $classes; ?> media-vimeo-<?php print $id; ?>">
<?php endif; ?>
  <iframe class="media-vimeo-player" <?php print $api_id_attribute; ?>width="<?php print $width; ?>" height="<?php print $height; ?>" title="<?php print $title; ?>" src="<?php print $url; ?>" frameborder="0" allowfullscreen><?php print $alternative_content; ?></iframe>
<?php if (!$no_wrapper): ?>
  </div>
<?php endif; ?>
