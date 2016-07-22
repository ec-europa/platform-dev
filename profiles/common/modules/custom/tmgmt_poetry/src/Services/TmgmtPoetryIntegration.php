<?php

/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\TmgmtPoetryIntegration.
 */

namespace Drupal\tmgmt_poetry\Services;

/**
 * Class TmgmtPoetryIntegration.
 *
 * Helper class for all of those functions which are related to tmgmt module.
 *
 * @package Drupal\tmgmt_poetry\Services
 */
class TmgmtPoetryIntegration {
  const POETRY_TRANSLATOR = 'poetry';
  const POETRY_MAIN_JOB_PREFIX = 'MAIN_%_POETRY_%';
  private $xmlReqObj;
  private $xmlReference;

  public $languages;
  public $translator;

  /**
   * TmgmtIntegration constructor.
   *
   * @param \SimpleXMLElement $xml_req_obj
   *    Request SimpleXMLElement object.
   * @param string $xml_reference
   *    String with request reference.
   */
  public function __construct(\SimpleXMLElement $xml_req_obj, $xml_reference) {
    $this->xmlReqObj = $xml_req_obj;
    $this->xmlReference = $xml_reference;
    $this->setProperites();
  }

  /**
   * Sets basic properties.
   */
  private function setProperites() {
    $this->languages = language_list();
    $this->translator = tmgmt_translator_load(self::POETRY_TRANSLATOR);
  }

  /**
   * Provides main job translation id based on given reference.
   *
   * @param string $reference
   *   Reference string.
   *
   * @return mixed
   *   Array with Translation Job ID or FALSE;
   */
  public static function getMainJobId($reference) {
    return db_select('tmgmt_job', 'job')
      ->fields('job', ['tjid'])
      ->condition('job.reference', '%' . $reference . '%', 'LIKE')
      ->execute()
      ->fetchAssoc();
  }

}
