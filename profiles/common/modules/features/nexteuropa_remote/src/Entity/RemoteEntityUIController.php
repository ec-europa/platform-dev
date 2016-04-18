<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_remote\Entity\RemoteEntityUIController.
 */

namespace Drupal\nexteuropa_remote\Entity;

/**
 * Class RemoteEntityUIController.
 *
 * @package Drupal\nexteuropa_remote\Entity
 */
class RemoteEntityUIController extends \EntityDefaultUIController {

  // @codingStandardsIgnoreStart
  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    // @codingStandardsIgnoreEnd
    $defaults = [
      'file' => $this->entityInfo['admin ui']['file'],
      'file path' => isset($this->entityInfo['admin ui']['file path']) ? $this->entityInfo['admin ui']['file path'] : drupal_get_path('module', $this->entityInfo['module']),
    ];

    // Add view, edit and delete menu items for content entities.
    $items[$this->entityInfo['path']] = [
      'page callback' => 'entity_ui_entity_page_view',
      'page arguments' => [1],
      'load arguments' => [$this->entityType],
      'access callback' => 'nexteuropa_remote_access',
      'access arguments' => ['view', 1],
    ] + $defaults;
    $items[$this->entityInfo['path'] . '/view'] = [
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'load arguments' => [$this->entityType],
      'weight' => -10,
    ] + $defaults;
    $items[$this->entityInfo['path'] . '/edit'] = [
      'page callback' => 'entity_ui_get_form',
      'page arguments' => [$this->entityType, 1],
      'load arguments' => [$this->entityType],
      'access callback' => 'nexteuropa_remote_access',
      'access arguments' => ['edit', 1],
      'title' => 'Edit',
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    ] + $defaults;
    $items[$this->entityInfo['path'] . '/delete'] = [
      'page callback' => 'drupal_get_form',
      'page arguments' => [
        $this->entityType . '_operation_form',
        $this->entityType,
        1,
        'delete',
      ],
      'load arguments' => [$this->entityType],
      'access callback' => 'nexteuropa_remote_access',
      'access arguments' => ['delete', 1],
      'title' => 'Delete',
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
    ] + $defaults;
    $items['remote-entity/get/%'] = [
      'page callback' => 'nexteuropa_remote_get_remote_entity',
      'access arguments' => array('access content'),
      'page arguments' => [2],
      'title' => 'Get',
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
    ] + $defaults;
    return $items;
  }

}
