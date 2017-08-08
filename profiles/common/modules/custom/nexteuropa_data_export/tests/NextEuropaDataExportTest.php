<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_data_export\Tests\NextEuropaDataExportTest.
 */

namespace Drupal\nexteuropa_data_export\Tests;

/**
 * Class NextEuropaDataExportTest.
 *
 * @package Drupal\nexteuropa_data_export\Tests
 */
class NextEuropaDataExportTest extends NextEuropaDataExportAbstractTest {

  private $nodes = array();

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    for ($i = 0; $i < 5; $i++) {
      $node = new \stdClass();
      $node->type = 'test_export';
      $node->title = 'title-' . $i;
      $node->field_test_export_text_field = array('text-field-' . $i);
      $this->nodes[] = $this->driver->createNode($node);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function tearDown() {
    parent::tearDown();
    foreach ($this->nodes as $node) {
      node_delete($node->nid);
    }
  }

  /**
   * Test that VBO data export produces a TXT file from the selected rows.
   */
  public function testTxtDataExport() {

    foreach (array('test-export/download', 'test-export') as $path) {

      // Visit VBO page.
      $this->visit($path);

      // Select data export bulk operation.
      $this->page()->selectFieldOption('edit-operation', 'action::nexteuropa_data_export_export_action');

      // Select first three nodes.
      $this->page()->checkField('edit-views-bulk-operations-0');
      $this->page()->checkField('edit-views-bulk-operations-1');
      $this->page()->checkField('edit-views-bulk-operations-2');

      // Press VBO execute button.
      $this->page()->pressButton('edit-submit--2');

      // Be sure we are redirected on the field choosing page.
      $this->assertTrue($this->page()->hasContent('Choose fields to export'));
      $this->assertTrue($this->page()->hasSelect('edit-fields'));

      // Only export title and text field.
      $this->page()->selectFieldOption('edit-fields', 'title');
      $this->page()->selectFieldOption('edit-fields', 'field_test_export_text_field', TRUE);

      // Run export.
      $this->page()->pressButton('edit-submit');

      // Get export content.
      $content = $this->page()->getContent();

      // Make sure only the selected fields are exported.
      $this->assertContains('[Title]', $content);
      $this->assertContains('[Text field]', $content);
      $this->assertNotContains('[Content]', $content);

      // Only first three nodes should be exported.
      foreach (array(0, 1, 2) as $i) {
        $this->assertContains('title-' . $i, $content);
        $this->assertContains('text-field-' . $i, $content);
      }

      // Last two nodes should not be exported.
      foreach (array(3, 4) as $i) {
        $this->assertNotContains('title-' . $i, $content);
        $this->assertNotContains('text-field-' . $i, $content);
      }

      // Get result page headers.
      $headers = $this->getSession()->getResponseHeaders();

      if ($path == 'test-export/download') {
        // Check that exported data is served as a file.
        $this->assertEquals($headers['Content-Disposition'][0], 'attachment; filename="test_export.txt"');
      }
      else {
        // Check that exported data is not served as a file.
        $this->assertArrayNotHasKey('Content-Disposition', $headers);
      }
    }
  }

}
