<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\TokenHandlerInterface
 */

namespace Drupal\nexteuropa_token\Entity;

/**
 * Interface TokenHandlerInterface
 * @package Drupal\nexteuropa_token\Entity
 */
interface TokenHandlerInterface {

  /**
   * Return list of supported token type.
   *
   * @return array
   */
  public function getSupportedTokenTypes();

  /**
   * Return token suffix portion, i.e. that part of the token string that
   * follows [node:1: or [user:1:
   *
   * @return string
   */
  public function getTokenSuffix();

  /**
   * Return TRUE if token is a valid entity tokens.
   *
   * @param $original
   * @return bool
   */
  public function isValidToken($original);

  /**
   * Get entity ID from a token string.
   *
   * @param $original
   * @return string
   */
  public function getEntityIdFromToken($original);
}
