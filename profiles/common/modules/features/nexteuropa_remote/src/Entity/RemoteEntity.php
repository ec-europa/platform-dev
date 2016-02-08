<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_remote\Entity\RemoteEntity.
 */

namespace Drupal\nexteuropa_remote\Entity;

/**
 * Class RemoteEntity.
 *
 * @package Drupal\nexteuropa_remote\Entity
 */
class RemoteEntity extends \Entity {

  /**
   * Unique ID.
   *
   * @var int
   */
  public $id;

  /**
   * User ID owning the remote entity.
   *
   * @var int
   */
  public $uid;

  /**
   * Language-independent label.
   *
   * @var string
   */
  public $label = '';

  /**
   * Default bundle type.
   *
   * @var string
   */
  public $type = 'default';

  /**
   * Entity language.
   *
   * @var string
   */
  public $language = LANGUAGE_NONE;

  /**
   * The Unix timestamp when the entity was created.
   *
   * @var string
   */
  public $created;

  /**
   * The Unix timestamp when the entity was changed.
   *
   * @var string
   */
  public $changed;

  /**
   * Whether the entity is active (1) or not (0).
   *
   * @var int
   */
  public $status = 1;

  /**
   * Overridden to care about created and changed times.
   */
  public function save() {
    // Do not automatically set a created values for already existing entities.
    if (empty($this->created) && (!empty($this->is_new) || !$this->id)) {
      $this->created = REQUEST_TIME;
    }
    $this->changed = REQUEST_TIME;
    $this->is_new_revision = TRUE;
    $this->uid = $GLOBALS['user']->uid;
    parent::save();
  }

  /**
   * Sets a new user.
   *
   * @param object $account
   *   The user account object or the user account id (uid).
   */
  public function setUser($account) {
    $this->uid = is_object($account) ? $account->uid : $account;
  }

  /**
   * Gets the user account.
   *
   * @return object
   *   The user account object.
   */
  public function user() {
    return user_load($this->uid);
  }

  /**
   * Default URI callback.
   *
   * @return string
   *    Return entity URI.
   */
  public function defaultUri() {
    return [
      'path' => 'remote-entity/' . $this->id,
    ];
  }

}
