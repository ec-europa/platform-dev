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
   * Remember the list of enabled module before executing a scenario.
   *
   * @BeforeScenario
   */
  public function rememberDefaultEnabledModules() {
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
    $this->defaultEnabledModules = module_list(TRUE);
  }

  /**
   * Disabled and uninstall modules.
   *
   * @AfterScenario
   */
  public function cleanModule() {
    $after_scenario_modules = module_list(TRUE);

    $modules_diff = array_diff($after_scenario_modules, $this->defaultEnabledModules);

    if ($modules_diff) {
      module_disable($modules_diff);
      drupal_uninstall_modules($modules_diff);
      drupal_flush_all_caches();
    }

    $this->defaultEnabledModules = array();
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
   *   It always returns TRUE; otherwise it throws an exceptions.
   *
   * @throws \Exception
   *   Thrown when a module does not exist.
   *
   * @Given the/these module/modules is/are enabled
   */
  public function enableModule(TableNode $modules_table) {
    $cache_flushing = FALSE;
    $message = array();
    foreach ($modules_table->getHash() as $row) {
      if (!module_exists($row['modules'])) {
        if (!module_enable($row)) {
          $message[] = $row['modules'];
        }
        else {
          $cache_flushing = TRUE;
        }
      }
    }

    if (!empty($message)) {
      throw new \Exception(sprintf('Modules "%s" not found', implode(', ', $message)));
    }

    if ($cache_flushing) {
      drupal_flush_all_caches();
    }

    return TRUE;

  }

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
   * @return bool
   *   It always returns TRUE; otherwise it throws an exceptions.
   *
   * @throws \Exception
   *   It is thrown if one of the modules of the featureset is not enabled.
   *
   * @Given the/these featureSet/FeatureSets is/are enabled
   */
  public function enableFeatureSet(TableNode $featureset_table) {
    $cache_flushing = FALSE;
    $message = array();
    $featuresets = feature_set_get_featuresets();
    foreach ($featureset_table->getHash() as $row) {
      foreach ($featuresets as $featureset_available) {
        if ($featureset_available['title'] == $row['featureSet'] &&
          feature_set_status($featureset_available) === FEATURE_SET_DISABLED
        ) {
          if (feature_set_enable_feature_set($featureset_available)) {
            $cache_flushing = TRUE;
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

    if ($cache_flushing) {
      drupal_flush_all_caches();
    }

    return TRUE;
  }

}
