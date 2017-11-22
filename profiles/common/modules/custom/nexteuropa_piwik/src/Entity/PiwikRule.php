<?php

/**
 * @file
 * Definition of Drupal\nexteuropa_piwik\Entity\PiwikRule.
 */

namespace Drupal\nexteuropa_piwik\Entity;

use \Entity;

/**
 * PIWIK rule entity.
 */
class PiwikRule extends Entity {
  const DIRECT_PATH = 'direct';
  const REGEXP_PATH = 'regexp';

}
