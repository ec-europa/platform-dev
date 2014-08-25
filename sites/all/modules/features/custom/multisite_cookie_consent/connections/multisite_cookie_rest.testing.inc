<?php
/**
 * @file
 * Contains classes for Client connection testing.
 */

/**
 * Test basic connection.
 */
class ClientsConnectionMultiSiteCookieRESTServerCheck implements ClientsConnectionTestingInterface {

    /**
     * The labels for the test.
     *
     * (This is because it would seem you can't define class variables using
     * expressions.)
     */
    function testLabels() {
        return array(
            'label' => t('Check server'),
            'description' => t('Test the basic connection. Checks if service is available.'),
            'button' => t('Test connection'),
        );
    }


    /**
     * Creates the form element for the test.
     *
     * This gets a form element with the basics in place. If your test needs input
     * parameters, add form elements here.
     *
     * @param $element
     *  A form element for the test's settings and button.
     *
     * @return
     *  The form element with the test's additions.
     */
    function testForm($element) {
        $element['params']['serverinfo'] = array(
            '#type' => 'checkbox',
            '#title' => t('See service response'),
        );
        return $element;
    }

    /**
     * Execute the test.
     *
     * Connection test handlers should return the raw data they got back from the
     * connection for display to the user.
     *
     * @param $connection
     *  The connection handler.
     * @param $button_form_values
     *  The form values for the test form element. The values for elements added
     *  to the form are in $button_form_values['params'].
     *
     * @return
     *  Data from the remote connection. This is output to the form as raw data.
     */
    function test($connection, &$button_form_values) {
        try {
            $check = $connection->serverCheck($button_form_values['params']['serverinfo']);
        }
        catch (Exception $e) {
            drupal_set_message(t('Could not connect to the remote site, got error message "@message".', array(
                '@message' => $e->getMessage(),
            )), 'warning');
            return;
        }
        if (is_array($check)) {
            drupal_set_message(t('Sucessfully connected in to the remote. '
                . 'You can find details '
                . 'about the cookie respository SERVER below.'));
            if(module_exists('devel')){
                dpm($check);
                $check = '';
            }
        }
        else {
            return $check;
            }

    }

}

/**
 * Test node load from a Drupal Services REST connection.
 */
class ClientsConnectionMultiSiteCookieRESTCookieRetrieve implements ClientsConnectionTestingInterface {

    /**
     * The labels for the test.
     */
    function testLabels() {
        return array(
            'label' => t('Cookie retrieval'),
            'description' => t('Load cookie information from remote service.'),
            'button' => t('Load cookie'),
        );
    }

    /**
     * Creates the form element for the test.
     *
     * This gets a form element with the basics in place. If your test needs input
     * parameters, add form elements here.
     *
     * @param $element
     *  A form element for the test's settings and button.
     *
     * @return
     *  The form element with the test's additions.
     */
    function testForm($element) {
        $element['params']['cid'] = array(
            '#type' => 'textfield',
            '#title' => t('Cookie ID'),
            '#size' => 30,
            '#required' => TRUE,
        );

         $element['params']['serverinfo'] = array(
            '#type' => 'checkbox',
            '#title' => t('See service response'),
        );
        return $element;
    }

    /**
     * Execute the test.
     *
     * Connection test handlers should return the raw data they got back from the
     * connection for display to the user.
     *
     * @param $connection
     *  The connection handler.
     * @param $button_form_values
     *  The form values for the test form element. The values for elements added
     *  to the form are in $button_form_values['params'].
     *
     * @return
     *  Data from the remote connection. This is output to the form as raw data.
     */
    function test($connection, &$button_form_values) {

        // Must be cast to integer for faffiness of XMLRPC and Services.
        $cookie_id = $button_form_values['params']['cid'];

        try {
            $response = $connection->retrieveCookie( $cookie_id, 'GET', $button_form_values['params']['serverinfo']);
        }
        catch (Exception $e) {
            drupal_set_message(t('Could not retrieve a node from the remote site, got error message "@message".', array(
                '@message' => $e->getMessage(),
            )), 'warning');
            return;
        }

        if (is_array($response)) {
            drupal_set_message(t('Sucessfully connected in to the remote. '
                . 'You can find details '
                . 'about the cookie respository SERVER below.'));
            if(module_exists('devel')){
                dpm($response);
                $cookie_data = '';
                return;
            } else {
                return $response;
            }
        } else {
            return $response;
        }

    }

}

/**
 * Test entity creation on a Drupal Services connection.
 */
class ClientsConnectionMultiSiteCookieRESTCookieCreate implements ClientsConnectionTestingInterface {

    /**
     * The labels for the test.
     *
     * (This is because it would seem you can't define class variables using
     * expressions.)
     */
    function testLabels() {
        return array(
            'label' => t('Create a cookie.'),
            'description' => t('Create a cookie on the remote site from an array of data.'),
            'button' => t('Create'),
        );
    }

    /**
     * Creates the form element for the test.
     *
     * This gets a form element with the basics in place. If your test needs input
     * parameters, add form elements here.
     *
     * @param $element
     *  A form element for the test's settings and button.
     *
     * @return
     *  The form element with the test's additions.
     */
    function testForm($element) {

       //provide some json examples
       $sample_data = '{
"_id": "YOUR COOKIE ID",
"type": "cookie",
"cck": false,
"translation": {
"en": {
"default": true,
"name": "MY COOKIE HUMAN NAME",
"description": "My cookie description."
}
},
"sites": [
"mysiteurl"
]
}';
        $element['params']['data'] = array(
            '#type' => 'textarea',
            '#rows' => 10,
            '#title' => t('Data'),
            '#description' => t('The POST data to pass for the creation of the new cookie.') . '<br>'
                . t('Sample data:') . '<br>'
                . "<pre>$sample_data</pre>",
        );

        return $element;
    }

    /**
     * Execute the test.
     *
     * Connection test handlers should return the raw data they got back from the
     * connection for display to the user.
     *
     * @param $connection
     *  The connection handler.
     * @param $button_form_values
     *  The form values for the test form element. The values for elements added
     *  to the form are in $button_form_values['params'].
     *
     * @return
     *  Data from the remote connection. This is output to the form as raw data.
     */
    function test($connection, &$button_form_values) {

       //fetch submited data object
       $data = drupal_json_decode($button_form_values['params']['data']);

        if (module_exists('devel')) {
            dpm($data, 'POST data');
            $json_error = json_last_error();
            if ($json_error != JSON_ERROR_NONE) {
                dpm($json_error, 'JSON error');
            }
        }

        try {
            $result = $connection->makeCookieRequest('POST', $data);
        }

        catch (Exception $e) {
            drupal_set_message($e->getMessage(), 'warning');
            //dsm($e);

            return;
        }
        return $result;
    }

}

/**
 * Test a generic REST request.
 */
class ClientsConnectionDrupalRESTTestGeneric implements ClientsConnectionTestingInterface {

    /**
     * The labels for the test.
     */
    function testLabels() {
        return array(
            'label' => t('Test a generic request'),
            'description' => t('Test a generic request by specifying the method, service, and resource.'),
            'button' => t('Execute'),
        );
    }

    /**
     * Creates the form element for the test.
     *
     * This gets a form element with the basics in place. If your test needs input
     * parameters, add form elements here.
     *
     * @param $element
     *  A form element for the test's settings and button.
     *
     * @return
     *  The form element with the test's additions.
     */
    function testForm($element) {
        $element['params']['method'] = array(
            '#type' => 'select',
            '#title' => t('Method'),
            '#options' => drupal_map_assoc(array(
                'GET',
                'POST',
                'PUT',
            )),
            '#required' => TRUE,
        );

        $entity_types = array_keys(entity_get_info());
        sort($entity_types);
        $entity_type_options = drupal_map_assoc($entity_types);
        $entity_type_options['_text'] = t('- Other -');

        $element['params']['entity'] = array(
            '#type' => 'select',
            '#title' => t('Entity type'),
            '#description' => t('The entity type to act on; i.e., the resource.'),
            '#options' => $entity_type_options,
            '#required' => FALSE,
        );

        $element['params']['entity_text'] = array(
            '#type' => 'textfield',
            '#title' => t('Entity type'),
            '#description' => t('The entity type to act on, if not in the list above.'),
            '#required' => FALSE,
        );

        $element['params']['entity_prefix'] = array(
            '#type' => 'checkbox',
            '#title' => t('Prefix entity type for Services Entity resource'),
            '#description' => t("Add the 'entity_' prefix to the entity type, for use with entity resources defined by Services Entity module."),
            '#required' => FALSE,
        );

        $element['params']['path'] = array(
            '#type' => 'textfield',
            '#title' => t('Path suffix'),
            '#description' => t('The remainder of the path, e.g., the entity ID, the entity ID and the action, etc.'),
        );

        $element['params']['data'] = array(
            '#type' => 'textarea',
            '#title' => t('Data'),
            '#description' => t('The POST or PUT data to pass, as a JSON array.'),
        );
        $element['params']['data_type'] = array(
            '#type' => 'radios',
            '#title' => t('Data type'),
            '#description' => t('The type of the data.'),
            '#options' => array(
                'json'  => 'JSON',
                'php'   => 'PHP array',
            ),
        );

        return $element;
    }

    /**
     * Execute the test.
     *
     * Connection test handlers should return the raw data they got back from the
     * connection for display to the user.
     *
     * @param $connection
     *  The connection handler.
     * @param $button_form_values
     *  The form values for the test form element. The values for elements added
     *  to the form are in $button_form_values['params'].
     *
     * @return
     *  Data from the remote connection. This is output to the form as raw data.
     */
    function test($connection, &$button_form_values) {
        if (!empty($button_form_values['params']['entity_text'])) {
            $entity_type = $button_form_values['params']['entity_text'];
        }
        else {
            $entity_type = $button_form_values['params']['entity'];
        }

        if ($button_form_values['params']['entity_prefix']) {
            $resource = 'entity_' . $entity_type;
        }
        else {
            $resource = $entity_type;
        }

        if (!empty($button_form_values['params']['path'])) {
            $path = $resource . '/' . $button_form_values['params']['path'];
        }
        else {
            $path = $resource;
        }
        $method = $button_form_values['params']['method'];

        if (!empty($button_form_values['params']['data'])) {
            if ($button_form_values['params']['data_type'] == 'json') {
                $data = drupal_json_decode($button_form_values['params']['data']);
            }
            else {
                eval('$data = ' . $button_form_values['params']['data'] . ';');
            }
        }
        else {
            $data = array();
        }

        drupal_set_message(t("Making @method request to @path.", array(
            '@method' => $method,
            '@path' => $path,
        )));

        if (module_exists('devel')) {
            dpm($data, 'Data');
            $json_error = json_last_error();
            if ($json_error != JSON_ERROR_NONE) {
                dpm($json_error, 'JSON error');
            }
        }

        try {
            $result = $connection->makeRequest($path, $method, $data);
        }
        catch (Exception $e) {
            drupal_set_message(t('Could not access the remote site, got error message "@message".', array(
                '@message' => $e->getMessage(),
            )), 'warning');

            return;
        }

        return $result;
    }

}
