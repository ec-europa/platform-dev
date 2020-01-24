<?php

namespace Drupal\nexteuropa_core\Tests;

use Drupal\nexteuropa\Unit\AbstractUnitTest;
use function bovigo\assert\assertThat;
use function bovigo\assert\predicate\hasKey;

/**
 * Class HookAlterTest.
 *
 * @package Drupal\nexteuropa_core\Tests
 */
class HookAlterTest extends AbstractUnitTest {

  /**
   * Test nexteuropa_core_token_info_alter().
   */
  public function testTokenInfoAlterSmoke() {
    $data = [];
    nexteuropa_core_token_info_alter($data);
    assertThat($data, hasKey('tokens'));
    assertThat($data['tokens'], hasKey('term'));
    assertThat($data['tokens']['term'], hasKey('parents-uri'));
  }

}
