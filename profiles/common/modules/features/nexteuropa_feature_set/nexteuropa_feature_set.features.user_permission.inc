<?php
/**
 * @file
 * nexteuropa_feature_set.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nexteuropa_feature_set_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'enable feature set contact_form'.
  $permissions['enable feature set contact_form'] = array(
    'name' => 'enable feature set contact_form',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set  e_library_standard'.
  $permissions['enable feature set e_library_standard'] = array(
    'name' => 'enable feature set e_library_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set ec_content_slider'.
  $permissions['enable feature set ec_content_slider'] = array(
    'name' => 'enable feature set ec_content_slider',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set ec_embedded_image'.
  $permissions['enable feature set ec_embedded_image'] = array(
    'name' => 'enable feature set ec_embedded_image',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set ec_embedded_video'.
  $permissions['enable feature set ec_embedded_video'] = array(
    'name' => 'enable feature set ec_embedded_video',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set ec_profiles'.
  $permissions['enable feature set ec_profiles'] = array(
    'name' => 'enable feature set ec_profiles',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set ec_world_countries'.
  $permissions['enable feature set ec_world_countries'] = array(
    'name' => 'enable feature set ec_world_countries',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set events_standard'.
  $permissions['enable feature set events_standard'] = array(
    'name' => 'enable feature set events_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set f_a_q'.
  $permissions['enable feature set f_a_q'] = array(
    'name' => 'enable feature set f_a_q',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set fat_footer'.
  $permissions['enable feature set fat_footer'] = array(
    'name' => 'enable feature set fat_footer',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set feed_rss_core'.
  $permissions['enable feature set feed_rss_core'] = array(
    'name' => 'enable feature set feed_rss_core',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set idea_standard'.
  $permissions['enable feature set idea_standard'] = array(
    'name' => 'enable feature set idea_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set links_standard'.
  $permissions['enable feature set links_standard'] = array(
    'name' => 'enable feature set links_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multi_user_blog'.
  $permissions['enable feature set multi_user_blog'] = array(
    'name' => 'enable feature set multi_user_blog',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multilingual_tools'.
  $permissions['enable feature set multilingual_tools'] = array(
    'name' => 'enable feature set multilingual_tools',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_activity_standard'.
  $permissions['enable feature set multisite_activity_standard'] = array(
    'name' => 'enable feature set multisite_activity_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_audio'.
  $permissions['enable feature set multisite_audio'] = array(
    'name' => 'enable feature set multisite_audio',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported 'enable feature set multisite_business_indicators_standard'.
  $permissions['enable feature set multisite_business_indicators_standard'] = array(
    'name' => 'enable feature set multisite_business_indicators_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_crop_and_resize'.
  $permissions['enable feature set multisite_crop_and_resize'] = array(
    'name' => 'enable feature set multisite_crop_and_resize',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_maxlength'.
  $permissions['enable feature set multisite_maxlength'] = array(
    'name' => 'enable feature set multisite_maxlength',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_mediagallery_standard'.
  $permissions['enable feature set multisite_mediagallery_standard'] = array(
    'name' => 'enable feature set multisite_mediagallery_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_megamenu'.
  $permissions['enable feature set multisite_megamenu'] = array(
    'name' => 'enable feature set multisite_megamenu',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_metatags'.
  $permissions['enable feature set multisite_metatags'] = array(
    'name' => 'enable feature set multisite_metatags',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_multilingual_references'.
  $permissions['enable feature set multisite_multilingual_references'] = array(
    'name' => 'enable feature set multisite_multilingual_references',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_notifications_core'.
  $permissions['enable feature set multisite_notifications_core'] = array(
    'name' => 'enable feature set multisite_notifications_core',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_registration_standard'.
  $permissions['enable feature set multisite_registration_standard'] = array(
    'name' => 'enable feature set multisite_registration_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set multisite_translations'.
  $permissions['enable feature set multisite_translations'] = array(
    'name' => 'enable feature set multisite_translations',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set news_standard'.
  $permissions['enable feature set news_standard'] = array(
    'name' => 'enable feature set news_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set newsletters'.
  $permissions['enable feature set newsletters'] = array(
    'name' => 'enable feature set newsletters',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set nexteuropa_geofield'.
  $permissions['enable feature set nexteuropa_geofield'] = array(
    'name' => 'enable feature set nexteuropa_geofield',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set nexteuropa_geojson_feeds'.
  $permissions['enable feature set nexteuropa_geojson_feeds'] = array(
    'name' => 'enable feature set nexteuropa_geojson_feeds',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set nexteuropa_integration'.
  $permissions['enable feature set nexteuropa_integration'] = array(
    'name' => 'enable feature set nexteuropa_integration',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set nexteuropa_notices'.
  $permissions['enable feature set nexteuropa_notices'] = array(
    'name' => 'enable feature set nexteuropa_notices',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set nexteuropa_webtools'.
  $permissions['enable feature set nexteuropa_webtools'] = array(
    'name' => 'enable feature set nexteuropa_webtools',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set node_pager'.
  $permissions['enable feature set node_pager'] = array(
    'name' => 'enable feature set node_pager',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set sitemap'.
  $permissions['enable feature set sitemap'] = array(
    'name' => 'enable feature set sitemap',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set splash_screen'.
  $permissions['enable feature set splash_screen'] = array(
    'name' => 'enable feature set splash_screen',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set survey_standard'.
  $permissions['enable feature set survey_standard'] = array(
    'name' => 'enable feature set survey_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set text_collapse'.
  $permissions['enable feature set text_collapse'] = array(
    'name' => 'enable feature set text_collapse',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature set wiki_standard'.
  $permissions['enable feature set wiki_standard'] = array(
    'name' => 'enable feature set wiki_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  return $permissions;
}
