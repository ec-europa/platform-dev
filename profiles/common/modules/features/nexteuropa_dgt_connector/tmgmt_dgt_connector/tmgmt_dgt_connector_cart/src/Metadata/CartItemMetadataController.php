<?php

namespace Drupal\tmgmt_dgt_connector_cart\Metadata;

use EntityDefaultMetadataController;

/**
 * DGT FTT Translator mapping entity.
 */
class CartItemMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];
    $properties['created'] = array(
      'label' => t('training created'),
      'schema field' => 'created',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('created date of the assessment data.'),
    );
    $properties['updated'] = array(
      'label' => t('training updated'),
      'schema field' => 'updated',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('updated date of the assessment data.'),
    );
    $properties['title'] = array(
      'label' => t('training title'),
      'schema field' => 'title',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('title of the rating data.'),
    );
    $properties['type'] = array(
      'type' => 'text',
      'label' => t('Type'),
      'description' => t('The human readable name of the bundle type.'),
      'setter callback' => 'entity_property_verbatim_set',
      'getter callback' => 'entity_property_getter_method',
      'options list' => 'mymodule_type_options_list',
      'required' => TRUE,
      'schema field' => 'type',
    );
    return $info;
  }
}