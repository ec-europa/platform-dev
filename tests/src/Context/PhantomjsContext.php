<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MinkContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Testwork\Hook\Scope\BeforeSuiteScope;
use PhantomInstaller\PhantomBinary;
use Symfony\Component\Process\Process;

/**
 * Start PhantomJS before the tests run.
 *
 * Don't try to stop the process or you will get an exception:
 *   [Behat\Mink\Exception\DriverException]
 *   Could not close connection
 * Just let it go, Symfony\Component\Process\Process will stop it anyway.
 */
class PhantomjsContext implements Context {

  private static $process;

  /**
   * Start PhantomJS.
   *
   * @BeforeSuite
   */
  public static function startPhantomjs(BeforeSuiteScope $scope) {
    $cmd = sprintf('exec %s --webdriver=%d', PhantomBinary::BIN, 8643);
    self::$process = new Process($cmd);
    self::$process->start();

    // Wait 1 sec to let PhantomJS start.
    sleep(1);
  }

}
