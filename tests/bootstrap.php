<?php

/**
 * @file
 * PHPUnit bootstrap file.
 */

use Drupal\Driver\DrupalDriver;

require_once DRUPAL_ROOT . '/vendor/autoload.php';

$driver = new DrupalDriver(DRUPAL_ROOT, BASE_URL);
$driver->setCoreFromVersion();
$driver->bootstrap();
