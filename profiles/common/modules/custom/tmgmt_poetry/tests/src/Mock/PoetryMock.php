<?php

namespace Drupal\tmgmt_poetry_test\Mock;

/**
 * Class provides mock of POETRY SOAP Web Service.
 */
class PoetryMock {
  const SOAP_METHOD = 'FPFISPoetryIntegrationRequest';
  public $drupalWsdl;
  public $poetryWsdl;
  private $settings;
  private $client;

  /**
   * PoetryMock constructor.
   */
  public function __construct() {
    // Setting up WSDL endpoints.
    $this->setDrupalWsdl();
    $this->setPoetryWsdl();

    // Fetching settings.
    $this->settings = variable_get('poetry_service');
  }

  /**
   * Setting up Drupal WSDL endpoint URL.
   */
  public function setDrupalWsdl() {
    $this->drupalWsdl = url(
      drupal_get_path("module", "tmgmt_poetry") . "/wsdl/PoetryIntegration.wsdl",
      array(
        'absolute' => TRUE,
        'language' => (object) array('language' => FALSE),
      )
    );
  }

  /**
   * Setting up Poetry WSDL endpoint URL.
   */
  public function setPoetryWsdl() {
    $this->poetryWsdl = url(
      drupal_get_path("module", "tmgmt_poetry_test") . "/tmgmt_poetry_test.wsdl",
      array(
        'absolute' => TRUE,
        'language' => (object) array('language' => FALSE),
      )
    );
  }

  /**
   * Method for returning Poetry settings.
   *
   * @return array
   *    Poetry settings array.
   */
  public function getSettings() {
    return $this->settings;
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

  public function instantiateServer() {
    $uri = url('tmgmt_poetry_test/soap_server', array('absolute' => TRUE, 'language' => (object) array('language' => FALSE)));
    // When in non-wsdl mode the uri option must be specified.
    $options = array('uri' => $uri);
    // Create a new SOAP server.
    $server = new \SoapServer($this->poetryWsdl, $options);
    // Attach the API class to the SOAP Server.
    $server->setClass('Drupal\tmgmt_poetry_test\Mock\PoetryMock');
    // Start the SOAP requests handler.
    $server->handle();
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
  public function requestService($user, $password, $message) {
    // asXML method always adds '\n' after header which for some systems
    // is causing issues. Function beneath is striping of added header.
    $message = explode("\n", $message, 2)[1];
    $response_xml = simplexml_load_string($message);
    $request = $response_xml->request;
    $demande_id = (array) $request->demandeId;
    if (!isset($demande_id['numero'])) {
      $demande_id['numero'] = rand(10000, 99999);
    }

    $xml = theme('poetry_confirmation_of_receiving_translation_request',
      array(
        'demande_id' => $demande_id,
      )
    );

    $this->saveTranslationRequest($message);

    return new \SoapVar('<requestServiceReturn><![CDATA[' . $xml . ']]> </requestServiceReturn>', \XSD_ANYXML);
  }

  /**
   * Helper method for saving requests coming to POETRY mock.
   *
   * @param string $message
   *    XML request.
   */
  private function saveTranslationRequest($message) {
    $xml = simplexml_load_string($message);
    $request = $xml->request;
    $reference = implode("_", (array) $request->demandeId);

    $path = TMGMT_POETRY_TEST_REQUESTS_PATH . $reference . '.xml';
    $dirname = dirname($path);
    if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
      file_save_data($message, $path);
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
    $this->instantiateClient($this->drupalWsdl);
    try {
      $response = $this->client->{self::SOAP_METHOD}(
        $this->settings['callback_user'],
        $this->settings['callback_password'],
        $message
      );
    }
    catch (Exception $exc) {
      watchdog_exception('tmgmt_poetry_test', $exc);
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
    return array(
      'languages' => $languages,
      'demande_id' => $data['demande_id'],
      'status' => 'REF',
      'format' => 'HTML',
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

    return array(
      'demande_id' => (array) $xml->request->demandeId,
      'content' => (string) $xml->request->documentSource->documentSourceFile,
      'attributions' => $attributions,
    );
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
    $body = (string) $xml_content->body->div->div[1]->p;
    // Overwriting title with language prefix.
    $xml_content->body->div->div[0] = "[$language] " . $title;
    // Overwriting body with language prefix.
    $xml_content->body->div->div[1] = '<p>' . "[$language] " . $body . '</p>';
    $translated_content = explode("\n", $xml_content->asXML(), 2)[1];

    return base64_encode($translated_content);
  }

}
