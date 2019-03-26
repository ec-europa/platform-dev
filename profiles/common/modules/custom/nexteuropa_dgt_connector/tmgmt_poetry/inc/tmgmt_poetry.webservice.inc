<?php

/**
 * @file
 * Webservice definition and behaviour.
 *
 * @deprecated in favor of nexteuropa_poetry.
 */

use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;

/**
 * Function to define our webservice and register the available methods.
 */
function _tmgmt_poetry_service_callback() {
  // Generate our own SOAP server.
  $context = stream_context_create();
  $uri = url(drupal_get_path("module", "tmgmt_poetry") . "/wsdl/PoetryIntegration.wsdl", array(
    'absolute' => TRUE,
    'language' => (object) array('language' => FALSE),
  ));

  $server = new SoapServer($uri, array(
    'stream_context' => $context,
    'cache_wsdl' => WSDL_CACHE_NONE,
  ));
  $server->AddFunction("FPFISPoetryIntegrationRequest");
  $server->handle();
}

/**
 * Function available to call from our webservice.
 */
function FPFISPoetryIntegrationRequest($user, $password, $msg) {
  watchdog(
    'tmgmt_poetry',
    "Receive request: !msg",
    array('!msg' => htmlentities($msg)),
    WATCHDOG_INFO
  );

  $poetry_translator = tmgmt_translator_load('poetry');

  // Use the Poetry Mock translator if the tmgmt_poetry_mock is enabled.
  if (module_exists('tmgmt_poetry_mock')) {
    $poetry_translator = tmgmt_translator_load(PoetryMock::TRANSLATOR_NAME);
  }

  // Load the received XML and load the referenced Job.
  $xml = simplexml_load_string($msg);
  $request = $xml->request;
  $reference = implode("/", (array) $request->demandeId);

  // Authenticate the request.
  if (!_tmgmt_poetry_authenticate($user, $password, $poetry_translator)) {
    // Send answer 'ERROR' to poetry.
    watchdog(
      "tmgmt_poetry",
      "Poetry callback failed authentication.",
      array(),
      WATCHDOG_ERROR
    );

    $xml = _tmgmt_poetry_generate_answer_xml(NULL, 'ERROR: Failed authentication', -1, $request);

    return $xml->asXML();
  }

  $languages = language_list();

  // Watchdog is only temporary information, save the file to the filesystem.
  $path = 'public://tmgmt_file/dgt_responses/' . $reference . '.xml';
  $dirname = drupal_dirname($path);
  if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
    file_save_data($msg, $path);
  }

  // Get main job in order to register the messages.
  $main_reference = 'MAIN_%_POETRY_%' . $reference;
  $ids = tmgmt_poetry_obtain_related_translation_jobs(NULL, $reference)
    ->fetchAll();

  // Handling the case where we can't find the corresponding job.
  if (!$ids) {
    watchdog(
      "tmgmt_poetry",
      "Callback can't find a job with remote reference !reference .",
      array('!reference' => $reference),
      WATCHDOG_ERROR);

    // Send answer to poetry.
    $xml_answer = _tmgmt_poetry_generate_answer_xml(
      NULL,
      'ERROR: Job does not exist',
      -1,
      $request
    );

    return $xml_answer->asXML();
  }

  $ids = array_shift($ids);
  $main_job = tmgmt_job_load($ids->tjid);

  // If the received message has a status, record it in the job.
  // </STATUS>.
  if (isset($request->status)) {
    $cancelled = FALSE;
    $status_message = "";
    foreach ($request->status as $status) {
      // Check status code.
      switch ($status['code']) {
        case 'SUS':
          $status_message = TMGMT_POETRY_STATUS_MSG_SUS;
          $cancelled = FALSE;
          break;

        case 'ONG':
          $status_message = TMGMT_POETRY_STATUS_MSG_ONG;
          $cancelled = FALSE;
          break;

        case 'LCK':
          $status_message = TMGMT_POETRY_STATUS_MSG_LCK;
          $cancelled = FALSE;
          break;

        case 'EXE':
          $status_message = TMGMT_POETRY_STATUS_MSG_EXE;
          $cancelled = FALSE;
          break;

        case 'REF':
          $status_message = TMGMT_POETRY_STATUS_MSG_REF;
          $cancelled = TRUE;
          break;

        case 'CNL':
          $status_message = TMGMT_POETRY_STATUS_MSG_CNL;
          $cancelled = TRUE;
          break;
      }

      // Status update for the whole request.
      // </STATUS> - type:demande.
      if ($status['type'] == 'demande') {
        if (isset($status->statusMessage)) {
          $message = (string) $status->statusMessage;
        }
        else {
          $message = t('No message.');
        }

        $main_job->addMessage(
          t("DGT update received. Request status: @status. Message: @message"),
          array(
            '@status' => $status_message,
            '@message' => $message,
          )
        );

        if ($cancelled) {
          $reference = '%' . $reference;

          $ids = tmgmt_poetry_obtain_related_translation_jobs(array(), $reference)
            ->fetchAll();
          foreach ($ids as $id) {
            $job = tmgmt_job_load($id->tjid);
            $job->aborted(t('Request aborted by DGT.'), array());
          }
        }
        elseif ($main_job->isAborted()) {
          $reference = '%' . $reference;
          $ids = tmgmt_poetry_obtain_related_translation_jobs(array(), $reference)
            ->fetchAll();

          foreach ($ids as $id) {
            $reopen_job = tmgmt_job_load($id->tjid);
            $reopen_job->setState(
              TMGMT_JOB_STATE_ACTIVE,
              t('Request re-opened by DGT.')
            );
            $reopen_job_item = tmgmt_job_item_load($ids->tjiid);
            $reopen_job_item->active();
          }
        }
      }

      // Status update for a specific language.
      // </STATUS> - type:attribution.
      if ($status['type'] == 'attribution') {
        if (!empty($status['lgCode'])) {
          $reference = '%' . $reference;
          $language_code = drupal_strtolower((string) $status['lgCode']);
          $language_code = $poetry_translator->mapToLocalLanguage($language_code);
          $language_job = array($language_code);
        }
        else {
          $reference = 'MAIN_%_POETRY_%' . $reference;
          $language_job = array();
        }
        $ids = tmgmt_poetry_obtain_related_translation_jobs($language_job, $reference)
          ->fetchAll();
        $ids = array_shift($ids);
        $job = tmgmt_job_load($ids->tjid);
        $job_item = tmgmt_job_item_load($ids->tjiid);

        if (!empty($job->target_language) && !empty($languages[(string) $job->target_language])) {
          $language = $languages[(string) $job->target_language]->name;
        }
        else {
          $language = "";
        }

        $main_job->addMessage(
          t("DGT update received. Affected language: @language. Request status: @status."),
          array(
            '@language' => $language,
            '@status' => $status_message,
          )
        );

        _tmgmt_poetry_update_item_status($job_item->tjiid, "", $status_message, "");
      }
    }
  }

  // Check the attributions to look for translations and delai confirmations.
  // </ATTRIBUTIONS>.
  foreach ($request->attributions as $attributions) {
    $reference = '%' . $reference;
    $language_code = drupal_strtolower((string) $attributions['lgCode']);
    $language_code = $poetry_translator->mapToLocalLanguage($language_code);
    $language_job = array($language_code);

    $ids = tmgmt_poetry_obtain_related_translation_jobs($language_job, $reference)
      ->fetchAll();
    $ids = array_shift($ids);
    $job = tmgmt_job_load($ids->tjid);
    $job_item = tmgmt_job_item_load($ids->tjiid);

    if (!isset($attributions['format']) || (isset($attributions['format']) && (strpos($job->getSetting('export_format'), drupal_strtolower((string) $attributions['format'])) === FALSE))) {
      $main_job->addMessage(
        t('Received format "@format" is not compatible, translation job format "@job_format" should be used instead'),
        array(
          '@format' => (string) $attributions['format'],
          '@job_format' => $job->getSetting('export_format'),
        )
      );

      $xml = _tmgmt_poetry_generate_answer_xml(
        $main_job,
        'ERROR: Received format is not compatible',
        -1,
        $request
      );

      return $xml->asXML();
    }

    if (!empty($job->target_language) && !empty($languages[(string) $job->target_language])) {
      $language = $languages[(string) $job->target_language]->name;
    }
    else {
      $language = "";
    }

    // Update the delai provided by DGT.
    if (!empty($attributions->attributionsDelaiAccepted)) {
      _tmgmt_poetry_update_item_status($job_item->tjiid, "", "", (string) $attributions->attributionsDelaiAccepted);
    }

    // If the received message has the translated file, add it to the job.
    if (isset($attributions->attributionsFile)) {
      $content = (string) $attributions->attributionsFile;
      $content = _tmgmt_poetry_replace_job_in_content(base64_decode($content), $job, $job_item);

      $controller = tmgmt_file_format_controller($job->getSetting('export_format'));
      if ($controller) {
        // Validate the file.
        $validated_job = $controller->validateImport($content);
        if (!$validated_job) {
          $main_job->addMessage(
            t('@language Failed to validate file, import aborted.'),
            array('@language' => $language),
            'error');
        }
        elseif ($validated_job->tjid != $job->tjid) {
          $uri = $validated_job->uri();
          $label = $validated_job->label();
          $main_job->addMessage(
            t('@language Import file is from job <a href="@url">@label</a>, import aborted.'),
            array(
              '@language' => $language,
              '@url' => url($uri['path']),
              '@label' => $label,
            )
          );
        }
        else {
          try {
            if (!$job->isAborted()) {
              // Validation successful, start import.
              $job->addTranslatedData($controller->import($content));

              $main_job->addMessage(
                t('@language Successfully received the translation file.'),
                array('@language' => $language)
              );

              // Update the status to executed when we receive a translation.
              _tmgmt_poetry_update_item_status($job_item->tjiid, "", "Executed", "");
            }

            // Save the file and make it available in the job.
            $name = "JobID" . $job->tjid . '_' . $job->source_language . '_' . $job->target_language;
            $path = 'public://tmgmt_file/' . $name . '.' . $job->getSetting('export_format');

            $dirname = drupal_dirname($path);
            if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY)) {
              $file = file_save_data($content, $path);
              file_usage_add($file, 'tmgmt_file', 'tmgmt_job', $job->tjid);
              $main_job->addMessage(
                t('Received tanslation can be downloaded <a href="!link">here</a>.'),
                array('!link' => file_create_url($path))
              );
            }
          }
          catch (Exception $e) {
            $main_job->addMessage(
              t('@language File import failed with the following message: @message'),
              array(
                '@language' => $language,
                '@message' => $e->getMessage(),
              ),
              'error'
            );
            watchdog_exception('tmgmt_poetry', $e);
          }
        }
      }
    }
  }

  // Send answer 'OK' to poetry.
  watchdog(
    "tmgmt_poetry",
    "Send response 'status' with remote reference @reference: !xml",
    array(
      '@reference' => $main_reference,
      '!xml' => htmlentities($xml->asXML()),
    ),
    WATCHDOG_INFO
  );

  $xml = _tmgmt_poetry_generate_answer_xml($job, 'OK', 0, $request);

  return $xml->asXML();

}

/**
 * Helper function to authenticate request made to our service.
 */
function _tmgmt_poetry_authenticate($user, $password, $translator) {
  // Get the Poetry translator configuration.
  $settings = $translator->getSetting('settings');
  return ($settings['callback_user'] === $user && $settings['callback_password'] === $password);
}

/**
 * Helper function to generate an answer xml for received Poetry requests.
 */
function _tmgmt_poetry_generate_answer_xml($job = NULL, $message = 'OK', $code = 0, $received_request = NULL) {
  // Create initial XML element using POETRY headers.
  $xml = new SimpleXMLElement("<?xml version=\"1.0\" encoding=\"utf-8\" ?>
    <POETRY xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:noNamespaceSchemaLocation=\"http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd\">
    </POETRY>");

  // Add main request element.
  $request = $xml->addChild('request');

  if ($received_request !== NULL) {
    $reference = implode('/', (array) $received_request->demandeId);
  }
  elseif ($job !== NULL) {
    $reference = $job->reference;
  }

  $request->addAttribute('id', $reference);
  $request->addAttribute('type', 'status');

  // Add request identifier.
  $demande_id_data = explode('/', $reference);
  $demande_id = $request->addChild('demandeId');
  $demande_id->addChild('codeDemandeur', $demande_id_data[0]);
  $demande_id->addChild('annee', $demande_id_data[1]);
  $demande_id->addChild('numero', $demande_id_data[2]);
  $demande_id->addChild('version', $demande_id_data[3]);
  $demande_id->addChild('partie', $demande_id_data[4]);
  $demande_id->addChild('produit', $demande_id_data[5]);

  $status = $request->addChild('status');
  $status->addAttribute('type', 'request');
  $status->addAttribute('code', $code);

  $status_date = $status->addChild('statusDate', date('d/m/Y'));
  $status_date->addAttribute('format', 'dd/mm/yyyy');

  $status_time = $status->addChild('statusTime', date('h:i:s'));
  $status_time->addAttribute('format', 'hh:mm:ss');

  $status->addChild('statusMessage', $message);

  return $xml;
}

/**
 * Local Exception class.
 */
class TMGMTPoetryException extends Exception {

  /**
   * Override of the parent __construct method.
   */
  public function __construct($message = "", $data = array(), $code = 0, Exception $previous = NULL) {
    parent::__construct(strtr($message, $data), $code, $previous);
  }

}
