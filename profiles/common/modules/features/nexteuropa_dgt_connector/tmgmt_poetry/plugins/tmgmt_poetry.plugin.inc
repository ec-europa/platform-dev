<?php

/**
 * @file
 * Provides Poetry translation plugin controller.
 */

/**
 * DGT Connector translation plugin controller.
 */
class TMGMTPoetryTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {
  const COMMUNICATION_SYNCHRONE = 'synchrone';
  const COMMUNICATION_ASYNCHRONE = 'asynchrone';
  const REQUEST_TYPE_NEW_POST = 'newPost';

  /**
   * Translation service URL.
   *
   * @var string
   */

  /**
   * Override parent defaultSettings method.
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
    $poetry_settings = array('settings', 'organization', 'contacts');
    $poetry_service = array(
      'address',
      'method',
    );

    $all_settings = array();
    $poetry_hard_settings = variable_get('poetry_service');

    // If the configuration in the settings.php is missing don't check further.
    if (empty($poetry_hard_settings)) {
      return FALSE;
    }

    // Get setting value for each setting.
    foreach ($poetry_settings as $setting) {
      $all_settings[$setting] = $translator->getSetting($setting);
    }

    // If one of the arg is not set, don't check further.
    foreach ($poetry_service as $service_arg) {
      if (isset($poetry_hard_settings[$service_arg])) {
        $all_settings[$service_arg] = $poetry_hard_settings[$service_arg];
      }
      else {
        return FALSE;
      }
    }

    // If any of these are empty, the translator is not properly configured.
    foreach ($all_settings as $key => $value) {
      if (empty($value)) {
        return FALSE;
      }
    };

    return TRUE;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::canTranslation().
   *
   * We will check are source and target language supported
   * and the number of items.
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    // Check that only one item is being requested.
    $items = $job->getItems();
    if (count($items) > 1) {
      return FALSE;
    }
    // Check that the item does not have pending requests.
    $item = array_shift($items);
    if (!empty($item)) {
      $results = db_select('tmgmt_job_item', 'tji')
        ->fields('tji', array('tjid', 'tjiid'))
        ->condition('item_type', $item->item_type, '=')
        ->condition('item_id', $item->item_id, '=')
        ->execute()
        ->fetchAllAssoc('tjid');
      if ($results) {
        foreach ($results as $result) {
          if ($job = tmgmt_job_load($result->tjid)) {
            if ($job->hasPoetryTranslator() && $job->getState() == 1) {
              // Check the poetry status.
              $result_ps = db_select('poetry_status', 'ps')
                ->fields('ps', array('status'))
                ->condition('tjiid', $result->tjiid, '=')
                ->execute()
                ->fetchAssoc();
              if (empty($result_ps) || (!empty($result_ps) && $result_ps['status'] == POETRY_STATUS_MESSAGE_PEN)) {
                return FALSE;
              }
            }
          }
        }
      }
    }
    // All languages are supported at the moment.
    return TRUE;
  }

  /**
   * Implements getNotCanTranslateReason().
   *
   * Show the reason why we can not translate.
   */
  public function getNotCanTranslateReason(TMGMTJob $job) {
    if (count($job->getItems()) > 1) {
      return t('@translator can not translate more than 1 item per request.', array(
        '@translator' => $job->getTranslator()
          ->label(),
      ));
    }
    else {
      return t('An active translation for this item already exists');
    }
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::requestTranslation().
   */
  public function requestTranslation(TMGMTJob $job) {

    // Pull the source data array through the job and flatten it.
    $xml = $this->prepareDataForSending($job);
    // Request translation from MT@EC service.
    $response = $this->doRequest(array('xml' => $xml), $job);
    // Handling response.
    $response_xml = simplexml_load_string($response);
    // If it is not an xml response, the SOAP request failed.
    if (!$response_xml) {
      _tmgmt_poetry_tmgmt_job_reject(
        $job,
        "Rejected",
        "There was an error with the SOAP service.",
        $response
      );
    }
    else {
      $request = $response_xml->request;

      $statuses = $request->status;
      // Check the statuses of the response
      // in order to verify that everything is correct.
      foreach ($statuses as $status) {
        $message = (string) $status->statusMessage;
        if ($message != 'OK') {
          _tmgmt_poetry_tmgmt_job_reject(
            $job,
            "Rejected",
            "There was an error with the Poetry request.",
            $message
          );
        }
      }

      if (isset($request->demandeId)) {
        // Insert or update the mapping information.
        $demande_id = (array) $request->demandeId;
        $items = $job->getItems();
        $item = array_shift($items);

        $result = db_select('poetry_map', 'pm')
          ->fields('pm', array('annee', 'numero', 'version', 'partie'))
          ->condition('entity_type', $item->item_type, '=')
          ->condition('entity_id', $item->item_id, '=')
          ->execute()
          ->fetchAssoc();
        if (!$result) {
          db_insert('poetry_map')
            ->fields(array(
              'entity_type' => $item->item_type,
              'entity_id' => $item->item_id,
              'annee' => $demande_id['annee'],
              'numero' => $demande_id['numero'],
              'version' => $demande_id['version'],
              'partie' => $demande_id['partie'],
            ))
            ->execute();
        }
        else {
          // @FIXME Do not overwrite data. Might not be for the same revision.
          db_update('poetry_map')
            ->fields(array(
              'annee' => $demande_id['annee'],
              'numero' => $demande_id['numero'],
              'version' => $demande_id['version'],
              'partie' => $demande_id['partie'],
            ))
            ->condition('entity_type', $item->item_type, '=')
            ->condition('entity_id', $item->item_id, '=')
            ->execute();
        }
      }

      if (!$job->isRejected()) {
        if (strpos($job->reference, '_POETRY_') === FALSE) {
          $job->reference .= '_POETRY_' . implode('/', $demande_id);
        }
        $job->submitted('Job has been successfully submitted for translation. Project ID is: %project_id',
          array('%project_id' => $job->reference));
      }
    }
  }

  /**
   * Prepares data to be send to Poetry service.
   *
   * @param TMGMTJob $job
   *   Job object.
   *
   * @return string
   *   Data for sending to the translator service.
   */
  protected function prepareDataForSending(TMGMTJob $job) {
    $xml = $this->generateRequestXml($job);
    return $xml;
  }

  /**
   * Helper function to create the XML to send to Poetry.
   */
  protected function generateRequestXml($job) {

    // Load translator settings.
    $translator = $job->getTranslator();
    // Load data exporter.
    $controller = tmgmt_file_format_controller($job->getSetting('export_format'));

    // Generate the data into a XML format and encode it to be translated.
    $export = $controller->export($job);
    $content = base64_encode($export);

    // Generate the ID for the request.
    $items = $job->getItems();
    $item = array_shift($items);
    $settings = $translator->getSetting('settings');
    $id_data = $this->generateRequestId($item, $settings);

    // Generate the callback parameters.
    $callback_username = $settings['callback_user'];
    $callback_password = $settings['callback_password'];
    $callback_address = url(drupal_get_path("module", "tmgmt_poetry") . "/wsdl/PoetryIntegration.wsdl", array(
      'absolute' => TRUE,
      'language' => (object) array('language' => FALSE),
    ));
    $callback_path = 'FPFISPoetryIntegrationRequest';
    $callback_remark = '';

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

    $website_identifier = $settings['website_identifier'];
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
    $item_type = $item->item_type;
    $item_id = $item->item_id;
    $source_url = url($item_type . "/" . $item_id, array('absolute' => TRUE));
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
    $retour->addChild('retourUser', $callback_username);
    $retour->addChild('retourPassword', $callback_password);
    $retour->addChild('retourAddress', $callback_address);
    $retour->addChild('retourPath', $callback_path);
    $retour->addChild('retourRemark', $callback_remark);

    // Add the content to be translated.
    $filename = 'content.html';
    $document_source = $request->addChild('documentSource');
    $document_source->addAttribute('format', 'HTML');
    $document_source->addChild('documentSourceName', $filename);
    $language = $document_source->addChild('documentSourceLang');
    $language->addAttribute('lgCode', drupal_strtoupper($job->getTranslator()
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
        $attribution->addAttribute('lgCode', drupal_strtoupper($job->getTranslator()
          ->mapToRemoteLanguage($job_additional_lang_key)));
        $attribution->addAttribute('action', $attribute_action);
        $attribution_delai = $attribution->addChild('attributionsDelai', date('d/m/Y', strtotime($job->settings['delai'])));
        $attribution_delai->addAttribute('format', 'DD/MM/YYYY ');
      }
    }
    return $xml;
  }

  /**
   * Helper method to generate a request id.
   *
   * @param TMGMTJobItem $item
   *   Item to search for.
   * @param array $settings
   *   Settings.
   */
  protected function generateRequestId(TMGMTJobItem $item, array $settings) {

    // Check if a request id exists for the item.
    $result = db_select('poetry_map', 'pm')
      ->fields('pm', array('annee', 'numero', 'version', 'partie'))
      ->condition('entity_type', $item->item_type, '=')
      ->condition('entity_id', $item->item_id, '=')
      ->execute()
      ->fetchAssoc();
    if ($result and isset($result['numero']) and $result['numero'] != -1 and isset($result['version']) and $result['version'] < 99) {
      // If a usable request id exists, increase the version and return it.
      $id_data = array(
        'codeDemandeur' => $settings['code'],
        'annee' => $result['annee'],
        'numero' => $result['numero'],
        'version' => $result['version'] + 1,
        'partie' => $result['partie'],
        'produit' => 'TRA',
      );
      return $id_data;
    }
    else {
      // If it doesn't, check the highest numero.
      $query = db_select('poetry_map', 'pm');
      $query->addExpression('MAX(numero)', 'max_numero');
      $max_numero = $query->execute()
        ->fetchAssoc();
      if (!empty($max_numero['max_numero'])) {
        $query = db_select('poetry_map', 'pm')
          ->fields('pm', array('annee', 'numero', 'version', 'partie'))
          ->condition('numero', $max_numero['max_numero'], '=');
        $query->addExpression('MAX(partie)', 'max_partie');
        $result = $query->execute()
          ->fetchAssoc();
        // If we have a numero and we haven't reached the max partie,
        // increment it and return it.
        if ($result && $result['max_partie'] < 99 && $result['numero'] > -1) {
          $id_data = array(
            'codeDemandeur' => $settings['code'],
            'annee' => $result['annee'],
            'numero' => $result['numero'],
            'version' => $result['version'] = 00,
            'partie' => $result['max_partie'] + 1,
            'produit' => 'TRA',
          );
          return $id_data;
        }
      }
    }

    // If we have found nothing, request a new numero.
    $id_data = array(
      'codeDemandeur' => $settings['code'],
      'annee' => date("Y"),
      'sequence' => $settings['counter'],
      'version' => 00,
      'partie' => 00,
      'produit' => 'TRA',

    );
    return $id_data;
  }

  /**
   * Execute a request against the Poetry API.
   */
  protected function doRequest(array $query, TMGMTJob $job) {
    return $this->sendSoapRequest($query['xml'], $job);
  }

  /**
   * Helper method to send a soap request.
   *
   * @param SimpleXMLElement $xml
   *   XML to send.
   * @param TMGMTJob $job
   *   Job we are processing.
   */
  protected function sendSoapRequest(SimpleXMLElement $xml, TMGMTJob $job) {
    $msg = $xml->asXML();

    $translator = $job->getTranslator();
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

  /**
   * Overrides getSupportedTargetLanguages().
   */
  public function getSupportedTargetLanguages(TMGMTTranslator $translator, $source_language) {
    $languages = array();
    $list_languages = language_list();

    foreach ($list_languages as $key => $value) {
      $languages[$key] = $key;
    }

    return $languages;
  }

  /**
   * Performs and deals with addition of new target languages request.
   *
   * @param \TMGMTPoetryJob $job
   *   Main TMGMT job.
   * @param array $new_languages
   *   An array with new target languages.
   * @param int $delivery_date
   *   Delivery date timestamp ('delai').
   */
  public function addNewTargetLanguages(TMGMTPoetryJob $job, array $new_languages, $delivery_date) {
    $languages = language_list();
    $poetry_xml = $this->prepareRequestPoetryXml();
    $translator = $job->getTranslator();
    $settings = $translator->getSetting('settings');
    $this->appendRequestXmlElement(
      $poetry_xml,
      self::REQUEST_TYPE_NEW_POST,
      self::COMMUNICATION_SYNCHRONE,
      $job,
      $new_languages,
      $delivery_date,
      $settings
    );

    $response = $this->sendAddNewTargetLanguagesRequest($poetry_xml, $settings['poetry_user'], $settings['poetry_password']);
    $response_xml = $response ? simplexml_load_string($response) : FALSE;

    if (!$response_xml) {
      $job->addMessage(
        "There was a SOAP error while requesting addition of new target languages. Message error: @error",
        ['@error' => $response],
        'error'
      );
    }
    else {
      $processed_lang = [];
      foreach ($new_languages as $language) {
        // Create a job and a job item for the given language.
        _tmgmt_poetry_create_job_and_item($language, $job);
        // Helper array to store processed languages.
        $processed_lang[] = $languages[$language]->name;
      }
      // Setting up messages to notify a user.
      $processed_languages = implode(', ', $processed_lang);
      $job->addMessage("The following languages were added to the ongoing translation request: @processed_languages.",
        ['@processed_languages' => $processed_languages]);
      drupal_set_message(t("The following languages were added to the ongoing translation request: @processed_languages",
        ['@processed_languages' => $processed_languages]));
    }

  }

  /**
   * Sends addition of new target languages request.
   *
   * @param \SimpleXMLElement $poetry_xml
   *   Main XML document.
   *
   * @return mixed
   *   FALSE or string with XML response.
   */
  protected function sendAddNewTargetLanguagesRequest(SimpleXMLElement $poetry_xml, $poetry_user, $poetry_password) {
    $msg = $poetry_xml->asXML();
    $msg_watchdog = htmlentities("Send request (new target languages): " . $msg);
    watchdog('tmgmt_poetry', $msg_watchdog, array(), WATCHDOG_DEBUG);
    $poetry = variable_get("poetry_service");

    // Create soap client and send the request.
    try {
      $client = new SoapClient($poetry['address'], array('cache_wsdl' => WSDL_CACHE_NONE));

      $response = $client->$poetry['method']($poetry_user, $poetry_password, $msg);

      return $response;
    }
    catch (Exception $e) {
      watchdog_exception('tmgmt_poetry', $e);
    }

    return FALSE;
  }

  /**
   * Prepares the main XML document.
   *
   * @return \SimpleXMLElement
   *   Main XML document.
   */
  protected function prepareRequestPoetryXml() {
    $xmlns_xsi = "http://www.w3.org/2001/XMLSchema-instance";
    $xsi_no_name = "http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd";
    $xml = '<?xml version="1.0" encoding="UTF-8"?>' . PHP_EOL;
    $xml .= "<POETRY xmlns:xsi=\"$xmlns_xsi\" xsi:noNamespaceSchemaLocation=\"$xsi_no_name\"></POETRY>";

    return new SimpleXMLElement($xml);
  }

  /**
   * Appends the 'request' XML element to the main XML request document.
   *
   * Function responsible for the complete creation of the 'request' element.
   *
   * @param \SimpleXMLElement $poetry_xml
   *   Main XML document.
   * @param string $request_type
   *   XML request type attribute.
   * @param string $comm_type
   *   XML request communication type attribute.
   * @param \TMGMTPoetryJob $job
   *   Main TMGMT job.
   * @param array $new_languages
   *   An array with new target languages.
   * @param int $delivery_date
   *   Delivery date timestamp ('delai').
   * @param array $settings
   *   Translator settings.
   */
  protected function appendRequestXmlElement(SimpleXMLElement $poetry_xml, $request_type, $comm_type, TMGMTPoetryJob $job, array $new_languages, $delivery_date, $settings) {
    // Add the 'request' XML element to the main XML document.
    $req_id_split = explode('_POETRY_', $job->reference);
    $request_id = end($req_id_split);
    $request = $poetry_xml->addChild('request');
    $request->addAttribute('type', $request_type);
    $request->addAttribute('communication', $comm_type);
    $request->addAttribute('id', $request_id);

    // Append the 'demandeId' XML element.
    $this->appendDemandeIdXmlElement($request, $request_id);

    $new_languages = array_map(
      function ($new_language) use ($job) {
        return $job->getTranslator()->mapToRemoteLanguage($new_language);
      },
      $new_languages
    );

    // Append the 'attributions' XML elements.
    $this->appendAttributionsXmlElement($request, $new_languages, $delivery_date, $settings);
  }

  /**
   * Appends the 'demandeId' XML element to the 'request' XML element.
   *
   * @param \SimpleXMLElement $request_xml
   *   The 'request' XML element.
   * @param string $request_id
   *   String with job reference id.
   */
  protected function appendDemandeIdXmlElement(SimpleXMLElement $request_xml, $request_id) {
    $demande = explode('/', $request_id);
    $demande_id = $request_xml->addChild('demandeId');
    $demande_id->addChild('codeDemandeur', $demande[0]);
    $demande_id->addChild('annee', $demande[1]);
    $demande_id->addChild('numero', $demande[2]);
    $demande_id->addChild('version', $demande[3]);
    $demande_id->addChild('partie', $demande[4]);
    $demande_id->addChild('produit', $demande[5]);
  }

  /**
   * Appends the 'attributions' XML elements to the 'request' XML element.
   *
   * @param \SimpleXMLElement $request_xml
   *   The 'request' XML element.
   * @param array $new_languages
   *   An array with new target languages.
   * @param int $delivery_date
   *   Delivery date timestamp ('delai').
   * @param array $settings
   *   Translator settings.
   */
  protected function appendAttributionsXmlElement(SimpleXMLElement $request_xml, array $new_languages, $delivery_date, $settings) {
    $callback_username = $settings['callback_user'];
    $callback_address = url(drupal_get_path("module", "tmgmt_poetry") . "/wsdl/PoetryIntegration.wsdl", array(
      'absolute' => TRUE,
      'language' => (object) array('language' => FALSE),
    ));

    $formatted_delivery_date = format_date($delivery_date, 'custom', 'd/m/Y');

    foreach ($new_languages as $language) {
      $attribution = $request_xml->addChild('attributions');
      $attribution->addAttribute('lgCode', drupal_strtoupper($language));
      $attribution->addAttribute('format', 'HTML');
      $attribution->addChild('attributionsDelai', $formatted_delivery_date);
      $attribution_send = $attribution->addChild('attributionsSend');
      $attribution_send->addAttribute('type', 'smtp');
      $attribution_send->addChild('retourUser', $callback_username);
      $attribution_send->addChild('retourAddress', $callback_address);
    }
  }

}
