<?php

namespace Drupal\nexteuropa_token\Entity\ViewModeType;

/**
 * Class TermViewModeType.
 */
class TermViewModeType extends ViewModeTypeBase {

  /**
   * The entity type.
   *
   * @var string
   */
  protected $entityType = 'taxonomy_term';

  /**
   * {@inheritdoc}
   */
  public function entityView() {
    $configuration = $this->getConfiguration();

    if ($term = $this->entityLoad()) {
      return taxonomy_term_view($term, $configuration['view mode']);
    }

    return FALSE;
  }

}
