<?php

/**
 * @file
 * Contains Drupal\nexteuropa\Transformation\Transformer\ArgumentTransformer.
 */

namespace Drupal\nexteuropa\Transformation\Transformer;

use Behat\Behat\Definition\Call\DefinitionCall;
use Behat\Behat\Transformation\Transformer\ArgumentTransformer as ArgumentTransformerInterface;

/**
 * Class ArgumentTransformer in charge of the "nept_element" transformation.
 *
 * @package Drupal\nexteuropa\Transformation\Transformer
 */
class ArgumentTransformer implements ArgumentTransformerInterface {
  /**
   * Extension configuration.
   *
   * @var
   */
  private $config;

  /**
   * ExtensionTransformer constructor.
   */
  public function __construct($config) {
    $this->config = $config;
  }

  /**
   * Defines conditions the current transformation process must be triggered.
   *
   * @inheritDoc
   */
  public function supportsDefinitionAndArgument(DefinitionCall $definition_call, $argument_index, $argument_value) {
    if (is_object($argument_value) || is_array($argument_value)) {
      return FALSE;
    }

    return ((!empty($this->config['transform_tokens'])) && (isset($this->config['transform_tokens'][$argument_value])));
  }

  /**
   * Implements the transformation based on the 'transform_tokens' parameter.
   *
   * @inheritDoc
   */
  public function transformArgument(DefinitionCall $definition_call, $argument_index, $argument_value) {
    $available_tokens = $this->config['transform_tokens'];
    return $available_tokens[$argument_value];
  }

}
