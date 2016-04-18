<?php

/**
 * @file
 * PHPUnit bootstrap file.
 */

require_once './vendor/autoload.php';
// Directory change necessary since Drupal often uses relative paths.
chdir(DRUPAL_ROOT);
require_once 'includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
