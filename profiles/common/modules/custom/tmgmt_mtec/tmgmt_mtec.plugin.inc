<?php

/**
 * @file
 * Provides MT@EC translation plugin controller.
 */

/**
 * MT@EC translation plugin controller.
 */
class TMGMTMtecTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {

  /**
   * Override parent defaultSettings method.
   */
  public function defaultSettings() {
    return array(
      'export_format' => 'xlf',
      'allow_override' => TRUE,
      'scheme' => 'public',
      'xliff_processing' => TRUE,
    );
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::isAvailable().
   */
  public function isAvailable(TMGMTTranslator $translator) {
    // Check if the required variables are set.
    $ftp_settings = variable_get('ftp_server');
    $mtec_service = variable_get('mtec_service');
    if (!empty($ftp_settings) && !empty($mtec_service)) {
      if (!empty($ftp_settings['address']) && !empty($ftp_settings['port']) &&
        !empty($ftp_settings['user']) && !empty($ftp_settings['password']) &&
        !empty($mtec_service['address']) && !empty($mtec_service['applicationName'])) {
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::canTranslation().
   *
   * We will check are source and target language supported.
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    // All languages are supported at the moment.
    return TRUE;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::requestTranslation().
   */
  public function requestTranslation(TMGMTJob $job) {

    // Export the data into a file and place it into the FTP server.
    $filename = $this->prepareDataForSending($job);

    // If the file could not be created or uploaded,
    // inform the users and reject the job.
    if (empty($filename)) {
      $job->rejected("There was an error uploading the content to the FTP server",
        array(), 'error');
    }
    else {
      // If the file is on the FTP server,
      // request translation from MT@EC service.
      $translator = $job->getTranslator();
      $response = $this->doRequest($job->getTranslator(), array(
        'source' => drupal_strtoupper($job->source_language),
        'target' => drupal_strtoupper($job->target_language),
        'folder' => $job->uuid,
        'filename' => $filename,
        'tjid' => $job->tjid,
      ));

      // Handle the response of the request to MT@EC.
      if (!empty($response->return)) {
        $job->reference = $response->return;
        $job->submitted('Job has been successfully submitted for translation. Project ID is: %project_id',
          array('%project_id' => $job->reference));
      }
      else {
        $job->rejected("There was an error with the SOAP service . Message error: @error",
          array('@error' => $response), 'error');
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getSupportedTargetLanguages(TMGMTTranslator $translator, $source_language) {
    // Retrieve the supported languages from the site configuration.
    $languages = array();
    $list_languages = language_list();

    foreach ($list_languages as $key => $value) {
      $languages[$key] = $key;
    }

    return $languages;
  }

  /**
   * Execute a request against the MT@EC API.
   *
   * @param TMGMTTranslator $translator
   *   The translator entity to get the settings from.
   * @param array $query
   *   Array of arguments.
   *
   * @return object
   *   The response object returned by soapCall().
   */
  protected function doRequest(TMGMTTranslator $translator, array $query = array()) {
    global $base_url;

    // Define callback URLs.
    $url_request_callback = 'tmgmt_mtec/tmgmt_mtec_correct_callback?tjid=' . $query['tjid'];
    $url_request_error = 'tmgmt_mtec/tmgmt_mtec_error_callback?tjid=' . $query['tjid'];

    // Get the information of the FTP server.
    $ftp_server = variable_get('ftp_server', '');
    $ftp_location = 'ftp://' . $ftp_server['user'] . ':' . $ftp_server['password'] . '@' . $ftp_server['address'] . ':' . $ftp_server['port'] . '/' . $query['folder'];

    // Get the information of the MT@EC service.
    $mtec_service = variable_get('mtec_service', '');

    // Get MTEC settings from translator.
    $mtec_settings = $translator->getSetting('mtec_settings');

    // Build array to construct XML to pass to the webservice.
    $wsdl_text = array(
      'priority'              => 1,
      'documentToTranslate'   => $ftp_location . '/' . $query['filename'],
      'textToTranslate'   => '',
      'requesterCallback'     => $base_url . '/' . $url_request_callback,
      'errorCallback'         => $base_url . '/' . $url_request_error,
      'targetTranslationPath' => $ftp_location,
      'originalFileName'      => $query['filename'],
      'sourceLanguage'        => $query['source'],
      'targetLanguage'        => $query['target'],
      'username'              => $mtec_settings['user_name'],
      'applicationName'       => $mtec_service['applicationName'],
      'domains'               => 'all',
      'requestType'           => 'doc',
      'outputFormat'           => 'xlf',
      'institution'           => $mtec_settings['institution'],
      'departmentNumber'      => $mtec_settings['departmentNumber'],
      'externalReference'     => $query['tjid'],
    );

    // Create soap client.
    try {
      $client = new SoapClient($mtec_service['address']);
    }
    catch (Exception $e) {
      $response = 'Error new SoapClient : ' . $e->getMessage();
    }

    // Send the SOAP request and handle possible errors.
    try {
      $response = $client->__soapCall('asktranslation', array('arg0' => array('arg0' => $wsdl_text)));
    }
    catch (Exception $e) {
      $response = 'Error sending soap call : ' . $e->getMessage();
    }
    return $response;
  }

  /**
   * Prepares data to be send to MT@EC service.
   *
   * @param TMGMTJob $job
   *   Job object.
   *
   * @return string
   *   Data for sending to the translator service.
   */
  protected function prepareDataForSending(TMGMTJob $job) {
    $filename = '';

    // Load job data.
    $ftp_server = variable_get('ftp_server');
    $server_file = _tmgmt_mtec_filename_builder($job->tjid, $job->getSetting('export_format'));

    // Load data exporter.
    $exporter = tmgmt_file_format_controller($job->getSetting('export_format'));

    // Load a temp file with the data to be translated.
    $temp = tmpfile();
    fwrite($temp, $exporter->export($job));
    fseek($temp, 0);

    // Open connection and login to the FTP server.
    $conn_id = ftp_connect($ftp_server['address'], $ftp_server['port']);
    if (!$conn_id) {
      watchdog('MT@EC', "Couldn't connect to the FTP server.", WATCHDOG_ERROR);
      return $filename;
    }
    $login_result = ftp_login($conn_id, $ftp_server['user'], $ftp_server['password']);
    if (!$login_result) {
      watchdog('MT@EC', "Couldn't login to the FTP server.", WATCHDOG_ERROR);
      return $filename;
    }
    if (!ftp_pasv($conn_id, TRUE)) {
      watchdog("tmgmt_ftp_ftp_output", "Ftp connection not available!", WATCHDOG_ERROR);
      $job->addMessage("Ftp connection not available.");
    }
    else {
      // Create folder using the jobs uuid.
      $folders = ftp_nlist($conn_id, '.');
      if (!in_array($job->uuid, $folders)) {
        ftp_mkdir($conn_id, $job->uuid);
      }
      // Write the file into the ftp server.
      $upload = ftp_fput($conn_id, $job->uuid . '/' . $server_file, $temp, FTP_BINARY);
      if ($upload) {
        watchdog("tmgmt_ftp_ftp_output", "Ftp connection has loaded and the file with the content was saved");
        $job->addMessage("Ftp connection has loaded and the file with the content was saved.");
        $filename = $server_file;
      }
      else {
        watchdog("tmgmt_ftp_ftp_output", "Ftp connection has loaded, but the file with the content was not saved.", WATCHDOG_ERROR);
        $job->addMessage("Ftp connection has loaded, but the file with the content was not saved.");
      }
    }
    // Close connection.
    ftp_close($conn_id);
    return $filename;
  }

}
