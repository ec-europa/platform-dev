<?php

/**
 * @file
 * PHPUnit bootstrap file.
 */

require_once DRUPAL_ROOT . '/vendor/autoload.php';

$driver = new \Drupal\Driver\DrupalDriver(DRUPAL_ROOT, BASE_URL);
$driver->setCoreFromVersion();
$driver->bootstrap();
