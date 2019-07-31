<?php

/**
 * @file
 * Custom POETRY Mock actions.
 */

use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;

/**
 * Translate Job based on given request from the file and redirect.
 *
 * @param string $lg_code
 *   Request translation file.
 * @param int $file_id
 *   Request translation dump file ID.
 * @param int $entity_id
 *   An entity ID.
 */
function _tmgmt_poetry_mock_translate_job($lg_code, $file_id, $entity_id) {
  $poetry_mock = new PoetryMock();
  $poetry_mock->translateJob($lg_code, $file_id, $entity_id);
}

/**
 * Refuse translation job based on given request from the file.
 *
 * @param int $file_id
 *   Request translation file dump ID.
 * @param int $entity_id
 *   An entity ID.
 */
function _tmgmt_poetry_mock_refuse_job($file_id, $entity_id) {
  $poetry_mock = new PoetryMock();
  $poetry_mock->refuseJob($file_id, $entity_id);
}

/**
 * Sends status request to Drupal.
 *
 * @param string $status_code
 *   Request translation file dump ID.
 * @param int $job_id
 *   TMGMT Poetry job ID.
 */
function _tmgmt_poetry_mock_send_status($status_code, $job_id) {
  $poetry_mock = new PoetryMock();
  $request_status_msg = 'OK';
  $demande_status_msg = _tmgmt_poetry_mock_get_demande_status($status_code);
  $poetry_mock->sendStatus($job_id, $status_code, $request_status_msg, $demande_status_msg);
}

/**
 * Returns the 'demande' status message for given status code.
 *
 * @param string $status_code
 *   Status code.
 *
 * @return string
 *   The 'demande' status message.
 */
function _tmgmt_poetry_mock_get_demande_status($status_code) {
  $status_msg = '';
  switch ($status_code) {
    case 'ong':
      $status_msg = 'REQUEST ACCEPTED';
      break;
  }

  return $status_msg;
}
