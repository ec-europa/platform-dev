<?php

/**
 * @file
 * Creates vocabulary, fields and field instances.
 */

/**
 * Creates the nuts regions taxonomy term.
 */
function nuts_regions_vocabulary() {

  // Defines fields for the taxonomy term.
  $array_fields = array(

    // Defines the nuts level field.
    'nuts_level' => array(
      'field_name' => 'nuts_level',
      'type' => 'list_integer',
      'settings' => array(
        'allowed_values' => array(
          0 => 0,
          1 => 1,
          2 => 2,
          3 => 3,
        ),
      ),
      'module' => 'list',
      'active' => '1',
      'cardinality' => '1',
    ),

    // Defines the nuts id field. This is an integer.
    'nuts_id' => array(
      'field_name' => 'nuts_id',
      'type' => 'number_integer',
      'module' => 'number',
      'active' => '1',
      'cardinality' => '1',
    ),

    // Defines the nuts code field. This is a string containing the country
    // code and the nuts regions hierarchy. E.g. BE123 is child region of BE12.
    'nuts_code' => array(
      'field_name' => 'nuts_code',
      'type' => 'text',
      'module' => 'text',
      'active' => '1',
      'cardinality' => '1',
    ),

    // Defines the nuts description field. This is the name of the region.
    'nuts_description' => array(
      'field_name' => 'nuts_description',
      'type' => 'text',
      'module' => 'text',
      'active' => '1',
      'cardinality' => '1',
    ),

    // Defines the nuts country code field. This is a string of the 2 digit
    // country code. E.g. BE or EL.
    'nuts_country' => array(
      'field_name' => 'nuts_country',
      'type' => 'text',
      'module' => 'text',
      'active' => '1',
      'cardinality' => '1',
    ),

    // Defines the nuts remark field.
    'nuts_remark' => array(
      'field_name' => 'nuts_remark',
      'type' => 'text',
      'module' => 'text',
      'active' => '1',
      'cardinality' => '1',
    ),
  );

  $t = get_t();

  // Defines the field instances.
  $array_instances = array(

    // Defines the nuts level field instance.
    'nuts_level' => array(
      'label' => $t('Level'),
      'field_name' => 'nuts_level',
      'entity_type' => 'taxonomy_term',
      'bundle' => 'nuts_regions',
      'description' => 'Select the NUTS level.',
      'required' => TRUE,
      'widget' => array(
        'type' => 'options_select',
        'weight' => 0,
      ),
      'display' => array(),
    ),

    // Defines the nuts id field instance.
    'nuts_id' => array(
      'label' => $t('Code (ID)'),
      'field_name' => 'nuts_id',
      'required' => TRUE,
      'widget' => array(
        'type' => 'number',
      ),
      'entity_type' => 'taxonomy_term',
      'bundle' => 'nuts_regions',
    ),

    // Defines the nuts code field instance.
    'nuts_code' => array(
      'label' => $t('NUTS Code'),
      'field_name' => 'nuts_code',
      'required' => TRUE,
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'entity_type' => 'taxonomy_term',
      'bundle' => 'nuts_regions',
    ),

    // Defines the nuts code field instance.
    'nuts_country' => array(
      'label' => $t('NUTS Country'),
      'field_name' => 'nuts_country',
      'required' => TRUE,
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'entity_type' => 'taxonomy_term',
      'bundle' => 'nuts_regions',
    ),

    // Defines the nuts description field instance.
    'nuts_description' => array(
      'label' => $t('Description'),
      'field_name' => 'nuts_description',
      'required' => TRUE,
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'entity_type' => 'taxonomy_term',
      'bundle' => 'nuts_regions',
    ),

    // Defines the nuts remark field instance.
    'nuts_remark' => array(
      'label' => $t('Remark'),
      'field_name' => 'nuts_remark',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'entity_type' => 'taxonomy_term',
      'bundle' => 'nuts_regions',
    ),
  );

  // Creates the taxonomy term entity.
  $obj = (object) array();
  $obj->name = $t("NUTS regions");
  $obj->description = $t("Eurostat's NUTS regions (Nomenclature of territorial units for statistics)");
  $obj->machine_name = "nuts_regions";
  $obj->hierarchy = 2;
  $obj->module = "taxonomy";
  taxonomy_vocabulary_save($obj);

  // Creates the fields.
  foreach ($array_fields as $field) {
    field_create_field($field);
  }

  // Creates the field instances.
  foreach ($array_instances as $instance) {
    field_create_instance($instance);
  }

}

/**
 * Creates the nuts region field.
 *
 * @todo needs to be attached to some kind of entity in order to exist.
 */
function nuts_regions_field() {

  $array_fields = array(

    // Defines the nuts region field/
    'nuts_region' => array(
      'field_name' => 'nuts_region',
      'cardinality' => 1,
      'foreign keys' => array(
        'tid' => array(
          'columns' => array(
            'tid' => 'tid',
          ),
          'table' => 'taxonomy_term_data',
        ),
      ),
      'indexes' => array(
        'tid' => array(
          0 => 'tid',
        ),
      ),
      'settings' => array(
        'allowed_values' => array(
          0 => array(
            'vocabulary' => 'nuts_regions',
            'parent' => '0',
          ),
        ),
      ),
      'type' => 'taxonomy_term_reference',
    ),
  );

  // Defines the field instance for the user entity.
  // @todo discuss if this is desirable.

  $t = get_t();
  $array_instances = array(
    'nuts_region' => array(
      'field_name' => 'nuts_region',
      'label' => $t('NUTS region'),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_select',
      ),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'taxonomy',
          'settings' => array(),
          'type' => 'taxonomy_term_reference_link',
        ),
      ),
      'entity_type' => 'user',
      'bundle' => 'user',
    ),
  );

  // Creates the defined field(s).
  foreach ($array_fields as $field) {
    field_create_field($field);
  }

  // Creates the field instance on the user entity.
  foreach ($array_instances as $instance) {
    field_create_instance($instance);
  }

}
