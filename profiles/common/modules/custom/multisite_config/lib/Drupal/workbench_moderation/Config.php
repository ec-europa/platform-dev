<?php

/**
 * @file
 * Contains \\Drupal\\workbench_moderation\\Config.
 */

namespace Drupal\workbench_moderation;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\workbench_moderation
 */
class Config extends ConfigBase {

  /**
   * Create a new or existing moderation state.
   *
   * Moderation state names must be unique, so saving a state object with a
   * non-unique name updates the existing state.
   *
   * @param string $name
   *   State name.
   * @param string $label
   *   State label.
   * @param string $description
   *   State description.
   * @param int $weight
   *   State weight.
   *
   * @return mixed
   *   Created state object.
   */
  public function createModerationState($name, $label, $description = NULL, $weight = 0) {
    $state = new \stdClass();
    $state->name = $name;
    $state->label = $label;
    $state->description = $description;
    $state->weight = $weight;
    return workbench_moderation_state_save($state);
  }

  /**
   * Create a new moderation state transition.
   *
   * @param string $to
   *   Transition state name.
   * @param string $from
   *   Transition state name.
   * @param string $name
   *   Transition name.
   *
   * @return mixed
   *   Saved status.
   */
  public function createModerationStateTransition($to, $from, $name = '') {
    if ($from != $to) {
      $transition = new \stdClass();
      $transition->name = $name;
      $transition->from_name = $from;
      $transition->to_name = $to;
      return workbench_moderation_transition_save($transition);
    }
  }

  /**
   * Enable Workbench moderation for the specified content type.
   *
   * @param string $type
   *   Content type machine name.
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
