<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\DrushContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Hook\Scope\BeforeFeatureScope;
use Drupal\DrupalExtension\Context\DrushContext as DrupalExtensionDrushContext;
use Symfony\Component\Filesystem\Filesystem;
use Symfony\Component\Process\Exception\ProcessFailedException;
use Symfony\Component\Process\Process;

/**
 * Context for the operations which are drush related.
 *
 * @package Drupal\nexteuropa\Context
 */
class DrushContext extends DrupalExtensionDrushContext {
  /**
   * Context configuration.
   *
   * @var array
   */
  private static $configuration;

  /**
   * Drush binary location.
   *
   * @var string
   */
  private $drushBin;

  /**
   * Database dump location.
   *
   * @var string
   */
  private $dumpLocation;

  /**
   * Start Time Feature.
   *
   * @var mixed
   */
  private static $startFeature;

  /**
   * DrushContext constructor.
   *
   * Existence of the constructor is needed in order to extend a base class.
   *
   * @param string $drush_bin
   *   Drush binary location.
   * @param string $db_dump_location
   *   Database dump location.
   */
  public function __construct($drush_bin, $db_dump_location) {
    $this->drushBin = $drush_bin;
    $this->dumpLocation = $db_dump_location;
  }

  /**
   * Importing the initial database dump.
   *
   * @BeforeFeature
   */
  public static function prepareDatabaseForFeatureTest(BeforeFeatureScope $scope) {
    /** @var \Behat\Behat\Context\Environment\UninitializedContextEnvironment $env */
    $env = $scope->getEnvironment();
    $contexts = $env->getContextClassesWithArguments();

    // We need to access this directly since the class here is not instantiated.
    self::$configuration = $contexts[DrushContext::class];

    if (!self::checkIfDbDumpFileExist()) {
      self::createDbDump();
    }
    else {
      self::dropDataBase();
      self::importDataBase();
    }

    self::$startFeature = microtime(TRUE);
  }

  /**
   * Show performance stats.
   *
   * @AfterFeature
   */
  public static function showStatForFeatureTest() {
    $time_elapsed = microtime(TRUE) - self::$startFeature;
    print ('Feature tests completed in ' . round($time_elapsed, 2) . ' sec.' . PHP_EOL);
  }

  /**
   * Checks if the database dump file exist.
   *
   * @return bool
   *   TRUE/FALSE
   */
  private static function checkIfDbDumpFileExist() {
    $fs = new Filesystem();
    return $fs->exists(self::$configuration['db_dump_location']);
  }

  /**
   * Creates the database dump.
   */
  private static function createDbDump() {
    print('Creating the database dump.' . PHP_EOL);
    $command = "sql-dump --result-file=" . self::$configuration['db_dump_location'];
    self::runStaticDrushCommand($command);
  }

  /**
   * Drops the database.
   */
  private static function dropDataBase() {
    print('Dropping the database dump.' . PHP_EOL);
    $command = "sql-drop -y";
    self::runStaticDrushCommand($command);
  }

  /**
   * Imports database from the dump file.
   */
  private static function importDataBase() {
    print('Importing the database dump.' . PHP_EOL);
    $command = "sqlc < " . self::$configuration['db_dump_location'];
    self::runStaticDrushCommand($command);
  }

  /**
   * Clears all of the Drupal caches.
   */
  private static function clearAllCaches() {
    print('Clearing all caches.' . PHP_EOL);
    $command = "cc all -y";
    self::runStaticDrushCommand($command);
  }

  /**
   * Runs the drush command and measure the elapsed time.
   *
   * @param string $command
   *   String which contains the drush command. Ex. 'sql-drop -y'.
   */
  private static function runStaticDrushCommand($command) {
    $start = microtime(TRUE);
    $drush = self::$configuration['drush_bin'];
    $process = new Process($drush . ' ' . $command);
    $process->run();

    if (!$process->isSuccessful()) {
      throw new ProcessFailedException($process);
    }

    $time_elapsed = microtime(TRUE) - $start;
    print ('Operation done in ' . round($time_elapsed, 2) . ' sec.' . PHP_EOL . PHP_EOL);
  }

}
