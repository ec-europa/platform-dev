<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator plugin controller.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultTranslatorPluginController;

use Drupal\ne_tmgmt_dgt_ftt_translator\Tools\DataProcessor;
use \EC\Poetry\Poetry;
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
  public function requestReview($jobs, $parameters) {
    $rules_response = array();

    // Checking if there is a node associated with the given job.
    if ($node = $this->getNodeFromTmgmtJob($jobs[0])) {
      // Getting the identifier data.
      $identifier = $this->getIdentifier($jobs[0], $node->nid);

      // Getting the request data.
      $data = $this->getRequestData($jobs, $node);

      // Overwrite the data if we have some parameters.
      if (!empty($parameters)) {
        $data = $this->overwriteRequestData($data, $parameters);
      }

      // Sending a review request to DGT Services.
      $dgt_response = $this->sendReviewRequest($identifier, $data);

      // Process the DGT response to get the Rules response.
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
  public function requestTranslations($jobs, $parameters) {
    $rules_response = array();

    // Checking if there is a node associated with the given job.
    if ($node = $this->getNodeFromTmgmtJob($jobs[0])) {
      // Getting the identifier data.
      $identifier = $this->getIdentifier($jobs[0], $node->nid);

      // Using the latest reference id for the node.
      // This reference is created by the Review request.
      /** @var DgtFttTranslatorMapping $mapping_entity */
      $mapping_entity = $this->getReviewIdentifier($node);
      $identifier['identifier.year'] = $mapping_entity->year;
      $identifier['identifier.number'] = $mapping_entity->number;
      $identifier['identifier.part'] = $mapping_entity->part;

      // Getting the request data.
      $data = $this->getRequestData($jobs, $node);

      // Overwrite the data if we have some parameters.
      if (!empty($parameters)) {
        $data = $this->overwriteRequestData($data, $parameters);
      }

      // Sending a review request to DGT Services.
      $dgt_response = $this->sendTranslationRequest($identifier, $data);

      // Process the DGT response to get the Rules response.
      $rules_response = $this->processResponse($dgt_response, $jobs);
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
  private function processResponse(Status $response, $jobs) {
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

    // Prepare arrays for the 'Rules' and logging mechanism.
    $response_data = $this->getRulesDataArrays($response);
    $this->logResponseData($response_data);

    return $response_data;
  }

  /**
   * Sends the 'review' request to the DGT Service.
   *
   * @param array $identifier
   *   An array with the identifier data.
   * @param array $data
   *   An array with the request data.
   *
   * @return \EC\Poetry\Messages\Responses\Status DGT Services response
   *   DGT Services response
   */
  private function sendReviewRequest(array $identifier, array $data) {
    // Instantiate the Poetry Client object.
    $poetry = new Poetry($identifier);
    $message = $poetry->get('request.send_review_request');
    $message->withArray($data);

    return $poetry->getClient()->send($message);
  }

  /**
   * Sends the 'translation' request to the DGT Service.
   *
   * @param array $identifier
   *   An array with the identifier data.
   * @param array $data
   *   An array with the request data.
   *
   * @return \EC\Poetry\Messages\Responses\Status DGT Services response
   *   DGT Services response
   */
  private function sendTranslationRequest(array $identifier, array $data) {
    // Instantiate the Poetry Client object.
    $poetry = new Poetry($identifier);
    $message = $poetry->get('request.create_request');
    $message->withArray($data);

    return $poetry->getClient()->send($message);
  }

}
