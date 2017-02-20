<?php

/**
 * @file
 * Media_avportal/includes/themes/media-avportal-video.tpl.php.
 *
 * Template file for theme('media_avportal_video').
 *
 * Variables available:
 *  $uri - The media uri for the YouTube video (e.g., avportal://v/xsy7x8c9).
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
<iframe 
    width="<?php print $width; ?>" 
    height="<?php print $height; ?>" frameborder="0" allowfullscreen="" mozallowfullscreen="" webkitallowfullscreen="" 
    id="videoplayer<?php print $video_id; ?>" scrolling="no" 
    src="<?php print $ec_embedded_video_url ?>">
</iframe>

<?php if(!empty($language_switcher)) : ?>
<div class="language-switcher">
<?php print $language_switcher; ?>
</div>
<?php endif; ?>
