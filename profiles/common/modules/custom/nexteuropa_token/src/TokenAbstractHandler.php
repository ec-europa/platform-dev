<?php

namespace Drupal\nexteuropa_token;

/**
 * Class TokenAbstractHandler.
 *
 * @package Drupal\nexteuropa_token
 */
abstract class TokenAbstractHandler implements TokenHandlerInterface {

  /**
   * Returns true if passed argument is a valid token type.
   *
   * @param string $type
   *    Token type machine name.
   *
   * @return bool
   *    TRUE if valid token type, FALSE otherwise.
   */
  protected function isValidTokenType($type) {
    $types = $this->getEntityTokenTypes();
    return isset($types[$type]);
  }

  /**
   * Get list of entity info arrays, keyed by the entity's token-like name.
   *
   * @return array
   *    List of entity info arrays.
   */
  protected function getEntityTokenTypes() {
    $return = array();
    $tokens = token_get_info();
    foreach (entity_get_info() as $entity_type => $entity_info) {
      // Check for the token type name for a specific entity type.
      $entity_type = (isset($entity_info['token type'])) ? $entity_info['token type'] : $entity_type;
      // If token type already exists, add it to the return array.
      if (isset($tokens['types'][$entity_type])) {
        $return[$entity_type] = $entity_info;
      }
    }
    return $return;
  }

  /**
   * Get an entity key ID given the entity's token-like name.
   *
   * @param string $type
   *    Entity type machine name.
   *
   * @return string
   *    Entity ID key.
   */
  protected function getEntityKeysId($type) {
    $token_types = $this->getEntityTokenTypes();
    return $token_types[$type]['entity keys']['id'];
  }

}
