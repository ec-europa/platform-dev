<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\UrlTokenHandler.
 */

namespace Drupal\nexteuropa_token\Entity;

/**
 * Class UrlTokenHandler.
 *
 * @package Drupal\nexteuropa_token\Entity
 */
class UrlTokenHandler extends TokenAbstractHandler {

  /**
   * {@inheritdoc}
   */
  public function getTokenSuffix() {
    return 'url';
  }

  /**
   * {@inheritdoc}
   */
  public function getTokenName($entity_id = 'ID') {
    return $entity_id . ':' . $this->getTokenSuffix();
  }

  /**
   * {@inheritdoc}
   */
  public function hookTokenInfoAlter(&$data) {
    foreach ($this->getEntityTokenTypes() as $token_type => $entity_info) {
      $data['tokens'][$token_type][$this->getTokenName()] = array(
        'name' => t("!entity URL", array('!entity' => $entity_info['label'])),
        'description' => t("Provide absolute internal URL for the specified entity."),
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function hookTokens($type, $tokens, array $data = array(), array $options = array()) {
    $replacements = array();

    if ($this->isValidTokenType($type)) {
      $token_types = token_get_entity_mapping('token');
      foreach ($tokens as $name => $original) {
        if ($this->isValidToken($original)) {
          $entity_id = $this->getEntityIdFromToken($original);
          $entity_type = $token_types[$type];

          $entity_info = entity_get_info($entity_type);
          $entity = $entity_info['load hook']($entity_id);

          if ($entity = $entity_info['load hook']($entity_id)) {
            $replacements[$original] = $this->getEntityUrl($entity_type, $entity);
          }
          else {
            $this->watchdogTokenNotFound($data, $original);
            $replacements[$original] = "";
          }
        }
      }
    }
    return $replacements;
  }

}
