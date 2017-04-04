<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_core\Tests\EntityTest.
 */

namespace Drupal\nexteuropa_core\Tests;

use Drupal\nexteuropa\Unit\AbstractUnitTest;

/**
 * Class EntityTest.
 *
 * @package Drupal\nexteuropa_core\Tests
 */
class EntityTest extends AbstractUnitTest {

  /**
   * Test Entities.
   *
   * Test existence of entity_type property,
   * which when missing should be injected.
   */
  public function testEntityType() {
    $node = new \stdClass();
    $node->type = 'article';
    $node->title = 'Test';
    node_save($node);

    $node_loaded = node_load($node->nid);

    $this->assertEquals($node_loaded->entity_type, 'node');
  }

}
