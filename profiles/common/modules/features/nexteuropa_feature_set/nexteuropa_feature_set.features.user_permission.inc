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

  // Exported permission: 'enable feature setcontact_form'.
  $permissions['enable feature setcontact_form'] = array(
    'name' => 'enable feature setcontact_form',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature sete_library_standard'.
  $permissions['enable feature sete_library_standard'] = array(
    'name' => 'enable feature sete_library_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setec_content_slider'.
  $permissions['enable feature setec_content_slider'] = array(
    'name' => 'enable feature setec_content_slider',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setec_embedded_image'.
  $permissions['enable feature setec_embedded_image'] = array(
    'name' => 'enable feature setec_embedded_image',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setec_embedded_video'.
  $permissions['enable feature setec_embedded_video'] = array(
    'name' => 'enable feature setec_embedded_video',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setec_profiles'.
  $permissions['enable feature setec_profiles'] = array(
    'name' => 'enable feature setec_profiles',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setec_world_countries'.
  $permissions['enable feature setec_world_countries'] = array(
    'name' => 'enable feature setec_world_countries',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setevents_standard'.
  $permissions['enable feature setevents_standard'] = array(
    'name' => 'enable feature setevents_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setf_a_q'.
  $permissions['enable feature setf_a_q'] = array(
    'name' => 'enable feature setf_a_q',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setfat_footer'.
  $permissions['enable feature setfat_footer'] = array(
    'name' => 'enable feature setfat_footer',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setfeed_rss_core'.
  $permissions['enable feature setfeed_rss_core'] = array(
    'name' => 'enable feature setfeed_rss_core',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setidea_standard'.
  $permissions['enable feature setidea_standard'] = array(
    'name' => 'enable feature setidea_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setlinks_standard'.
  $permissions['enable feature setlinks_standard'] = array(
    'name' => 'enable feature setlinks_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmulti_user_blog'.
  $permissions['enable feature setmulti_user_blog'] = array(
    'name' => 'enable feature setmulti_user_blog',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultilingual_tools'.
  $permissions['enable feature setmultilingual_tools'] = array(
    'name' => 'enable feature setmultilingual_tools',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_activity_standard'.
  $permissions['enable feature setmultisite_activity_standard'] = array(
    'name' => 'enable feature setmultisite_activity_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_audio'.
  $permissions['enable feature setmultisite_audio'] = array(
    'name' => 'enable feature setmultisite_audio',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_business_indicators_standard'.
  $permissions['enable feature setmultisite_business_indicators_standard'] = array(
    'name' => 'enable feature setmultisite_business_indicators_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_crop_and_resize'.
  $permissions['enable feature setmultisite_crop_and_resize'] = array(
    'name' => 'enable feature setmultisite_crop_and_resize',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_maxlength'.
  $permissions['enable feature setmultisite_maxlength'] = array(
    'name' => 'enable feature setmultisite_maxlength',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_mediagallery_standard'.
  $permissions['enable feature setmultisite_mediagallery_standard'] = array(
    'name' => 'enable feature setmultisite_mediagallery_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_megamenu'.
  $permissions['enable feature setmultisite_megamenu'] = array(
    'name' => 'enable feature setmultisite_megamenu',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_metatags'.
  $permissions['enable feature setmultisite_metatags'] = array(
    'name' => 'enable feature setmultisite_metatags',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_multilingual_references'.
  $permissions['enable feature setmultisite_multilingual_references'] = array(
    'name' => 'enable feature setmultisite_multilingual_references',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_notifications_core'.
  $permissions['enable feature setmultisite_notifications_core'] = array(
    'name' => 'enable feature setmultisite_notifications_core',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_registration_standard'.
  $permissions['enable feature setmultisite_registration_standard'] = array(
    'name' => 'enable feature setmultisite_registration_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setmultisite_translations'.
  $permissions['enable feature setmultisite_translations'] = array(
    'name' => 'enable feature setmultisite_translations',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnews_standard'.
  $permissions['enable feature setnews_standard'] = array(
    'name' => 'enable feature setnews_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnewsletters'.
  $permissions['enable feature setnewsletters'] = array(
    'name' => 'enable feature setnewsletters',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnexteuropa_geofield'.
  $permissions['enable feature setnexteuropa_geofield'] = array(
    'name' => 'enable feature setnexteuropa_geofield',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnexteuropa_geojson_feeds'.
  $permissions['enable feature setnexteuropa_geojson_feeds'] = array(
    'name' => 'enable feature setnexteuropa_geojson_feeds',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnexteuropa_integration'.
  $permissions['enable feature setnexteuropa_integration'] = array(
    'name' => 'enable feature setnexteuropa_integration',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnexteuropa_notices'.
  $permissions['enable feature setnexteuropa_notices'] = array(
    'name' => 'enable feature setnexteuropa_notices',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnexteuropa_webtools'.
  $permissions['enable feature setnexteuropa_webtools'] = array(
    'name' => 'enable feature setnexteuropa_webtools',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setnode_pager'.
  $permissions['enable feature setnode_pager'] = array(
    'name' => 'enable feature setnode_pager',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setsitemap'.
  $permissions['enable feature setsitemap'] = array(
    'name' => 'enable feature setsitemap',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setsplash_screen'.
  $permissions['enable feature setsplash_screen'] = array(
    'name' => 'enable feature setsplash_screen',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setsurvey_standard'.
  $permissions['enable feature setsurvey_standard'] = array(
    'name' => 'enable feature setsurvey_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature settext_collapse'.
  $permissions['enable feature settext_collapse'] = array(
    'name' => 'enable feature settext_collapse',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  // Exported permission: 'enable feature setwiki_standard'.
  $permissions['enable feature setwiki_standard'] = array(
    'name' => 'enable feature setwiki_standard',
    'roles' => array(),
    'module' => 'multisite_drupal_features_set_standard',
  );

  return $permissions;
}
