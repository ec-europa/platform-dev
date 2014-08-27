<?php
function multisite_cookie_consent_admin_settings(){

    // Configuration for connecting to the service
    $form['eucookie_consent'] = array(
        '#type' => 'fieldset',
        '#title' => t('eucookie consent settings'),
    );

    //link to external consent javascript, it can be overwritten
    $form['eucookie_consent']['eucookie_consent_ec_consent_javascript'] = array(
        '#type' => 'textfield',
        '#title' => t('Consent JavaScript file'),
        '#description' => t('This file is required! If you store this file locally, you can overwrite this setting, otherwise leave as it is.'),
        '#required' => true,
        '#default_value' => variable_get('eucookie_consent_ec_consent_javascript', 'http://ec.europa.eu/wel/cookie-consent/consent.js'),
    );

    //link to external consent javascript, it can be overwritten
    $form['eucookie_consent']['eucookie_consent_ec_consent_loggedin'] = array(
        '#type' => 'checkbox',
        '#title' => t('Display banner for logged in?'),
        '#description' => t('By default the cookie consent banner will shown
        only for anonymous user but check if you want to display it also for logged in users.'),
        '#default_value' => variable_get('eucookie_consent_ec_consent_loggedin', '0'),
    );

    //get cookie info and store it to the database
    //future to be replaced by entity remote api
    $form['eucookie_consent']['eucookie_consent_purge'] = array(
        '#type' => 'checkbox',
        '#title' => t('Do you want to save or update remote cookie information?'),
        '#description' => t('Update/save remote cookie descriptions and translations.'),
    );

    // Submit button.
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save configuration'),
    );

    return $form;
}

/**
 * Submission function for eucookie_consent_admin_settings form.
 */
function multisite_cookie_consent_admin_settings_submit($form, &$form_state){
    //overwrite the pointer to the EC consent.js file
    variable_set('eucookie_consent_ec_consent_javascript', $form_state['values']['eucookie_consent_ec_consent_javascript']);
    //set variable if you want to display banner to logged in users
    variable_set('eucookie_consent_ec_consent_loggedin', $form_state['values']['eucookie_consent_ec_consent_loggedin']);


    //fecth data from remote services
    if ($form_state['values']['eucookie_consent_purge'] == 1) {
        // get connection
        $conection_name = variable_get('multisite_cookie_connection');
        if($conection_name) {
            $connection = clients_connection_load($conection_name);
            try {
                //Check connection with the cookie Server
                $cookies = $connection->serverCheck(true);
            }
            catch (Exception $e) {
                drupal_set_message(t('Could not connect to the Cookie remote service, see error message "@message".', array(
                    '@message' => $e->getMessage(),
                )), 'error');
                $cookies = FALSE;
            }

            if ($cookies){
                //remove previously stored cookies
                multisite_cookie_consent_removecookie();
                //Todo: Tamaz find a way to get only the cookies relevant for this site
                foreach ($cookies['rows'] as $cookie){
                    //save each cookie on client side
                    multisite_cookie_consent_savecookie($cookie['id'] , $cookie['value']);
                }
                $cookie_notice_page = l('View cookie notice page' , 'cookie-notice',  array('html' => TRUE,
                    'attributes' => array('target' => '_blank')));
                drupal_set_message('Cookies saved! '. $cookie_notice_page );
            }

        }
        else {
            drupal_set_message('Please configure your connection first.');
        }
    }

}