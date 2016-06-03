<?php

/**
 * @file
 * Contains \NextEuropaIntegrationSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\TableNode;
use Drupal\integration\ResourceSchema\ResourceSchemaFactory;
use Drupal\integration\Backend\BackendFactory;
use Drupal\integration_producer\ProducerFactory;

/**
 * Behat step definitions for the NextEuropa Multilingual module.
 */
class NextEuropaIntegrationSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * {@inheritdoc}
   */
  protected $drupal;

  /**
   * Constructs a NextEuropaIntegrationSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Create resource schema.
   *
   * @param string $name
   *    Configuration object name.
   * @param \Behat\Gherkin\Node\TableNode $table
   *    Configuration object properties.
   *
   * @Given a :name resource schema:
   */
  public function assertResourceSchema($name, TableNode $table) {
    $resource_schema = ResourceSchemaFactory::create($name);
    $mapping = $table->getRowsHash();
    foreach ($mapping as $name => $label) {
      $resource_schema->setField($name, $label);
    }
  }

  /**
   * Create backend.
   *
   * @param string $name
   *    Configuration object name.
   * @param \Behat\Gherkin\Node\TableNode $table
   *    Configuration object properties.
   *
   * @Given a :name backend:
   */
  public function assertBackend($name, TableNode $table) {
    $settings = $table->getRowsHash();
    if (!isset($settings['plugin'])) {
      throw new \InvalidArgumentException("Plugin type must be specified.");
    }
    if (!isset($settings['resource_schema'])) {
      throw new \InvalidArgumentException("Resource schema must be specified.");
    }
    $backend = BackendFactory::create($name, $settings['plugin']);
    $backend->setResourceSchema($settings['resource_schema']);
  }

  /**
   * Create producer.
   *
   * @param string $name
   *    Configuration object name.
   * @param \Behat\Gherkin\Node\TableNode $table
   *    Configuration object properties.
   *
   * @Given a :producer producer:
   */
  public function assertProducer($name, TableNode $table) {
    $settings = $table->getRowsHash();
    if (!isset($settings['plugin'])) {
      throw new \InvalidArgumentException("Plugin type must be specified.");
    }
    if (!isset($settings['backend'])) {
      throw new \InvalidArgumentException("Backend must be specified.");
    }
    if (!isset($settings['bundle'])) {
      throw new \InvalidArgumentException("Bundle must be specified.");
    }
    if (!isset($settings['resource_schema'])) {
      throw new \InvalidArgumentException("Resource schema must be specified.");
    }
    $producer = ProducerFactory::create($name, $settings['plugin']);
    $producer->setBackend($settings['backend']);
    $producer->setEntityBundle($settings['bundle']);
    $producer->setResourceSchema($settings['resource_schema']);
  }

  /**
   * Add mapping to producer.
   *
   * @param string $name
   *    Configuration object name.
   * @param \Behat\Gherkin\Node\TableNode $table
   *    Configuration object properties.
   *
   * @Given the following mapping for the :name producer:
   */
  public function addMappingToProducer($name, TableNode $table) {
    $producer = ProducerFactory::getInstance($name);
    $mapping = $table->getRowsHash();
    foreach ($mapping as $source => $destination) {
      $producer->setMapping($source, $destination);
    }
  }

  /**
   * Produce document and assert properties.
   *
   * @param string $name
   *    Configuration object name.
   * @param string $type
   *    Node type.
   * @param string $title
   *    Node title.
   * @param \Behat\Gherkin\Node\TableNode $table
   *    Document properties.
   *
   * @Then a document build by the :name producer for :type content with title :title should have:
   */
  public function assertDocument($name, $type, $title, TableNode $table) {
    $producer = ProducerFactory::getInstance($name);
    $node = $this->getNodeByTitle($type, $title);
    $document = $producer->build($node);

    // @todo: implement assertions.
  }

  /**
   * Get a node by specifying its type and title.
   *
   * @param string $type
   *    The node type.
   * @param string $title
   *    The node title.
   *
   * @return object
   *    The node object.
   */
  protected function getNodeByTitle($type, $title) {
    $nodes = node_load_multiple([], ['title' => $title, 'type' => $type], TRUE);
    if ($nodes) {
      return array_shift($nodes);
    }
    throw new \InvalidArgumentException("Node of type '{$type}' and title '{$title}' not found.");
  }

}
