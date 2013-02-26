<?php

/**
 * @file
 * Provides Ecweb Translator plugin controller.
 *
 */

/**
 * Google translator plugin controller.
 */
class TMGMTEcwebTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {

  /**
   * Name of parameter that contains source string to be translated.
   *
   * @var string
   */
  protected $qParamName = 'q';

  /**
   * Maximum supported characters.
   *
   * @var int
   */
  protected $maxCharacters = 5000;

  /**
   * Available actions for Ecweb translator.
   *
   * @var array
   */
  protected $availableActions = array('translate', 'languages', 'detect');

  /**
   * Max number of text queries for translation sent in one request.
   *
   * @var int
   */
  protected $qChunkSize = 5;

  /**
   * Overrides TMGMTDefaultTranslatorPluginController::isAvailable().
   */
  public function isAvailable(TMGMTTranslator $translator) {
    return TRUE;
  }

  /**
   * Overrides TMGMTDefaultTranslatorPluginController::canTranslate().
   */
  /*
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    if (!parent::canTranslate($translator, $job)) {
      return FALSE;
    }

    foreach (array_filter(tmgmt_flatten_data($job->getData()), '_tmgmt_filter_data') as $value) {
      if (drupal_strlen($value['#text']) > $this->maxCharacters) {
        return FALSE;
      }
    }

    return TRUE;
  }
  */
  
  /**
   * Implements TMGMTTranslatorPluginControllerInterface::requestTranslation().
   */
  public function requestTranslation(TMGMTJob $job) {
    // Pull the source data array through the job and flatten it.
    $data = array_filter(tmgmt_flatten_data($job->getData()), '_tmgmt_filter_data');

    $translation = array();
    $q = array();
    $keys_sequence = array();
    $i = 0;

    foreach ($data as $key => $value) {
      $q[] = $value['#text'];
      $keys_sequence[] = $key;
    }

    try {

      // Split $q into chunks of self::qChunkSize.
      foreach (array_chunk($q, $this->qChunkSize) as $_q) {
        
        // Collect translated texts with use of initial keys.
        foreach ($_q as $translated) {
          $translation[$keys_sequence[$i]]['#text'] = $translated;
          $i++;
          
        }
      }
      
      // The translation job has been successfully submitted.
      $job->submitted('The translation job has been submitted.');

      // Save the translated data through the job.
      // NOTE that this line of code is reached only in case all translation
      // requests succeeded.
      $job->addTranslatedData(tmgmt_unflatten_data($translation));
    }
    catch (TMGMTEcwebException $e) {
      $job->rejected('Translation has been rejected with following error: !error',
        array('!error' => $e->getMessage()), 'error');
    }
  }

  /**
   * Helper method to do translation request.
   *
   * @param TMGMTJob $job
   * @param array|string $q
   *   Text/texts to be translated.
   *
   * @return array
   *   Userialized JSON containing translated texts.
   */
  protected function EcwebRequestTranslation(TMGMTJob $job, $q) {
    return $this->doRequest($job->getTranslator(), 'translate', array(
      'source' => $job->source_language,
      'target' => $job->target_language,
      $this->qParamName => $q,
    ), array(
      'headers' => array(
        'Content-Type' => 'text/plain',
      ),
    ));
  }


  /**
   * Overrides TMGMTDefaultTranslatorPluginController::hasCheckoutSettings().
   */
  public function hasCheckoutSettings(TMGMTJob $job) {
    return FALSE;
  }


  /**
   * Overrides TMGMTDefaultTranslatorPluginController::getSupportedTargetLanguages().
   */
  
  public function getSupportedTargetLanguages(TMGMTTranslator $translator, $source_language) {
    $languages = array();

    $list_languages = language_list();
    //print_r($list_languages);
    //exit();

    foreach ($list_languages as $key => $value)
      $languages[$key] = $key;

    return $languages;
  }

}

