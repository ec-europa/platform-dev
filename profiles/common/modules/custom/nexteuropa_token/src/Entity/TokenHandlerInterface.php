<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\TokenHandlerInterface.
 */

namespace Drupal\nexteuropa_token\Entity;

/**
 * Interface TokenHandlerInterface.
 *
 * @package Drupal\nexteuropa_token\Entity
 */
interface TokenHandlerInterface {

  /**
   * Return list of supported token type.
   *
   * @return array
   *    Return list of supported token types.
   */
  public function getSupportedTokenTypes();

  /**
   * Return token suffix portion, e.g. what follows "[node:1:" or "[user:1:".
   *
   * @return string
   *    Return token suffix.
   */
  public function getTokenSuffix();

  /**
   * Return TRUE if token is a valid entity tokens.
   *
   * @param string $original
   *    Token, in its original format, eg. [node:1:view-mode:full].
   *
   * @return bool
   *    TRUE if it is a valid token, FALSE otherwise.
   */
  public function isValidToken($original);

  /**
   * Get entity ID from a token string.
   *
   * @param string $original
   *    Token, in its original format, eg. [node:1:view-mode:full].
   *
   * @return string
   *    Extracted Entity ID.
   */
  public function getEntityIdFromToken($original);

  /**
   * Return entity URL.
   *
   * @param string $entity_type
   *    Entity type.
   * @param object $entity
   *    Entity object.
   *
   * @return string
   *    Entity URL.
   */
  public function getEntityUrl($entity_type, $entity);

}
