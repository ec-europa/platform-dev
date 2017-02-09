<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\ModuleContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\TableNode;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\isTrue;
use function bovigo\assert\predicate\isEmpty;

/**
 * Context with module, feature and feature_set management.
 */
class ModuleContext extends RawDrupalContext {

  /**
   * Initial module list to restore at the end of the test.
   *
   * @var array
   */
  protected $initialModuleList = array();

  /**
   * Enables one or more modules.
   *
   * Provide modules data in the following format:
   *
   * | modules |
   * | blog    |
   * | book    |
   *
   * @param TableNode $modules_table
   *   The table listing modules.
   *
   * @throws \Exception
   *   Thrown when a module does not exist.
   *
   * @Given the/these module/modules is/are enabled
   */
  public function enableModule(TableNode $modules_table) {
    $this->initialModuleList = module_list(TRUE);
    foreach ($modules_table->getHash() as $row) {
      module_enable([$row['modules']]);
    }
    drupal_flush_all_caches();
  }

  /**
   * Restores the initial values of the Drupal variables.
   *
   * @AfterScenario
   */
  public function restoreInitialState() {
    if (!empty($this->initialModuleList)) {
      $list_after = module_list(TRUE);
      $lists_diff = array_values(
        array_merge(
          array_diff($this->initialModuleList, $list_after),
          array_diff($list_after, $this->initialModuleList)
        )
      );
      if (!empty($lists_diff)) {
        module_disable($lists_diff);
        drupal_flush_all_caches();
        module_list(TRUE);
        foreach ($lists_diff as $module) {
          assert(module_exists($module), isTrue(), "Module {$module} could not be uninstalled.");
        }
      }
      $this->initialModuleList = array();
    }
  }

  /**
   * Enables one or more Feature Set(s).
   *
   * Provide feature set names in the following format:
   *
   * | featureSet |
   * | Events     |
   * | Links      |
   *
   * @param TableNode $table
   *   The table listing feature set titles.
   *
   * @return bool
   *   It always returns true; otherwise it throws an exception.
   *
   * @throws \Exception
   *   It is thrown if one of the modules of the feature set is not enabled.
   *
   * @Given the/these featureSet/FeatureSets is/are enabled
   */
  public function enableFeatureSet(TableNode $table) {
    $cache_flushing = FALSE;
    $message = array();
    $sets = feature_set_get_featuresets();
    foreach ($table->getHash() as $row) {
      foreach ($sets as $set) {
        if ($set['title'] == $row['featureSet'] && feature_set_status($set) === FEATURE_SET_DISABLED) {
          if (feature_set_enable_feature_set($set)) {
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
      drupal_flush_all_caches();
    }

    return TRUE;
  }

}
