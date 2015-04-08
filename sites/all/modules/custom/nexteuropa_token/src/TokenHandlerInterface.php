<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\TokenHandlerInterface
 */

namespace Drupal\nexteuropa_token;

interface TokenHandlerInterface {

  /**
   * @return mixed
   */
  public function hookToken();

  /**
   * @param $type
   * @param $tokens
   * @param array $data
   * @param array $options
   * @return mixed
   */
  public function hookTokens($type, $tokens, array $data = array(), array $options = array());

  /**
   * @param $data
   * @return mixed
   */
  public function hookTokenInfoAlter(&$data);

}
