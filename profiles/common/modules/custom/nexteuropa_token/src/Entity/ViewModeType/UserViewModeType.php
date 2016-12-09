<?php

namespace Drupal\nexteuropa_token\Entity\ViewModeType;

/**
 * Class UserViewModeType.
 */
class UserViewModeType extends ViewModeTypeBase {

  /**
   * The entity type.
   *
   * @var string
   */
  protected $entityType = 'user';

  /**
   * {@inheritdoc}
   */
  public function entityView() {
    $configuration = $this->getConfiguration();

    if ($account = user_load($configuration['entity id'])) {
      if ($this->entityAccess()) {
        return user_view($account, $configuration['view mode']);
      }
    }

    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function entityAccess($operation = 'view') {
    return user_access('access user profiles');
  }

}
