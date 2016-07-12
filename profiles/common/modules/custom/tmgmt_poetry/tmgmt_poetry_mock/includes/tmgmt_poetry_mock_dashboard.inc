<?php
/**
 * @file
 * tmgmt_poetry_mock_dashboard.inc
 */

use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;

/**
 * POETRY Service Mock dashboard callback function.
 */
function tmgmt_poetry_mock_dashboard() {
  $x = 1;

  _poetry_mock_prepare_request_files();
  return "Bam";
}

function _poetry_mock_prepare_request_files() {
  $request_files = PoetryMock::getAllRequestTranslationFiles();

  if (!empty($request_files)) {
    foreach ($request_files as $request_file) {
      $file_object = file_load($request_file->fid);
      $message = file_get_contents($file_object->uri);
      $request_data = PoetryMock::getDataFromRequest($message);
      $entity_details = PoetryMock::getEntityDetailsByDemandeId($request_data['demande_id']);
      $jobs = PoetryMock::getActiveTranslationJobsByEntityId($entity_details['entity_id']);
      if (!empty($jobs)) {
        foreach ($jobs as $job) {
          $data_set[$job->tjid]['reference'] = $job->reference;
        }

      }

    }
  }
}