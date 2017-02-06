<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\ModuleContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\TableNode;

/**
 * Context with module, feature and feature_set management.
 */
class ModuleContext extends RawDrupalContext {

  /**
   * List of modules enabled before the scenario.
   *
   * @var array
   */
  protected $defaultEnabledModules = array();

  /**
   * List of feature sets to enable for Behat scenarios.
   *
   * @var array
   */
  protected $testActivatedFeatureSets = array();

  /**
   * Enables one or more Feature Set(s).
   *
   * Provide feature set names in the following format:
   *
   * | featureSet  |
   * | Events      |
   * | Links       |
   *
   * @param TableNode $featureset_table
   *   The table listing feature set titles.
   *
   * @throws \Exception
   *    Throws exception if the feature_set activation failed.
   *
   * @Given the/these featureSet/FeatureSets is/are enabled
   */
  public function enableFeatureSet(TableNode $featureset_table) {
    $message = array();
    $featuresets = feature_set_get_featuresets();
    foreach ($featureset_table->getHash() as $row) {
      foreach ($featuresets as $featureset_available) {
        if ($featureset_available['title'] == $row['featureSet'] &&
          feature_set_status($featureset_available) === FEATURE_SET_DISABLED) {
          if (feature_set_enable_feature_set($featureset_available)) {
            $this->testActivatedFeatureSets[] = $featureset_available;
          }
          else {
            $message[] = $row['featureSet'];
          }
        }
      }
    }

    if (!empty($message)) {
      throw new \Exception(sprintf('Feature Set "%s" not correctly enabled', implode(', ', $message)));
    }
  }

  /**
   * Disables one or more Feature Set(s).
   *
   * Disable any Feature Set that were enabled during Feature test.
   *
   * @AfterScenario
   */
  public function cleanFeatureSet() {
    if (!empty($this->testActivatedFeatureSets)) {
      // Disable and uninstall any feature set that were enabled.
      foreach ($this->testActivatedFeatureSets as $featureset) {
        if (isset($featureset['disable'])) {
          $featureset['uninstall'] = $featureset['disable'];
          feature_set_disable_feature_set($featureset);
        }
      }
      $this->testActivatedFeatureSets = array();
    }
  }

  /**
   * Enables one or more modules.
   *
   * Provide modules data in the following format:
   *
   * | modules  |
   * | blog     |
   * | book     |
   *
   * @param TableNode $modules_table
   *   The table listing modules.
   *
   * @return bool
   *   Always returns TRUE.
   *
   * @throws \Exception
   *   Thrown when a module does not exist.
   *
   * @Given the/these module/modules is/are enabled
   */
  public function enableModule(TableNode $modules_table) {
    $rebuild = FALSE;
    $message = array();
    foreach ($modules_table->getHash() as $row) {
      if (!module_exists($row['modules'])) {
        if (!module_enable($row)) {
          $message[] = $row['modules'];
        }
        else {
          $rebuild = TRUE;
        }
      }
    }

    if (!empty($message)) {
      throw new \Exception(sprintf('Modules "%s" not found', implode(', ', $message)));
    }
    else {
      if ($rebuild) {
        drupal_flush_all_caches();
      }
      return TRUE;
    }
  }

  /**
   * Remember the list of active modules.
   *
   * @BeforeScenario
   */
  public function rememberCurrentModules() {
    $this->defaultEnabledModules = module_list();
  }

  /**
   * Disabled and uninstall modules.
   *
   * @AfterScenario
   */
  public function cleanModule() {
    $current_enabled_list = module_list();
    $diff_modules_list = array_diff($current_enabled_list, $this->defaultEnabledModules);
    if (!empty($diff_modules_list)) {
      // Disable and uninstall any modules that were enabled.
      $keys = array_keys($diff_modules_list);
      do {
        $key = array_pop($keys);
        $module_to_treat = $diff_modules_list[$key];
        // Why passing by a custom recursive process instead of just using
        // "module_disable" and "drupal_uninstall_modules"?
        // Because of the order of execution of them for each modules;
        // in some cases, the process ends up with some modules that are still
        // enabled while they have to.
        if (
          module_exists($module_to_treat)
          && (drupal_get_installed_schema_version($module_to_treat) != SCHEMA_UNINSTALLED)
        ) {
          $this->uninstallModuleWithDependents($module_to_treat);
        }
        unset($diff_modules_list[$key]);
      } while (!empty($keys));

      $this->defaultEnabledModules = array();
      // Clearing the caches to remove modules related data from them.
      drupal_flush_all_caches();
    }
  }

  /**
   * Uninstall a module by uninstalling first its dependent modules.
   *
   * @param string $module_name
   *   The module to uninstall.
   *
   * @throws \Exception
   *   If the uninstall failed because of problem with a dependency.
   */
  private function uninstallModuleWithDependents($module_name) {
    if (isset($this->defaultEnabledModules[$module_name])) {
      // If the module was already active before the scenario,
      // The process cannot not run longer because something is abnormal in
      // the module dependencies.
      throw new \Exception(
        sprintf(
          'The "%s" Module uninstall failed because of a potential bidirectional dependency problem. ',
          $module_name
        )
      );
    }

    $module_data = system_rebuild_module_data();
    if (isset($module_data[$module_name])) {
      if (module_exists($module_name)) {
        $module_info = $module_data[$module_name];
        // First treating dependent modules that have been activated with this
        // module.
        if (!empty($module_info->required_by)) {
          $dependents = array_keys($module_info->required_by);
          foreach ($dependents as $dependent) {
            $this->uninstallModuleWithDependents($dependent);
          }

        }
        // Then, Disabling the module.
        module_disable(array($module_name));
      }
      // Ensure that it is correctly uninstalled.
      drupal_uninstall_modules(array($module_name));
    }
  }

}
