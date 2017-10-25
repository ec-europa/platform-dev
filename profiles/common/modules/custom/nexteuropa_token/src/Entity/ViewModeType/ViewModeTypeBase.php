<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\ViewModeType\ViewModeTypeBase.
 */

namespace Drupal\nexteuropa_token\Entity\ViewModeType;

/**
 * Abstract class ViewModeTypeBase.
 */
abstract class ViewModeTypeBase implements ViewModeTypeInterface {

  /**
   * The entity type.
   *
   * @var string
   */
  protected $entityType = 'node';

  /**
   * The entity.
   *
   * @var \Entity
   */
  protected $entity;

  /**
   * The weight.
   *
   * @var int
   */
  protected $weight = 0;

  /**
   * The object configuration.
   *
   * @var array
   */
  protected $configuration = array();

  /**
   * {@inheritdoc}
   */
  public function getType() {
    return $this->entityType;
  }

  /**
   * {@inheritdoc}
   */
  public function getWeight() {
    return (int) $this->weight;
  }

  /**
   * {@inheritdoc}
   */
  public function getConfigurationDefault() {
    return array(
      'view mode' => 'full',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getConfiguration() {
    return $this->configuration + $this->getConfigurationDefault();
  }

  /**
   * {@inheritdoc}
   */
  public function setConfiguration(array $configuration = array()) {
    $this->configuration = $configuration;

    return $this;
  }

  /**
   * {@inheritdoc}
   */
  public function getEntity() {
    if (!isset($this->entity)) {
      $this->entity = $this->entityLoad();
    }

    return $this->entity;
  }

  /**
   * {@inheritdoc}
   */
  public function entityAccess($operation = 'view') {
    return entity_access($operation, $this->getType(), array($this->getEntity()));
  }

  /**
   * {@inheritdoc}
   */
  public function entityLoad() {
    $configuration = $this->getConfiguration();

    $entities = entity_load($this->getType(), array($configuration['entity id']));

    return array_pop($entities);
  }

  /**
   * {@inheritdoc}
   */
  public function entityView() {
    $configuration = $this->getConfiguration();

    if ($node = $this->entityLoad()) {
      if ($this->entityAccess()) {
        return entity_view($this->getType(), array($this->getEntity()), $configuration['view mode']);
      }
    }

    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function setEntityId($eid) {
    $configuration = $this->getConfiguration();

    $configuration['entity id'] = (int) $eid;

    $this->setConfiguration($configuration);
  }

  /**
   * {@inheritdoc}
   */
  public function getAvailableViewModes() {
    // Todo: Use field_view_mode_settings() function.
    // Todo: bundle handling.
    $entity_info = entity_get_info($this->getType());

    return array_keys($entity_info['view modes']);
  }

  /**
   * {@inheritdoc}
   */
  public function isValidViewMode() {
    $configuration = $this->getConfiguration();

    return in_array($configuration['view mode'], $this->getAvailableViewModes());
  }

}
