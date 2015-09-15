<?php

/**
 * @file
 * Contains \WebtoolsSubContext.
 */

use Drupal\DrupalExtension\Context\DrupalSubContextBase;

/**
 * Step definitions for the European Commission Super Search module.
 */
class WebtoolsSubContext extends DrupalSubContextBase {

  /**
   * BeforeFeature webtools.
   *
   * @BeforeFeature @webtools
   */
  public static function beforeFeature($scope) {

    if (!module_exists('nexteuropa_webtools')) {
      module_enable(array('nexteuropa_webtools'));
    }

    // Grant permission 'view bean page' for tests:
    // it's less difficult to check the webtools page that the block.
    multisite_config_service('user')->grantPermission('anonymous user', array('view bean page'));
    multisite_config_service('user')->grantPermission('authenticated user', array('view bean page'));
  }


  /**
   * BeforeScenario webtools_create_default_block.
   *
   * @BeforeScenario @webtools_create_default_block
   */
  public static function beforeScenario($scope) {

    $bean_block = bean_load_delta('webtools_test_protocol');
    if (!$bean_block) {
      $bean_values = array(
        'delta' => 'webtools_test_protocol',
        'label' => 'webtools_test_protocol',
        'title' => 'Webtools Test Protocol',
        'type' => 'webtools',
      // Bean type.
        'view_mode' => 'default',
        'data' => array('view_mode' => 'default'),
        'region' => array('ec_resp' => 'sidebar_left'),
        'field_json_object' => array(
          'und' => array(
            '0' => array('value' => '{"service":"charts","data":{"type": "column3d","dataFormat": "json","dataSource": {"data": [{"label": "foo","value": "420000"},{"label": "bar","value": "810000"},{"label": "baz","value": "720000"}]}}}'),
          ),
        ),
      );
      $bean_block = bean_create($bean_values);
      $bean_block->save();
    }
  }

}
