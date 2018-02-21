<?php

namespace Drupal\tmgmt_dgt_connector_cart\Metadata;

use EntityDefaultMetadataController;

/**
 * TMGMT DGT Translator mapping entity.
 */
class CartBundleMetadataController extends EntityDefaultMetadataController {

  /**
   * Override entity properties to add custom ones.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];
    $properties['cbid'] = array(
      'label' => t('Cart Bundle ID'),
      'schema field' => 'cbid',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('The ID of the Cart Bundle.'),
    );
    $properties['uid'] = array(
      'label' => t('User ID'),
      'type' => 'user',
      'schema field' => 'uid',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('ID of the author.'),
    );
    $properties['tjid'] = array(
      'label' => t('Translation job ID'),
      'schema field' => 'tjid',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => FALSE,
      'description' => t('Related translation job ID.'),
    );
    $properties['target_languages'] = array(
      'label' => t('Target languages'),
      'schema field' => 'target_languages',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Target languages of the bundle.'),
    );
    $properties['status'] = array(
      'label' => t('Status'),
      'schema field' => 'status',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Status of the bundle.'),
    );
    $properties['created'] = array(
      'label' => t('Creation date'),
      'type' => 'date',
      'schema field' => 'created',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Creation date of the bundle.'),
    );
    $properties['changed'] = array(
      'label' => t('Changed date'),
      'type' => 'date',
      'schema field' => 'changed',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'description' => t('Updated date of the bundle.'),
    );

    return $info;
  }

}
