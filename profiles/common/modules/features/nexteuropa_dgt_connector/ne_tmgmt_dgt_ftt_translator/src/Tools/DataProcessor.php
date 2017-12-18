<?php

namespace Drupal\ne_tmgmt_dgt_ftt_translator\Tools;

use Drupal\ne_dgt_rules\DgtRulesTools;
use Drupal\nexteuropa_core\Psr3Watchdog;
use EntityFieldQuery;
use EC\Poetry\Poetry;
use EC\Poetry\Messages\Responses\Status;
use TMGMTJob;

/**
 * Helper trait with methods for processing translator's data and settings.
 */
trait DataProcessor {
  /**
   * TMGMT Job object.
   *
   * @var array
   */
  private $jobs;

  /**
   * Node object.
   *
   * @var object
   */
  private $node;

  /**
   * Translator settings keys.
   *
   * @var array
   */
  private $settingsKeys = array('settings', 'organization', 'contacts');

  /**
   * Translator settings.
   *
   * @var array
   */
  private $settings;

  /**
   * TMGMT Translator object.
   *
   * @var TMGMTTranslator
   */
  private $translator;

  /**
   * Translator mapping entity.
   *
   * @var string
   */
  public $translatorEntityType = 'ne_tmgmt_dgt_ftt_map';

  /**
   * Default delay date - 72 hours form the date of sending request.
   *
   * @var string
   */
  private $defaultDelayDate;

  /**
   * Provides the data array for a request.
   *
   * @param array $jobs
   *   Array TMGMT Job object.
   * @param object $node
   *   Node object.
   *
   * @return array
   *   Request data array.
   */
  public function getRequestData(array $jobs, $node) {
    // Setting out the node object property.
    $this->node = $node;
    // Setting out the job property.
    $this->jobs = $jobs;
    // Setting out the translator property.
    $this->translator = $jobs[0]->getTranslator();
    // Setting out the default delay date - 72 hours.
    $this->defaultDelayDate = date('d/m/Y', time() + 259200);
    // Getting the translator settings.
    $settings = $this->getTranslatorSettings();

    return array(
      'details' => $this->getRequestDetails($settings),
      'return_address' => $this->getReturnAddress($settings),
      'source' => $this->getSource($settings),
      'contact' => $this->getContact($settings),
      'target' => $this->getTarget($settings),
    );
  }

  /**
   * Provides translator settings array.
   *
   * @return array
   *   An array with the translator settings.
   */
  private function getTranslatorSettings() {
    $settings = array();

    // Get settings values for each category keys.
    foreach ($this->settingsKeys as $setting_key) {
      $settings[$setting_key] = $this->translator->getSetting($setting_key);
    }

    return $settings;
  }

  /**
   * Provides the request details.
   *
   * @param array $settings
   *   Translator settings.
   *
   * @return array
   *   Array with data.
   */
  private function getRequestDetails(array $settings) {
    return array(
      'client_id' => t('Job ID: @tjid', array('@tjid' => $this->jobs[0]->identifier())),
      'title' => $this->node->title,
      'author' => $settings['organization']['author'],
      'responsible' => $settings['organization']['responsible'],
      'requester' => $settings['organization']['requester'],
      'applicationId' => 'FPFIS',
      'delay' => $this->defaultDelayDate,
      'reference_files_remark' => url(drupal_get_path_alias('node/' . $this->node->nid), array('absolute' => TRUE)),
      'procedure' => 'NEANT',
      'destination' => 'PUBLIC',
      'type' => 'INTER',
      'workflowCode' => $settings['settings']['dgt_ftt_workflow_code'],
    );
  }

  /**
   * Provides the request return address.
   *
   * @param array $settings
   *   Translator settings.
   *
   * @return array
   *   Array with data.
   */
  private function getReturnAddress(array $settings) {
    return array(
      'action' => 'UPDATE',
      'type' => 'webService',
      'user' => $settings['settings']['callback_username'],
      'password' => $settings['settings']['callback_password'],
      'address' => _ne_tmgmt_dgt_ftt_translator_get_client_wsdl(),
      'path' => 'handle',
    );
  }

  /**
   * Provides the request source.
   *
   * @param array $settings
   *   Translator settings.
   *
   * @return array
   *   Array with data.
   */
  private function getSource(array $settings) {
    return array(
      'format' => 'HTML',
      'name' => 'content.html',
      'file' => $this->getContent(),
      'legiswrite_format' => 'No',
      'source_language' => array(
        array(
          'code' => drupal_strtoupper($this->translator->mapToRemoteLanguage($this->node->language)),
          'pages' => 1,
        ),
      ),
    );
  }

  /**
   * Provides the request contact.
   *
   * @param array $settings
   *   Translator settings.
   *
   * @return array
   *   Array with data.
   */
  private function getContact(array $settings) {
    return array(
      array(
        'type' => 'auteur',
        'nickname' => $settings['contacts']['author'],
      ),
      array(
        'type' => 'secretaire',
        'nickname' => $settings['contacts']['secretary'],
      ),
      array(
        'type' => 'contact',
        'nickname' => $settings['contacts']['contact'],
      ),
      array(
        'type' => 'responsable',
        'nickname' => $settings['contacts']['responsible'],
      ),
    );
  }

  /**
   * Provides the request target.
   *
   * @param array $settings
   *   Translator settings.
   *
   * @return array
   *   Array with data.
   */
  private function getTarget(array $settings) {
    $return = array();

    foreach ($this->jobs as $job) {
      $return[] = array(
        'action' => 'INSERT',
        'format' => 'HTML',
        'language' => drupal_strtoupper($this->translator->mapToRemoteLanguage($job->target_language)),
        'delay' => $this->defaultDelayDate,
      );
    }

    return $return;
  }

  /**
   * Provides BASE64 encoded content from the node.
   */
  private function getContent() {
    // Load data exporter.
    $controller = tmgmt_file_format_controller($this->jobs[0]->getSetting('export_format'));

    // Generate the data into a XML format and encode it to be translated.
    $export = $controller->export($this->jobs[0]);

    return base64_encode($export);
  }

  /**
   * Provides an identifier array.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   * @param int $node_id
   *   Node ID.
   *
   * @return array|bool
   *   An array with an identifier data or FALSE in case of errors;
   */
  public function getIdentifier(TMGMTJob $job, $node_id) {
    $identifier = $this->getRequestIdentifier($job, $node_id);

    // If the 'sequence' key is set there are no entries in the mapping table
    // or the 'part' counter value reached 99.
    if (isset($identifier['identifier.sequence'])) {
      $client_action = 'request.get_new_number';
      $dgt_response = $this->sendRequest($client_action, $identifier);
      // Checking the DGT services response status.
      if ($dgt_response->isSuccessful()) {
        // Creating a new mapping entity and performing the review request.
        $job->client_action = $client_action;
        $this->createDgtFttTranslatorMappingEntity($dgt_response, $job);

        return $this->getIdentifier($job, $node_id);
      }
      else {
        // Log the error or other details from the response to the watchdog.
        return FALSE;
      }
    }

    return $identifier;
  }

  /**
   * Provides an identifier array.
   *
   * @param int $node
   *   Node Object.
   *
   * @return array|bool
   *   An array with an identifier data or FALSE in case of errors;
   */
  public function getReviewIdentifier($node) {
    return DgtRulesTools::findMappingsByNode($node);
  }

  /**
   * Provides an identifier array in order to send a request.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   * @param object $node_id
   *   Node id.
   *
   * @return array
   *   An array with the identifier data.
   */
  private function getRequestIdentifier(TMGMTJob $job, $node_id) {
    // Getting the default values based on the configuration.
    $identifier = $this->getRequestIdentifierDefaults($job);

    // Setting up helper default values.
    $identifier['identifier.part'] = 0;
    $identifier['identifier.version'] = 0;
    $unset_key = 'identifier.number';

    // @todo: test the logic of this part.
    // Getting the latest mapping entity in order to set the part and number.
    if ($mapping_entity = $this->getLatestDgtFttTranslatorMappingEntity()) {
      // Checking if the 'part' counter value reached 99.
      if ($mapping_entity->part < 99) {
        $identifier['identifier.number'] = $mapping_entity->number;
        if ($mapping_entity->client_action != 'request.get_new_number') {
          $identifier['identifier.part'] = $mapping_entity->part + 1;
        }
        $unset_key = 'identifier.sequence';
      }
    }

    unset($identifier[$unset_key]);

    // Checking if there are mappings for the given content and setting version.
    if ($mapping_entity = $this->getDgtFttTranslatorMappingByProperty('entity_id', $node_id)) {
      if ($mapping_entity->client_action != 'request.get_new_number') {
        $identifier['identifier.version'] = $mapping_entity->version + 1;
      }
    }

    return $identifier;
  }

  /**
   * Provides the request identifier default values.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   *
   * @return array
   *   An array with the identifier default values.
   */
  private function getRequestIdentifierDefaults(TMGMTJob $job) {
    // Getting a translator from the job.
    $translator = $job->getTranslator();
    // Getting translator settings.
    $settings = $translator->getSetting('settings');
    $poetry_service = variable_get('poetry_service');

    return array(
      'identifier.code' => $settings['dgt_code'],
      'identifier.year' => date("Y"),
      'identifier.sequence' => $settings['dgt_counter'],
      'client.wsdl' => _ne_tmgmt_dgt_ftt_translator_get_client_wsdl(),
      'service.wsdl' => $poetry_service['address'],
      'service.username' => $settings['dgt_ftt_username'],
      'service.password' => $settings['dgt_ftt_password'],
    );
  }

  /**
   * Provides the latest DGT FTT Translator Mapping entity.
   *
   * @return DgtFttTranslatorMapping|bool
   *   Entity or FALSE if there are no entries in the entity table.
   */
  private function getLatestDgtFttTranslatorMappingEntity() {
    // Querying for the latest entry based on the max id.
    $latest_entity_id = db_query("SELECT MAX(id) FROM {ne_tmgmt_dgt_ftt_map}")->fetchField();

    // Checking if we have any entries in the table.
    if (is_null($latest_entity_id)) {
      return FALSE;
    }

    return entity_load_single($this->translatorEntityType, $latest_entity_id);;
  }

  /**
   * Provides the latest mapping entity based on property and its value query.
   *
   * @param string $property_name
   *   Property name.
   * @param string $property_value
   *   Property value.
   *
   * @return \Drupal\ne_tmgmt_dgt_ftt_translator\Entity\DgtFttTranslatorMapping|bool
   *   A mapping entity or FALSE if there are no results.
   */
  protected function getDgtFttTranslatorMappingByProperty($property_name, $property_value) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $this->translatorEntityType)
      ->propertyCondition($property_name, $property_value);
    $result = $query->execute();

    if (isset($result[$this->translatorEntityType])) {
      $mapping_ids = array_keys($result[$this->translatorEntityType]);
      $mapping_entity_id = max($mapping_ids);
      $mapping_entity = entity_load_single($this->translatorEntityType, $mapping_entity_id);

      return $mapping_entity;
    }

    return FALSE;
  }

  /**
   * Provides a node object related to a given translation job.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   *
   * @return bool|mixed
   *   A node object or FALSE if there are no results.
   */
  public function getNodeFromTmgmtJob(TMGMTJob $job) {
    // Getting job items from the job (in our case there should be always one).
    $job_items = $job->getItems();

    // Checking if we have job item for a given job.
    if (!empty($job_items)) {
      /** @var \TMGMTJobItem $job_item */
      $job_item = array_shift($job_items);
      // Checking if an item type is 'node'.
      if ($job_item->item_type === 'node') {
        // Returning the node object.
        return node_load($job_item->item_id);
      }
    }

    return FALSE;
  }

  /**
   * Creates the DGT FTT Translator Mapping entity.
   *
   * @param \EC\Poetry\Messages\Responses\Status $response
   *   The DGT Service response.
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   */
  private function createDgtFttTranslatorMappingEntity(Status $response, TMGMTJob $job) {
    // Extracting TMGMT Job Item from the TMGMT Job in order to get data.
    /** @var \TMGMTJobItem $job_item */
    $job_items = $job->getItems();
    if (count($job_items) == 1) {
      $job_item = array_shift($job_items);
      // Creating the mapping entity.
      $map_entity = entity_create(
        'ne_tmgmt_dgt_ftt_map',
        array(
          'tjid' => $job_item->tjid,
          'entity_id' => $job_item->item_id,
          'entity_type' => $job_item->item_type,
          'year' => $response->getIdentifier()->getYear(),
          'number' => $response->getIdentifier()->getNumber(),
          'version' => $response->getIdentifier()->getVersion(),
          'part' => $response->getIdentifier()->getPart(),
          'delay' => property_exists($job, 'client_request_data') ? strtotime(str_replace('/', '-', $job->client_request_data['details']['delay'])) : 0,
          'client_action' => property_exists($job, 'client_action') ? $job->client_action : '',
        )
      );
      $map_entity->save();
    };
  }

  /**
   * Updating the TMGMT Job and TMGMT Job Item with data from the DGT response.
   *
   * @param \EC\Poetry\Messages\Responses\Status $response
   *   DGT Service response.
   * @param array $jobs
   *   TMGMT Job object.
   */
  private function updateTmgmtJobAndJobItem(Status $response, array $jobs) {
    foreach ($jobs as $job) {
      $job->reference = $response->getMessageId();
      $job->save();
    }
  }

  /**
   * Provides data arrays in order to expose useful values to the Rules.
   *
   * @param \EC\Poetry\Messages\Responses\Status $response
   *   DGT Service response.
   *
   * @return array
   *   An array with data that are going to be exposed in the Rules.
   */
  private function getRulesDataArrays(Status $response) {
    // Initiation of the response data array.
    $response_data = array(
      'dgt_service_response' => array(
        'ref_id' => '',
        'raw_xml' => '',
      ),
      'dgt_service_response_status' => array(
        'code' => '',
        'language' => '',
        'date' => '',
        'time' => '',
        'message' => '',
      ),
      'dgt_service_demand_status' => array(
        'code' => '',
        'language' => '',
        'date' => '',
        'time' => '',
        'message' => '',
      ),
    );

    // Whenever there is an XML response it will be exposed to the Rules.
    $response_data['dgt_service_response']['raw_xml'] = $response->getRaw();

    // Checking if there is a 'request status' in the response object.
    if ($response->hasRequestStatus()) {
      $response_data['dgt_service_response']['ref_id'] = $response->getMessageId();

      $request_status = array(
        'code' => $response->getRequestStatus()->getCode(),
        'language' => $response->getRequestStatus()->getLanguage(),
        'date' => $response->getRequestStatus()->getDate(),
        'time' => $response->getRequestStatus()->getTime(),
        'message' => $response->getRequestStatus()->getMessage(),
      );

      $response_data['dgt_service_response_status'] = $request_status;
    }

    // Checking if there is an 'demand status' in the response object.
    if ($response->hasDemandStatus()) {
      $demand_status = array(
        'code' => $response->getDemandStatus()->getCode(),
        'language' => $response->getDemandStatus()->getLanguage(),
        'date' => $response->getDemandStatus()->getDate(),
        'time' => $response->getDemandStatus()->getTime(),
        'message' => $response->getDemandStatus()->getMessage(),
      );

      $response_data['dgt_service_demand_status'] = $demand_status;
    }

    return $response_data;
  }

  /**
   * Overwrites request data with given parameters.
   *
   * @param array $data
   *   An array with the request data.
   * @param array $parameters
   *   An array with additional parameters.
   *
   * @return array
   *   An overwrite request data array.
   */
  public function overwriteRequestData(array $data, array $parameters) {
    foreach ($parameters as $group_key => $group_parameters) {
      foreach ($group_parameters as $parameter_key => $parameter) {
        if (!is_null($parameter)) {
          $data[$group_key][$parameter_key] = $parameter;
        }
      }
    }

    return $data;
  }

  /**
   * Overwrites request identifier with given parameters.
   *
   * @param array $identifier
   *   An array with the request identifier.
   * @param array $parameters
   *   An array with additional parameters.
   *
   * @return array
   *   An overwrite request identifier array.
   */
  public function overwriteRequestIdentifier(array $identifier, array $parameters) {
    foreach ($parameters as $parameter_key => $parameter_value) {
      if (!is_null($parameter_value)) {
        $identifier[$parameter_key] = $parameter_value;
      }
    }

    return $identifier;
  }

  /**
   * Logs the DGT Service response data.
   *
   * @param array $response_data
   *   An array with the DGT Service response data.
   */
  private function logResponseData(array $response_data) {
    // @todo: Implement logging into files system.
  }

  /**
   * Updating the TMGMT Job and TMGMT Job Item with data from the DGT response.
   *
   * @param \EC\Poetry\Messages\Responses\Status $response
   *   DGT Service response.
   * @param array $jobs
   *   An array of TMGMT Job objects.
   */
  private function abortTmgmtJobAndJobItem(Status $response, array $jobs) {
    foreach ($jobs as $job) {
      if ($statuses = $response->getWarnings()) {
        $job->addMessage(
          'There were warnings with the poetry request: :msg',
          array(':msg' => implode('. ', $statuses)),
          'warning'
        );
        watchdog('ne_tmgmt_dgt_ftt_translator',
          "The TMGMT Job '$job->tjid' have warnings with the poetry request: :msg",
          array(':msg' => implode('. ', $statuses)),
          WATCHDOG_WARNING
        );
      }

      if ($statuses = $response->getErrors()) {
        $job->addMessage(
          'There were errors with the poetry request: :msg',
          array(':msg' => implode('. ', $statuses)),
          'error'
        );
        watchdog('ne_tmgmt_dgt_ftt_translator',
          "The TMGMT Job '$job->tjid' have errors with the poetry request: :msg",
          array(':msg' => implode('. ', $statuses)),
          WATCHDOG_ERROR
        );
      }

      $job->aborted();
    }
  }

  /**
   * Sends the request to the DGT Service.
   *
   * @param string $client_action
   *   A client action which will be performed.
   * @param array $identifier
   *   An array with the identifier data.
   * @param array $data
   *   An array with the request data.
   *
   * @return \EC\Poetry\Messages\Responses\Status
   *   DGT Services response
   */
  private function sendRequest($client_action, array $identifier, array $data = array()) {
    // Instantiate the Poetry Client object.
    $identifier['logger'] = new Psr3Watchdog();
    $identifier['log_level'] = variable_get('poetry_client_log_level', FALSE);
    $poetry = new Poetry($identifier);
    $message = $poetry->get($client_action);

    if (!empty($data)) {
      $message->withArray($data);
    }

    return $poetry->getClient()->send($message);
  }

}
