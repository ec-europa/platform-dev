<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\IntegrationLayerContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Drupal\integration_consumer\ConsumerFactory;
use Drupal\integration_producer\ProducerFactory;
use Drupal\nexteuropa\Component\PyStringYamlParser;
use InterNations\Component\HttpMock\Matcher\ExtractorFactory;
use InterNations\Component\HttpMock\Matcher\MatcherFactory;
use InterNations\Component\HttpMock\MockBuilder;
use InterNations\Component\HttpMock\RequestCollectionFacade;
use InterNations\Component\HttpMock\Server;
use Migration;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;
use function bovigo\assert\predicate\hasKey;
use function bovigo\assert\predicate\isNotNull;
use function bovigo\assert\predicate\isOfSize;
use function bovigo\assert\predicate\isOfType;
use function bovigo\assert\predicate\isNotEmpty;

/**
 * Behat context with functionality related to Integration.
 */
class IntegrationLayerContext implements Context {

  /**
   * The port the mocked central Integration HTTP server should listen on.
   *
   * @var int
   */
  protected $mockServerPort;

  /**
   * Array of configuration entity objects created during test execution.
   *
   * @var \Drupal\integration\Configuration\AbstractConfiguration[]
   */
  protected $configurationEntities = [];

  /**
   * Indicates if the consumer was configured.
   *
   * @var bool
   */
  protected $backendWasConfigured = FALSE;

  /**
   * The mocked central Integration HTTP server.
   *
   * @var Server
   */
  protected $server;

  /**
   * Facade to access requests made to the mocked HTTP server.
   *
   * @var RequestCollectionFacade
   */
  protected $requests;

  /**
   * IntegrationLayerContext constructor.
   *
   * @param int $mock_server_port
   *   The port the mocked central Integration HTTP server should listen on.
   */
  public function __construct($mock_server_port = 8888) {
    $this->mockServerPort = $mock_server_port;
  }

  /**
   * Gets the mocked central Integration HTTP server.
   *
   * Initializes the server if it was not used before.
   * By default it responds to any POST requests with 201 Created response,
   * additional behavior can be added in further steps.
   *
   * @return Server
   *   The mocked central Integration HTTP server.
   */
  protected function getServer() {
    if (!$this->server) {
      $this->server = new Server($this->mockServerPort, 'localhost');

      $this->server->start();

      // Accept any POSTS.
      $mock = new MockBuilder(new MatcherFactory(), new ExtractorFactory());
      $mock
        ->when()
        ->methodIs('POST')
        ->then()
        ->statusCode(201);

      $this->server->setUp($mock->flushExpectations());
    }

    return $this->server;
  }

  /**
   * Gets the requests made to the mocked Integration backend.
   *
   * @return RequestCollectionFacade
   *   The requests facade.
   */
  protected function getRequests() {
    if (!$this->requests) {
      $this->requests = new RequestCollectionFacade($this->server->getClient());
    }

    return $this->requests;
  }

  /**
   * Reverts configuration done by the context.
   *
   * @AfterScenario
   */
  public function revertConfiguration() {
    // Remove configuration entities.
    foreach ($this->configurationEntities as $configuration) {
      if ($configuration->entityType() == 'integration_consumer') {
        /** @var AbstractConsumer $consumer */
        $consumer = ConsumerFactory::getInstance($configuration->getMachineName());
        $consumer->processRollback();

        // Remove consumer & its corresponding migration.
        Migration::deregisterMigration('test_consumer');
      }
      $configuration->delete();
    }

    if ($this->backendWasConfigured) {
      entity_delete('integration_backend', 'http_mock');
    }

    if ($this->server && $this->server->isStarted()) {
      $this->server->stop();
    }
  }

  /**
   * Asserts the language of content received by the central Integration server.
   *
   * @Then the central Integration server received content in the following languages:
   */
  public function assertIntegrationServerReceivedContentWithTheFollowingLanguages(
    TableNode $table
  ) {
    $rows = $table->getHash();
    $expected_languages = array_map(
      function ($row) {
        return $row['language'];
      },
      $rows
    );

    $first_language_in_the_table = reset($expected_languages);

    $request = $this->getRequests()->last();
    $json_body = (string) $request->getBody();
    $document = json_decode($json_body);

    assert($document->default_language, equals($first_language_in_the_table));

    // The list of languages is not necessarily ordered in the same way,
    // so use sort() on both before comparing.
    sort($document->languages);
    sort($expected_languages);
    assert($document->languages, equals($expected_languages));

    assert((array) $document->fields->title, isOfSize(count($expected_languages)));

    foreach ($rows as $translation) {
      assert(
        $document->fields->title->{$translation['language']}[0],
        equals($translation['title'])
      );
    }
  }

  /**
   * Configures an Integration backend for testing purposes.
   *
   * The backend points to our mocked Integration HTTP server.
   */
  private function setupTestBackend() {
    if (!$this->backendWasConfigured) {
      $server = $this->getServer();

      $backend = entity_load_single('integration_backend', 'couchdb');

      $test_backend = clone $backend;
      $test_backend->id = NULL;
      $test_backend->authentication = 'no_authentication';
      $test_backend->machine_name = 'http_mock';
      $test_backend->name = 'HTTP Mock';
      $test_backend->settings['plugin']['backend']['base_url'] = $server->getBaseUrl();

      entity_save('integration_backend', $test_backend);

      $this->backendWasConfigured = TRUE;

      if (!$server->isStarted()) {
        $server->start();
      }
    }
  }

  /**
   * Sets up specific responses for 'news' on the mocked Integration server.
   *
   * @When the central Integration server publishes the following news with id :arg1:
   */
  public function theIntegrationServerBackendPublishesTheFollowingNews(
    $arg1,
    TableNode $table
  ) {
    $data = $table->getHash();
    $translations = [];
    foreach ($data as $row) {
      $translations[$row['language']] = [
        'title' => $row['title'],
        'body' => $row['body'],
      ];
    }
    $languages = array_keys($translations);
    $default_language = reset($languages);

    $date = new \DateTime('now', new \DateTimeZone('UTC'));
    $news = [
      '_id' => $arg1,
      'created' => $date->format('Y-m-d H:i:s'),
      'updated' => $date->format('Y-m-d H:i:s'),
      'languages' => $languages,
      'default_language' => $default_language,
      'fields' => [
        'title' => [],
        'body' => [],
      ],
    ];

    foreach ($translations as $language => $translation) {
      $news['fields']['title'][$language] = [$translation['title']];
      $news['fields']['body'][$language] = [$translation['body']];
    }

    $list = json_encode(['rows' => [['id' => $arg1]]]);

    $mock = new MockBuilder(new MatcherFactory(), new ExtractorFactory());
    $mock
      ->when()
      ->pathIs('/docs/types/news')
      ->methodIs('GET')
      ->then()
      ->statusCode(200)
      ->body($list);

    $mock
      ->when()
      ->methodIs('GET')
      ->pathIs('/docs/types/news/' . $arg1)
      ->then()
      ->statusCode(200)
      ->body(json_encode($news));

    $this->getServer()->setUp($mock->flushExpectations());
  }

  /**
   * Asserts that the Integration consumer imported a specific item.
   *
   * @Then the Integration consumer imported the item with id :arg1 as the following page:
   */
  public function assertIntegrationConsumerImportedTheFollowingPage(
    $arg1,
    TableNode $table
  ) {
    $consumer = ConsumerFactory::getInstance('test_consumer');

    $map = $consumer->getMap();
    $row = $map->getRowBySource([$arg1]);

    assert($row, hasKey('destid1'));
    $nid = $row['destid1'];
    assert($nid, isNotNull());

    $node = node_load($nid);

    $expected_translations = $table->getHash();
    assert($node->translations->data, isOfSize(2));

    foreach ($expected_translations as $expected_translation) {
      assert(
        $node->translations->data,
        hasKey($expected_translation['language'])
      );

      assert(
        $node->title_field[$expected_translation['language']][0]['value'],
        equals($expected_translation['title'])
      );

      assert(
        $node->field_ne_body[$expected_translation['language']][0]['value'],
        equals($expected_translation['body'])
      );
    }
  }

  /**
   * Create Integration Layer producer stating its configuration as shown below.
   *
   * And the following Integration Layer node producer is created:
   *   """
   *     name: test_news
   *     bundle: page
   *     resource: news
   *     mapping:
   *       title_field: title
   *       field_ne_body: body
   *   """
   *
   * @param \Behat\Gherkin\Node\PyStringNode $node
   *    PyString containing configuration in YAML format.
   *
   * @Given the following Integration Layer node producer is created:
   */
  public function createIntegrationLayerProducer(PyStringNode $node) {
    $this->setupTestBackend();
    $parser = new PyStringYamlParser($node);
    $configuration = $parser->parse();
    $this->assertValidConfiguration($configuration);

    /** @var \Drupal\integration_producer\AbstractProducer $producer */
    $producer = ProducerFactory::create($configuration['name'])
      ->setEntityBundle($configuration['bundle'])
      ->setResourceSchema($configuration['resource']);
    foreach ($configuration['mapping'] as $source => $destination) {
      $producer->setMapping($source, $destination);
    }
    $producer->getConfiguration()->save();
    $this->configurationEntities[] = $producer->getConfiguration();
  }

  /**
   * Create Integration Layer consumer stating its configuration as shown below.
   *
   * And the following Integration Layer node consumer is created:
   *   """
   *     name: test_news
   *     backend: http_mock
   *     bundle: page
   *     resource: news
   *     mapping:
   *       title: title_field
   *       body: field_ne_body
   *   """
   *
   * @param \Behat\Gherkin\Node\PyStringNode $node
   *    PyString containing configuration in YAML format.
   *
   * @Given the following Integration Layer node consumer is created:
   */
  public function createIntegrationLayerConsumer(PyStringNode $node) {
    $this->setupTestBackend();
    $parser = new PyStringYamlParser($node);
    $configuration = $parser->parse();
    $this->assertValidConfiguration($configuration);
    assert($configuration, hasKey('backend'));

    /** @var \Drupal\integration_consumer\AbstractConsumer $consumer */
    $consumer = ConsumerFactory::create($configuration['name'], $configuration['backend'])
      ->setEntityBundle($configuration['bundle'])
      ->setResourceSchema($configuration['resource']);
    foreach ($configuration['mapping'] as $source => $destination) {
      $consumer->setMapping($source, $destination);
    }
    $consumer->getConfiguration()->save();
    $this->configurationEntities[] = $consumer->getConfiguration();
  }

  /**
   * Assert that configuration array is actually valid.
   *
   * @param array $configuration
   *    Configuration array.
   */
  protected function assertValidConfiguration(array $configuration) {
    assert($configuration, hasKey('name'));
    assert($configuration, hasKey('bundle'));
    assert($configuration, hasKey('resource'));
    assert($configuration, hasKey('mapping'));
    assert($configuration['mapping'], isOfType('array'));
    assert($configuration['mapping'], isNotEmpty());
  }

}
