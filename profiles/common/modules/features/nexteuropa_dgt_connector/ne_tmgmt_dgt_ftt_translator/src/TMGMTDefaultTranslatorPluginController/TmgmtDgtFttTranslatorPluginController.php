<?php

/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator plugin controller.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultTranslatorPluginController;

use Drupal\ne_tmgmt_dgt_ftt_translator\Tools\DataProcessor;
use \EC\Poetry\Messages\Responses\Status;
use TMGMTDefaultTranslatorPluginController;
use TMGMTTranslator;
use TMGMTJob;

/**
 * TMGMT DGT FTT translator plugin controller.
 */
class TmgmtDgtFttTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {
  // Helper trait with methods for processing settings and the request data.
  use DataProcessor;

  /**
   * Override parent defaultSettings method.
   *
   * Copy paste form the old implementation.
   */
  public function defaultSettings() {
    return array(
      'export_format' => 'html_poetry',
      'allow_override' => TRUE,
      'scheme' => 'public',
    );
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::isAvailable().
   */
  public function isAvailable(TMGMTTranslator $translator) {
    // Checking if the common global configuration variables are available.
    if (!$this->checkPoetryServiceSettings()) {

      return FALSE;
    }
    // Settings array keys specific for the translator.
    $dgt_ftt_settings = array('settings', 'organization', 'contacts');

    // Get setting value for each setting.
    foreach ($dgt_ftt_settings as $setting) {
      $dgt_ftt_setting = $translator->getSetting($setting);
      // If any of these are empty, the translator is not properly configured.
      if (empty($dgt_ftt_setting)) {

        return FALSE;
      }
      // Checking values under given settings array.
      foreach ($dgt_ftt_setting as $dgt_ftt_setting_value) {
        if (empty($dgt_ftt_setting_value)) {

          return FALSE;
        }
      }
    }

    return TRUE;
  }

  /**
   * Checks if the global Poetry Service settings are available.
   *
   * @return bool
   *   TRUE/FALSE depending on the check result.
   */
  private function checkPoetryServiceSettings() {
    $poetry_service = array('address', 'method');

    $poetry_hard_settings = variable_get('poetry_service');

    // If the configuration in the settings.php is missing don't check further.
    if (empty($poetry_hard_settings)) {

      return FALSE;
    }

    // If one of the arg is not set, don't check further.
    foreach ($poetry_service as $service_arg) {
      if (!isset($poetry_hard_settings[$service_arg])) {

        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    // Anything can be exported.
    return TRUE;
  }

  /**
   * Custom method which sends the review request to the DGT Service.
   *
   * @param array $jobs
   *   Array of TMGMT Job object.
   * @param array $parameters
   *   An array with additional parameters like the organisation data.
   *
   * @return array|bool
   *   An array with data for the 'Rules workflow' or FALSE if errors appear.
   */
  public function requestReview(array $jobs, array $parameters) {
    $rules_response = array();

    if (empty($jobs)) {
      return $rules_response;
    }

    // Checking if there is a node associated with the given job.
    if ($node = $this->getNodeFromTmgmtJob($jobs[0])) {
      // Getting the identifier data.
      $identifier = $this->getIdentifier($jobs[0], $node->nid);

      // Getting the request data.
      $data = $this->getRequestData($jobs, $node, $parameters['delay']);

      // Overwrite the request identifier and data with parameters from 'Rules'.
      $identifier = $this->overwriteRequestIdentifier($identifier, $parameters['identifier']);
      $data = $this->overwriteRequestData($data, $parameters['data']);

      // Sending a review request to DGT Services.
      $client_action = 'request.create_review_request';
      $dgt_response = $this->sendRequest($client_action, $identifier, $data);

      // Process the DGT response to get the Rules response.
      $jobs[0]->client_action = $client_action;
      $jobs[0]->client_request_data = $data;
      $rules_response = $this->processResponse($dgt_response, $jobs);

      /** @var TMGMTJob $job */
      foreach ($jobs as $job) {
        /** @var TMGMTJobItem $job_item */
        foreach ($job->getItems() as $job_item) {
          $job_item->accepted("Review Request has been created. Reference: @reference",
            array(
              '@reference' => $job->reference,
            )
          );
        }
      }

    }

    $rules_response['tmgmt_job'] = $jobs[0];

    return $rules_response;
  }

  /**
   * Custom method which sends the review request to the DGT Service.
   *
   * @param TMGMTJob $job
   *   TMGMT Job object.
   *
   * @return array|bool
   *   An array with data for the 'Rules workflow' or FALSE if errors appear.
   */
  public function requestTranslation(TMGMTJob $job) {
    return FALSE;
  }

  /**
   * Custom method which sends the translation request to the DGT Service.
   *
   * @param array $jobs
   *   Array of TMGMT Job object.
   * @param array $parameters
   *   An array with additional parameters like the organisation data.
   *
   * @return array|bool
   *   An array with data for the 'Rules workflow' or FALSE if errors appear.
   */
  public function requestTranslations(array $jobs, array $parameters) {
    $rules_response = array();

    // Checking if there is a node associated with the given job.
    if ($node = $this->getNodeFromTmgmtJob($jobs[0])) {
      // Getting the identifier data.
      $identifier = $this->getIdentifier($jobs[0], $node->nid);

      // Using the latest reference id for the node.
      // This reference is created by the Review request.
      /** @var DgtFttTranslatorMapping $mapping_entity */
      $mapping_entity = $this->getReviewIdentifier($node);
      if (!is_null($mapping_entity)) {
        $identifier['identifier.year'] = $mapping_entity->year;
        $identifier['identifier.number'] = $mapping_entity->number;
        $identifier['identifier.part'] = $mapping_entity->part;

        // Getting the request data.
        $data = $this->getRequestData($jobs, $node, $parameters['delay']);

        // Overwrite request identifier and data with parameters from 'Rules'.
        $identifier = $this->overwriteRequestIdentifier($identifier, $parameters['identifier']);
        $data = $this->overwriteRequestData($data, $parameters['data']);

        // Sending a review request to DGT Services.
        $client_action = 'request.create_translation_request';
        $dgt_response = $this->sendRequest($client_action, $identifier, $data);

        // Process the DGT response to get the Rules response.
        $jobs[0]->client_action = $client_action;
        $jobs[0]->client_request_data = $data;
        $rules_response = $this->processResponse($dgt_response, $jobs);
      }
      else {
        watchdog(
          'ne_tmgmt_dgt_ftt_translator',
          "There is no entry in the entity mapping table for given
          content. Please make sure that the review request was sent before
          the translation request. Node ID: %nid",
          array('%nid' => $node->nid),
          WATCHDOG_ERROR
        );
      }
    }

    $rules_response['tmgmt_job'] = $jobs[0];

    return $rules_response;
  }

  /**
   * Process response from DGT Services.
   *
   * @param \EC\Poetry\Messages\Responses\Status $response
   *   The response.
   * @param array $jobs
   *   Array of TMGMT Job object.
   *
   * @return array
   *   An array containing the ref id and raw xml.
   */
  private function processResponse(Status $response, array $jobs) {
    // There are no warnings and errors.
    if ($response->isSuccessful()) {
      // Updating TMGMT Job information.
      $this->updateTmgmtJobAndJobItem($response, $jobs);

      // Creating new mapping entity based on the response and job.
      $this->createDgtFttTranslatorMappingEntity($response, $jobs[0]);

      foreach ($jobs as $job) {
        $job->submitted('Job has been successfully submitted. Job Reference ID is: %job_reference',
          array('%job_reference' => $job->reference));
      }

      watchdog(
        'ne_tmgmt_dgt_ftt_translator',
        'The TMGMT Job %job_reference has been successfully submitted.',
        array('%job_reference' => $job->reference),
        WATCHDOG_INFO
      );
    }
    else {
      if ('0' === $response->getRequestStatus()->getCode()) {
        // Creating new mapping entity based on the response and job.
        $this->createDgtFttTranslatorMappingEntity($response, $jobs[0]);
      }

      // Abort the TMGMT Job and the JobItem.
      $this->abortTmgmtJobAndJobItem($response, $jobs);
    }

    return $this->getRulesDataArrays($response);
  }

}