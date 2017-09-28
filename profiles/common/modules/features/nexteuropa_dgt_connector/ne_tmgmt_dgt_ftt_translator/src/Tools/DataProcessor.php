<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator helper functions.
 */

/**
 * Helper trait with methods for processing translator's data and settings.
 */
namespace Drupal\ne_tmgmt_dgt_ftt_translator\Tools;

use Drupal\ne_tmgmt_dgt_ftt_translator\Entity\DgtFttTranslatorMapping;
use \EntityFieldQuery;
use \TMGMTJob;
use \TMGMTTranslator;

trait DataProcessor {
  /** @var  \TMGMTTranslator */
  private $translator;

  /**
   * Translator settings keys
   * @var array
   */
  private $settingsKeys = array('settings', 'organization', 'contacts');
  private $settings;
  private $translatorEntityType = 'ne_tmgmt_dgt_ftt_map';

  /**
   * Provides the data array for a request.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   * @param object $node
   *   Node object.

   * @return array
   *   Request data array.
   */
  public function getRequestData(\TMGMTJob $job, $node) {
    // Setting out the translator property.
    $this->translator = $job->getTranslator();
    $this->settings = $this->getTranslatorSettings();

    return array(
      'details' => $this->getRequestDetails($this->settings),
      'return_address' => $this->getReturnAddress($this->settings),
      'source' => $this->getSource($this->settings),
      'contact' => $this->getConstact($this->settings),
      'target' => $this->getTarget($this->settings),
    );
  }

  /**
   * Provides translator settings array.
   *
   * @return array
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
   *
   */
  private function getRequestDetails(array $settings) {

    return array();
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

    return array();
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

    return array();
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
  private function getConstact(array $settings) {

    return array();
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

    return array();
  }
  /**
   * Provides an identifier array in order to send a request.
   *
   * @param \TMGMTJob $job
   *   TMGMT Job object.
   * @param $node_id
   *   Node id
   * @return array|bool
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
   * Provides the latest 'ne_tmgmt_dgt_ftt_map' entity by passing a property
   * and its value.
   *
   * @param string $property_name
   *   Property name.
   * @param string $property_value
   *   Property value.
   *
   * @return bool|mixed
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
   * Provides an array with IDs of the TMGMT Job Items which are under
   * translation processes.
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
