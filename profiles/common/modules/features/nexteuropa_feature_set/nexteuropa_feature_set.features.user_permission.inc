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

  // Exported permission: 'manage feature contact_form'.
  $permissions['manage feature contact_form'] = array(
    'name' => 'manage feature contact_form',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature e_library_standard'.
  $permissions['manage feature e_library_standard'] = array(
    'name' => 'manage feature e_library_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature ec_content_slider'.
  $permissions['manage feature ec_content_slider'] = array(
    'name' => 'manage feature ec_content_slider',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature ec_embedded_image'.
  $permissions['manage feature ec_embedded_image'] = array(
    'name' => 'manage feature ec_embedded_image',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature ec_embedded_video'.
  $permissions['manage feature ec_embedded_video'] = array(
    'name' => 'manage feature ec_embedded_video',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature ec_profiles'.
  $permissions['manage feature ec_profiles'] = array(
    'name' => 'manage feature ec_profiles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature ec_world_countries'.
  $permissions['manage feature ec_world_countries'] = array(
    'name' => 'manage feature ec_world_countries',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature events_standard'.
  $permissions['manage feature events_standard'] = array(
    'name' => 'manage feature events_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature f_a_q'.
  $permissions['manage feature f_a_q'] = array(
    'name' => 'manage feature f_a_q',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature fat_footer'.
  $permissions['manage feature fat_footer'] = array(
    'name' => 'manage feature fat_footer',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature feed_rss_core'.
  $permissions['manage feature feed_rss_core'] = array(
    'name' => 'manage feature feed_rss_core',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature idea_standard'.
  $permissions['manage feature idea_standard'] = array(
    'name' => 'manage feature idea_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature links_standard'.
  $permissions['manage feature links_standard'] = array(
    'name' => 'manage feature links_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multi_user_blog'.
  $permissions['manage feature multi_user_blog'] = array(
    'name' => 'manage feature multi_user_blog',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multilingual_tools'.
  $permissions['manage feature multilingual_tools'] = array(
    'name' => 'manage feature multilingual_tools',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_activity_standard'.
  $permissions['manage feature multisite_activity_standard'] = array(
    'name' => 'manage feature multisite_activity_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_audio'.
  $permissions['manage feature multisite_audio'] = array(
    'name' => 'manage feature multisite_audio',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature
  // multisite_business_indicators_standard'.
  $permissions['manage feature multisite_business_indicators_standard'] = array(
    'name' => 'manage feature multisite_business_indicators_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_crop_and_resize'.
  $permissions['manage feature multisite_crop_and_resize'] = array(
    'name' => 'manage feature multisite_crop_and_resize',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_maxlength'.
  $permissions['manage feature multisite_maxlength'] = array(
    'name' => 'manage feature multisite_maxlength',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_mediagallery_standard'.
  $permissions['manage feature multisite_mediagallery_standard'] = array(
    'name' => 'manage feature multisite_mediagallery_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_megamenu'.
  $permissions['manage feature multisite_megamenu'] = array(
    'name' => 'manage feature multisite_megamenu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_multilingual_references'.
  $permissions['manage feature multisite_multilingual_references'] = array(
    'name' => 'manage feature multisite_multilingual_references',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_notifications_core'.
  $permissions['manage feature multisite_notifications_core'] = array(
    'name' => 'manage feature multisite_notifications_core',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_registration_standard'.
  $permissions['manage feature multisite_registration_standard'] = array(
    'name' => 'manage feature multisite_registration_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature multisite_translations'.
  $permissions['manage feature multisite_translations'] = array(
    'name' => 'manage feature multisite_translations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature news_standard'.
  $permissions['manage feature news_standard'] = array(
    'name' => 'manage feature news_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature newsletters'.
  $permissions['manage feature newsletters'] = array(
    'name' => 'manage feature newsletters',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature nexteuropa_geofield'.
  $permissions['manage feature nexteuropa_geofield'] = array(
    'name' => 'manage feature nexteuropa_geofield',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature nexteuropa_geojson_feeds'.
  $permissions['manage feature nexteuropa_geojson_feeds'] = array(
    'name' => 'manage feature nexteuropa_geojson_feeds',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature nexteuropa_integration'.
  $permissions['manage feature nexteuropa_integration'] = array(
    'name' => 'manage feature nexteuropa_integration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature nexteuropa_notices'.
  $permissions['manage feature nexteuropa_notices'] = array(
    'name' => 'manage feature nexteuropa_notices',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature nexteuropa_poetry'.
  $permissions['manage feature nexteuropa_dgt_connector'] = array(
    'name' => 'manage feature nexteuropa_dgt_connector',
    'roles' => array(
      'cem' => 'cem',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature nexteuropa_webtools'.
  $permissions['manage feature nexteuropa_webtools'] = array(
    'name' => 'manage feature nexteuropa_webtools',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature node_pager'.
  $permissions['manage feature node_pager'] = array(
    'name' => 'manage feature node_pager',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature sitemap'.
  $permissions['manage feature sitemap'] = array(
    'name' => 'manage feature sitemap',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature splash_screen'.
  $permissions['manage feature splash_screen'] = array(
    'name' => 'manage feature splash_screen',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature survey_standard'.
  $permissions['manage feature survey_standard'] = array(
    'name' => 'manage feature survey_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature text_collapse'.
  $permissions['manage feature text_collapse'] = array(
    'name' => 'manage feature text_collapse',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'manage feature wiki_standard'.
  $permissions['manage feature wiki_standard'] = array(
    'name' => 'manage feature wiki_standard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  return $permissions;
}
