<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator helper functions.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\Tools;

use Drupal\ne_tmgmt_dgt_ftt_translator\Entity\DgtFttTranslatorMapping;
use \EntityFieldQuery;
use \TMGMTJob;
use \TMGMTTranslator;

/**
 * Helper trait with methods for processing translator's data and settings.
 */
trait DataProcessor {
  /**
   * TMGMT Job object.
   *
   * @var TMGMTJob
   */
  private $job;

  /**
   * Node object.
   *
   * @var object.
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
   * @var \TMGMTTranslator
   */
  private $translator;

  /**
   * Translator mapping entity.
   *
   * @var string
   */
  private $translatorEntityType = 'ne_tmgmt_dgt_ftt_map';

  /**
   * Default delay date - 72 hours form the date of sending request.
   *
   * @var string
   */
  private $defaultDelayDate;

  /**
   * Provides the data array for a request.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   * @param object $node
   *   Node object.
   *
   * @return array
   *   Request data array.
   */
  public function getRequestData(\TMGMTJob $job, $node) {
    // Setting out the node object property.
    $this->node = $node;
    // Setting out the job property.
    $this->job = $job;
    // Setting out the translator property.
    $this->translator = $job->getTranslator();
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
      'client_id' => t('Job ID: @tjid', array('@tjid' => $this->job->identifier())),
      'title' => $this->node->title,
      'author' => $settings['organization']['author'],
      'responsible' => $settings['organization']['responsible'],
      'requester' => $settings['organization']['requester'],
      'applicationId' => 'FPFIS',
      'delay' => $this->defaultDelayDate,
      'reference_files_remark' => url(drupal_get_path_alias('node/'.$this->node->nid), array('absolute' => TRUE)),
      'procedure' => 'NEANT',
      'destination' => 'PUBLIC',
      'type' => 'INTER',
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
      'user' => $settings['settings']['dgt_ftt_username'],
      'password' => $settings['settings']['dgt_ftt_password'],
      'address' => _ne_tmgmt_dgt_ftt_translator_get_client_wsdl(),
      'path' => 'OEPoetryCallback',
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
          'code' => strtoupper($this->node->language),
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
        'nickname' => $settings['contacts']['secretaire'],
      ),
      array(
        'type' => 'contact',
        'nickname' => $settings['contacts']['secretaire'],
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
    return array(
      array(
        'action' => 'INSERT',
        'format' => 'HTML',
        'language' => strtoupper($this->node->language),
        'delay' => $this->defaultDelayDate,
      ),
    );
  }

  /**
   * Provides BASE64 encoded content from the node.
   *
   */
  private function getContent() {
    // Load data exporter.
    $controller = tmgmt_file_format_controller($this->job->getSetting('export_format'));

    // Generate the data into a XML format and encode it to be translated.
    $export = $controller->export($this->job);

    return base64_encode($export);
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
  public function getRequestIdentifier(TMGMTJob $job, $node_id) {
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
        $identifier['identifier.part'] = $mapping_entity->part + 1;
        $unset_key = 'identifier.sequence';
      }
    }

    unset($identifier[$unset_key]);

    // Checking if there are mappings for the given content and setting version.
    if ($mapping_entity = $this->getDgtFttTranslatorMappingByProperty('entity_id', $node_id)) {
      $identifier['identifier.version'] = $mapping_entity->version + 1;
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

    return array(
      'identifier.code' => $settings['dgt_code'],
      'identifier.year' => date("Y"),
      'identifier.sequence' => $settings['dgt_counter'],
      'client.wsdl' => _ne_tmgmt_dgt_ftt_translator_get_client_wsdl(),
      'service.wsdl' => 'http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'service.username' => $settings['dgt_ftt_username'],
      'service.password' => $settings['dgt_ftt_password'],
    );
  }

  /**
   * Provides the latest DGT FTT Translator Mapping entity.
   *
   * @return DgtFttTranslatorMapping/bool
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
   * @return DgtFttTranslatorMapping entity | bool
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
   * Provides IDs of TMGMT Job Items which are under translation processes.
   *
   * @param string $entity_id
   *   Entity ID (for some edge cases the string type can appear).
   *
   * @return array|bool
   *   An array with IDs or FALSE if no items where found.
   */
  protected function getActiveTmgmtJobItemsIds($entity_id) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'tmgmt_job_item')
      ->propertyCondition('item_id', $entity_id)
      ->propertyCondition('state', array(TMGMT_JOB_ITEM_STATE_ACTIVE, TMGMT_JOB_ITEM_STATE_REVIEW));

    $results = $query->execute();

    if (isset($results['tmgmt_job_item'])) {

      return array_keys($results['tmgmt_job_item']);
    }

    return FALSE;
  }

}
