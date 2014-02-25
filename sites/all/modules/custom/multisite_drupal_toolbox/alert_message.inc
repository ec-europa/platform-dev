<?php
/**
 * @file
 * Displays the default message for updates
 */

function get_message() {
$message = '
<p style="margin-left:144.0pt;">Dear webmaster,</p>
<p style="margin-left:144.0pt;">The multiple site frameworks update will be launched on the <strong>13th March 2014</strong>.</p>
<p style="margin-left:144.0pt;">Please read <a href="https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Deployment+strategy">the deployment strategy information</a> if you are not yet familiar with the update process.</p>
<p style="margin-left:144.0pt;">Summary:</p>
<p style="margin-left:144.0pt;">A copy of your production site will be made to your playground environment on <strong>13th March 2014</strong></p>
<p style="margin-left:144.0pt;">From that date you will no longer have access to the configuration screens of your production site. </p>
<p style="margin-left:144.0pt;">You will receive a DIFF report on <strong>14th March 2014</strong> which will list the impact of that upgrade on your site. </p>
<p style="margin-left:144.0pt;">You will have <strong>7 days</strong> to perform UAT on the playground environment and let us know of any issue you identified during that UAT period.</p>
<p style="margin-left:144.0pt;">If no issue is reported or/and if all issues have been solved in the meantime we will release the update on your production website     starting from <strong>24th<sup></sup> March 2014</strong>.</p>
<p style="margin-left:144.0pt;">Do not hesitate to <a href="mailto:DIGIT-FPFIS-SUPPORT@ec.europa.eu">contact us</a> if you have questions.</p>
<p style="margin-left:144.0pt;">The FPFIS Multisite team</p>
';
  return $message;
}

