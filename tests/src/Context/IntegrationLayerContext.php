<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\IntegrationLayerContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Gherkin\Node\TableNode;
use InterNations\Component\HttpMock\Matcher\ExtractorFactory;
use InterNations\Component\HttpMock\Matcher\MatcherFactory;
use InterNations\Component\HttpMock\MockBuilder;
use InterNations\Component\HttpMock\RequestCollectionFacade;
use InterNations\Component\HttpMock\Server;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;

/**
 * Behat context with functionality related to the Integration Layer.
 */
class IntegrationLayerContext implements Context {

  /**
   * Indicates if the producer was configured.
   *
   * @var bool
   */
  protected $producerWasConfigured = FALSE;

  /**
   * The mocked integration layer server.
   *
   * @var Server
   */
  protected $server;

  /**
   * Facade to access requests made to the mocked server.
   *
   * @var RequestCollectionFacade
   */
  protected $requests;

  /**
   * Configures an integration layer producer.
   *
   * @Given the integration layer producer is configured
   */
  public function theIntegrationLayerProducerIsConfigured() {
    $backend = entity_load_single('integration_backend', 'couchdb');

    $this->producerWasConfigured = TRUE;
    $this->revertConfiguration();

    $test_backend = clone $backend;
    $test_backend->id = NULL;
    $test_backend->authentication = 'no_authentication';
    $test_backend->machine_name = 'http-mock';
    $test_backend->name = 'HTTP Mock';
    $test_backend->settings['plugin']['backend']['base_url'] = 'http://localhost:8888';

    entity_save('integration_backend', $test_backend);

    $producer = entity_import('integration_producer', '{
      "entity_bundle" : "page",
      "backend" : "http-mock",
      "resource" : "news",
      "settings" : { "plugin" : { "mapping" : { "title_field" : "title", "field_ne_body" : "body" } } },
      "name" : "test",
      "machine_name" : "test-news",
      "plugin" : "node_producer",
      "enabled" : "1",
      "description" : null,
      "rdf_mapping" : []
    }');
    $saved = entity_save('integration_producer', $producer);

    $this->server = new Server('8888', 'localhost');

    $mock = new MockBuilder(new MatcherFactory(), new ExtractorFactory('/'));
    $mock
      ->when()
        ->methodIs('POST')
      ->then()
        ->statusCode(201);

    $this->server->start();

    $this->server->setUp($mock->flushExpectations());

    $this->requests = new RequestCollectionFacade($this->server->getClient());

    $this->producerWasConfigured = TRUE;
  }

  /**
   * Reverts configuration done by the context.
   *
   * @AfterScenario
   */
  public function revertConfiguration() {
    if ($this->producerWasConfigured) {
      entity_delete('integration_backend', 'http-mock');

      entity_delete('integration_producer', 'test-news');
    }

    if ($this->server) {
      $this->server->stop();
    }
  }

  /**
   * Asserts that the integration layer received content in certain languages.
   *
   * @Then the integration layer received content in the following languages:
   */
  public function assertIntegrationLayerReceivedContentWithTheFollowingLanguages(TableNode $table) {
    $rows = $table->getHash();
    $expected_languages = array_map(
      function ($row) {
        return $row['language'];
      },
      $rows
    );

    $request = $this->requests->last();
    $json_body = (string) $request->getBody();
    $document = json_decode($json_body);

    assert($document->languages, equals($expected_languages));
  }

}
