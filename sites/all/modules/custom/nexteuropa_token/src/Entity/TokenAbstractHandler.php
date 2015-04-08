<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\TokenAbstractHandler
 */

namespace Drupal\nexteuropa_token\Entity;

use Drupal\nexteuropa_token\TokenAbstractHandler as BaseTokenAbstractHandler;

/**
 * Class TokenAbstractHandler
 * @package Drupal\nexteuropa_token
 */
abstract class TokenAbstractHandler extends BaseTokenAbstractHandler implements TokenHandlerInterface {

  /**
   * {@inheritdoc}
   */
  public function hookToken() {
    return array();
  }

  /**
   * {@inheritdoc}
   */
  public function getSupportedTokenTypes() {
    return array('node', 'user', 'term');
  }

  /**
   * {@inheritdoc}
   */
  public function isValidToken($original) {
    return $this->getEntityIdFromToken($original);
  }

  /**
   * {@inheritdoc}
   */
  public function getEntityIdFromToken($original) {
    return $this->parseToken($original, 'entity_id');
  }

  /**
   * Parse entity token, by default return entity ID. It also provides an
   * additional $item parameter that could be useful in case we need to extract
   * other parts of the token.
   *
   * @param $original
   * @param string $item
   * @return string
   */
  protected function parseToken($original, $item = 'entity_id') {
    $matches = array();
    $supported_types = implode('|', $this->getSupportedTokenTypes());
    $regex = sprintf('/\[(%s)\:(\d*)\:%s\]/', $supported_types, $this->getTokenSuffix());
    preg_match_all($regex, $original, $matches);
    if ($item == 'entity_id') {
      return isset($matches[2][0]) && !empty($matches[2][0]) ? $matches[2][0] : '';
    }
  }
}
