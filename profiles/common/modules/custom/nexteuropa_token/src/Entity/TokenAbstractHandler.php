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
    return array('node', 'user', 'term', 'nexteuropa_remote');
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

  /**
   * {@inheritdoc}
   */
  public function getEntityUrl($entity_type, $entity) {
    $uri = entity_uri($entity_type, $entity);
    return url($uri['path'], array('absolute' => TRUE));
  }

  /**
   * Create a Watchdog Log, if it's a node we can tell where they have to fix.
   *
   * @param array $data
   *    Node Data.
   * @param string $original
   *    Token Original string.
   */
  protected function watchdogTokenNotFound($data, $original) {
    if (isset($data['node'])) {
      watchdog(
        'Nexteuropa Tokens',
        'The entity %entity has an invalid token: %token.',
        [
          '%entity' => $data['node']->title . ' (' . $data['node']->nid . ')',
          '%token' => $original,
        ],
        WATCHDOG_ERROR,
        l(t('Edit the node'), '/node/edit/' . $data['node']->nid)
      );
    }
    else {
      // Watchdog in case it's not a node.
      watchdog('Nexteuropa Tokens', 'Invalid token %token found.', ['%token' => $original], WATCHDOG_ERROR);
    }
  }

}
