<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\ModuleContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\TableNode;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\isEmpty;

/**
 * Context with module, feature and feature_set management.
 */
class ModuleContext extends RawDrupalContext {

  /**
   * List of modules enabled before the scenario.
   *
   * @var array
   */
  protected $initialModuleList  = array();


  /**
   * Remember the list of enabled module before executing a scenario.
   *
   * @BeforeScenario
   */
  public function rememberDefaultEnabledModules() {
    $this->initialModuleList  = module_list(TRUE);
  }

  /**
   * Disabled and uninstall modules.
   *
   * @AfterScenario
   */
  public function restoreInitialState() {
    $after_scenario_modules = module_list(TRUE);

    $lists_diff = array_diff($after_scenario_modules, $this->initialModuleList);

    if ($lists_diff) {
      module_disable($lists_diff, FALSE);
      drupal_uninstall_modules($lists_diff);
      drupal_flush_all_caches();
      // Check if modules are really uninstalled.
      module_list(TRUE);
      foreach ($lists_diff as $module) {
        if (module_exists($module)) {
          throw new \Exception(sprintf('Module "%s" could not be uninstalled', implode(', ', $module)));

        }
      }
    }
    $this->initialModuleList  = array();
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

    assert($message, isEmpty(), sprintf('Module "%s" not correctly enabled', implode(', ', $message)));

    if ($cache_flushing) {
      drupal_flush_all_caches();
    }
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

    assert($message, isEmpty(), sprintf('Feature Set "%s" not correctly enabled', implode(', ', $message)));

    if ($cache_flushing) {
      // Necessary for rebuilding the menu after enabling some specific
      // features.
      drupal_flush_all_caches();
    }
  }

}
