<?php

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
      $token_types = token_get_entity_mapping();
      foreach ($tokens as $original) {
        if ($this->isValidToken($original)) {
          $entity_id = $this->getEntityIdFromToken($original);
          $entity_type = $token_types[$type];
          $entity_info = entity_get_info($entity_type);
          // Check if the entity is available.
          if ($entity = $entity_info['load hook']($entity_id)) {
            // Does the user have access ?
            if (!$this->entityAccess($entity)) {
              $replacements[$original] = '';
              continue;
            }

            $label = entity_label($entity_type, $entity);
            $uri = entity_uri($entity_type, $entity);
            $link_from_token = l($label, $uri['path'], array('absolute' => TRUE));
            // Use trim() in order to remove unwanted characters around the
            // link that the "link" theming could add.
            $replacements[$original] = rtrim($link_from_token);
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

  /**
   * Does the viewer have access to the entity?
   *
   * @param object $entity
   *   The entity checked against.
   *
   * @return bool
   *   The response.
   */
  public function entityAccess($entity) {
    global $user;

    // Make sure we don't render a node inside itself, preventing infinite loop.
    $object = menu_get_object('node');
    if (is_object($object) && isset($object->nid) && $object->nid == $entity->nid) {
      drupal_set_message(t('Cannot render a node inside itself, remove any view mode token related to the current node.'));
      return FALSE;
    }

    // Make sure current user can actually access the rendered node.
    if (user_access('bypass node access') || user_access('administer nodes')) {
      return TRUE;
    }
    if (!node_access('view', $entity)) {
      return FALSE;
    }
    if ($entity->status == 0) {
      return ($entity->uid == $user->uid) && user_access('view own unpublished content');
    }
    else {
      return TRUE;
    }
  }

}
