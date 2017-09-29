<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator plugin controller.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultTranslatorPluginController;

use Drupal\ne_tmgmt_dgt_ftt_translator\Entity\DgtFttTranslatorMapping;
use Drupal\ne_tmgmt_dgt_ftt_translator\Tools\DataProcessor;
use \EC\Poetry;
use \TMGMTDefaultTranslatorPluginController;
use \TMGMTTranslator;
use \TMGMTJob;

/**
 * TMGMT DGT FTT translator plugin controller.
 */
class TmgmtDgtFttTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {
  /**
   * Helper trait with methods for processing settings and the request data.
   */
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
    // @todo: check if it's not easier to provide those variables in this
    // module. Variables are provided for the whole environment.
    // Checking if the common global configuration variables are available.
    // if ($this->checkPoetryServiceSettings()) {
    //  return FALSE;
    // }.
    $dgt_ftt_settings = array('settings', 'organization', 'contacts');
    $all_settings = array();

    // Get setting value for each setting.
    foreach ($dgt_ftt_settings as $setting) {
      $all_settings[$setting] = $translator->getSetting($setting);
    }

    // If any of these are empty, the translator is not properly configured.
    foreach ($all_settings as $value) {
      if (empty($value)) {
        return FALSE;
      }
    };

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
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   * @param object $node
   *   Node object.
   *
   * @return bool
   *
   */
  public function requestReview(TMGMTJob $job, $node) {
    if ($this->checkRequestReviewConditions($job, $node->nid)) {
      $identifier = $this->getRequestIdentifier($job, $node->nid);
      // If the 'number' key is set we are going to send the review request.
      if (isset($identifier['identifier.number'])) {
        // Sending the 'review' request.
        $data = $this->getRequestData($job, $node);
        $dgt_response = $this->sendReviewRequest($identifier, $data);
        // Put there the reference ID
        $job = $this->updateTmgmtJobAndJobItem();

        return array (
          'tmgmt_job' => $job,
          'dgt_response' =>$dgt_response,
        );
      }

      // If the 'sequence' key is set there are no entries in the mapping table
      // or the 'part' counter value reached 99.
      if (isset($identifier['identifier.sequence'])) {
        $dgt_response = $this->sendNewNumberRequest($identifier);
        // Checking the DGT services response status.
        $statuses = $dgt_response->getStatuses();
        if($statuses[0]['code'] === 0) {
          // Creating a new mapping entity and performing the review request.
          $this->createDgtFttTranslatorMappingEntity($dgt_response, $identifier);
          $this->requestReview($job, $node);

        }
        else {
          // Log the error or other details from the response to the watchdog.
          return FALSE;
        }
      }

    }

    return FALSE;
  }

  /**
   * Sends the 'review' request to the DGT Service.
   *
   * @param array $identifier
   *   An array with the identifier data.
   *
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

    $response = $poetry->getClient()->send($message);

    return $response;

  }

  /**
   * Sends the 'new number' request to the DGT Service.
   *
   * @param array $identifier
   *   An array with values which are required to instantiate OE Poetry client.
   * @return \EC\Poetry\Messages\Responses\Status
   */
  private function sendNewNumberRequest($identifier) {
    $poetry = new Poetry\Poetry($identifier);
    $message = $poetry->get('request.request_new_number');

    return $poetry->getClient()->send($message);
  }

  /**
   * Creates the DGT FTT Translator Mapping entity.
   *
   */
  private function createDgtFttTranslatorMappingEntity(Poetry\Messages\Responses\Status $response, $node) {

  }

  /**
   * Updating the TMGMT Job and TMGMT Job Item with data from the DGT response.
   */
  private function updateTmgmtJobAndJobItem() {

  }

  /**
   * Helper function to check if the job and content met request requirement.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   * @param string $entity_id
   *   Entity ID (for some edge cases the string type can appear).
   * @param string $entity_type
   *   Entity type.
   *
   * @return bool
   *   TRUE/FALSE depending on conditions checks.
   */
  private function checkRequestReviewConditions(TMGMTJob $job, $entity_id, $entity_type = 'node') {
    // @todo: to be removed, check if it fits to canTranslate.
    return TRUE;
    // Checking if there aren't any translation processes for a given job and
    // content.
    if ($job->getState() === TMGMT_JOB_STATE_UNPROCESSED && !$this->getActiveTmgmtJobItemsIds($entity_id)) {

      return TRUE;
    }

    // Informing user that the review request can not be send.
    $error_message = t("Content type with following ID '@entity_id' and type
      '@entity_type' is currently included in one of the translation processes.
      You can not request the review for the content which is currently under
      translation process. Please finish ongoing processes for a given content
      and try again.",
      array('@entity_id' => $entity_id, '@entity_type' => $entity_type)
    );

    drupal_set_message($error_message, 'error');

    // Logging an error to the watchdog.
    watchdog('ne_tmgmt_dgt_ftt_translator',
      "Content type with following ID: '$entity_id' and type: '$entity_type' is
       currently included in one of the translation processes. The review
       request for the content which is under ongoing translation processes can
       not be send.",
      array(),
      WATCHDOG_ERROR
    );

    return FALSE;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::requestTranslation().
   */
  public function requestTranslation(TMGMTJob $job) {
    // TODO: Implement requestTranslation() method.
  }

}
