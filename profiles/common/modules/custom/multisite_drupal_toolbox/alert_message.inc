<?php
/**
 * @file
 * Displays the default message for updates.
 */

/**
 * Get message template.
 */
function get_message() {
  $message = '
  <p>Dear webmaster,</p>
  <p>The multiple site frameworks update will be launched on the <strong>7th May 2014</strong>.</p>
  <p>Please read <a href="https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Deployment+strategy">the deployment strategy information</a> if you are not yet familiar with the update process.</p>
  <p>Summary:</p>
  <p>A copy of your production site will be made to your playground environment on <strong>7th May 2014</strong></p>
  <p>From that date you will no longer have access to the configuration screens of your production site. </p>
  <p>You will receive a DIFF report on <strong>12th May 2014</strong> which will list the impact of that upgrade on your site. </p>
  <p>You will have <strong>7 days</strong> to perform UAT on the playground environment and let us know of any issue you identified during that UAT period.</p>
  <p>If no issue is reported or/and if all issues have been solved in the meantime we will release the update on your production website starting from <strong>19th<sup></sup> May 2014</strong>.</p>
  <p style="color:red">You will be able to check the full planning from our <a href="https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Events">wiki calendar</a>.</p>
  <p>Do not hesitate to <a href="mailto:DIGIT-FPFIS-SUPPORT@ec.europa.eu">contact us</a> if you have questions.</p>
  <p>The FPFIS Multisite team</p>
  ';
  return $message;
}
