<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\ViewModeType\BeanViewModeType.
 */

namespace Drupal\nexteuropa_token\Entity\ViewModeType;

/**
 * Class BeanViewModeType.
 */
class BeanViewModeType extends ViewModeTypeBase {

  /**
   * The entity type.
   *
   * @var string
   */
  protected $entityType = 'bean';

  /**
   * {@inheritdoc}
   */
  public function entityView() {
    $configuration = $this->getConfiguration();

    if ($bean = $this->entityLoad()) {
      if ($this->entityAccess()) {
        return bean_view($bean, $configuration['view mode']);
      }
    }

    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function entityAccess($operation = 'view') {
    return bean_access('view', $this->getEntity());
  }

}
