<?php

/**
 * @file
 * Provides Poetry translation plugin controller.
 */

/**
 * MT@EC translation plugin controller.
 */
class TMGMTPoetryTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {

  /**
   * Translation service URL.
   *
   * @var string
   */

  /**
   * Override parent defaultSettings method.
   */
  public function defaultSettings() {
    return array(
      'export_format' => 'html',
      'allow_override' => TRUE,
      'scheme' => 'public',
      // Making this setting TRUE by default is more appropriate, however we
      // need to make it FALSE due to backwards compatibility.
      'xliff_processing' => TRUE,
    );
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::isAvailable().
   */
  public function isAvailable(TMGMTTranslator $translator) {
    $contacts_set = FALSE;
    $poetry_settings_set = FALSE;

    // Check if the translator settings are set.
    $contacts = $translator->getSetting('contacts');
    if (!empty($contacts['author']) && !empty($contacts['secretary']) &&
      !empty($contacts['contact']) && !empty($contacts['responsible'])) {
      $contacts_set = TRUE;
    }

    // Check if the poetry variables are set.
    $poetry_service = variable_get('poetry_service');
    if ((isset($poetry_service['address']) && !empty($poetry_service['address'])) &&
      (isset($poetry_service['method']) && !empty($poetry_service['method'])) &&
      (isset($poetry_service['user']) && !empty($poetry_service['user'])) &&
      (isset($poetry_service['password']) && !empty($poetry_service['password'])) &&
      (isset($poetry_service['callback_user']) && !empty($poetry_service['callback_user'])) &&
      (isset($poetry_service['callback_password']) && !empty($poetry_service['callback_password']))) {
      $poetry_settings_set = TRUE;
    }
    return $contacts_set && $poetry_settings_set;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::canTranslation().
   *
   * We will check are source and target language supported.
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    // All languages are supported at the moment.
    return TRUE;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::requestTranslation().
   */
  public function requestTranslation(TMGMTJob $job) {

    // Pull the source data array through the job and flatten it.
    $xml = $this->prepareDataForSending($job);
    // Request translation from MT@EC service.
    $response = $this->doRequest(array('xml' => $xml));
    // Handling response.
    $response_xml = simplexml_load_string($response);
    // If it is not an xml response, the SOAP request failed.
    if (!$response_xml) {
      $job->rejected("There was an error with the SOAP service . Message error: @error",
        array('@error' => $response), 'error');
    }
    else {
      $request = $response_xml->request;
      $statuses = $request->status;
      // Check the statuses of the response
      // in order to verify that everything is correct.
      foreach ($statuses as $status) {
        $message = (string) $status->statusMessage;
        if ($message != 'OK') {
          $job->rejected("There was an error with the Poetry request . Message error: @error",
          array('@error' => $message), 'error');
        }
      }
      if (!$job->isRejected()) {
        $demande_id = (array) $request->demandeId;
        $job->reference = implode('/', $demande_id);
        $job->submitted('Job has been successfully submitted for translation. Project ID is: %project_id',
          array('%project_id' => $job->reference));
      }
    }
  }

  /**
   * Overrides TMGMTDefaultTranslatorPluginController::getSupportedTargetLanguages().
   */
  public function getSupportedTargetLanguages(TMGMTTranslator $translator, $source_language) {
    $languages = array();
    $list_languages = language_list();

    foreach ($list_languages as $key => $value) {
      $languages[$key] = $key;
    }

    return $languages;
  }

  /**
   * Execute a request against the Poetry API.
   */
  protected function doRequest(array $query = array()) {
    $xml = $query['xml'];

    $result = _tmgmt_poetry_send_soap_request($xml);
    return $result;
  }

  /**
   * Prepares data to be send to Poetry service.
   *
   * @param TMGMTJob $job
   *   Job object.
   *
   * @return string
   *   Data for sending to the translator service.
   */
  protected function prepareDataForSending(TMGMTJob $job) {

    $xml = _tmgmt_poetry_generate_request_xml($job);

    return $xml;
  }
}
