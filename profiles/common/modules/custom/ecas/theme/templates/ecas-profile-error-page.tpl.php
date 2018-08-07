<?php

/**
 * @file
 * Template file for theme('ecas_profile_error_page').
 *
 * Variables available:
 *   $error_text: (mandatory) the main text describing the detected error.
 */
?>
<div class="ecl-message__body status-error messages error">
  <?php print t("Some required information of your profile are incorrect!"); ?>
</div>
<br />
<div>
  <?php print $error_text; ?>
</div>
