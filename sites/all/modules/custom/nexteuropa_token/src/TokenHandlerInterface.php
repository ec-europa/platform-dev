<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\TokenHandlerInterface.
 */

namespace Drupal\nexteuropa_token;

/**
 * Interface TokenHandlerInterface.
 *
 * @package Drupal\nexteuropa_token
 */
interface TokenHandlerInterface {

  /**
   * Provide replacement values for placeholder tokens.
   *
   * @param string $type
   *   The machine-readable name of the type (group) of token being replaced.
   * @param mixed $tokens
   *   An array of tokens to be replaced.
   * @param array $data
   *   (optional) An associative array of data objects.
   * @param array $options
   *   (optional) An associative array of options for token replacement.
   *
   * @return array
   *   An associative array of replacement values.
   *
   * @see hook_token_info_alter()
   * @see hook_tokens()
   */
  public function hookTokens($type, $tokens, array $data = array(), array $options = array());

  /**
   * Alter the metadata about available placeholder tokens and token types.
   *
   * @param mixed $data
   *   The associative array of token definitions from hook_token_info().
   */
  public function hookTokenInfoAlter(&$data);

}
