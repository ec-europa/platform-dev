<?php

/**
 * @file
 * Helper functions for module installation.
 */

/**
 * Set variables translatable if the i18n_variable module is enabled.
 */
function _ecas_set_variables_translatable() {
  if (!module_exists('i18n_variable')) {
    return;
  }

  $variable_realm_list_language = variable_get('variable_realm_list_language', array());
  $ecas_variables = array(
    ECAS_EMAIL_ERROR_MESSAGE,
    ECAS_EMAIL_ERROR_MESSAGE_SOCIAL,
    ECAS_LOGIN_MESSAGE,
    ECAS_WARNING_MESSAGE,
  );
  variable_set('variable_realm_list_language', array_merge($variable_realm_list_language, $ecas_variables));
}

/**
 * Gets the default value for the ECAS_EMAIL_ERROR_MESSAGE variable.
 *
 * @return array
 *   Associative array setting the value and the format of the text set for
 *   the error message text in case of a missing e-mail in EU Login profile.
 */
function _ecas_get_default_missing_mail_variable() {
  $text = <<< EOF
<p><strong>The received EU login data that concern you does not include an e-mail address.</strong></p>
<p>The features proposed by this site like event notifications, newsletters, etc. require this address.</p>
<p>Please check your EU Login account or contact the <a href="https://webgate.ec.europa.eu/cas/contact.html">EU login team.</a></p>
EOF;
  return array(
    'value' => $text,
    'format' => 'full_html',
  );
}

/**
 * Gets the default value for the ECAS_EMAIL_ERROR_MESSAGE_SOCIAL variable.
 *
 * @return array
 *   Associative array setting the value and the format of the text set for
 *   the error message text in case of a missing e-mail in EU Login profile.
 */
function _ecas_get_default_missing_mail_social_variable() {
  $text = <<< EOF
<p><strong>The received EU login data that concern you does not include an e-mail address.</strong></p>
<p>The features proposed by this site like event notifications, newsletters, etc. require this address.</p>
<p><strong>If you are using a Facebook account</strong> to log in this site, please ensure you give the authorization to communicate your e-mail address to EU Login.</p>
<h3>To consult these Facebook settings</h3>
<p>Please follow these steps:</p>
<ol>
    <li>Go to your Facebook settings, in the "Apps and websites" page (<a href="http://www.facebook.com?tab=applications">https://www.facebook.com?tab=applications</a>)
    </li>
    <li>Click on the "View and edit" link display blow the "EU Login" label;</li>
    <li>Check that your e-mail address is displayed on the displayed popup and the box is checked on its right<br/>[ecas-illustration:fb-apps-settings-edit]
    </li>
</ol>
<p>If your e-mail address is not displayed or the box is not checked, you can redo the EU login registration via Facebook or create a specific EU Login account by filling this form located here:<br/>
[ecas-url:account-request-link].
</p>
<p></p>
<h3>To allow EU Login receiving the e-mail address</h3>
<p>Please follow these steps:</p>
<ol>
    <li>Go to your Facebook settings, in the "Apps and websites" page (<a href="http://www.facebook.com?tab=applications">https://www.facebook.com?tab=applications</a>)
    </li>
    <li>Check the box beside the "EU Login" block and click the "Remove button" on the left<br/>[ecas-illustration:fb-apps-settings-form]
    </li>
    <li>Confirm the removal<br/>[ecas-illustration:fb-apps-settings-confirm]</li>
    <li>Ensure you are correctly logged out from EU Login.</li>
    <li>Redo the login process via Facebook by ensuring you authorize EU Login to receive the e-mail address.<br/>
        It occurs if the e-mail address transmission is mentioned in the authorization popup<br/>[ecas-illustration:fb-apps-login-confirmation]<br/>
        If the e-mail address transmission is not mentioned, click the "Edit this" in the authorization popup and check the box displayed on the right of your e-mail address<br/>[ecas-illustration:fb-apps-login-settings-edit].
    </li>
    <li>Confirm by clicking the blue button "Continues as {your user name}"</li>
</ol>
<p></p>
<h3>In case of issue</h3>
<p>If nothing above works, please contact the <a href="https://webgate.ec.europa.eu/cas/contact.html">EU login team.</a>
</p>
EOF;
  return array(
    'value' => $text,
    'format' => 'full_html',
  );
}