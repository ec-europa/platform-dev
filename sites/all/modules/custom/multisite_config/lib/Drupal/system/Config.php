<?php

/**
 * @file
 * Contains \Drupal\system\Config
 */

namespace Drupal\system;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Get current theme machine name.
   *
   * @global type $theme
   * @return type
   */
  public function getCurrentTheme() {
    global $theme;
    return $theme;
  }

  /**
   * Get current theme info object.
   *
   * @global type $theme_info
   * @return type
   */
  public function getCurrentThemeInfo() {
    global $theme_info;
    return $theme_info;
  }

  /**
   * Set default theme given its machine name.
   * Returns FALSE if theme is not found, TRUE otherwise.
   *
   * @param string $name
   *    Theme machine name.
   * @return boolean
   */
  public function setDefaultTheme($name) {

    $themes = list_themes(TRUE);
    if (isset($themes[$name])) {
      theme_enable(array($name));
      variable_set('theme_default', $name);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }


  /**
   * Set admin theme given its machine name.
   * Returns FALSE if theme is not found, TRUE otherwise.
   *
   * @param string $name
   *    Theme machine name.
   * @return boolean
   */
  public function setAdminTheme($name) {

    $themes = list_themes(TRUE);
    if (isset($themes[$name])) {
      theme_enable(array($name));
      variable_set('admin_theme', $name);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Set a module's weight.
   *
   * @param type $module
   * @param type $weight
   * @return boolean
   */
  public function setModuleWeight($module, $weight = 0) {

    if (module_exists($module)) {
      return db_update('system')
        ->fields(array('weight' => $weight))
        ->condition('name', $module)
        ->condition('type', 'module')
        ->execute();
    }
    else {
      return FALSE;
    }
  }

  /**
   * Get variable.
   *
   * @param type $name
   * @param type $default
   * @return type
   */
  public function getVariable($name, $default = NULL) {
    return variable_get($name, $default);
  }

  /**
   * Set variable.
   *
   * @param type $name
   * @param type $value
   * @return type
   */
  public function setVariable($name, $value = NULL) {
    return variable_set($name, $value);
  }

  /**
   * Delete variable.
   *
   * @param type $name
   * @return type
   */
  public function deleteVariable($name) {
    return variable_del($name);
  }
}
