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
  const TRANSLATOR_NAME = 'tmgmt_poetry_test_translator';
  const TRANSLATOR_LABEL = 'TMGMT Poetry Test translator';
  const COUNTER_STRING = 'NEXT_EUROPA_COUNTER';
  const COUNTER_VALUE = '1234';
  const COUNTER_VALUE_NOK = '-1';
  const CALLBACK_USER = 'Callback';
  const CALLBACK_PASSWORD = 'CallbackPWD';
  const POETRY_USER = 'Poetry';
  const POETRY_PASSWORD = 'PoetryPWD';
  public $settings;
  public $credentials;
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
    $this->credentials = array(
      'callback_user' => CALLBACK_USER,
      'callback_password' => CALLBACK_PASSWORD,
      'poetry_user' => POETRY_USER,
      'poetry_password' => POETRY_PASSWORD,
    );
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
      array(
        'cache_wsdl' => WSDL_CACHE_NONE,
        'trace' => 1,
      )
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

    // This is to deal with initial request when website doesn't have counter.
    if (isset($demande_id['sequence'])) {
      if ($demande_id['sequence'] == self::COUNTER_STRING) {
        $demande_id['numero'] = self::COUNTER_VALUE;
        unset($demande_id['sequence']);
      }
      else {
        $demande_id['numero'] = self::COUNTER_VALUE_NOK;
        // Generating response XML based on template.
        $xml = theme(
          'poetry_confirmation_of_receiving_translation_request_error_configuration',
          array(
            'demande_id' => $demande_id,
            'message' => t(
              "Error in xmlActions:newRequest: Counter name not found (code_demandeur=@codedemandeur, compteur=@sequence, year=@annee)",
              array(
                "@codedemandeur" => $demande_id['codeDemandeur'],
                "@sequence" => $demande_id['sequence'],
                "@annee" => $demande_id['annee'],
              )
            ),
          )
        );
        // Sending response.
        return new \SoapVar('<requestServiceReturn><![CDATA[' . $xml . ']]> </requestServiceReturn>', \XSD_ANYXML);
      }
    }
    $reference = self::prepareReferenceNumber($demande_id);

    // Saving translation request as a file with give reference ID.
    self::saveTranslationRequest($message, $reference);

    // Generating response XML based on template.
    $xml = theme(
      'poetry_confirmation_of_receiving_translation_request',
      array('demande_id' => $demande_id)
    );

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
        $this->credentials['callback_user'],
        $this->credentials['callback_password'],
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
    $requests = array();
    if (isset($data['demande_id']['sequence'])) {
      $data['demande_id']['numero'] = self::COUNTER_VALUE;
    }
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
    // Initial translation request.
    if (isset($data['demande_id']['sequence'])) {
      unset($data['demande_id']['sequence']);
      $data['demande_id']['numero'] = self::COUNTER_VALUE;
    }
    // In case if numero is not set.
    if (!isset($data['demande_id']['numero'])) {
      $data['demande_id']['numero'] = self::COUNTER_VALUE;
    }

    return array(
      'languages' => $languages,
      'demande_id' => $data['demande_id'],
      'status' => 'REF',
      'format' => 'HTML',
    );
  }

  /**
   * Prepares status request data.
   *
   * @param array $demande_id
   *   'Demande ID' array.
   * @param string $status_code
   *   Status code.
   * @param string $request_status_msg
   *   Request status message.
   * @param string $demande_status_msg
   *   'Demande' status message.
   * @param string $lg_code
   *   Language code.
   *
   * @return array
   *   Array with data status request data.
   */
  public static function prepareSendStatusData($demande_id, $status_code, $request_status_msg, $demande_status_msg, $lg_code) {
    return array(
      'demande_id' => $demande_id,
      'format' => 'HTML',
      'status_code' => $status_code,
      'request_status_msg' => $request_status_msg,
      'demande_status_msg' => $demande_status_msg,
      'lg_code' => $lg_code,
    );
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
    return array(
      'language' => $attribution['language'],
      'format' => $attribution['format'],
      'content' => self::translateRequestContent(
        $content,
        $attribution['language']
      ),
      'demande_id' => $demande_id,
    );
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
    $languages = array();
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
      $attributions[(string) $attribution->attributes()->{'lgCode'}] = array(
        'language' => (string) $attribution->attributes()->{'lgCode'},
        'format' => (string) $attribution->attributes()->{'format'},
      );
    }

    $contacts = array();
    foreach ($xml->request->contacts as $contact) {
      $contacts[] = array(
        'type' => (string) $contact->attributes()->type,
        'nickname' => (string) $contact->contactNickname,
      );
    }

    return array(
      'demande_id' => (array) $xml->request->demandeId,
      'demande' => (array) $xml->request->demande,
      'contacts' => $contacts,
      'content' => (string) $xml->request->documentSource->documentSourceFile,
      'attributions' => $attributions,
    );
  }

  /**
   * Helper function to mimic translation by adding language prefix.
   *
   * The code is based on _tmgmt_poetry_replace_job_in_content().
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
    $dom = new \DOMDocument();
    multisite_drupal_toolbox_load_html($dom, $decoded_content);
    if ($dom->documentElement->hasAttributeNS(NULL, 'xmlns')) {
      $dom->documentElement->removeAttributeNS(NULL, 'xmlns');
    }
    $xml_content = simplexml_import_dom($dom);
    // Add language prefix to the title and body first paragraph.
    $title = (string) $xml_content->body->div->div[0];
    // Overwriting title with language prefix.
    $xml_content->body->div->div[0] = "[$language] $title";
    // Adding language prefix into the body.
    $xml_content->body->div->div[1]->p[] = "[$language]";
    $translated_content = '<!DOCTYPE html PUBLIC
        "-//W3C//DTD XHTML 1.0 Strict//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">' . PHP_EOL .
      $xml_content->asXML();
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
      ->fields('pm', array('entity_type', 'entity_id'))
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
      ->fields('fm', array('fid'))
      ->condition('filemime', 'application/xml', '=')
      ->condition('uri', db_like(TMGMT_POETRY_MOCK_REQUESTS_PATH) . '%', 'LIKE')
      ->orderBy('timestamp', 'DESC')
      ->execute()
      ->fetchAllAssoc('fid');

    if ($result) {
      return file_load_multiple(array_keys($result));
    }

    return array();
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
    $query->fields(
      'item',
      array(
        'tjiid',
        'item_type',
        'item_id',
        'state',
      )
    );
    // List of available fields form tmgmt_job column.
    $query->fields(
      'job',
      array(
        'tjid',
        'reference',
        'source_language',
        'target_language',
        'state',
        'changed',
      )
    );

    $result = $query->execute()->fetchAllAssoc('tjid');
    return $result;
  }

  /**
   * Prepare to translate job based on given parameters.
   *
   * @param string $lg_code
   *    Language code.
   * @param int $file_id
   *    Translation request file dump ID.
   * @param int $tjiid
   *    A translation job item ID.
   */
  public function translateJob($lg_code, $file_id, $tjiid) {
    if ($lg_code and $file_id) {
      $file_object = file_load($file_id);
      $message = file_get_contents($file_object->uri);
      // Prepare responses array.
      $responses = self::prepareTranslationResponseData($message, strtoupper($lg_code));
      foreach ($responses as $response) {
        $message = theme('poetry_receive_translation', $response);
        $this->sendRequestToDrupal($message);
      }
      $msg = t('Translation was received. !link.', array(
        '!link' => l(
            t('Check the translation page'),
            _tmgmt_poetry_mock_get_job_item_entity_path($tjiid, TRUE)
        ),
      ));
      drupal_set_message($msg, 'status');
    }
    else {
      drupal_set_message(t('Error, data was missing.'), 'error');
    }
    drupal_goto();
  }

  /**
   * Prepare to refuse job translation based on given data.
   *
   * @param int $file_id
   *    Translation request file dump ID.
   * @param int $tjiid
   *    A translation job item ID.
   */
  public function refuseJob($file_id, $tjiid) {
    if ($file_id) {
      $file_object = file_load($file_id);
      $message = file_get_contents($file_object->uri);
      // Prepare responses array.
      $response = self::prepareRefuseJobResponseData($message);
      $message = theme('poetry_refuse_translation', $response);
      $this->sendRequestToDrupal($message);
      $msg = t('Translation was refused. !link.', array(
        '!link' => l(
          t('Check the translation page'),
          _tmgmt_poetry_mock_get_job_item_entity_path($tjiid, TRUE)
        ),
      ));
      drupal_set_message($msg, 'status');
    }
    else {
      drupal_set_message(t('Error, data was missing.'), 'error');
    }
    drupal_goto();
  }

  /**
   * Sends given status with messages to Drupal.
   *
   * @param int $job_id
   *   TMGMT Poetry Job ID.
   * @param string $status_code
   *   The status code.
   * @param string $request_status_msg
   *   The request status message.
   * @param string $demande_status_msg
   *   The 'demande' status message.
   */
  public function sendStatus($job_id, $status_code, $request_status_msg, $demande_status_msg) {
    $job = tmgmt_job_load($job_id);
    $lg_code = drupal_strtoupper($job->getTranslator()->mapToRemoteLanguage($job->target_language));
    $status_code = drupal_strtoupper($status_code);
    $demande_id = self::prepareDemandeIdArray($job->reference);

    // Prepare responses array.
    $data = self::prepareSendStatusData($demande_id, $status_code, $request_status_msg, $demande_status_msg, $lg_code);
    $message = theme('poetry_send_status', $data);
    $this->sendRequestToDrupal($message);
    $entity = self::getEntityDetailsByDemandeId($demande_id);
    $msg = t(
      'The status request was sent. !link.',
      array(
        '!link' => l(
          t('Check the translation page'),
          $entity['entity_type'] . '/' . $entity['entity_id'] . '/translate'
        ),
      )
    );
    drupal_set_message($msg, 'status');
    drupal_goto();
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

    $demande_id = array();
    if (isset($matches['codeDemandeur'])) {
      $demande_id['codeDemandeur'] = $matches['codeDemandeur'];
    }
    if (isset($matches['annee'])) {
      $demande_id['annee'] = $matches['annee'];
    }
    if (isset($matches['numero'])) {
      $demande_id['numero'] = $matches['numero'];
    }
    if (isset($matches['version'])) {
      $demande_id['version'] = $matches['version'];
    }
    if (isset($matches['partie'])) {
      $demande_id['partie'] = $matches['partie'];
    }
    if (isset($matches['produit'])) {
      $demande_id['produit'] = $matches['produit'];
    }

    return $demande_id;
  }

  /**
   * Gets the translation request data by their tmgmt_poetry job reference.
   *
   * @param string $job_reference
   *   A tmgmt_poetry job reference.
   *
   * @return array
   *   An array with reference and request file details.
   */
  public static function getTranslationRequestByJobReference($job_reference) {
    $demande_id = self::getDemandeIdFromJobReference($job_reference);

    $file_name = self::prepareReferenceNumber($demande_id) . '.xml';

    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'file')
      ->propertyCondition('filename', $file_name);
    $result = $query->execute();

    if (count($result['file']) == 1) {
      $file_info = reset($result['file']);

      return array(
        'demande_id' => $demande_id,
        'file' => file_load($file_info->fid),
      );
    }

    if (count($result['file']) > 1) {
      $file_info = reset($result['file']);

      return array(
        'demande_id' => $demande_id,
        'file' => file_load($file_info->fid),
        'files' => $result['file'],
      );
    }
  }

  /**
   * Returning properly formatted reference number string.
   *
   * @param array $demande_id
   *   An array with reference elements.
   *
   * @return string
   *   The string with properly formatted reference number.
   */
  public static function prepareReferenceNumber($demande_id) {
    return $demande_id['codeDemandeur']
      . '_' . $demande_id['annee']
      . '_' . $demande_id['numero']
      . '_' . $demande_id['version']
      . '_' . $demande_id['partie']
      . '_' . $demande_id['produit'];
  }

  /**
   * Returns 'Demande ID' array based on given job reference.
   *
   * @param string $reference
   *   TMGMT Poetry Job reference.
   *
   * @return array
   *   'Demande ID' array.
   */
  public static function prepareDemandeIdArray($reference) {
    $demande_id = array();
    $req_id_split = explode('_POETRY_', $reference);
    $request_id = end($req_id_split);
    $demande = explode('/', $request_id);

    if (count($demande) == 6) {
      $demande_id['codeDemandeur'] = $demande[0];
      $demande_id['annee'] = $demande[1];
      $demande_id['numero'] = $demande[2];
      $demande_id['version'] = $demande[3];
      $demande_id['partie'] = $demande[4];
      $demande_id['produit'] = $demande[5];
    }

    return $demande_id;
  }

}
