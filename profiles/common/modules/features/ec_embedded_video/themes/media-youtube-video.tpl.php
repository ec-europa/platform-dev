<?php

/**
 * @file
 * Template file for theme('media_youtube_video').
 *
 * Variables available:
 *  $uri - The media uri for the YouTube video (e.g., youtube://v/xsy7x8c9).
 *  $video_id - The unique identifier of the YouTube video (e.g., xsy7x8c9).
 *  $id - The file entity ID (fid).
 *  $url - The full url including query options for the Youtube iframe.
 *  $options - An array containing the Media Youtube formatter options.
 *  $api_id_attribute - An id attribute if the Javascript API is enabled;
 *  otherwise NULL.
 *  $width - The width value set in Media: Youtube file display options.
 *  $height - The height value set in Media: Youtube file display options.
 *  $title - The Media: YouTube file's title.
 *  $alternative_content - Text to display for browsers that don't support
 *  iframes.
 *  $no_wrapper - If TRUE, video's wrappers are not displayed.
 */
?>
<?php if (!$no_wrapper): ?>
  <div class="<?php print $classes; ?> media-youtube-<?php print $id; ?>">
<?php endif ?>
  <iframe class="media-youtube-player" <?php print $api_id_attribute; ?>width="<?php print $width; ?>" height="<?php print $height; ?>" title="<?php print $title; ?>" src="<?php print $url; ?>" frameborder="0" allowfullscreen><?php print $alternative_content; ?></iframe>
<?php if (!$no_wrapper): ?>
  </div>
<?php endif ?>
