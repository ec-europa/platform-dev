<?php

namespace Drupal\nexteuropa_token\Entity\ViewModeType;

/**
 * Interface ViewModeTypeInterface.
 */
interface ViewModeTypeInterface {

  /**
   * Set the entity ID.
   *
   * @param int $eid
   *   The entity ID.
   *
   * @return self
   *   Return itself.
   */
  public function setEntityId($eid);

  /**
   * Return default configuration.
   *
   * @return array
   *   The default configuration.
   */
  public function getConfigurationDefault();

  /**
   * Returns the type of entity.
   *
   * @return string
   *   The type of entity.
   */
  public function getType();

  /**
   * Returns an array of string containing available view modes.
   *
   * @return string[]
   *   The array of available view modes.
   */
  public function getAvailableViewModes();

  /**
   * Set the object's configuration.
   *
   * @param array $configuration
   *   The object's configuration.
   *
   * @return self
   *   Return itself.
   */
  public function setConfiguration(array $configuration = array());

  /**
   * Get the object's configuration.
   *
   * @return array
   *   The configuration array.
   */
  public function getConfiguration();

  /**
   * Return the entity object.
   *
   * @return \Entity
   *   The entity.
   */
  public function getEntity();

  /**
   * Load the entity.
   *
   * @return \Entity
   *   The entity.
   */
  public function entityLoad();

  /**
   * Check if we have access to an entity.
   *
   * @param string $operation
   *   The operation to evaluate.
   *
   * @return bool
   *   True or False
   */
  public function entityAccess($operation = 'view');

  /**
   * Render an entity.
   *
   * @return array|bool
   *   The render array, FALSE otherwise.
   */
  public function entityView();

  /**
   * Check if the view mode is valid.
   *
   * @return bool
   *   True if valid, False otherwise.
   */
  public function isValidViewMode();

}
