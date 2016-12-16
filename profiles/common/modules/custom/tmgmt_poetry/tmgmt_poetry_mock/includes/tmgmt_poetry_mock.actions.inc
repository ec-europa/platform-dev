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
 *    Request translation file.
 * @param int $file_id
 *    Request translation dump file ID.
 * @param int $entity_id
 *    An entity ID.
 */
function _tmgmt_poetry_mock_translate_job($lg_code, $file_id, $entity_id) {
  $poetry_mock = new PoetryMock();
  $poetry_mock->translateJob($lg_code, $file_id, $entity_id);
}

/**
 * Refuse translation job based on given request from the file.
 *
 * @param int $file_id
 *    Request translation file dump ID.
 * @param int $entity_id
 *    An entity ID.
 */
function _tmgmt_poetry_mock_refuse_job($file_id, $entity_id) {
  $poetry_mock = new PoetryMock();
  $poetry_mock->refuseJob($file_id, $entity_id);
}
