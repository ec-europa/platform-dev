<?php

/**
 * @file
 * Contains \Drupal\version_management\Config
 */

namespace Drupal\version_management;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Allow the major version management for a node type.
   *
   * @param  $node_type
   */
  public function enableVersionManagement($node_type = NULL) {
    $version_management_node_types = variable_get('version_management_node_types', array());
    $version_management_node_types[$node_type] = $node_type;
    variable_set('version_management_node_types',$version_management_node_types);
  }
} 
