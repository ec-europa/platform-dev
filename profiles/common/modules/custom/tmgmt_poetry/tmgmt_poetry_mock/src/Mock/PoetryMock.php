<?php

/**
 * @file
 * Contains Drupal\tmgmt_poetry_mock\Mock\PoetryMock.
 */

namespace Drupal\tmgmt_poetry_mock\Mock;

/**
 * Class provides mock of POETRY SOAP Web Service.
 */
class PoetryMock {
  const SOAP_METHOD = 'FPFISPoetryIntegrationRequest';
  public $settings;
  private $client;

  /**
   * PoetryMock constructor.
   */
  public function __construct() {
    $this->setPoetrySettings();
  }

  /**
   * Method for setting up Poetry specific settings.
   */
  public function setPoetrySettings() {
    $this->settings = variable_get('poetry_service');
  }

  /**
   * Method for instantiating SOAP Client based on given WSDL.
   *
   * @param string $wsdl_endpoint
   *    Absolute URL to the SOAP WSDL resource.
   */
  private function instantiateClient($wsdl_endpoint) {
    $this->client = new \SoapClient(
      $wsdl_endpoint,
      [
        'cache_wsdl' => WSDL_CACHE_NONE,
        'trace' => 1,
      ]
    );
  }

  /**
   * Simulate connection to webservice.
   *
   * @param string $user
   *   Username to connect to webservice.
   * @param string $password
   *   Password to connect to webservice.
   * @param string $message
   *   Message.
   *
   * @return string
   *   Message returned by webservice.
   */
  public static function requestService($user, $password, $message) {
    // Fetching and transforming data from the request.
    $response_xml = simplexml_load_string($message);
    $request = $response_xml->request;
    $demande_id = (array) $request->demandeId;
    $reference = implode("_", (array) $demande_id);

    // Saving translation request as a file with give reference ID.
    self::saveTranslationRequest($message, $reference);

    // Generating response XML based on template.
    $xml = theme('poetry_confirmation_of_receiving_translation_request', ['demande_id' => $demande_id]);

    // Sending response.
    return new \SoapVar('<requestServiceReturn><![CDATA[' . $xml . ']]> </requestServiceReturn>', \XSD_ANYXML);
  }

  /**
   * Helper method for saving requests coming to POETRY mock.
   *
   * @param string $message
   *    XML request.
   */
  public static function saveTranslationRequest($message, $reference) {
    $path = TMGMT_POETRY_MOCK_REQUESTS_PATH . $reference . '.xml';
    $dirname = dirname($path);
    if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      file_save_data($message, $path);
    }
    else {
      watchdog(
        'poetry_mock',
        'Unable to prepare requests directory',
        array(),
        WATCHDOG_ERROR
      );
    }
  }

  /**
   * Method for mimicking requests from Poetry to Drupal.
   *
   * @param string $message
   *    XML message which should be send.
   *
   * @return mixed
   *    Response from service.
   */
  public function sendRequestToDrupal($message) {
    $this->instantiateClient($this->settings['drupal_wsdl']);
    try {
      $response = $this->client->{self::SOAP_METHOD}(
        $this->settings['callback_user'],
        $this->settings['callback_password'],
        $message
      );
    }
    catch (Exception $exc) {
      watchdog_exception('tmgmt_poetry_mock', $exc);
    }

    return $response;
  }

  /**
   * Helper function which prepares translate response data.
   *
   * @param string $message
   *    Translation request XML data.
   * @param string $lg_code
   *    Language code. If ALL then all languages will be processed one by one.
   *
   * @return array Array with translation response data.
   *    Array with translation response data.
   */
  public static function prepareTranslationResponseData($message, $lg_code) {
    $data = self::getDataFromRequest($message);
    $requests = [];

    if (isset($data['attributions']) && isset($data['content']) && $lg_code == 'ALL') {
      foreach ($data['attributions'] as $attribution) {
        $requests[$attribution['language']] = self::getTranslationResponseData(
          $attribution,
          $data['content'],
          $data['demande_id']
        );
      }

      return $requests;
    }

    if ($lg_code != 'ALL') {
      $attribution = $data['attributions'][$lg_code];
      $requests[$lg_code] = self::getTranslationResponseData(
        $attribution,
        $data['content'],
        $data['demande_id']
      );

      return $requests;
    }

    return $requests;
  }

  /**
   * Helper function which prepares refuse job response data.
   *
   * @param string $message
   *    Translation request XML data.
   *
   * @return array Array with translation response data.
   *    Array with translation response data.
   */
  public static function prepareRefuseJobResponseData($message) {
    $data = self::getDataFromRequest($message);
    $languages = self::getLanguagesFromRequest($message);
    return [
      'languages' => $languages,
      'demande_id' => $data['demande_id'],
      'status' => 'REF',
      'format' => 'HTML',
    ];
  }

  /**
   * Helper function for setting up translation response data array.
   *
   * @param array $attribution
   *    Part of request which is related to given translation language request.
   * @param string $content
   *    Encoded content that was send for the translation.
   * @param array $demande_id
   *    Array with IDs regarding translation request.
   *
   * @return array
   *    Array with translation response data.
   */
  private static function getTranslationResponseData($attribution, $content, $demande_id) {
    return [
      'language' => $attribution['language'],
      'format' => $attribution['format'],
      'content' => self::translateRequestContent(
        $content,
        $attribution['language']
      ),
      'demande_id' => $demande_id,
    ];
  }

  /**
   * Helper method to fetch languages from translation request.
   *
   * @param string $message
   *    Translation request XML data.
   *
   * @return array
   *    Array with languages.
   */
  public static function getLanguagesFromRequest($message) {
    $request_data = self::getDataFromRequest($message);
    $languages = [];
    foreach ($request_data['attributions'] as $attribution) {
      $languages[$attribution['language']] = $attribution['language'];
    }

    return $languages;
  }

  /**
   * Helper function which prepares data from translation request.
   *
   * @param string $message
   *    Translation request content.
   *
   * @return array
   *    Array with data from translation request.
   */
  public static function getDataFromRequest($message) {
    $xml = simplexml_load_string($message);
    foreach ($xml->request->attributions as $attribution) {
      $attributions[(string) $attribution->attributes()->{'lgCode'}] = [
        'language' => (string) $attribution->attributes()->{'lgCode'},
        'format' => (string) $attribution->attributes()->{'format'},
      ];
    }

    return [
      'demande_id' => (array) $xml->request->demandeId,
      'content' => (string) $xml->request->documentSource->documentSourceFile,
      'attributions' => $attributions,
    ];
  }

  /**
   * Helper function to mimic translation by adding language prefix.
   *
   * @param string $content
   *    Content that should be translated (encoded HTML markup).
   * @param string $language
   *    Translation language.
   *
   * @return string
   *    Encoded translated content for the translation response.
   */
  private static function translateRequestContent($content, $language) {
    $decoded_content = base64_decode($content);
    $xml_content = simplexml_load_string($decoded_content);
    // Add language prefix to the title and body first paragraph.
    $title = (string) $xml_content->body->div->div[0];
    // Overwriting title with language prefix.
    $xml_content->body->div->div[0] = "[$language] " . $title;
    // Adding language prefix into the body.
    $xml_content->body->div->div[1]->p[] = "[$language]";
    $translated_content = explode("\n", $xml_content->asXML(), 2)[1];

    return base64_encode($translated_content);
  }

  /**
   * Helper method for fetching an entity details based on demande_id.
   *
   * @param array $demande_id
   *    An array with identifiers for POETRY translation request.
   *
   * @return mixed
   *    An array with result.
   */
  public static function getEntityDetailsByDemandeId($demande_id) {
    return db_select('poetry_map', 'pm')
      ->fields('pm', ['entity_type', 'entity_id'])
      ->condition('annee', $demande_id['annee'], '=')
      ->condition('numero', $demande_id['numero'], '=')
      ->condition('version', $demande_id['version'], '=')
      ->condition('partie', $demande_id['partie'], '=')
      ->execute()
      ->fetchAssoc();
  }

  /**
   * Helper method for fetching all translation request files.
   *
   * @return array
   *    An array with objects or an empty one if there is no results.
   */
  public static function getAllRequestTranslationFiles() {
    $result = db_select('file_managed', 'fm')
      ->fields('fm', ['fid'])
      ->condition('filemime', 'application/xml', '=')
      ->condition('uri', db_like(TMGMT_POETRY_MOCK_REQUESTS_PATH) . '%', 'LIKE')
      ->orderBy('timestamp', 'DESC')
      ->execute()
      ->fetchAllAssoc('fid');

    if ($result) {
      return file_load_multiple(array_keys($result));
    }

    return [];
  }

  /**
   * Helper method for removing all translation request files.
   */
  public static function removeAllRequestTranslationFiles() {
    db_delete('file_managed')
      ->condition('filemime', 'application/xml', '=')
      ->condition('uri', db_like(TMGMT_POETRY_MOCK_REQUESTS_PATH) . '%', 'LIKE')
      ->execute();
  }

  /**
   * Helper method for fetching active translation jobs based on give entity id.
   *
   * @param int $entity_id
   *    Entity id.
   *
   * @return mixed
   *    An array of results with active translation jobs for given entity id.
   */
  public static function getActiveTranslationJobsByEntityId($entity_id) {
    $query = db_select('tmgmt_job_item', 'item');
    $query->join('tmgmt_job', 'job', 'item.tjid = job.tjid');
    $query->groupBy('job.tjid');
    $query->condition('item.item_id', $entity_id, '=');
    $query->condition('job.state', TMGMT_JOB_STATE_ACTIVE, '=');
    // List of available fields form tmgmt_job_item column.
    $query->fields('item', [
      'tjiid',
      'item_type',
      'item_id',
      'state',
    ]
    );
    // List of available fields form tmgmt_job column.
    $query->fields('job', [
      'tjid',
      'reference',
      'source_language',
      'target_language',
      'state',
      'changed',
    ]
    );

    $result = $query->execute()->fetchAllAssoc('tjid');
    return $result;
  }

  /**
   * Helper method for translating job based on given parameters.
   *
   * @param string $lg_code
   *    Language code.
   * @param int $file_id
   *    Translation request file dump ID.
   * @param string $entity_type
   *    An entity type.
   * @param int $entity_id
   *    An entity id.
   */
  public function translateJob($lg_code, $file_id, $entity_type, $entity_id) {
    if ($lg_code and $file_id) {
      $file_object = file_load($file_id);
      $message = file_get_contents($file_object->uri);
      // Prepare responses array.
      $responses = self::prepareTranslationResponseData($message, strtoupper($lg_code));
      foreach ($responses as $response) {
        $message = theme('poetry_receive_translation', $response);
        $this->sendRequestToDrupal($message);
      }
      // Redirect to translate tab for given entity ID.
      drupal_goto($entity_type . '/' . $entity_id . '/translate');
    }
  }

  /**
   * Helper method for refusing job translation based on given data.
   *
   * @param int $file_id
   *    Translation request file dump ID.
   * @param string $entity_type
   *    An entity type.
   * @param int $entity_id
   *    An entity id.
   */
  public function refuseJob($file_id, $entity_type, $entity_id) {
    if ($file_id) {
      $file_object = file_load($file_id);
      $message = file_get_contents($file_object->uri);
      // Prepare responses array.
      $response = self::prepareRefuseJobResponseData($message);
      $message = theme('poetry_refuse_translation', $response);
      $this->sendRequestToDrupal($message);

      // Redirect to translate tab for given entity ID.
      drupal_goto($entity_type . '/' . $entity_id . '/translate');
    }
  }

  /**
   * Get the poetry demande_id from a tmgmt_poetry job reference.
   *
   * @param string $job_reference
   *   The tmgmt_poetry job reference.
   *
   * @return array
   *   The poetry demande_id data.
   */
  private static function getDemandeIdFromJobReference($job_reference) {
    $parts = array(
      '(?<codeDemandeur>[a-z0-9]+)',
      '(?<annee>[0-9]+)',
      '(?<numero>[0-9]+)',
      '(?<version>[0-9]+)',
      '(?<partie>[0-9]+)',
      '(?<produit>[a-z0-9]+)',
    );
    $pattern = '@' . implode('/', $parts) . '$@i';
    preg_match(
      $pattern,
      $job_reference,
      $matches
    );

    return array(
      'codeDemandeur' => $matches['codeDemandeur'],
      'annee' => $matches['annee'],
      'numero' => $matches['numero'],
      'version' => $matches['version'],
      'partie' => $matches['partie'],
      'produit' => $matches['produit'],
    );
  }

  /**
   * Gets the translation request data by their tmgmt_poetry job reference.
   *
   * @param string $job_reference
   *   A tmgmt_poetry job reference.
   */
  public static function getTranslationRequestByJobReference($job_reference) {
    $demande_id = self::getDemandeIdFromJobReference($job_reference);

    $file_path = TMGMT_POETRY_MOCK_REQUESTS_PATH . implode('_', $demande_id) . '.xml';

    $result = db_select('file_managed', 'fm')
      ->fields('fm', ['fid'])
      ->condition('filemime', 'application/xml', '=')
      ->condition('uri', $file_path)
      ->execute()
      ->fetchAllAssoc('fid');

    if ($result) {
      return array(
        'demande_id' => $demande_id,
        'file' => file_load(key($result)),
      );
    }
  }

}
