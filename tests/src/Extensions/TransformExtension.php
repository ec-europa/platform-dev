<?php

/**
 * @file
 * Contains Drupal\nexteuropa\Extensions\TransformExtension.
 */

namespace Drupal\nexteuropa\Extensions;

use Behat\Testwork\ServiceContainer\Extension as ExtensionInterface;
use Behat\Behat\Transformation\ServiceContainer\TransformationExtension;
use Behat\Testwork\ServiceContainer\ExtensionManager;
use Symfony\Component\Config\Definition\Builder\ArrayNodeDefinition;
use Symfony\Component\DependencyInjection\ContainerBuilder;
use Symfony\Component\DependencyInjection\Definition;

/**
 * Class TransformExtension.
 *
 * @package Drupal\nexteuropa\Extensions
 */
class TransformExtension implements ExtensionInterface {

  /**
   * Extension configuration ID.
   */
  const NEPT_TRANSFORM_ID = 'nept_transform';

  /**
   * Implement getConfigKey() method.
   *
   * @inheritDoc
   */
  public function getConfigKey() {
    return self::NEPT_TRANSFORM_ID;
  }

  /**
   * Implement initialize() method.
   *
   * @inheritDoc
   */
  public function initialize(ExtensionManager $extension_manager) {

  }

  /**
   * Implement configure() method.
   *
   * @inheritDoc
   */
  public function configure(ArrayNodeDefinition $builder) {
    // @codingStandardsIgnoreStart
    $builder->
      children()->
        arrayNode('transform_tokens')->
          info('Tokens that will be used by Behat transformation process (see Drupal\nexteuropa\Transformation\Transformer\ArgumentTransformer)' . PHP_EOL
            . 'Defined tokens must be prefixed by "nept_element:" and their value defines the CSS selector for element that cannot be identified by a label' . PHP_EOL
            . 'Example: The language selector block of Drupal:' . PHP_EOL
            . '  nept_element:page-language-switcher: ".block-language-selector-page"' . PHP_EOL
          )->
          useAttributeAsKey('key')->
          prototype('variable')->
          end()->
        end()->
      end()->
    end();
    // @codingStandardsIgnoreEnd
  }

  /**
   * Loads the ArgumentTransformer and passes the settings to it.
   *
   * @inheritDoc
   */
  public function load(ContainerBuilder $container, array $config) {
    $class_name = 'Drupal\nexteuropa\Transformation\Transformer\ArgumentTransformer';
    $definition = new Definition($class_name, array($config));
    $definition->addTag(TransformationExtension::ARGUMENT_TRANSFORMER_TAG, array('priority' => 50));
    $container->addDefinitions([$definition]);
  }

  /**
   * Implement process() method.
   *
   * @inheritDoc
   */
  public function process(ContainerBuilder $container) {

  }

}
