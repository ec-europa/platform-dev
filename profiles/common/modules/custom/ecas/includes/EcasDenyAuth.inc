<?php

/**
 * @file
 * Contains EcasDenyAuth.
 */

/**
 * Contains logic to check and manage authentication denie.
 */
class EcasDenyAuth {

  /**
   * This variable stores current login process's status to check and manage.
   *
   * @var string
   * @access private
   */
  private $status;

  /**
   * This variable stores user language object.
   *
   * @var object
   * @access private
   */
  private $language;

  /**
   * This variable stores warning message arguments.
   *
   * @var array
   * @access private
   */
  private $messageArgs;

  /**
   * This variable stores redirection attributes.
   *
   * @var array
   * @access public
   */
  public $redirectionAttributes;

  /**
   * Construct EcasDenyAuth object.
   */
  public function __construct(array $props = array()) {
    $this->language = isset($props['language']) ? $props['language'] : NULL;
    $this->messageArgs = isset($props['message_args']) ? $props['message_args'] : array();

    // Set redirection attributes.
    $this->setRedirectionAttributes();
  }

  /**
   * Main method proceeding to login status evaluation and user redirection.
   *
   * If the authentication has to be denied, session is destroyed
   * and user is redirected to an informative page.
   *
   * @param string $status
   *   The login status to check.
   * @param bool $process
   *   Indicates if authentication should be denied or not.
   * @param array $extend
   *   (Optional) If provided, authentication status evaluation can
   *   be extended using provided values.
   */
  public function check($status, $process, array $extend = array()) {
    $this->status = $status;
    $this->process = $process;
    $this->extend = $extend;

    $denieAuth = $this->evaluateStatus();

    if ($denieAuth) {

      $this->redirect();
    }
  }

  /**
   * Private method which evaluate status.
   *
   * The evaluation can be extended with advanced check steps
   * or only based on $process value.
   */
  private function evaluateStatus() {

    $denieAuth = FALSE;

    switch ($this->status) {

      case 'authentication_strength':

        $denieAuth = ($this->userRolesAreWhitelisted()) ? FALSE : !$this->loginStrengthIsCompliant();

        break;

      case 'eu_login_authentication':
      case 'eu_login_account_attributes':
      case 'e-mail_defined':
      case 'e-mail_exists':
      case 'social_login_role':
      case 'account_status':

        $denieAuth = $this->process;

        break;

    }

    return $denieAuth;
  }

  /**
   * Private method checking if current user has only whitelisted roles.
   *
   * First checks if the functionality should be enabled.
   */
  private function userRolesAreWhitelisted() {
    $userRoles = $this->extend['user_roles'];
    $whitelistedRoles = variable_get('ecas_whitelisted_user_roles', NULL);
    $userIsWhitelisted = !isset($whitelistedRoles) ? TRUE : empty(array_diff($userRoles, $whitelistedRoles));

    return $userIsWhitelisted;
  }

  /**
   * Private method checking EU Login authentication strength.
   */
  private function loginStrengthIsCompliant() {
    $loginStrengths = count($this->extend['login_strengths']['strength']);

    return ($loginStrengths > 1) ? TRUE : FALSE;
  }

  /**
   * Private method setting redirection attributes.
   */
  private function setRedirectionAttributes() {

    $this->redirectionAttributes = array(
      'eu_login_authentication' => array(
        'page_argument' => ECAS_WARNING_REASON_UNKNOWN,
        'message' => 'ECAS authentication failed for unexpected reasons.',
      ),
      'eu_login_account_attributes' => array(
        'page_argument' => ECAS_WARNING_REASON_INCOMPLETE_USER,
        'message' => 'Login process failed for "%ecas_name" because of an EU login user with missing required attributes.',
      ),
      'e-mail_defined' => array(
        'page_argument' => ECAS_WARNING_REASON_NO_EMAIL,
        'message' => 'Login denied for %ecas_name because it has no e-mail defined.',
      ),
      'e-mail_exists' => array(
        'page_argument' => ECAS_WARNING_REASON_EXISTING_EMAIL,
        'message' => 'Login denied for %ecas_name because the e-mail is already used by another account.',
      ),
      'social_login_role' => array(
        'page_argument' => ECAS_WARNING_REASON_SOCIAL,
        'message' => 'Login denied for %ecas_name because the account has more than authenticated role.',
      ),
      'account_status' => array(
        'page_argument' => ECAS_WARNING_REASON_BLOCKED,
        'message' => 'Login denied for %ecas_name because the account is not active yet.',
      ),
      'authentication_strength' => array(
        'page_argument' => ECAS_WARNING_TFA_REQUIRED,
        'message' => "Login denied for %ecas_name because his account requires a stronger EU Login authentication.",
      ),
    );
  }

  /**
   * Triggers the redirection to the ecas warning page.
   *
   * @param array $data
   *   (Optional) Array of variables used in case of this method
   *   is called directly from outside class scope.
   *
   * @see drupal_goto()
   */
  public function redirect(array $data = array()) {
    $message = (!isset($data['message'])) ? $this->redirectionAttributes[$this->status]['message'] : $data['message'];
    $path_page_argument = (!isset($data['page_argument'])) ? $this->redirectionAttributes[$this->status]['page_argument'] : $data['page_argument'];
    $language = (empty($this->language)) ? language_default() : $this->language;

    if ($message != '') {
      watchdog('user', $message, $this->messageArgs, WATCHDOG_ERROR);
    }

    $this->endSession();

    // Ensure that the user is correctly redirected to warning page because
    // if drupal_goto() detects an internal path in destination parameter, it
    // will use it instead of the submitted parameters, see function code.
    if (isset($_REQUEST['destination'])) {
      unset($_REQUEST['destination']);
    }
    if (isset($_REQUEST['edit']['destination'])) {
      unset($_REQUEST['edit']['destination']);
    }

    drupal_goto('eulogin_warning/' . $path_page_argument, array('language' => $language));
  }

  /**
   * Public method ending session and set global variable $user to anonymous.
   */
  public static function endSession() {
    global $user;

    session_destroy();

    $user = drupal_anonymous_user();
  }

  /**
   * Public method allowing to refresh object properties.
   */
  public function set(array $props) {
    $this->language = isset($props['language']) ? $props['language'] : $this->language;
    $this->messageArgs = isset($props['message_args']) ? $props['message_args'] : $this->messageArgs;
  }

}
