<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_remote\Entity\RemoteEntityMetadataController.
 */

namespace Drupal\nexteuropa_remote\Entity;

/**
 * Class RemoteEntityMetadataController.
 *
 * @package Drupal\nexteuropa_remote\Entity
 */
class RemoteEntityMetadataController extends \EntityDefaultMetadataController {

  /**
   * Get entity's properties information.
   *
   * @return array
   *    Properties info array.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['label'] = [
      'type' => 'text',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'label' => t('Label'),
      'schema field' => 'label',
    ];

    $properties['user'] = [
      'label' => t("User"),
      'type' => 'user',
      'description' => t("User ID owning the remote entity."),
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_setter_method',
      'setter permission' => 'administer nexteuropa remote entities',
      'required' => TRUE,
      'schema field' => 'uid',
    ];

    $properties['created'] = [
      'label' => t("Date created"),
      'type' => 'date',
      'description' => t("The date the remote entity was created."),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer nexteuropa remote entities',
      'schema field' => 'created',
    ];

    $properties['changed'] = [
      'label' => t("Date changed"),
      'type' => 'date',
      'schema field' => 'changed',
      'description' => t("The date the remote entity was most recently updated."),
    ];

    $properties['status'] = [
      'label' => t("Status"),
      'type' => 'boolean',
      'schema field' => 'status',
      'description' => t("Whether the remote entity is active (true) or not (false)."),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer nexteuropa remote entities',
    ];

    return $info;
  }

}
