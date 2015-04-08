<?php

require_once './vendor/autoload.php';
chdir(DRUPAL_ROOT); // Necessary since Drupal often uses relative paths.
require_once 'includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
