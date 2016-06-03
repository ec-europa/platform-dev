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
            // Watchdog. If it is a node we can tell exactly where they have to
            // fix it.
            if ($data['node']) {
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
            // Return an empty replacement to not show a broken link.
            $replacements[$original] = '';
          }
        }
      }
    }
    return $replacements;
  }

}
