<?php

namespace Drupal\nexteuropa\Extensions;

use Drupal\DrupalExtension\ServiceContainer\DrupalExtension as OriginalDrupalExtension;
use Symfony\Component\Config\Definition\Builder\ArrayNodeDefinition;

/**
 * Class DrupalExtension.
 *
 * @package Drupal\nexteuropa\Extensions
 */
class DrupalExtension extends OriginalDrupalExtension {

  /**
   * Adds "front_" selectors to "selector" declaration.
   *
   * @inheritDoc
   */
  public function configure(ArrayNodeDefinition $builder) {
    parent::configure($builder);

    // @codingStandardsIgnoreStart
    $builder->
      children()->
        arrayNode('selectors')->
          children()->
            scalarNode('message_selector')->end()->
            scalarNode('error_message_selector')->end()->
            scalarNode('success_message_selector')->end()->
            scalarNode('warning_message_selector')->end()->
            scalarNode('front_message_selector')->end()->
            scalarNode('front_error_message_selector')->end()->
            scalarNode('front_success_message_selector')->end()->
            scalarNode('front_warning_message_selector')->end();
    // @codingStandardsIgnoreEnd
  }

}
