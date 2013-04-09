<?php
/**
 * @file
 * Displays the default message for updates
 */
 
function get_message() {
  $message = '
<p style="margin-left:144.0pt;"><em>Dear webmaster,</em></p>
<p style="margin-left:144.0pt;"><em>The multiple site frameworks update will be launched on 07 December 2012.</em></p>
<p style="margin-left:144.0pt;"><em>Please read the deployment strategy information https://webgate.ec.europa.eu/multisite/fpfis/en/wiki/deployment-strategy-multiple-site if you are not yet familiar with the update process.</em></p>
<p style="margin-left:144.0pt;"><em>Summary:</em></p>
<p style="margin-left:144.0pt;"><em>A copy of your production site will be made to your playground environment on </em><strong>07 December 2012</strong></p>
<p style="margin-left:144.0pt;"><em>From that date you will no longer have access to the configuration screens of your production site. </em></p>
<p style="margin-left:144.0pt;"><em>You will receive a DIFF report on </em><strong>10 December 2012</strong><em> which will list the impact of that upgrade on your site.</em></p>
<p style="margin-left:144.0pt;"><em>You will have </em><strong>15 days</strong><em> to perform UAT on the playground environment and let us know of any issue you identified during that UAT period.</em></p>
<p style="margin-left:144.0pt;"><em>If no issue is reported or/and if all issues have been solved in the meantime we will release the update on your production website on </em><strong>07<sup>th</sup> of January 2013</strong>.</p>
<p style="margin-left:144.0pt;"><em>Please review regularly the roadmap calendar https://webgate.ec.europa.eu/multisite/fpfis/en/roadmap to be informed of future releases.</em></p>
<p style="margin-left:144.0pt;"><em>Do not hesitate to contact us if you have questions.</em></p>
<p style="margin-left:144.0pt;"><em>The FPFIS Multisite team</em></p>
  ';
  return $message;
}
