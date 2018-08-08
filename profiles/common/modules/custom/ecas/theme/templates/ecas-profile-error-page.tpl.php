<?php

/**
 * @file
 * Template file for theme('ecas_profile_error_page').
 *
 * Variables available:
 *   $error_text: (mandatory) the main text describing the detected error.
 */
?>
<div class="ecl-message ecl-message--error messages error">
  <p><?php print t("Some required information of your profile are incorrect!"); ?></p>
</div>
<br />
<div class="ecl-editor">
  <?php print $error_text; ?>
</div>
