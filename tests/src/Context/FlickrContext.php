<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FlickrContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Context for configuring the Flickr integration.
 */
class FlickrContext implements Context {

  /**
   * The Flickr API key.
   *
   * @var string
   */
  protected $key;

  /**
   * The Flickr API secret.
   *
   * @var string
   */
  protected $secret;

  /**
   * The variable context.
   *
   * @var VariableContext
   */
  protected $variableContext;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->variableContext = $environment->getContext(VariableContext::class);
  }

  /**
   * Constructs a new FlickrContext.
   *
   * @param string $key
   *   The Flickr API key.
   * @param string $secret
   *   The Flickr API secret.
   */
  public function __construct($key, $secret) {
    $this->key = $key;
    $this->secret = $secret;
  }

  /**
   * Configures the Flickr API keys for the media_flickr module.
   *
   * @Given a valid Flickr API key & secret have been configured
   */
  public function aValidFlickrApiKeySecretHaveBeenConfigured() {
    $this->variableContext->setVariable('media_flickr__api_key', $this->key);
    $this->variableContext->setVariable('media_flickr__api_secret', $this->secret);
  }

}
