<?php

namespace Drupal\tmgmt_dgt_connector_cart\Metadata;

use EntityDefaultMetadataController;

/**
 * DGT FTT Translator mapping entity.
 */
class CartItemMetadataController extends EntityDefaultMetadataController {

  /**
   * Override entity properties to add custom ones.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];
    $properties['cbid'] = array(
      'label' => t('Cart bundle ID'),
      'schema field' => 'cbid',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Related cart bundle ID.'),
    );
    $properties['plugin type'] = array(
      'label' => t('Plugin type'),
      'schema field' => 'entity_type',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('TMGMT Job item plugin type.'),
    );
    $properties['entity_type'] = array(
      'label' => t('Entity type'),
      'schema field' => 'entity_type',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Related entity type.'),
    );
    $properties['entity_id'] = array(
      'label' => t('Entity ID'),
      'schema field' => 'entity_id',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Related entity ID.'),
    );
    $properties['context_url'] = array(
      'label' => t('Context URL'),
      'schema field' => 'context_url',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => FALSE,
      'description' => t('Context URL.'),
    );
    $properties['context_comment'] = array(
      'label' => t('Context comment'),
      'schema field' => 'context_comment',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => FALSE,
      'description' => t('Context comment.'),
    );
    $properties['tjiid'] = array(
      'label' => t('Translation job item ID'),
      'schema field' => 'tjiid',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => FALSE,
      'description' => t('Related translation job item ID.'),
    );
    $properties['created'] = array(
      'label' => t('Creation date'),
      'schema field' => 'created',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Creation date of the item.'),
    );
    $properties['updated'] = array(
      'label' => t('training updated'),
      'schema field' => 'Updated date',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Updated date of the item.'),
    );
    return $info;
  }

}
