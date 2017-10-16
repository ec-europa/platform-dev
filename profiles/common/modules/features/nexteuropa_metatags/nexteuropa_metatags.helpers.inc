<?php
/**
 * @file
 * Code for the NextEuropa Metatags module.
 */

/**
 * Custom helper function.
 *
 * @return array
 *   Returns the error message if the config of metatags does not comply.
 */
function _nexteuropa_metatags_check_metatag_config() {
  $messages = array();

  if ($config = metatag_config_load('global')) {
    $meta_to_check = array('X-UA-Compatible', 'viewport');

    foreach ($meta_to_check as $meta) {
      if (!isset($config->config[$meta]) || (isset($config->config[$meta]) && empty($config->config[$meta]['value']))) {
        $messages[$meta] = t('The <em>@meta</em> global meta is empty, please <a href="@link">configure it</a> properly.', array('@meta' => $meta, '@link' => url('admin/config/search/metatags/config/global')));
      }
    }
  }

  return $messages;
}

/**
 * Custom function to get the list of IPG classifications.
 */
function _nexteuropa_metatags_classification_options() {
  $vid_classification = db_select('taxonomy_vocabulary', 't')
    ->fields('t')
    ->condition('machine_name', 'classification', '=')
    ->execute()
    ->fetchAll();
  // Get Taxonomy tree.
  $classification = taxonomy_get_tree($vid_classification[0]->vid);

  $list = array();
  foreach ($classification as $key => $obj_term) {
    $list[$obj_term->name] = $obj_term->name . ' - ' . strip_tags($obj_term->description);
  }
  return $list;
}


/**
 * Create the "metatags ess gf".
 */
function _nexteuropa_metatags_create_metatag_config() {
  // Check if the vocabulary is already created.
  if (FALSE !== taxonomy_vocabulary_machine_name_load('metatags_ess_gf')) {
    return;
  }

  // Create a vocabulary dedicated to the ESS metatags.
  multisite_config_service('taxonomy')->createVocabulary('metatags_ess_gf', 'Metatags ESS GF', 'Values of the ESS_GF metatag');
  $vocabulary = taxonomy_vocabulary_machine_name_load('metatags_ess_gf');

  // Create a field to store the id of the tag value.
  $field_meta_id = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_meta_id',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 10,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Create a field to store the value of the tag.
  $field_meta_value = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_meta_value',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  field_create_field($field_meta_id);
  field_create_field($field_meta_value);

  // Create an instance of field_meta_id in the vocabulary ess_matetags_gf.
  $field_instance_meta_id = array(
    'bundle' => $vocabulary->machine_name,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_meta_id',
    'label' => 'Meta id',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'basic_html' => 'basic_html',
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'basic_html' => array(
              'weight' => 5,
            ),
            'filtered_html' => array(
              'weight' => -9,
            ),
            'full_html' => array(
              'weight' => -10,
            ),
            'plain_text' => array(
              'weight' => -8,
            ),
          ),
        ),
      ),
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 41,
    ),
  );

  // Create an instance of field_meta_value in the vocabulary ess_matetags_gf.
  $field_instance_meta_value = array(
    'bundle' => $vocabulary->machine_name,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_meta_value',
    'label' => 'Meta value',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'basic_html' => 'basic_html',
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'basic_html' => array(
              'weight' => 5,
            ),
            'filtered_html' => array(
              'weight' => -9,
            ),
            'full_html' => array(
              'weight' => -10,
            ),
            'plain_text' => array(
              'weight' => -8,
            ),
          ),
        ),
      ),
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 42,
    ),
  );

  field_create_instance($field_instance_meta_id);
  field_create_instance($field_instance_meta_value);

  // Add terms.
  $metatags_ess_gf = array(
    array(
      "id" => "1",
      "name" => "Functioning of the EU",
      "value" => "GLOBAL::FUNCTIONING OF THE EU",
      "weight" => "0",
      "childs" => array(
        array(
          "id" => "1.1",
          "name" => "EU institutions, administration and staff",
          "value" => "GLOBAL::FUNCTIONING OF THE EU::EU INSTITUTIONS ADMINISTRATION AND STAFF",
          "weight" => "0",
        ),
        array(
          "id" => "1.2",
          "name" => "EU Law",
          "value" => "GLOBAL::FUNCTIONING OF THE EU::EU LAW",
          "weight" => "1",
        ),
        array(
          "id" => "1.3",
          "name" => "Information & communication of the EU",
          "value" => "GLOBAL::FUNCTIONING OF THE EU::INFORMATION AND COMMUNICATION OF THE EU",
          "weight" => "2",
        ),
        array(
          "id" => "1.4",
          "name" => "Enlargement",
          "value" => "GLOBAL::FUNCTIONING OF THE EU::ENLARGEMENT",
          "weight" => "3",
        ),
      ),
    ),
    array(
      "id" => "2",
      "name" => "Life & rights in the EU",
      "value" => "GLOBAL::LIFE AND RIGHTS IN THE EU",
      "weight" => "1",
      "childs" => array(
        array(
          "id" => "2.1",
          "name" => "Justice",
          "value" => "GLOBAL::LIFE AND RIGHTS IN THE EU::JUSTICE",
          "weight" => "0",
        ),
        array(
          "id" => "2.2",
          "name" => "Citizens' rights and security",
          "value" => "GLOBAL::LIFE AND RIGHTS IN THE EU::CITIZENS RIGHTS AND SECURITY",
          "weight" => "1",
        ),
        array(
          "id" => "2.3",
          "name" => "Immigration, residence and travel",
          "value" => "GLOBAL::LIFE AND RIGHTS IN THE EU::IMMIGRATION RESIDENCE AND TRAVEL",
          "weight" => "2",
        ),
      ),
    ),
    array(
      "id" => "3",
      "name" => "EU in the world",
      "value" => "GLOBAL::EU IN THE WORLD",
      "weight" => "2",
      "childs" => array(
        array(
          "id" => "3.1",
          "name" => "EU international role ",
          "value" => "GLOBAL::EU IN THE WORLD::EU INTERNATIONAL ROLE",
          "weight" => "0",
        ),
        array(
          "id" => "3.2",
          "name" => "Development and humanitarian aid",
          "value" => "GLOBAL::EU IN THE WORLD::DEVELOPMENT AND HUMANITARIAN AID",
          "weight" => "1",
        ),
        array(
          "id" => "3.3",
          "name" => "Relations with non-EU countries",
          "value" => "GLOBAL::EU IN THE WORLD::RELATIONS WITH NON-EU COUNTRIES",
          "weight" => "2",
        ),
      ),
    ),
    array(
      "id" => "4",
      "name" => "Work & education",
      "value" => "GLOBAL::WORK AND EDUCATION",
      "weight" => "3",
      "childs" => array(
        array(
          "id" => "4.1",
          "name" => "Employment",
          "value" => "GLOBAL::WORK AND EDUCATION::EMPLOYMENT",
          "weight" => "0",
        ),
        array(
          "id" => "4.2",
          "name" => "Education",
          "value" => "GLOBAL::WORK AND EDUCATION::EDUCATION",
          "weight" => "1",
        ),
        array(
          "id" => "4.3",
          "name" => "Social protection",
          "value" => "GLOBAL::WORK AND EDUCATION::SOCIAL PROTECTION",
          "weight" => "2",
        ),
        array(
          "id" => "4.4",
          "name" => "Youth",
          "value" => "GLOBAL::WORK AND EDUCATION::YOUTH",
          "weight" => "3",
        ),
      ),
    ),
    array(
      "id" => "5",
      "name" => "Health, wellbeing & consumer protection",
      "value" => "GLOBAL::HEALTH WELLBEING AND CONSUMER PROTECTION",
      "weight" => "4",
      "childs" => array(
        array(
          "id" => "5.1",
          "name" => "Health",
          "value" => "GLOBAL::HEALTH WELLBEING AND CONSUMER PROTECTION::HEALTH",
          "weight" => "0",
        ),
        array(
          "id" => "5.2",
          "name" => "Sport",
          "value" => "GLOBAL::HEALTH WELLBEING AND CONSUMER PROTECTION::SPORT",
          "weight" => "1",
        ),
        array(
          "id" => "5.3",
          "name" => "Consumer Protection (& food safety)",
          "value" => "GLOBAL::HEALTH WELLBEING AND CONSUMER PROTECTION::CONSUMER PROTECTION (AND FOOD SAFETY)",
          "weight" => "2",
        ),
      ),
    ),
    array(
      "id" => "6",
      "name" => "Economy, finance & investment",
      "value" => "GLOBAL::ECONOMY FINANCE AND INVESTMENT",
      "weight" => "5",
      "childs" => array(
        array(
          "id" => "6.1",
          "name" => "Economy and monetary affairs",
          "value" => "GLOBAL::ECONOMY FINANCE AND INVESTMENT::ECONOMY AND MONETARY AFFAIRS",
          "weight" => "0",
        ),
        array(
          "id" => "6.2",
          "name" => "Budget and finances",
          "value" => "GLOBAL::ECONOMY FINANCE AND INVESTMENT::BUDGET AND FINANCES",
          "weight" => "1",
        ),
        array(
          "id" => "6.3",
          "name" => "Investment",
          "value" => "GLOBAL::ECONOMY FINANCE AND INVESTMENT::INVESTMENT",
          "weight" => "2",
        ),
        array(
          "id" => "6.4",
          "name" => "Taxation",
          "value" => "GLOBAL::ECONOMY FINANCE AND INVESTMENT::TAXATION",
          "weight" => "3",
        ),
      ),
    ),
    array(
      "id" => "7",
      "name" => "Business & industry",
      "value" => "GLOBAL::BUSINESS AND INDUSTRY",
      "weight" => "6",
      "childs" => array(
        array(
          "id" => "7.1",
          "name" => "Sectors",
          "value" => "GLOBAL::BUSINESS AND INDUSTRY::SECTORS",
          "weight" => "0",
        ),
        array(
          "id" => "7.2",
          "name" => "Internal market rules (& competition)",
          "value" => "GLOBAL::BUSINESS AND INDUSTRY::INTERNAL MARKET RULES (AND COMPETITION)",
          "weight" => "1",
        ),
        array(
          "id" => "7.3",
          "name" => "Customs",
          "value" => "GLOBAL::BUSINESS AND INDUSTRY::CUSTOMS",
          "weight" => "2",
        ),
      ),
    ),
    array(
      "id" => "8",
      "name" => "Environment, food & natural resources",
      "value" => "GLOBAL::ENVIRONMENT FOOD AND NATURAL RESOURCES",
      "weight" => "7",
      "childs" => array(
        array(
          "id" => "8.1",
          "name" => "Climate change",
          "value" => "GLOBAL::ENVIRONMENT FOOD AND NATURAL RESOURCES::CLIMATE CHANGE",
          "weight" => "0",
        ),
        array(
          "id" => "8.2",
          "name" => "Environment",
          "value" => "GLOBAL::ENVIRONMENT FOOD AND NATURAL RESOURCES::ENVIRONMENT",
          "weight" => "1",
        ),
        array(
          "id" => "8.3",
          "name" => "Natural Resources",
          "value" => "GLOBAL::ENVIRONMENT FOOD AND NATURAL RESOURCES::NATURAL RESOURCES",
          "weight" => "2",
        ),
        array(
          "id" => "8.4",
          "name" => "Food production",
          "value" => "GLOBAL::ENVIRONMENT FOOD AND NATURAL RESOURCES::FOOD PRODUCTION",
          "weight" => "3",
        ),
      ),
    ),
    array(
      "id" => "9",
      "name" => "Infrastructure, research & innovation",
      "value" => "GLOBAL::INFRASTRUCTURE RESEARCH AND INNOVATION",
      "weight" => "8",
      "childs" => array(
        array(
          "id" => "9.1",
          "name" => "Energy",
          "value" => "GLOBAL::INFRASTRUCTURE RESEARCH AND INNOVATION::ENERGY",
          "weight" => "0",
        ),
        array(
          "id" => "9.2",
          "name" => "Transport",
          "value" => "GLOBAL::INFRASTRUCTURE RESEARCH AND INNOVATION::TRANSPORT",
          "weight" => "1",
        ),
        array(
          "id" => "9.3",
          "name" => "Telecommunications",
          "value" => "GLOBAL::INFRASTRUCTURE RESEARCH AND INNOVATION::TELECOMMUNICATIONS",
          "weight" => "2",
        ),
        array(
          "id" => "9.4",
          "name" => "Research & innovation",
          "value" => "GLOBAL::INFRASTRUCTURE RESEARCH AND INNOVATION::RESEARCH AND INNOVATION",
          "weight" => "3",
        ),
      ),
    ),
    array(
      "id" => "10",
      "name" => "Media, culture & languages in the EU",
      "value" => "GLOBAL::MEDIA CULTURE AND LANGUAGES IN THE EU",
      "weight" => "9",
      "childs" => array(
        array(
          "id" => "10.1",
          "name" => "Media",
          "value" => "GLOBAL::MEDIA CULTURE AND LANGUAGES IN THE EU::MEDIA",
          "weight" => "0",
        ),
        array(
          "id" => "10.2",
          "name" => "Culture",
          "value" => "GLOBAL::MEDIA CULTURE AND LANGUAGES IN THE EU::CULTURE",
          "weight" => "1",
        ),
        array(
          "id" => "10.3",
          "name" => "Languages in the EU",
          "value" => "GLOBAL::MEDIA CULTURE AND LANGUAGES IN THE EU::LANGUAGES IN THE EU",
          "weight" => "2",
        ),
      ),
    ),
  );

  foreach ($metatags_ess_gf as $metatags) {
    $fields = array(
      'field_meta_id' => array(LANGUAGE_NONE => array(0 => array('value' => $metatags['id']))),
      'field_meta_value' => array(LANGUAGE_NONE => array(0 => array('value' => $metatags['value']))),
    );
    multisite_config_service('taxonomy')->createTaxonomyTerm('metatags_ess_gf', $metatags['name'], NULL, $fields, $metatags['weight']);
    if (isset($metatags['childs'])) {
      foreach ($metatags['childs'] as $childs) {
        $fields = array(
          'field_meta_id' => array(LANGUAGE_NONE => array(0 => array('value' => $childs['id']))),
          'field_meta_value' => array(LANGUAGE_NONE => array(0 => array('value' => $childs['value']))),
        );
        multisite_config_service('taxonomy')->createTaxonomyTerm('metatags_ess_gf', $childs['name'], $metatags['name'], $fields, $childs['weight']);
      }
    }
  }
}

/**
 * Delete the "metatags ess gf".
 */
function _nexteuropa_metatags_delete_metatag_config() {
  // Delete the vocabulary.
  multisite_config_service('taxonomy')->deleteVocabulary('metatags_ess_gf');
}

/**
 * Create permissions to administrator/contributor/editor.
 */
function _nexteuropa_metatags_create_permission() {
  // Set permissions to the administrator role.
  $permissions = array(
    'edit meta tags',
    'administer meta tags',
  );
  multisite_config_service('user')->grantPermission('administrator', $permissions);

  // Set permissions to the contributor and editor role.
  $permissions = array(
    'edit meta tags',
  );
  multisite_config_service('user')->grantPermission('contributor', $permissions);
  multisite_config_service('user')->grantPermission('editor', $permissions);
}
