<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator plugin controller.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultTranslatorPluginController;

use Drupal\ne_tmgmt_dgt_ftt_translator\Entity\DgtFttTranslatorMapping;
use Drupal\ne_tmgmt_dgt_ftt_translator\Tools\DataProcessor;
use \EC\Poetry;
use \EC\Poetry\Messages\Responses\Status;
use TMGMTDefaultTranslatorPluginController;
use TMGMTTranslator;
use TMGMTJob;
use TMGMTJobItem;

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
    $poetry_service = array(
      'address',
      'method',
    );
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
   * @param TMGMTJob $job
   *   TMGMT Job object.
   * @param array $parameters
   *   An array with additional parameters like the organisation data.
   *
   * @return array|bool
   *   An array with data for the 'Rules workflow' or FALSE if errors appear.
   */
  public function requestReview(TMGMTJob $job, $parameters) {
    $rules_response = array();

    // Checking if there is a node associated with the given job.
    if ($node = $this->getNodeFromTmgmtJob($job)) {
      // Getting the identifier data.
      $identifier = $this->getIdentifier($job, $node->nid);

      // Getting the request data.
      $data = $this->getRequestData($job, $node);

      // Overwrite the data if we have some parameters.
      if (!empty($parameters)) {
        $this->overwriteRequestData($data, $parameters);
      }

      // Sending a review request to DGT Services.
      $dgt_response = $this->sendReviewRequest($identifier, $data);

      // Process the DGT response to get the Rules response.
      $rules_response = $this->processResponse($dgt_response, $job);
    }

    return array(
      'tmgmt_job' => $job,
      'dgt_service_response' => $rules_response,
    );
  }

  /**
   * Process response from DGT Services.
   *
   * @param \EC\Poetry\Messages\Responses\Status $response
   *   The response.
   * @param TMGMTJob $job
   *   TMGMT Job object.
   *
   * @return array
   *   An array containing the ref id and raw xml.
   */
  private function processResponse(Status $response, TMGMTJob $job) {
    $return = array(
      'ref_id' => '',
      'raw_xml' => '',
    );

    if ($response->isSuccess()) {
      // Updating TMGMT Job information.
      $this->updateTmgmtJobAndJobItem($response, $job);

      // Creating new mapping entity based on the response and job.
      $this->createDgtFttTranslatorMappingEntity($response, $job);

      // Setting up values for the Rules.
      $return['ref_id'] = $response->getMessageId();
      $return['raw_xml'] = $response->getRaw();
    }

    return $return;
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
   * DGT Services response
   */
  private function sendReviewRequest(array $identifier, array $data) {
    // Instantiate the Poetry Client object.
    $poetry = new Poetry\Poetry($identifier);
    $message = $poetry->get('request.send_review_request');
    $message->withArray($data);

    /** @var Status $response */
    $response = $poetry->getClient()->send($message);

    return $response;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::requestTranslation().
   */
  public function requestTranslation(TMGMTJob $job) {
    // TODO: Implement requestTranslation() method.
  }

}
