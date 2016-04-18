<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_remote\Entity\RemoteEntityController.
 */

namespace Drupal\nexteuropa_remote\Entity;

/**
 * Class RemoteEntityController.
 *
 * @package Drupal\nexteuropa_remote\Entity
 */
class RemoteEntityController extends \EntityAPIController {

  /**
   * Overridden create method adding entity default values.
   *
   * @param array $values
   *    Entity values.
   *
   * @return RemoteEntity
   *    Entity object, not yet persisted in the database.
   */
  public function create(array $values = []) {
    $values += [
      'created' => REQUEST_TIME,
      'language' => LANGUAGE_NONE,
      'uid' => $GLOBALS['user']->uid,
    ];
    return parent::create($values);
  }

}
