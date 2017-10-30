<?php

module_load_include('inc', 'nexteuropa_metatags', 'nexteuropa_metatags.helpers');

/**
 * Alter record insertion provided by modules with the previous hook.
 *
 * @see hook_metatag_info()
 */
function nexteuropa_metatags_metatag_info_alter(&$info) {
  // Remove the generator metatag that we never want to show.
  unset($info['tags']['generator']);
}

/**
 * Implements hook_metatag_config_default().
 *
 * Provides default for nexteuropa tags.
 */
function nexteuropa_metatags_metatag_config_default() {
  // Optionally skip loading the defaults.
  if (!variable_get('metatag_load_defaults', TRUE)) {
    return;
  }
  $og_image_fid = variable_get('meta_og_image', '');

  // Only overrides default if value is already set.
  $meta_creator = variable_get('meta_creator', '');
  $reference = variable_get('meta_reference', '');

  $configs = array();

  $config = new stdClass();
  $config->instance = 'global';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    // Basic Tags.
    'keywords' => array(
      'value' => 'European Commission, European Union, EU',
    ),
    // Nexteuropa tags.
    'creator' => array(
      'value' => !empty($meta_creator) ? $meta_creator : 'COMM/DG/UNIT',
    ),
    'reference' => array(
      'value' => !empty($reference) ? $reference : '[site:name]',
    ),
    'classification' => array(
      'value' => '[variable:classification]',
      'readonly' => 'readonly',
    ),
    // Basic tags.
    'description' => array(
      'value' => '[site:name] - [site:slogan]',
    ),
    'title' => array(
      'value' => '[current-page:title] | [site:name]',
    ),
    // Advances tags.
    'canonical' => array(
      'value' => '[current-page:url:absolute]',
    ),
    'shortlink' => array(
      'value' => '[current-page:url:unaliased]',
    ),
    'content-language' => array(
      'value' => '[language:language-ui:language]',
    ),
    'date' => array(
      'value' => '[current-date:short]',
    ),
    'dcterms.format' => array(
      'value' => 'text/html',
    ),
    'dcterms.identifier' => array(
      'value' => '[current-page:url:absolute]',
    ),
    'dcterms.title' => array(
      'value' => '[current-page:title]',
    ),
    'dcterms.type' => array(
      'value' => 'Text',
    ),
    // Open graph tags.
    'og:description' => array(
      'value' => '[site:name] - [site:slogan]',
    ),
    'og:image' => array(
      'value' => !empty($og_image_fid) ? '[files:uri:' . $og_image_fid . ']' : '',
    ),
    'og:site_name' => array(
      'value' => '[site:name] - European Commission',
    ),
    'og:title' => array(
      'value' => '[current-page:title]',
    ),
    'og:type' => array(
      'value' => 'website',
    ),
    'og:url' => array(
      'value' => '[current-page:url:absolute]',
    ),
    'revisit-after' => array(
      'value' => 15,
      'period' => 'day',
    ),
    'robots' => array(
      'value' => array(
        'index' => 'index',
        'follow' => 'follow',
        'noindex' => 0,
        'nofollow' => 0,
        'noarchive' => 0,
        'nosnippet' => 0,
        'noodp' => 0,
        'noydir' => 0,
        'noimageindex' => 0,
        'notranslate' => 0,
      ),
    ),
    // Mobile & ui adjustments tags.
    'viewport' => array(
      'value' => 'width=device-width, initial-scale=1.0',
    ),
    // Windows & windows mobile tags.
    'x-ua-compatible' => array(
      'value' => 'IE=edge',
    ),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'node';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    // tags.
    'article:modified_time' => array(
      'value' => '[node:changed:custom:c]',
    ),
    'article:published_time' => array(
      'value' => '[node:created:custom:c]',
    ),
    'classification' => array(
      'value' => '[variable:classification], [node:field-meta-classification]',
    ),
    'dcterms.creator' => array(
      'value' => '[node:author]',
    ),
    'dcterms.date' => array(
      'value' => '[node:created:custom:Y-m-d\\TH:iP]',
    ),
    'dcterms.description' => array(
      'value' => '[node:summary]',
    ),
    'dcterms.language' => array(
      'value' => '[node:language]',
    ),
    'dcterms.title' => array(
      'value' => '[node:title]',
    ),
    'description' => array(
      'value' => '[node:field-meta-description]',
    ),
    'keywords' => array(
      'value' => '[node:field-tags]',
    ),
    'og:description' => array(
      'value' => '[node:field-meta-description]',
    ),
    'og:title' => array(
      'value' => '[node:title] - [site:name] - European Commission',
    ),
    'og:type' => array(
      'value' => '[node:content-type]',
    ),
    'og:updated_time' => array(
      'value' => '[node:changed:custom:c]',
    ),
  );
  $configs[$config->instance] = $config;

  // Before returning these, allow the bundled submodules to override them, thus
  // extending the "real" defaults before they can then be altered by other
  // modules.
  // See hook_metatag_bundled_config_alter() in the API documentation.
  drupal_alter('metatag_bundled_config', $configs);
  return $configs;
}

/**
 * Implements hook_metatag_info().
 *
 * Declaration of tags that are specifically provided by nexteuropa feature.
 */
function nexteuropa_metatags_metatag_info() {

  // Create a tag group for nexteuropa tags.
  $info['groups']['nexteuropa'] = array(
    'label' => t('Nexteuropa tags'),
    'description' => t('Add metatag information that respects the IPG guidelines and are required by corporate tools.'),
    'form' => array(
      '#weight' => 20,
    ),
  );

  // Create a tag group for Europa search tags.
  $info['groups']['ESS_metatags'] = array(
    'label' => t('ESS metatags : metatags for Europa Search indexation'),
    'description' => t('Add metatag information that are necessary for Europa search integration.'),
  );

  $options = array();
  if ($vocabulary = taxonomy_vocabulary_machine_name_load('metatags_ess_gf')) {
    $terms = taxonomy_get_tree($vocabulary->vid);
    foreach ($terms as $term) {
      $term_full = taxonomy_term_load($term->tid);
      $options[$term_full->field_meta_value[LANGUAGE_NONE][0]['value']] = str_repeat('-', $term->depth) . $term->name;
    }
  }
  $info['tags']['ESS_GF'] = array(
    'label' => t('ESS GF'),
    'description' => t('Global search'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'ESS_metatags',
    'form' => array(
      '#type' => 'select',
      '#options' => $options,
      '#empty_option' => t('- None -'),
    ),
    'select_or_other' => TRUE,
  );

  $info['tags']['ESS_RF'] = array(
    'label' => t('ESS RF'),
    'description' => t('Restricted search'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'ESS_metatags',
  );

  // Default values for each nexteuropa meta tag.
  $ne_defaults = array(
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'nexteuropa',
    'element' => array(
      '#theme' => 'metatag_property',
    ),
  );

  $info['tags']['creator'] = array(
    'label' => t('Creator'),
    'description' => t('Ex. COMM/DG/UNIT (max. 30 characters).<br/>This text will supply information to METADATA "Creator".<br/>See the <a href="http://ec.europa.eu/ipg/content/optimise/metadata/annex1_en.htm#section_2" target="_blank">IPG guidelines</a> for more information.'),
    'context' => array('global'),
  ) + $ne_defaults;

  $info['tags']['classification'] = array(
    'label' => t('IPG Classification'),
    'description' => t('Choose the classification for your website. You can 
    also enter the token value of a taxonomy term or reference field pointing 
    to the "classification" vocabulary, by selecting "other". This 
    classification complies with !url',
      array(
        '!url' => l(t('IPG guidelines'),
        'http://ec.europa.eu/ipg/content/optimise/metadata/annex2_en.htm'),
      )
    ),
    'select_or_other' => TRUE,
    'form' => array(
      '#type' => 'select',
      '#options' => _nexteuropa_metatags_classification_options(),
      '#empty_option' => t('- None -'),
      '#required' => TRUE,
    ),
    'devel_generate' => array(
      'type' => 'select',
    ),
  ) + $ne_defaults;

  $info['tags']['reference'] = array(
    'label' => t('Reference'),
    'description' => t('Usually the acronym of the DG / Site name (max. 30 characters).<br/>This text will supply information to METADATA "Reference".<br/>See the <a href="http://ec.europa.eu/ipg/content/optimise/metadata/annex1_en.htm#section_1" target="_blank">IPG guidelines</a> for more information.'),
    'select_or_other' => TRUE,
  ) + $ne_defaults;
  return $info;
}
