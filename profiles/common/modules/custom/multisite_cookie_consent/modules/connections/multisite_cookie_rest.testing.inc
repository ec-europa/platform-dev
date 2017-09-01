<?php
// @codingStandardsIgnoreFile: NEPT-198 - Module to be removed
/**
 * @file
 * Contains classes for Client connection testing.
 */

/**
 * Test basic connection.
 */
class MultisiteCookieRestClientsConnectionMultiSiteCookieRESTServerCheck implements ClientsConnectionTestingInterface {

  /**
   * The labels for the test.
   *
   * This is because it would seem you can't define class variables using
   * expressions.
   */
  public function testLabels() {
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
   * @param array $element
   *   A form element for the test's settings and button.
   *
   * @return array
   *   The form element with the test's additions.
   */
  public function testForm(array $element) {
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
   * @param object $connection
   *   The connection handler.
   * @param array $button_form_values
   *   The form values for the test form element. The values for elements added
   *   to the form are in $button_form_values['params'].
   *
   * @return mixed
   *   Data from the remote connection. This is output to the form as raw data.
   *   Might also return nothing.
   */
  public function test($connection, array &$button_form_values) {
    try {
      $check = $connection->serverCheck($button_form_values['params']['serverinfo']);
    }
    catch (Exception $e) {
      drupal_set_message(format_string('Could not connect to the remote site, got error message "@message".', array(
        '@message' => $e->getMessage(),
      )), 'warning');
      return;
    }
    if (is_array($check)) {
      drupal_set_message('Successfully connected in to the remote. You can find details about the cookie repository SERVER below.');
      debug($check);
    }
    else {
      return $check;
    }
  }

}

/**
 * Test node load from a Drupal Services REST connection.
 */
class MultisiteCookieRestClientsConnectionMultiSiteCookieRESTCookieRetrieve implements ClientsConnectionTestingInterface {

  /**
   * The labels for the test.
   */
  public function testLabels() {
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
   * @param array $element
   *   A form element for the test's settings and button.
   *
   * @return mixed
   *   The form element with the test's additions.
   */
  public function testForm(array $element) {
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
   * @param object $connection
   *   The connection handler.
   * @param array $button_form_values
   *   The form values for the test form element. The values for elements added
   *   to the form are in $button_form_values['params'].
   *
   * @return mixed
   *   Data from the remote connection. This is output to the form as raw data.
   */
  public function test($connection, array &$button_form_values) {
    // Must be cast to integer for faffiness of XMLRPC and Services.
    $cookie_id = $button_form_values['params']['cid'];

    try {
      $response = $connection->retrieveCookie($cookie_id, 'GET', $button_form_values['params']['serverinfo']);
    }
    catch (Exception $e) {
      drupal_set_message(format_string('Could not retrieve a node from the remote site, got error message "@message".', array(
        '@message' => $e->getMessage(),
      )), 'warning');
      return;
    }

    if (is_array($response)) {
      drupal_set_message('Successfully connected in to the remote. You can find details about the cookie repository SERVER below.');
      return $response;
    }
    else {
      return $response;
    }
  }

}

/**
 * Test entity creation on a Drupal Services connection.
 */
class MultisiteCookieRestClientsConnectionMultiSiteCookieRESTCookieCreate implements ClientsConnectionTestingInterface {

  /**
   * The labels for the test.
   *
   * This is because it would seem you can't define class variables using
   * expressions.
   */
  public function testLabels() {
    return array(
      'label' => t('Create a cookie.'),
      'description' => t('Create a cookie on the remote site from an array of data.'),
      'button' => t('Create cookie'),
    );
  }

  /**
   * Creates the form element for the test.
   *
   * This gets a form element with the basics in place. If your test needs input
   * parameters, add form elements here.
   *
   * @param array $element
   *   A form element for the test's settings and button.
   *
   * @return array
   *   The form element with the test's additions.
   */
  public function testForm(array $element) {
    // Provide some json examples.
    $sample_data = '{
    "_id": "cookies_",
    "type": "cookie",
    "cck": false,
    "translation": {
        "en": {
            "default": false,
            "name": "Cookie EN",
            "description": "English cookie description"
        },
        "fr": {
            "default": true,
            "name": "Cookie FR",
            "description": "French cookie description"
        },
        "de": {
            "default": false,
            "name": "Cookie DE",
            "description": "Cookie german description"
        },
        "pt": {
            "default": false,
            "name": "Cookie PT",
            "description": "cookie_portugal_description
        }
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
   * @param object $connection
   *   The connection handler.
   * @param array $button_form_values
   *   The form values for the test form element. The values for elements added
   *   to the form are in $button_form_values['params'].
   *
   * @return mixed
   *   Data from the remote connection. This is output to the form as raw data.
   */
  public function test($connection, array &$button_form_values) {
    // Fetch submitted data object.
    $data = drupal_json_decode($button_form_values['params']['data']);

    $json_error = json_last_error();
    if ($json_error != JSON_ERROR_NONE) {
      debug($json_error, 'JSON error');
    }

    try {
      $result = $connection->makeCookieRequest('POST', $data);
    }

    catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'warning');
      return;
    }
    return $result;
  }

}


/**
 * Test a Delete cookie.
 */
class MultisiteCookieRestClientsConnectionMultiSiteCookieRESTCookieDelete implements ClientsConnectionTestingInterface {

  /**
   * The labels for the test.
   */
  public function testLabels() {
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
   * @param array $element
   *   A form element for the test's settings and button.
   *
   * @return array
   *   The form element with the test's additions.
   */
  public function testForm(array $element) {
    $element['params']['cid'] = array(
      '#type' => 'textfield',
      '#title' => t('Cookie ID'),
      '#description' => t('Cookie id.'),
      '#required' => TRUE,
    );

    $element['params']['revision'] = array(
      '#type' => 'textfield',
      '#title' => t('Revision'),
      '#description' => t('Insert cookie revision you want to delete.'),
      '#required' => TRUE,
    );

    return $element;
  }

  /**
   * Execute the test.
   *
   * Connection test handlers should return the raw data they got back from the
   * connection for display to the user.
   *
   * @param object $connection
   *   The connection handler.
   * @param array $button_form_values
   *   The form values for the test form element. The values for elements added
   *   to the form are in $button_form_values['params'].
   *
   * @return mixed
   *   Data from the remote connection. This is output to the form as raw data.
   */
  public function test($connection, array &$button_form_values) {
    $method = 'DELETE';
    // @todo Variables $cid and $revision are unused in their scope.
    $cid = $button_form_values['params']['cid'];
    $revision = $button_form_values['params']['revision'];

    // @todo This refers to a variable $path which is not defined.
    drupal_set_message(format_string("Making @method request to @path.", array(
      '@method' => $method,
      '@path' => $path,
    )));

    // @todo This refers to a variable $data which is not defined.
    debug($data, 'Data');
    $json_error = json_last_error();
    if ($json_error != JSON_ERROR_NONE) {
      debug($json_error, 'JSON error');
    }

    try {
      $result = $connection->makeRequest($path, $method, $data);
    }
    catch (Exception $e) {
      drupal_set_message(format_string('Could not access the remote site, got error message "@message".', array(
        '@message' => $e->getMessage(),
      )), 'warning');

      return;
    }

    return $result;
  }

}
