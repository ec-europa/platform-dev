<?php

/**
 * @file
 * Template file for theme('media_avportal_video').
 *
 * Variables available:
 *  $uri - The media uri for the AV portal video (e.g., avportal://v/xsy7x8c9).
 *  $video_id - The unique identifier of the YouTube video (e.g., xsy7x8c9).
 *  $url - The full url including query options for the Youtube iframe.
 *  $options - An array containing the Media AV portal formatter options.
 *  $width - The width value set in Media: AV portal file display options.
 *  $height - The height value set in Media: AV portal file display options.
 */
?>
<iframe 
    width="<?php print $width; ?>" 
    height="<?php print $height; ?>" frameborder="0" allowfullscreen="" mozallowfullscreen="" webkitallowfullscreen="" 
    id="videoplayer<?php print $video_id; ?>" scrolling="no" 
    src="<?php print $ec_embedded_video_url ?>">
</iframe>
