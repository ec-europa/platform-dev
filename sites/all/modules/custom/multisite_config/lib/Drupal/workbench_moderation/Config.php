<?php

/**
 * @file
 * Contains \Drupal\workbench_moderation\Config
 */

namespace Drupal\workbench_moderation;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Create a new or existing moderation state.
   *
   * Moderation state names must be unique, so saving a state object with a
   * non-unique name updates the existing state.
   *
   * @param $name
   *    State name
   * @param type $label
   *    State label
   * @param type $description
   *    State description
   * @param type $weight
   *    State weight
   * @return type
   *    Created state object
   */
  public function createModerationState($name, $label, $description = NULL, $weight = 0) {
    $state = new \stdClass;
    $state->name = $name;
    $state->label = $label;
    $state->description = $description;
    $state->weight = $weight;
    return workbench_moderation_state_save($state);
  }

  /**
   * Create a new moderation state transition.
   *
   * @param type $from
   * @param type $to
   * @return type
   */
  public function createModerationStateTransition($from, $to) {
    if ($from != $to) {
      $transition = new \stdClass;
      $transition->from_name = $from;
      $transition->to_name = $to;
      return workbench_moderation_transition_save($transition);
    }
  }

  /**
   * Enable Workbench moderation for the specified content type.
   *
   * @param $type
   */
  public function enableWorkbenchModeration($type) {

    $options = variable_get('node_options_' . $type, array());
    foreach (array('moderation', 'revision') as $option) {
      if (!in_array($option, $options)) {
        $options[] = $option;
      }
    }
    variable_set('node_options_' . $type, $options);
  }
} 
