<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\LinkTokenHandler.
 */

namespace Drupal\nexteuropa_token\Entity;

/**
 * Class LinkTokenHandler.
 *
 * @package Drupal\nexteuropa_token\Entity
 */
class LinkTokenHandler extends TokenAbstractHandler {

  /**
   * {@inheritdoc}
   */
  public function getTokenSuffix() {
    return 'link';
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
        'name' => t("!entity link", array('!entity' => $entity_info['label'])),
        'description' => t("Provide absolute link for the specified entity."),
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function hookTokens($type, $tokens, array $data = array(), array $options = array()) {
    $replacements = array();

    if ($this->isValidTokenType($type)) {
      foreach ($tokens as $name => $original) {
        if ($this->isValidToken($original)) {

          $entity_id = $this->getEntityIdFromToken($original);
          $entity_type = ($type == 'term') ? 'taxonomy_term' : $type;

          $entity_info = entity_get_info($entity_type);
          // Check if the entity is available.
          if ($entity = $entity_info['load hook']($entity_id)) {
            $label = entity_label($entity_type, $entity);
            $uri = entity_uri($entity_type, $entity);
            $replacements[$original] = l($label, $uri['path'], array('absolute' => TRUE));
          }
          else {
            $this->watchdogTokenNotFound($data, $original);
            // Return an empty replacement to not show a broken link.
            $replacements[$original] = '';
          }
        }
      }
    }
    return $replacements;
  }

}
