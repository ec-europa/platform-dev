<?php

/**
 * @file
 * Module file of the Poetry DGT Connector.
 */

/**
 * Class DGTConnector.
 */
class DGTConnector {

  private $settings;

  /**
   * DGTConnector constructor.
   *
   * @param array $settings
   *   Hold needed information for the connector.
   */
  public function __construct($settings) {

    $this->settings = $settings;

    // Generate the callback parameters.
    $this->settings['callback_address'] = url(drupal_get_path("module", "tmgmt_poetry") . "/wsdl/PoetryIntegration.wsdl", array(
      'absolute' => TRUE,
      'language' => (object) array('language' => FALSE),
    ));
    $this->settings['callback_path'] = 'FPFISPoetryIntegrationRequest';
  }

  /**
   * Send request to DGT.
   *
   * @param array $id_data
   *    Data for request.
   * @param \TMGMTPoetryJob $job
   *    Job for request.
   * @param string $content
   *    Content for request.
   *
   * @return string
   *    Response.
   */
  public function doRequest($id_data, TMGMTPoetryJob $job, $content) {

    $translator = $job->getTranslator();

    // Add request information.
    $organization = $job->settings['organization'];

    $website_identifier = $this->settings['website_identifier'];
    if (isset($website_identifier)) {
      $request_title = "NE-CMS: {$website_identifier} - {$job->label}";
    }
    else {
      $request_title = 'NE-CMS: ' . $job->label;
    }

    $delai = date('d/m/Y', strtotime($job->settings['delai']));

    // Add the source url as a reference.
    $source_url = url('<front>', array('absolute' => TRUE));

    $settings = $this->settings;

    // Add the content to be translated.
    $language = drupal_strtoupper($translator
      ->mapToRemoteLanguage($job->source_language));

    $languages_to_request = array_merge(
      array($job->target_language => $job->target_language),
      $job->settings['languages']
    );

    $request_languages = [];
    foreach ($languages_to_request as $job_additional_lang_key => $job_additional_lang_value) {
      $attribute_action = NULL;
      if (isset($job->settings['translations']['removed']) && in_array($job_additional_lang_key, $job->settings['translations']['removed'])) {
        $attribute_action = 'DELETE';
      }
      elseif (!empty($job_additional_lang_value)) {
        if ((isset($job->settings['translations']['added']) && in_array($job_additional_lang_key, $job->settings['translations']['added']))
          || !isset($job->settings['translations'])
        ) {
          $attribute_action = 'INSERT';
        }
      }
      if (!empty($attribute_action)) {
        $request_languages[] = [
          'lgCode' => drupal_strtoupper($translator
            ->mapToRemoteLanguage($job_additional_lang_key)),
          'action' => $attribute_action,
          'delai' => date('d/m/Y', strtotime($job->settings['delai'])),
        ];
      }
    }

    $request_id = implode("/", $id_data);

    ob_start();
    include(drupal_get_path("module", "nexteuropa_dgt_connector") . '/libraries/dgt_connector/templates/request.tpl.php');
    $msg = ob_get_clean();

    $settings = $translator->getSetting('settings');
    $msg_watchdog = htmlentities("Send request: " . $msg);
    watchdog('tmgmt_poetry', $msg_watchdog, array(), WATCHDOG_DEBUG);

    // Get Poetry configuration.
    $poetry = variable_get("poetry_service");

    // Create soap client.
    try {
      $client = new SoapClient($poetry['address'], array(
        'cache_wsdl' => WSDL_CACHE_NONE,
      ));
    }
    catch (Exception $e) {
      watchdog_exception('tmgmt_poetry', $e);
    }

    if ($client) {
      // Send the SOAP request and handle possible errors.
      try {
        $method = $poetry['method'];
        $response = $client->$method($settings['poetry_user'],
          $settings['poetry_password'], $msg);
      }
      catch (Exception $e) {
        watchdog_exception('tmgmt_poetry', $e);
        $response = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><POETRY xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"\">
                     <request communication=\"asynchrone\" type=\"status\"><status code=\"-1\" type=\"request\">
                     <statusMessage>" . $e->getMessage() . "</statusMessage></status></request></POETRY>";
      }
      return $response;
    }
  }

}
