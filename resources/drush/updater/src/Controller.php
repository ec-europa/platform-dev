<?php

namespace Drush\updater;

use function Stringy\create as S;

/**
 * Updater controller.
 */
class Controller {

  /**
   * Executes available updaters.
   *
   * @param string $path
   *   The path to look for updaters.
   * @param array $args
   *   The command line arguments.
   * @param bool $testing
   *   If TRUE, $updaters will not be set as executed.
   *
   * @return array
   *   An array of executed functions returned results.
   */
  public static function executeUpdaters($path, $args, $testing = FALSE) {
    $return = array();
    $path = self::getUpdatersRealPath($path);
    $updaters = self::getUpdaters($path);
    foreach ($updaters as $updater) {
      include_once $updater;
      $function = str_replace('-', '_', str_replace('.php', '', basename($updater))) . '_update';
      if (function_exists($function) && !self::isUpdaterExecuted($function)) {
        drush_log(dt('Executing @function', array('@function' => $function)), 'info');
        $result = call_user_func_array($function, $args);
        if (!$testing && $result !== FALSE) {
          self::setUpdaterExecuted($function);
        }
        else {
          drush_log(dt('Function @function not set as executed.',
            array('@function' => $function)), 'warning');
        }
        $return[] = $result;
      }
    }
    return $return;
  }

  /**
   * Returns available updaters.
   *
   * @param string $path
   *   The path to look for updaters.
   *
   * @return array
   *   An array of available updaters.
   */
  public static function getUpdaters($path) {
    $path = self::getUpdatersRealPath($path);
    if (self::isValidUpdater($path)) {
      return array($path);
    }
    $updaters = array_diff(scandir($path), array('..', '.'));
    $updaters = array_filter($updaters, function ($item) use ($path) {
      return !is_dir($path . $item) && S($item)->startsWith('updater-')
        && S($item)->endsWith('.php');
    });
    return array_map(function ($item) use ($path) {
      return $path . $item;
    }, $updaters);
  }

  /**
   * Checks whether the specified path is a valid updater path.
   *
   * @param string $path
   *   The path to check.
   *
   * @return bool
   *   Returns TRUE if the path is a valid updater path, otherwise FALSE.
   */
  public static function isValidUpdater($path) {
    return is_file($path)
      && S(basename($path))->startsWith('updater-')
      && S(basename($path))->endsWith('.php');
  }

  /**
   * Checks if an updater was already executed.
   *
   * @param string $updater
   *   The name of the updater.
   *
   * @return bool
   *   Returns TRUE if the updater was already executed, otherwise FALSE.
   */
  private static function isUpdaterExecuted($updater) {
    $updates = self::getExecutedUpdaters();
    if (is_array($updates) && in_array($updater, $updates)) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Sets updater execution status.
   *
   * @param string $updater
   *   The name of the updater.
   */
  private static function setUpdaterExecuted($updater) {
    $updates = self::getExecutedUpdaters();
    if (is_array($updates)) {
      $updates[] = $updater;
    }
    else {
      $updates = array($updater);
    }
    self::setExecutedUpdaters($updates);
  }

  /**
   * Returns updaters real path.
   *
   * @param string $path
   *   The path received as command line argument.
   *
   * @return string
   *   The updaters real path.
   */
  private static function getUpdatersRealPath($path) {
    if (!S($path)->startsWith('/')) {
      $path = realpath(DRUPAL_ROOT . '/' . $path);
    }
    if (!file_exists($path)) {
      return drush_set_error('INVALID_PATH', dt('Invalid updaters path.'));
    }
    if (!is_file($path) && !S($path)->endsWith('/')) {
      $path .= '/';
    }
    return $path;
  }

  /**
   * Returns the updaters already executed.
   *
   * @return array
   *   An array of executed updaters.
   */
  private static function getExecutedUpdaters() {
    if (drush_drupal_major_version() < 8) {
      return variable_get('updater_executed_updaters');
    }
    else {
      return \Drupal::state()->get('updater_executed_updaters');
    }
  }

  /**
   * Stores the array of executed updaters.
   *
   * @param array $updaters
   *   The array of executed updaters.
   */
  private static function setExecutedUpdaters($updaters) {
    if (drush_drupal_major_version() < 8) {
      variable_set('updater_executed_updaters', $updaters);
    }
    else {
      \Drupal::state()->set('updater_executed_updaters', $updaters);
    }
  }

}
