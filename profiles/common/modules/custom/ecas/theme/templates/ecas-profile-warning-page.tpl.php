<?php

/**
 * @file
 * Template file for theme('ecas_profile_error_page').
 *
 * Variables available:
 *   $error_text: (mandatory) the main text describing the detected error.
 */
?>
<h2 class="ecl-heading ecl-heading--h2"><?php print $warning_title; ?></h2>
<div class="ecl-editor">
  <?php print $warning_text; ?>
</div>
