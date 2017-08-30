<?php

/**
 * @file
 * Contains classes for Client connections handlers.
 *
 * This is extending the base class from the Web Service Clients module.
 *
 * @see https://www.drupal.org/project/clients
 */

/**
 * Class for Drupal client connections, REST D7.
 */
class clients_connection_multisite_cookie_rest extends clients_connection_base {

  /**
   * Declare an array of properties which should be treated as credentials.
   *
   * This lets the credentials storage plugin know which configuration
   * properties to take care of.
   *
   * @return array
   *   A flat array of property names.
   */
  public function credentialsProperties() {
    return array('username', 'password');
  }

  /**
   * Extra form elements specific to a class's edit form.
   *
   * @see clients_connection_form()
   * @see clients_connection_form_submit()
   */
  public function connectionSettingsFormAlter(&$form, &$form_state) {
    $form['endpoint']['#description'] = t('Remote service URL e.g. http://mysite.com/service-endpoint');

    // There is no configuration other than the credentials.
    $form['credentials']['username'] = array(
      '#type' => 'textfield',
      '#title' => t('Service username'),
      '#size' => 30,
      '#maxlength' => 60,
      '#attributes' => array('autocomplete' => 'off'),
      '#description' => t('This should be same as the username on the server you are connecting to.'),
      '#required' => TRUE,
    );

    $password_exists = isset($this->credentials['password']);
    $password_description = $password_exists
      ? t('This should be same as the password on the server you are connecting to. Leave blank unless you need to change this.')
      : t('This should be same as the password on the server you are connecting to.');
    $form['credentials']['password'] = array(
      '#type' => 'password',
      '#title' => t('Service password'),
      '#size' => 30,
      '#maxlength' => 60,
      '#attributes' => array('autocomplete' => 'off'),
      '#description' => $password_description,
      '#required' => !$password_exists,
    );
  }

  /**
   * Submit handler for saving/updating connections of this class.
   *
   * @see clients_connection_form_submit()
   */
  public function connectionSettingsForm_submit($form, &$form_state) {
    // This is here to show an example of how this method works.
    parent::connectionSettingsForm_submit($form, $form_state);
    // Set our variable with Connection machine name.
    variable_set('multisite_cookie_connection', $form['name']['#default_value']);
  }

  /**
   * Common helper for reacting to an error from a REST call.
   *
   * Gets the error from the response, logs the error message, and throws an
   * exception, which should be caught by the module making use of the Clients
   * connection API.
   *
   * @param object $response
   *   The REST response data, decoded.
   *
   * @throws Exception
   *   Thrown when the response code is anything other than '200' or '201'.
   */
  public function handleRestError($response) {

    if (!in_array($response->code, array("200", "201"))) {

      watchdog('clients', 'Error with REST request. Error was code @code with error "@error" and message "@message".', array(
        '@code'     => $response->code,
        '@error'    => $response->error,
        '@message'  => isset($response->status_message) ? filter_xss($response->status_message) : '(no message)',
      ));

      throw new Exception(format_string("Clients connection error, got message '@message'.", array(
        '@message' => isset($response->status_message) ? filter_xss($response->status_message) : $response->error,
      )), $response->code);
    }
  }

  /**
   * Checks cookie remote server.
   *
   * @param bool $server_info
   *   If you need a detailed server info pass TRUE to this variable.
   *
   * @return mixed
   *   The full data returned from the remote call or TRUE / FALSE value, or
   *   nothing in case $server_info is FALSE.
   *
   * @throws \Exception
   *   Thrown when the response JSON cannot be decoded successfully.
   */
  public function serverCheck($server_info = FALSE) {
    $options = array(
      'headers' => array(
        'Content-Type' => 'application/json',
        'Cache-Control' => 'no-cache',
      ),
      'method'  => 'GET',
    );
    $response = drupal_http_request($this->endpoint, $options);
    // Check if response was successful.
    $this->handleRestError($response);
    // Getting data.
    $result = drupal_json_decode($response->data);
    // It's possible for the response to have a 200, but the data to be
    // malformed.
    if (!is_array($result) || json_last_error() != JSON_ERROR_NONE) {
      $args = array('@data' => $response->data);
      throw new Exception(format_string("Clients connection error logging in. Data received was: '@data'.", $args), $response->code);
    }
    if ($server_info == TRUE && $response->code == 200) {
      return $result;
    }
    elseif ($server_info == FALSE && $response->code == 200) {
      drupal_set_message(t('Remote service is alive! To view the server response please check the "See service response".'));
    }
    else {
      return FALSE;
    }
  }

  /**
   * Retrieves a cookie.
   *
   * @param string $cid
   *   The cookie ID.
   * @param string $method
   *   Method to send to remote service.
   * @param bool $server_info
   *   Display server response.
   *
   * @return bool|mixed
   *   The cookie, or FALSE if no cookie was returned.
   *
   * @throws \Exception
   *   Thrown when the response JSON cannot be decoded successfully.
   */
  public function retrieveCookie($cid, $method, $server_info = FALSE) {
    $options = array(
      'headers' => array(
        'Content-Type' => 'application/json',
        'Cache-Control' => 'no-cache',
      ),
      'method'  => $method,
    );

    $request_remote = $this->endpoint . '/cookies/' . $cid;
    $response = drupal_http_request($request_remote, $options);
    // Check if response was successful.
    $this->handleRestError($response);
    // Getting data.
    $result = drupal_json_decode($response->data);
    // It's possible for the response to have a 200, but the data to be
    // malformed.
    if (!is_array($result) || json_last_error() != JSON_ERROR_NONE) {
      $args = array('@data' => $response->data);
      throw new Exception(format_string("Clients connection error logging in. Data received was: '@data'.", $args), $response->code);
    }

    if ($server_info && in_array($response->code, array(200, 201))) {
      return $result;
    }
    elseif (!$server_info && in_array($response->code, array(200, 201))) {
      $message = t('Remote service is alive! To view the server response please check the "See service response".');
      drupal_set_message(t('%message'), array('%message' => $message));
      return;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Log in as the configured user.
   *
   * This requires the server type 'application/x-www-form-urlencoded' to be
   * enabled.
   *
   * @return mixed
   *   The full data returned from the remote call.
   *
   * @throws \Exception
   *   Thrown when the response JSON cannot be decoded successfully.
   */
  public function userLogin() {
    // Based on example code at http://drupal.org/node/910598.
    $this->credentialsLoad();

    $data = array(
      'username' => $this->credentials['username'],
      'password' => $this->credentials['password'],
    );
    $data = http_build_query($data, '', '&');

    $headers = array(
      'Accept' => 'application/json',
    );

    $options = array(
      'headers' => $headers,
      'method'  => 'POST',
      'data'    => $data,
    );

    $response = drupal_http_request($this->endpoint . '/user/login', $options);

    // Check if login was successful.
    $this->handleRestError($response);

    $data = json_decode($response->data);

    // It's possible for the response to have a 200, but the data to be
    // malformed. This happens for example when the remote site is running a
    // debugger.
    if (!is_object($data) || json_last_error() != JSON_ERROR_NONE) {
      $args = array('@data' => $response->data);
      throw new Exception(format_string("Clients connection error logging in. Data received was: '@data'.", $args), $response->code);
    }

    // Set our cookie for subsequent requests.
    $this->cookie = $data->session_name . '=' . $data->sessid;

    return $data;
  }

  /**
   * API function to request a remote resource.
   *
   * This function has a rubbish name and parameters for historical reasons:
   * XMLRPC connection classes were developed first.
   *
   * @param string $method
   *   The path of the remote resource to retrieve.
   * @param array $method_params
   *   A flat array of further parameters for the request. This should contain:
   *   - The HTTP method.
   *   - (optional) An array of data for the request, such as POST data.
   *
   * @return mixed
   *   Whatever is returned from the remote site.
   */
  public function callMethodArray($method, $method_params = array()) {
    $resource_path = $method;
    $http_method = array_shift($method_params);
    // The data array doesn't have to be present, so we have to fiddle about
    // to make sure we don't pass a NULL for it to makeRequest().
    if (count($method_params)) {
      $data = array_shift($method_params);
    }
    else {
      $data = array();
    }

    return $this->makeRequest($resource_path, $http_method, $data);
  }

  /**
   * Make a REST request.
   *
   * Examples:
   * - Retrieve a node: makeRequest('node/NID', 'GET');
   * - Update a node: makeRequest('node/NID', 'POST', $data);
   *
   * @param string $resource_path
   *   The path of the resource. Eg, 'node', 'node/1', etc.
   * @param string $http_method
   *   The HTTP method. One of 'GET', 'POST', 'PUT', 'DELETE'. For an
   *   explanation of how the HTTP method affects the resource request, see the
   *   Services documentation at http://drupal.org/node/783254.
   * @param array $data
   *   (Optional) An array of data to pass to the request.
   *
   * @return mixed
   *   The data from the request response.
   */
  public function makeRequest($resource_path, $http_method, $data = array()) {
    // Start by assuming we need to log in.
    $login_needed = TRUE;

    // If the cookie is already set, we don't need to log in.
    if (isset($this->cookie)) {
      $login_needed = FALSE;
    }

    // If the service is 'user/register' (or services_entity module's copy), we
    // need to be anonymous.
    // If you want to use this services as an authenticated user, then use the
    // 'user/create' service, of which this is an alias.
    if ($resource_path == 'user/register' || $resource_path == 'entity_user/register') {
      $login_needed = FALSE;

      // Zap any cookie we might have from a previous request.
      $this->cookie = NULL;
    }

    if ($login_needed) {
      $this->userLogin();
    }

    $data = http_build_query($data, '', '&');

    $headers = array(
      'Accept' => 'application/json',
      // Pass in the login cookie we received previously.
      'Cookie' => $this->cookie,
    );

    // Add a CSRF token if the method is one that requires it.
    $methods = array('GET', 'HEAD', 'OPTIONS', 'TRACE');
    $non_safe_method = !in_array($http_method, $methods) || $resource_path == 'user/token';
    if ($non_safe_method) {
      $headers['X-CSRF-Token'] = $this->getXcsrfToken();
    }

    $options = array(
      'headers' => $headers,
      'method'  => $http_method,
      'data'    => $data,
    );

    $response = drupal_http_request($this->endpoint . '/' . $resource_path, $options);

    $this->handleRestError($response);

    $result = json_decode($response->data);
    return $result;
  }

  /**
   * Get the X-CSRF token.
   *
   * This calls the remote site to get the token, and caches it, so that
   * multiple requests made with the same connection don't need to retrieve it
   * again.
   *
   * This expects the 'user/token' action resource to be enabled on the
   * endpoint. This only exists in Services 3.5 and later. We do not support
   * earlier versions.
   *
   * @return string
   *   The X-CSRF token.
   *
   * @throws \Exception
   *   An exception if the remote site does not return a token.
   */
  public function getXcsrfToken() {
    if (isset($this->CSRFToken)) {
      return $this->CSRFToken;
    }

    $headers = array(
      'Accept' => 'application/json',
      // Pass in the login cookie we received previously.
      'Cookie' => $this->cookie,
    );

    $options = array(
      'headers' => $headers,
      'method'  => 'POST',
    );

    $response = drupal_http_request($this->endpoint . '/user/token', $options);
    if ($response->code == 200) {
      $data = json_decode($response->data);
      $this->CSRFToken = $data->token;
      return $this->CSRFToken;
    }
    else {
      throw new Exception(t("Unable to get a CSRF token from the remote site."));
    }
  }

  /**
   * Make a REST request.
   *
   * @param string $http_method
   *   The HTTP method. One of 'GET', 'POST', 'PUT', 'DELETE'. For an
   *   explanation of how the HTTP method affects the resource request, see the
   *   Services documentation at http://drupal.org/node/783254.
   * @param array $data
   *   (Optional) An array of data to pass to the request.
   *
   * @return mixed
   *   The data from the request response.
   */
  public function makeCookieRequest($http_method, $data = array()) {
    // Adding site_name to $data array.
    $data['sites'] = _multisite_cookie_consent_site_name();

    // Convert data in query builder.
    $data = drupal_json_encode($data);
    // Headers.
    $headers = array(
      'Content-Type' => 'application/json',
      'Accept' => 'application/json',
    );

    // Bulid options.
    $options = array(
      'headers' => $headers,
      'method' => $http_method,
      'data' => $data,
    );
    // Create response and send request to remote service.
    $response = drupal_http_request($this->endpoint . '/cookies', $options);
    $this->handleRestError($response);
    $result = json_decode($response->data);
    return $result;
  }

  /**
   * Retrieves static page content.
   *
   * @param bool $server_info
   *   Unused.
   *
   * @return bool|mixed
   *   The request, or FALSE if an error occurred.
   *
   * @throws Exception
   *   Thrown if an error occurred during JSON decoding.
   */
  public function retrieveStatictext($server_info = FALSE) {
    $options = array(
      'headers' => array(
        'Content-Type' => 'application/json',
        'Cache-Control' => 'no-cache',
      ),
      'method'  => 'GET',
    );
    // Make cookie page request.
    $request_remote = $this->endpoint . '/notice';
    $response = drupal_http_request($request_remote, $options);
    // Check if response was successful.
    $this->handleRestError($response);
    // Getting data, lets not convert this time to array.
    $result = $response->data;
    // It's possible for the response to have a 200, but the data to be
    // malformed.
    if (!($result) || json_last_error() != JSON_ERROR_NONE) {
      $args = array('@data' => $response->data);
      throw new Exception(format_string("Clients connection error logging in. Data received was: '@data'.", $args), $response->code);
    }

    // @todo The second condition of the construct is identical to the first
    //   one.
    if (in_array($response->code, array(200, 201))) {
      return $result;
    }
    elseif (in_array($response->code, array(200, 201))) {
      $message = t('Remote service is alive! To view the server response please check the "See service response".');
      drupal_set_message(t('%message'), array('%message' => $message));
      return;
    }
    else {
      return FALSE;
    }
  }

}
