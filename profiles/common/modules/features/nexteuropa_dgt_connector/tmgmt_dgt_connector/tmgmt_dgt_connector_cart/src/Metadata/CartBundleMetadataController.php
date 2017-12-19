<?php

namespace Drupal\tmgmt_dgt_connector_cart\Metadata;

use EntityDefaultMetadataController;

/**
 * DGT FTT Translator mapping entity.
 */
class CartBundleMetadataController extends EntityDefaultMetadataController {
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

    return $info;
  }
}