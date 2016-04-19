<?php

/**
 * @file
 * Contains \Drupal\integration\ResourceSchema\GenericResourceSchema.
 */

namespace Drupal\nexteuropa_integration\ResourceSchema;

use Drupal\integration\ResourceSchema\AbstractResourceSchema;
use Drupal\integration\ResourceSchema\Configuration\ResourceSchemaConfiguration;

/**
 * Class GenericResourceSchema.
 *
 * @package Drupal\nexteuropa_integration\ResourceSchema
 */
class GenericResourceSchema extends AbstractResourceSchema {

  /**
   * {@inheritdoc}
   */
  public function __construct(ResourceSchemaConfiguration $configuration) {    
    $this->setConfiguration($configuration);
  }

}
