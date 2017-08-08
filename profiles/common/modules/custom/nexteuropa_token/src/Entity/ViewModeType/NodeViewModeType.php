<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\ViewModeType\NodeViewModeType.
 */

namespace Drupal\nexteuropa_token\Entity\ViewModeType;

/**
 * Class NodeViewModeType.
 */
class NodeViewModeType extends ViewModeTypeBase {

  /**
   * The entity type.
   *
   * @var string
   */
  protected $entityType = 'node';

  /**
   * {@inheritdoc}
   */
  public function entityView() {
    $configuration = $this->getConfiguration();

    if ($node = $this->entityLoad()) {
      if ($this->entityAccess()) {
        return entity_view($this->getType(), array($this->getEntity()), $configuration['view mode']);
      }
    }

    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function entityAccess($operation = 'view') {
    global $user;
    $node = $this->getEntity();

    // Make sure we don't render a node inside itself, preventing infinite loop.
    $object = menu_get_object('node');
    if (is_object($object) && isset($object->nid) && $object->nid == $node->nid) {
      drupal_set_message(t('Cannot render a node inside itself, remove any view mode token related to the current node.'));
      return FALSE;
    }

    // Make sure current user can actually access the rendered node.
    if (user_access('bypass node access') || user_access('administer nodes')) {
      return TRUE;
    }
    if (!node_access($operation, $node)) {
      return FALSE;
    }
    if ($node->status == 0) {
      return ($node->uid == $user->uid) && user_access('view own unpublished content');
    }
    else {
      return TRUE;
    }

  }

}
