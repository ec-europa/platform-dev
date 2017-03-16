<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\ModuleContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Hook\Scope\BeforeFeatureScope;
use Behat\Gherkin\Node\TableNode;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\isEmpty;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Symfony\Component\Process\Exception\ProcessFailedException;
use Symfony\Component\Process\Process;

/**
 * Context with module, feature and feature_set management.
 */
class ModuleContext extends RawDrupalContext {

  /**
   * Drush binary location.
   *
   * @var string
   */
  private $drush;

  /**
   * Database dump location.
   *
   * @var string
   */
  private $dumpLocation;

  /**
   * ModuleContext constructor.
   *
   * @param string $drush
   *   Drush binary location.
   * @param string $dump_location
   *   Database dump location.
   */
  public function __construct($drush, $dump_location) {
    $this->drush = $drush;
    $this->dumpLocation = $dump_location;
  }

  /**
   * Importing the initial database dump.
   *
   * @BeforeFeature
   */
  public static function dropAndImportInitialDatabase(BeforeFeatureScope $scope) {
    /** @var \Behat\Behat\Context\Environment\UninitializedContextEnvironment $env */
    $env = $scope->getEnvironment();
    $contexts = $env->getContextClassesWithArguments();

    // We need to access this directly since the class here is not instantiated.
    $drush = $contexts[ModuleContext::class]['drush'];
    $dump_location = $contexts[ModuleContext::class]['dump_location'];

    $commands = [
      "{$drush} sql-drop -y",
      "{$drush} sqlc < {$dump_location}",
    ];

    foreach ($commands as $command) {
      $process = new Process($command);
      $process->run();
      if (!$process->isSuccessful()) {
        throw new ProcessFailedException($process);
      }
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
