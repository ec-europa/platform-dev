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

    // Create initial XML element using POETRY headers.
    $xml = new SimpleXMLElement("<?xml version=\"1.0\" encoding=\"utf-8\" ?>
<POETRY xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
xsi:noNamespaceSchemaLocation=\"http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd\">
</POETRY>");

    // Add main request element.
    $request = $xml->addChild('request');
    $request->addAttribute('communication', 'asynchrone');
    $request->addAttribute('id', implode("/", $id_data));
    $request->addAttribute('type', 'newPost');

    // Add the ID to the request.
    $demande_id = $request->addChild('demandeId');
    foreach ($id_data as $key => $value) {
      $demande_id->addChild($key, $value);
    }

    // Add request information.
    $organization = $job->settings['organization'];
    $demande = $request->addChild('demande');
    $demande->addChild('userReference', 'Job ID ' . $job->tjid);

    $website_identifier = $this->settings['website_identifier'];
    if (isset($website_identifier)) {
      $request_title = "NE-CMS: {$website_identifier} - {$job->label}";
    }
    else {
      $request_title = 'NE-CMS: ' . $job->label;
    }

    $demande->titre = $request_title;
    $demande->organisationResponsable = $organization['responsable'];
    $demande->organisationAuteur = $organization['auteur'];
    $demande->serviceDemandeur = $organization['demandeur'];
    $demande->addChild('applicationReference', 'FPFIS');
    $demande->addChild('delai', date('d/m/Y', strtotime($job->settings['delai'])));
    $demande->remarque = $job->settings['remark'];

    // Add the source url as a reference.
    $source_url = url('<front>', array('absolute' => TRUE));
    $demande->addChild('referenceFilesNote', $source_url);

    $procedure = $demande->addChild('procedure');
    $procedure->addAttribute('id', 'NEANT');

    $destination = $demande->addChild('destination');
    $destination->addAttribute('id', 'PUBLIC');

    $type = $demande->addChild('type');
    $type->addAttribute('id', 'INTER');

    // Get contact information from translator and add it to the request.
    foreach ($job->settings['contacts'] as $contact_type => $contact_nickname) {
      $contacts = $request->addChild('contacts');
      $contacts->addAttribute('type', $contact_type);
      $contacts->contactNickname = $contact_nickname;
    }

    // Add callback information to the request.
    $retour = $request->addChild('retour');
    $retour->addAttribute('type', 'webService');
    $retour->addAttribute('action', 'UPDATE');
    $retour->addChild('retourUser', $this->settings['callback_user']);
    $retour->addChild('retourPassword', $this->settings['callback_password']);
    $retour->addChild('retourAddress', $this->settings['callback_address']);
    $retour->addChild('retourPath', $this->settings['callback_path']);
    $retour->addChild('retourRemark', '');

    // Add the content to be translated.
    $filename = 'content.html';
    $document_source = $request->addChild('documentSource');
    $document_source->addAttribute('format', 'HTML');
    $document_source->addChild('documentSourceName', $filename);
    $language = $document_source->addChild('documentSourceLang');
    $language->addAttribute('lgCode', drupal_strtoupper($translator
      ->mapToRemoteLanguage($job->source_language)));
    $language->addChild('documentSourceLangPages', '1');
    $document_source->addChild('documentSourceFile', $content);

    $languages_to_request = array_merge(
      array($job->target_language => $job->target_language),
      $job->settings['languages']
    );

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
        $attribution = $request->addChild('attributions');
        $attribution->addAttribute('format', 'HTML');
        $attribution->addAttribute('lgCode', drupal_strtoupper($translator
          ->mapToRemoteLanguage($job_additional_lang_key)));
        $attribution->addAttribute('action', $attribute_action);
        $attribution_delai = $attribution->addChild('attributionsDelai', date('d/m/Y', strtotime($job->settings['delai'])));
        $attribution_delai->addAttribute('format', 'DD/MM/YYYY ');
      }
    }

    $msg = $xml->asXML();

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
