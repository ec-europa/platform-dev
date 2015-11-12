<?php

/**
 * @file
 * Contains \\Drupal\\system\\Config.
 */

namespace Drupal\system;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\system.
 */
class Config extends ConfigBase {

  /**
   * Get current theme machine name.
   *
   * @return string
   *    Current theme machine name.
   */
  public function getCurrentTheme() {
    global $theme;
    return $theme;
  }

  /**
   * Get current theme info object.
   *
   * @return object
   *    Current theme info object.
   */
  public function getCurrentThemeInfo() {
    global $theme_info;
    return $theme_info;
  }

  /**
   * Set default theme given its machine name.
   *
   * @param string $name
   *    Theme machine name.
   *
   * @return bool
   *    TRUE if theme is found and enabled, FALSE otherwise.
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
   *
   * @param string $name
   *    Theme machine name.
   *
   * @return bool
   *    TRUE if theme is found and enabled, FALSE otherwise.
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
   * @param string $module
   *    Module machine name.
   * @param int $weight
   *    Module weight.
   *
   * @return bool
   *    TRUE if module exists and operation has been performed, FALSE otherwise.
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
   * @param string $name
   *    Variable name.
   * @param mixed $default
   *    Variable default value.
   *
   * @return mixed
   *    Variable value.
   */
  public function getVariable($name, $default = NULL) {
    return variable_get($name, $default);
  }

  /**
   * Set variable.
   *
   * @param string $name
   *    Variable name.
   * @param mixed $value
   *    Variable default value.
   */
  public function setVariable($name, $value = NULL) {
    variable_set($name, $value);
  }

  /**
   * Delete variable.
   *
   * @param string $name
   *    Variable name.
   */
  public function deleteVariable($name) {
    variable_del($name);
  }

}
