<?php

/**
 * @file
 * Provides Poetry translation plugin controller.
 */

/**
 * DGT Connector translation plugin controller.
 */
class TMGMTPoetryTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {
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
      'callback_user',
      'callback_password',
      'poetry_user',
      'poetry_password',
    );

    $all_settings = array();
    $poetry_credentials_settings = variable_get('poetry_service');

    // If no credentials set in settings.php don't check further.
    if (empty($poetry_settings)) {
      return FALSE;
    }

    // Get setting value for each setting.
    foreach ($poetry_settings as $setting) {
      $all_settings[$setting] = $translator->getSetting($setting);
    }
    // If one of the arg is not set, don't check further.
    foreach ($poetry_service as $service_arg) {
      if (isset($poetry_credentials_settings[$service_arg])) {
        $all_settings[$service_arg] = $poetry_credentials_settings[$service_arg];
      }
      else {
        return FALSE;
      }
    }
    // If any of these is empty, translator is not properly configured.
    foreach ($all_settings as $k => $v) {
      if (empty($v)) {
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
          ->fields('tji', array('tjid'))
          ->condition('item_type', $item->item_type, '=')
          ->condition('item_id', $item->item_id, '=')
          ->execute()
          ->fetchAllAssoc('tjid');
      if ($results) {
        foreach ($results as $tjid) {
          if ($job = tmgmt_job_load($tjid->tjid)) {
            $translator = $job->getTranslator();
            if ($translator && $translator->plugin == 'poetry' && $job->getState() == 1) {
              return FALSE;
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
      return t('@translator can not translate more than 1 item per request.', array('@translator' => $job->getTranslator()->label()));
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
      $job->rejected("There was an error with the SOAP service . Message error: @error",
        array('@error' => $response), 'error');
    }
    else {
      $request = $response_xml->request;

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

      $statuses = $request->status;
      // Check the statuses of the response
      // in order to verify that everything is correct.
      foreach ($statuses as $status) {
        $message = (string) $status->statusMessage;
        if ($message != 'OK') {
          $job->rejected("There was an error with the Poetry request . Message error: @error",
            array('@error' => $message), 'error');
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

    // Encode the data to be translated.
    $content = base64_encode($controller->export($job));

    // Generate the ID for the request.
    $items = $job->getItems();
    $item = array_shift($items);
    $id_data = $this->generateRequestId($item, $translator->getSetting('settings'));

    // Generate the callback parameters.
    $poetry = variable_get("poetry_service");
    $callback_username = $poetry['callback_user'];
    $callback_password = $poetry['callback_password'];
    $callback_address = url(drupal_get_path("module", "tmgmt_poetry") . "/wsdl/PoetryIntegration.wsdl", array('absolute' => TRUE, 'language' => (object) array('language' => FALSE)));
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
    $titre = $demande->addChild('titre');
    $titre->value = 'NE-CMS: ' . $job->label;
    $demande->addChild('organisationResponsable', $organization['responsable']);
    $demande->addChild('organisationAuteur', $organization['auteur']);
    $demande->addChild('serviceDemandeur', $organization['demandeur']);
    $demande->addChild('applicationReference', 'FPFIS');
    $demande->addChild('delai', date('d/m/Y', strtotime($job->settings['delai'])));
    $demande->addChild('remarque', $job->settings['remark']);

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
    $contacts = $job->settings['contacts'];

    $auteur = $request->addChild('contacts');
    $auteur->addAttribute('type', 'auteur');
    $auteur->addChild('contactNickname', $contacts['auteur']);

    $secretaire = $request->addChild('contacts');
    $secretaire->addAttribute('type', 'secretaire');
    $secretaire->addChild('contactNickname', $contacts['secretaire']);

    $contact = $request->addChild('contacts');
    $contact->addAttribute('type', 'contact');
    $contact->addChild('contactNickname', $contacts['contact']);

    $responsable = $request->addChild('contacts');
    $responsable->addAttribute('type', 'responsable');
    $responsable->addChild('contactNickname', $contacts['responsable']);

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
    $language->addAttribute('lgCode', strtoupper($job->getTranslator()->mapToRemoteLanguage($job->source_language)));
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
        $attribution->addAttribute('lgCode', strtoupper($job->getTranslator()->mapToRemoteLanguage($job_additional_lang_key)));
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
    if ($result) {
      // If a request id exists, increase the version and return it.
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
        if ($result && $result['max_partie'] < 99) {
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
    $xml = $query['xml'];

    $result = $this->sendSoapRequest($xml, $job);
    return $result;
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
    watchdog('Poetry: Send request', htmlentities($msg), array(), WATCHDOG_DEBUG);

    // Get Poetry configuration.
    $poetry = variable_get("poetry_service");
    // Create soap client.
    try {
      $client = new SoapClient($poetry['address'], array('cache_wsdl' => WSDL_CACHE_NONE, 'trace' => 1));
    }
    catch (Exception $e) {
      $response = 'Error new SoapClient : ' . $e->getMessage();
      watchdog_exception('tmgmt_poetry', $e);
    }

    if ($client) {
      // Send the SOAP request and handle possible errors.
      try {
        $response = $client->$poetry['method']($poetry['poetry_user'], $poetry['poetry_password'], $msg);
      }
      catch (Exception $e) {
        $response = 'Error sending soap call : ' . $e->getMessage();
        watchdog_exception('tmgmt_poetry', $e);
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

}
