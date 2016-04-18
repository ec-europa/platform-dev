<?php
/**
 * @file
 * Contains nexteuropa_remote.pages.inc.
 */

/**
 * Implements hook_entity_info().
 */
function nexteuropa_remote_entity_info() {
  $info = [
    'nexteuropa_remote' => [
      'label' => t('Remote entity'),
      'plural label' => t('Remote entities'),
      'description' => t('Remote entities'),
      'entity class' => 'Drupal\nexteuropa_remote\Entity\RemoteEntity',
      'controller class' => 'Drupal\nexteuropa_remote\Entity\RemoteEntityController',
      'base table' => 'nexteuropa_remote_entity',
      'revision table' => 'nexteuropa_remote_entity_revision',
      'fieldable' => TRUE,
      'view modes' => [
        'full' => [
          'label' => t('Full page'),
          'custom settings' => FALSE,
        ],
        'title' => [
          'label' => t('Title'),
          'custom settings' => TRUE,
        ],
        'metadata' => [
          'label' => t('Metadata'),
          'custom settings' => TRUE,
        ],
      ],
      'entity keys' => [
        'id' => 'id',
        'revision' => 'revision_id',
        'bundle' => 'type',
        'label' => 'label',
        'language' => 'language',
      ],
      'bundles' => [
        'default' => [
          'label' => t('Default'),
          'admin' => [
            'path' => 'admin/structure/remote-entities/manage/default',
            'real path' => 'admin/structure/remote-entities/manage/default',
            'bundle argument' => 4,
            'access arguments' => ['administer nexteuropa remote entities'],
          ],
        ],
      ],
      'label callback' => 'entity_class_label',
      'uri callback' => 'entity_class_uri',
      'access callback' => 'nexteuropa_remote_access',
      'module' => 'nexteuropa_remote',
      'metadata controller class' => 'Drupal\nexteuropa_remote\Entity\RemoteEntityMetadataController',
      'admin ui' => [
        'path' => 'admin/structure/remote-entities',
        'file' => 'includes/nexteuropa_remote.pages.inc',
        'controller class' => 'Drupal\nexteuropa_remote\Entity\RemoteEntityUIController',
        'menu wildcard' => '%nexteuropa_remote',
      ],
      'path' => 'remote-entity/%nexteuropa_remote',
      'metatags' => TRUE,
      'translation' => [
        'entity_translation' => [
          'base path' => 'remote-entity/%nexteuropa_remote',
        ],
      ],
      'translatable' => 1,
    ],
  ];

  // Support entity cache module.
  if (module_exists('entitycache')) {
    $info['nexteuropa_remote']['field cache'] = FALSE;
    $info['nexteuropa_remote']['entity cache'] = TRUE;
  }
  return $info;
}
