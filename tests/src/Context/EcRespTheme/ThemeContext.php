<?php
/**
 * @file
 * Contains Drupal\nexteuropa\Context\EuropaTheme\ThemeContext.
 */

namespace Drupal\nexteuropa\Context\EcRespTheme;

use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Context with theme specific to Europa theme.
 */
class ThemeContext extends RawDrupalContext {

   /**
    * Ensure that europa theme is actually used.
    *
    * It is a "BeforeScenario" instead of a "BeforeFeature" or a "BeforeSuite"
    * because the variable setting is not taken into account at these levels.
    *
    * @BeforeScenario
    */
  public function enableEuropaTheme() {
    echo 'EC_RESP';
     $theme = variable_get('theme_default', '');

     if ($theme != 'ec_resp') {
       echo 'FORCE EC_RESP';
       // This set variable is not tracked through VariableContext process
       // because it must not be reset after each scenario of the feature.
       variable_set('theme_default', 'ec_resp');
       drupal_flush_all_caches();
     }
  }
}