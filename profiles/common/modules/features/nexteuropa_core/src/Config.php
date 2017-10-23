<?php

namespace Drupal\nexteuropa_core;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\nexteuropa_core.
 */
class Config extends ConfigBase {

  /**
   * Apply default NextEuropa configuration to a specific content type.
   *
   * This method is usually called into hook_install().
   *
   * @param string $type
   *   Content type machine name.
   *
   * @see nexteuropa_pages_install()
   */
  public function applyDefaultConfigurationToContentType($type) {

    // Replace title field.
    multisite_config_service('title')->replaceTitleField('node', $type, 'title');
    multisite_config_service('entity_translation')->enableEntityTranslation($type);

    // Add Organic Group fields.
    multisite_config_service('og')->createOgGroupAudienceField('node', $type);
    multisite_config_service('og')->createOgContentAccessField('node', $type);

    // Enable Workbench Moderation.
    multisite_config_service('workbench_moderation')->enableWorkbenchModeration($type);

    // Grant OG permissions if NextEuropa Editorial feature is enabled.
    if (module_exists('nexteuropa_editorial')) {
      $og_permissions = array();
      $og_permissions['contributor'] = array(
        'create ' . $type . ' content',
        'update own ' . $type . ' content',
        'delete own ' . $type . ' content',
      );
      $og_permissions['validator'] = $og_permissions['publisher'] = $og_permissions['administrator member'] = array(
        'create ' . $type . ' content',
        'update own ' . $type . ' content',
        'delete own ' . $type . ' content',
        'update any ' . $type . ' content',
        'delete any ' . $type . ' content',
      );
      foreach ($og_permissions as $role => $permissions) {
        multisite_config_service('og')->grantOgPermissions($role, $permissions, 'node', 'editorial_team', 'og');
      }
    }

    // Enable Linkchecker control for "Page" content type.
    multisite_config_service('linkchecker')->enableLinkcheckerForContentType($type);

    if (module_exists('scheduler')) {
      // Enable default scheduling options for a specific content type.
      multisite_config_service('scheduler')->enableSchedulerForContentType($type);
    }

    // Set unpublish moderation state to "expired".
    // This call cannot be included in the API method above since it is
    // a configuration specific to NextEuropa .
    variable_set('scheduler_unpublish_moderation_state_' . $type, 'expired');
  }

}
