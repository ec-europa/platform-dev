<?php

/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\PoetryCallback.
 */

namespace Drupal\tmgmt_poetry\Services;

use Drupal\tmgmt_poetry\Services\TmgmtPoetryIntegration;

/**
 * Class PoetryCallback.
 *
 * @package Drupal\tmgmt_poetry\Services
 */
class PoetryCallback {
  // Constants.
  const POETRY_REQUESTS_PATH = 'public://tmgmt_file/dgt_responses/';
  const POETRY_MAIN_JOB_PREFIX = 'MAIN_%_POETRY_%';
  const POETRY_REQUEST_WD_TYPE = 'PoetryCallback: Request';
  const POETRY_ERROR_MESSAGE_WD_TYPE = 'PoetryCallback: Error message';
  const POETRY_REQUEST_TYPE_STATUS = 'status';
  const POETRY_REQUEST_TYPE_TRANSLATION = 'translation';
  const POETRY_REQUEST_TYPE_UNKNOWN = 'unknown';

  // Poetry system settings.
  private $settings;

  // Request arguments.
  private $reqUser;
  private $reqPassword;
  private $reqMessage;

  // Helper properties.
  public $xmlReqObj;
  public $xmlRefArray;
  public $xmlReference;

  /**
   * PoetryCallback constructor.
   */
  public function __construct() {
    $this->setPoetrySettings();
  }

  /**
   * Sets Poetry settings.
   */
  public function setPoetrySettings() {
    $this->settings = variable_get("poetry_service");
  }

  /**
   * Gets Poetry settings.
   */
  public function getPoetrySettings() {
    return $this->settings;
  }

  /**
   * FPFIS Poetry Integration WSDL option callback.
   *
   * Main callback method which is called from PoetryListener.
   *
   * @param string $user
   *    Username from SOAP request.
   * @param string $password
   *    Password from SOAP request.
   * @param string $message
   *    SOAP request message content.
   *
   * @return string
   *    XML response for callback function.
   */
  public function FPFISPoetryIntegrationRequest($user, $password, $message) {
    // Setting up request properties to reuse them in the class methods.
    $this->setRequestArguments($user, $password, $message);
    // Log Poetry callback request to watchdog.
    $this->logToWatchdog(
      self::POETRY_REQUEST_WD_TYPE,
      filter_xss(htmlentities($message)),
      WATCHDOG_DEBUG
    );

    // Checking credentials and processing request.
    if ($this->checkRequestCredentials($user, $password)) {
      // Setting up helper properties.
      $this->setCallbackProperties();

      // Processing request and preparing response.
      return $this->processRequest();
    }

    // Returning XML error message in case of invalid credentials.
    return $this->generatePoetryCallbackAnsweer($this->xmlRefArray, -1, t('ERROR: Failed authentication'));
  }

  /**
   * Main function which process request and returns XML response.
   *
   * @return string
   *    XML response for Poetry callback function.
   */
  private function processRequest() {
    // Checking request type.
    $request_type = $this->getRequestType();

    // Processing request according to given type.
    switch ($request_type) {
      case self::POETRY_REQUEST_TYPE_STATUS:
        return $this->processStatusRequest();

      case self::POETRY_REQUEST_TYPE_TRANSLATION:
        return $this->processTranslationRequest();

      default:
        break;
    }
  }

  /**
   * Provides Poetry notice request type.
   *
   * @return string
   *    Returns request type.
   */
  private function getRequestType() {

    if ((string) $this->xmlReqObj['type'] === self::POETRY_REQUEST_TYPE_STATUS) {

      return self::POETRY_REQUEST_TYPE_STATUS;
    }

    if ((string) $this->xmlReqObj['type'] === self::POETRY_REQUEST_TYPE_TRANSLATION) {

      return self::POETRY_REQUEST_TYPE_TRANSLATION;
    }

    return self::POETRY_REQUEST_TYPE_UNKNOWN;
  }

  /**
   * Method for processing Poetry notification about statuses.
   *
   * Look in to Poetry documentation - unit 3.1 page 16 & unit 4.1 page 36.
   */
  private function processStatusRequest() {

  }

  /**
   * Method for processing Poetry notification of sanding back the translation.
   *
   * Look in to Poetry documentation - unit 4.2 page 38.
   */
  private function processTranslationRequest() {

  }

  /**
   * Helper method for fetching main_job object.
   *
   * @return bool|\TMGMTJob
   *    FALSE or TMGMTJob object.
   */
  private function getMainJob() {
    $main_reference = self::POETRY_MAIN_JOB_PREFIX . $this->xmlReference;
    $main_id = TmgmtPoetryIntegration::getMainJobId($main_reference);
    // Handling the case where we can't find the corresponding job.
    if ($main_id) {
      return tmgmt_job_load($main_id['tjid']);
    }

    return FALSE;
  }

  /**
   * Sets additional properties to simplify data processing.
   */
  private function setCallbackProperties() {
    $xml_object = simplexml_load_string($this->reqMessage);
    $this->xmlReqObj = $xml_object->request;
    $this->xmlRefArray = (array) $this->xmlReqObj->demandeId;
    $this->xmlReference = implode("/", (array) $this->xmlRefArray);
  }

  /**
   * Sets request arguments to use them integrally.
   */
  private function setRequestArguments($user, $password, $message) {
    $this->reqUser = $user;
    $this->reqPassword = $password;
    $this->reqMessage = $message;
  }

  /**
   * Checks credentials of the current SOAP request.
   *
   * @param string $user
   *    Username.
   * @param string $password
   *    Password.
   *
   * @return bool
   *    TRUE / FALSE depends on result of comparison.
   */
  private function checkRequestCredentials($user, $password) {
    return ($this->settings['callback_user'] === $user
      && $this->settings['callback_password'] === $password);
  }

  /**
   * Dumps current SOAP request to the file.
   */
  public function dumpRequestToFile() {
    $path = self::POETRY_REQUESTS_PATH . $this->xmlReference . '.xml';
    $dirname = dirname($path);

    if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
      file_unmanaged_save_data($this->reqMessage, $path);
    }
  }

  /**
   * Logs events to the watchdog.
   */
  public function logToWatchdog($type, $message, $severity) {
    watchdog(
      $type,
      $message,
      $severity
    );
  }

  /**
   * Generates XML response based on given parameters.
   *
   * @param array $demande_id
   *    An array with request identifiers.
   * @param int $code
   *    Code integer.
   * @param string $message
   *    Message string.
   *
   * @return string
   *    XML response generated based on template.
   */
  public function generatePoetryCallbackAnsweer($demande_id, $code, $message) {
    return theme('poetry_callback_answer', [
      'demande_id' => $demande_id,
      'code' => $code,
      'message' => $message,
    ]);
  }

}
