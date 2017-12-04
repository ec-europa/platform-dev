<?php

/**
 * @file
 * Provides TMGMT DGT Connector translation plugin controller.
 */

use EC\Poetry\Poetry;
use EC\Poetry\Messages\Components;
use EC\Poetry\Exceptions;
use Drupal\nexteuropa_core\Psr3Watchdog;
use Psr\Log\LogLevel;

/**
 * TMGMT DGT Connector translation plugin controller.
 *
 * It's now mostly based on TMGMTPoetryTranslatorPluginController
 * Later this should extend TMGMTDefaultTranslatorPluginController and
 * TMGMTPoetryTranslatorPluginController should be deprecated.
 */
class TmgmtDgtConnectorTranslatorPluginController extends TMGMTPoetryTranslatorPluginController {

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::canTranslation().
   *
   * Check if source and target languages are supported.
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    // Check that the item does not have pending requests.
    $items = $job->getItems();
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
   * {@inheritdoc}
   */
  public function getNotCanTranslateReason(TMGMTJob $job) {
    return t('A pending translation for this item already exists');
  }

  /**
   * {@inheritdoc}
   */
  public function requestTranslation(TMGMTJob $job) {
    // Request translation from Poetry.
    /** @var EC\Poetry\Messages\Responses\Status $response */
    $response = $this->sendRequest($job);

    // If it is not an xml response, the SOAP request failed.
    if (!$response) {
      _tmgmt_poetry_tmgmt_job_reject(
        $job,
        'Rejected',
        'There was an error with the SOAP service.',
        $response
      );
      return FALSE;
    }

    if (!$response->isSuccessful()) {

      if ($statuses = $response->getWarnings()) {
        $job->addMessage(
          'There were warnings with the Poetry request: :msg',
          array(':msg' => implode('. ', $statuses)),
          'warning'
        );
      }

      if ($statuses = $response->getErrors()) {
        _tmgmt_poetry_tmgmt_job_reject(
          $job,
          'Rejected',
          'There were errors with the Poetry request.',
          implode('. ', $statuses)
        );

        return FALSE;
      }
    }

    // Insert or update the mapping information.
    $demande_id = $response->getIdentifier();
    $items = $job->getItems();
    $item = current($items);

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
          'annee' => $demande_id->getYear(),
          'numero' => $demande_id->getNumber(),
          'version' => $demande_id->getVersion(),
          'partie' => $demande_id->getPart(),
        ))
        ->execute();
    }
    else {
      // @FIXME Do not overwrite data. Might not be for the same revision.
      db_update('poetry_map')
        ->fields(array(
          'annee' => $demande_id->getYear(),
          'numero' => $demande_id->getNumber(),
          'version' => $demande_id->getVersion(),
          'partie' => $demande_id->getPart(),
        ))
        ->condition('entity_type', $item->item_type, '=')
        ->condition('entity_id', $item->item_id, '=')
        ->execute();
    }

    if (!$job->isRejected()) {
      if (strpos($job->reference, '_POETRY_') === FALSE) {
        $job->reference .= '_POETRY_' . $demande_id->getFormattedIdentifier();
      }
      $job->submitted('Job has been successfully sent for translation. Project ID is: %project_id',
        array('%project_id' => $job->reference));
    }
  }

  /**
   * Execute a request against the Poetry API.
   */
  protected function sendRequest(TMGMTJob $job) {
    global $base_url;

    // Generate the identifier for the request.
    $translator = $job->getTranslator();
    $settings = $translator->getSetting('settings');
    $id_data = $this->generateRequestIdData($settings);

    // Get other pieces of information.
    $organization = $job->settings['organization'];
    $details_title = 'NE-CMS: ';
    $details_title .= (empty($settings['website_identifier']) ? '' : $settings['website_identifier'] . ' - ');
    $details_title .= $job->label;
    $delai = date('d/m/Y', strtotime($job->settings['delai']));

    // Generate the data into a XML format and encode it to be translated.
    $controller = tmgmt_file_format_controller($job->getSetting('export_format'));
    $export = $controller->export($job);
    $content = base64_encode($export);

    try {
      // Get client from Poetry client factory.
      /** @var \EC\Poetry\Poetry $poetry */
      $poetry = nexteuropa_poetry_client();

      // Start building the request message.
      /** @var EC\Poetry\Messages\Requests\CreateTranslationRequest $message */
      $message = $poetry->get('request.create_translation_request');

      $identifier = $message->withIdentifier();
      $identifier->setCode($id_data['codeDemandeur'])
        ->setYear($id_data['annee'])
        ->setVersion($id_data['version'])
        ->setPart($id_data['partie'])
        ->setProduct($id_data['produit']);

      if (isset($id_data['numero'])) {
        $identifier->setNumber($id_data['numero']);
      }
      else {
        $identifier->setSequence($id_data['sequence']);
      }

      $message->withDetails()
        ->setClientId('Job ID ' . $job->tjid)
        ->setTitle($details_title)
        ->setResponsible($organization['responsable'])
        ->setRequester($organization['demandeur'])
        ->setAuthor($organization['auteur'])
        ->setApplicationId('FPFIS')
        ->setDelay($delai)
        ->setRemark('')
        ->setReferenceFilesRemark($base_url)
        ->setProcedure('NEANT')
        ->setDestination('PUBLIC')
        ->setType('INTER');

      // Get contact information from translator and add it to the request.
      foreach ($job->settings['contacts'] as $type => $value) {
        $message->withContact()
          ->setType($type)
          ->setNickname($value);
      }

      $message->withReturnAddress()
        ->setType('webService')
        ->setAction('UPDATE')
        ->setUser($poetry->getSettings()->get('notification.username'))
        ->setPassword($poetry->getSettings()->get('notification.password'))
        ->setAddress($poetry->getSettings()->get('client.wsdl'))
        ->setPath('handle')
        ->setRemark('');

      $message->withSource()
        ->setFormat('HTML')
        ->setName('content.html')
        ->setFile($content)
        ->setLegiswriteFormat('No')
        ->withSourceLanguage()
        ->setCode(drupal_strtoupper($job->getTranslator()->mapToRemoteLanguage($job->source_language)))
        ->setPages(1);

      foreach ($job->settings['languages'] as $lang_val) {
        if ($lang_val) {
          $lang = drupal_strtoupper($translator->mapToRemoteLanguage($lang_val));
          $message->withTarget()
            ->setLanguage($lang)
            ->setFormat('HTML')
            ->setAction('INSERT')
            ->setDelay($delai);
        }
      }

      return $poetry->getClient()->send($message);
    }
    catch (Exceptions\ValidationException $exception) {
      drupal_set_message($exception->getMessage(), 'error');
      return FALSE;
    }

  }

  /**
   * Helper method to generate a request id.
   *
   * @param array $settings
   *   Settings.
   *
   * @return array
   *   The id data.
   */
  protected function generateRequestIdData(array $settings) {
    // Check the highest number, (if it exists and if it's lower then 99).
    $query = db_select('poetry_map', 'pm');
    $query->addExpression('MAX(numero)', 'max_numero');
    $max_numero = $query->execute()->fetchAssoc();

    if (!empty($max_numero['max_numero'])) {
      $query = db_select('poetry_map', 'pm')
        ->fields('pm', array('annee', 'numero', 'version', 'partie'))
        ->condition('numero', $max_numero['max_numero'], '=');
      $query->addExpression('MAX(partie)', 'max_partie');

      $result = $query->execute()->fetchAssoc();

      // If we have a number and we haven't reached the max partie,
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

    // Request a new number.
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

}
