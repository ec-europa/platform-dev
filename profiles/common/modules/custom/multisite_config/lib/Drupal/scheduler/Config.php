<?php

namespace Drupal\scheduler;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\scheduler.
 */
class Config extends ConfigBase {

  /**
   * Enable default scheduling options for a specific content type.
   *
   * @param string $type
   *    Content type machine name.
   */
  public function enableSchedulerForContentType($type) {
    variable_set('scheduler_expand_fieldset_' . $type, '0');
    variable_set('scheduler_publish_enable_' . $type, 1);
    variable_set('scheduler_publish_moderation_state_' . $type, 'published');
    variable_set('scheduler_publish_past_date_' . $type, 'error');
    variable_set('scheduler_publish_required_' . $type, 0);
    variable_set('scheduler_publish_revision_' . $type, 1);
    variable_set('scheduler_publish_touch_' . $type, 0);
    variable_set('scheduler_unpublish_default_time_' . $type, '');
    variable_set('scheduler_unpublish_enable_' . $type, 1);
    variable_set('scheduler_unpublish_required_' . $type, 0);
    variable_set('scheduler_unpublish_revision_' . $type, 0);
    variable_set('scheduler_use_vertical_tabs_' . $type, '0');
  }

}
