<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\TokenAbstractHandler.
 */

namespace Drupal\nexteuropa_token\Entity;

use Drupal\nexteuropa_token\TokenAbstractHandler as BaseTokenAbstractHandler;

/**
 * Class TokenAbstractHandler.
 *
 * @package Drupal\nexteuropa_token
 */
abstract class TokenAbstractHandler extends BaseTokenAbstractHandler implements TokenHandlerInterface {

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
   * Parse entity token, by default return entity ID.
   *
   * It also provides an additional $item to extract other token's parts.
   *
   * @param string $original
   *    Token string, in its original format, eg. [node:1:view-mode:full].
   * @param string $item
   *    Item to be extracted when parsing the token.
   *
   * @return string
   *    Extracted item.
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
