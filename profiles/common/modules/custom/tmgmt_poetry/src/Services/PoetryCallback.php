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
  const REQUESTS_PATH = 'public://tmgmt_file/dgt_responses/';
  const MAIN_JOB_PREFIX = 'MAIN_';
  // Watchdog entry types.
  const REQUEST_WD_TYPE = 'PoetryCallback: Request';
  const ERROR_MESSAGE_WD_TYPE = 'PoetryCallback: Error message';
  // Request types.
  const REQUEST_TYPE_STATUS = 'status';
  const REQUEST_TYPE_TRANSLATION = 'translation';
  const REQUEST_TYPE_UNKNOWN = 'unknown';
  // Status types.
  const REQUEST_STATUS_TYPE = 'request';
  const DEMANDE_STATUS_TYPE = 'demande';
  const ATTRIBUTION_STATUS_TYPE = 'attribution';
  const CORRECTION_STATUS_TYPE = 'correction';


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

  // Jobs.
  private $jobs;

  // Poetry translator.
  private $translator;

  // Drupal languages.
  private $languages;

  /**
   * PoetryCallback constructor.
   */
  public function __construct($settings) {
    $this->settings = $settings;
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
    // $response = PoetryResponse::getInstance();
    // return $response->build($settings);
    // Setting up request properties to reuse them in the class methods.
    $this->setRequestArguments($user, $password, $message);
    // Log Poetry callback request to watchdog.
    $this->logToWatchdog(
      self::REQUEST_WD_TYPE,
      filter_xss(htmlentities($message)),
      WATCHDOG_DEBUG
    );

    // Checking credentials and processing request.
    if ($this->checkRequestCredentials($user, $password)) {
      // Setting up helper properties.
      $this->setCallbackProperties();
      // Checking if there is at least one job related to given reference.
      // to be removed !!!
      $this->xmlReference = 'ABCD/2016/1234/0/1/TRA';
      if ($this->jobs = $this->getAllJobs()) {
        // Processing request and preparing response.
        return $this->processRequest();
      }

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
      case self::REQUEST_TYPE_STATUS:
        return $this->processStatusRequest();

      case self::REQUEST_TYPE_TRANSLATION:
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
    if ((string) $this->xmlReqObj['type'] === self::REQUEST_TYPE_STATUS) {
      return self::REQUEST_TYPE_STATUS;
    }
    if ((string) $this->xmlReqObj['type'] === self::REQUEST_TYPE_TRANSLATION) {
      return self::REQUEST_TYPE_TRANSLATION;
    }

    return self::REQUEST_TYPE_UNKNOWN;
  }

  /**
   * Method for processing Poetry notification about statuses.
   *
   * Look in to Poetry documentation - unit 3.1 page 16 & unit 4.1 page 36.
   */
  private function processStatusRequest() {
    $statuses = [];
    $attributions = [];
    // Preparing statuses array.
    if (isset($this->xmlReqObj->status)) {
      $statuses = $this->prepareStatuses();
    }
    if (isset($this->xmlReqObj->attributions)) {
      $attributions = $this->prepareAttributions();
    }

    $this->processStatusesData($statuses);
  }

  /**
   * Processing status. Main goal of that method is to add message.
   *
   * Message will have an information about demande status details.
   *
   * @param array $statuses
   *    An array with statuses.
   */
  private function processStatusesData($statuses) {
    // 'Demande' status should be only one per request.
    $demande_type = reset($statuses['demande']);
    $type = $demande_type['@attributes']['type'];
    $code = $demande_type['@attributes']['code'];
    // Get status code description.
    if (isset($demande_type['@attributes']['code'])) {
      $status = $this->getStatusCodeDescription($code);
    }
    else {
      $status = t('No status');
    }
    $message = $demande_type['statusMessage'] ? $demande_type['statusMessage'] : t('No message');
    // Performing  tasks on jobs related to the given request reference.
    // Fetching job items and putting them in to the array.
    foreach ($this->jobs as $job) {
      // Checks if this is a main job.
      if (0 === strpos($job->reference, self::MAIN_JOB_PREFIX)) {
        // @todo: left to add additional message in to main job.
      }
      TmgmtPoetryIntegration::addStatusMassageToJob($job, $type, $status, $message);

      // Refuse ans cancel job translation case.
      if ($code === 'REF' || $code === 'CNL') {
        // @todo: make sure that pt-pt case can be addressed properly.
        $lg_codes = array_keys($statuses['attribution']);
        $job_lg = strtoupper($job->target_language);
        if (in_array($job_lg, $lg_codes)) {
          $job->aborted("Request aborted by DGT.", array());
        }
      }
    }
  }

  /**
   * Provides simplified statuses array for further processing.
   *
   * @return array
   *    Statuses array.
   */
  private function prepareStatuses() {
    // Transforming SimpleXMLElement statuses array in to regular PHP
    // array split by status type to simplify processing.
    $statuses = [];
    foreach ($this->xmlReqObj->status as $status) {
      $status_type = (string) $status['type'];
      // All 'attribution' type statuses are having 'lgCode' property.
      // Inserting 'lgCode' as a key to simplify processing.
      if ($status_type == self::ATTRIBUTION_STATUS_TYPE) {
        $status_lg = (string) $status['lgCode'];
        $statuses[$status_type][$status_lg] = (array) $status;
      }
      else {
        $statuses[$status_type][] = (array) $status;
      }
    }

    return $statuses;
  }

  /**
   * Provides simplified attribution array for further processing.
   *
   * @return array
   *    Attributions array.
   */
  private function prepareAttributions() {
    // Transforming SimpleXMLElement attributions array in to regular PHP
    // array to simplify processing.
    $atrribs = [];
    foreach ($this->xmlReqObj->attributions as $attrib) {
      $attrib_lg = (string) $attrib['lgCode'];
      $attribs[$attrib_lg] = (array) $attrib;
    }

    return $attribs;
  }

  /**
   * Provides code description for given code acronym.
   *
   * @param string $status_code
   *    String with code status acronym passed as a string.
   *
   * @return string
   *    Status code description string.
   */
  private function getStatusCodeDescription($status_code) {
    // Array with status codes.
    $status_codes = [
      'CNL' => t('Canceled'),
      'EXE' => t('Executed'),
      'LCK' => t('Acceptance in Progress'),
      'ONG' => t('Ongoing'),
      'REF' => t('Refused'),
      'SUS' => t('Suspended'),
    ];
    // Checking if given status code exist in array.
    if (array_key_exists($status_code, $status_codes)) {
      return $status_codes[$status_code];
    }
    // Integer statuses - Poetry documentation unit 3.1 page 16.
    if ((int) $status_code == 0) {
      return t('Success');
    }
    if ((int) $status_code < 0) {
      return t('Error');
    }
    if ((int) $status_code > 0) {
      return t('Warning');
    }

    return t('Unknown');
  }

  /**
   * Method for processing Poetry notification of sanding back the translation.
   *
   * Look in to Poetry documentation - unit 4.2 page 38.
   */
  private function processTranslationRequest() {

  }

  /**
   * Provides all of jobs that are related to given reference.
   */
  private function getAllJobs() {
    return TmgmtPoetryIntegration::getJobsByReference($this->xmlReference);
  }

  /**
   * Sets additional properties to simplify data processing.
   */
  private function setCallbackProperties() {
    $xml_object = simplexml_load_string($this->reqMessage);
    $this->xmlReqObj = $xml_object->request;
    $this->xmlRefArray = (array) $this->xmlReqObj->demandeId;
    $this->xmlReference = implode("/", (array) $this->xmlRefArray);
    $this->translator = tmgmt_translator_load('poetry');
    $this->languages = language_list();
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
    $path = self::REQUESTS_PATH . $this->xmlReference . '.xml';
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
