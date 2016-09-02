<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\WebtoolsContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Context for configuring the WebtoolsContext.
 */
class WebtoolsContext implements Context {

  /**
   * The Smarloader Protocol-Relative URL.
   *
   * @var string
   */
  protected $smartloadurl;

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
   * Constructs a new WebtoolsContext.
   *
   * @param string $smartloadurl
   *   The Smarloader Protocol-Relative URL.
   */
  public function __construct($smartloadurl) {
    // @todo continuousphp insert the right $url
    // $this->smartloadUrl = $smartloadurl;
    $this->smartloadUrl = "http://europa.eu/webtools/load.js";
  }

  /**
   * Configures the Smarloader URL for the nexteuropa_webtools module.
   *
   * @Given a valid Smartload Url has been configured
   */
  public function aValidSmartloadUrlHasBeenConfigured() {
    $this->variableContext->setVariable('nexteuropa_webtools_smartloader_prurl', $this->$smartloadurl);
  }

  /**
   * Create a Webtools blocks.
   *
   * @param string $name
   *   Name of the block webtools.
   *
   * @Given a webtools :name exists
   *
   * @Then I create a new webtools :name
   */
  public function aWebtoolsExists($name) {
    $bean = bean_create(array('type' => 'webtools'));
    $bean->label = $name;
    $bean->title = $name . ' Title';
    $bean->field_custom_js_link = "link";
    $bean->field_json_object = array(
      'LANGUAGE_NONE' => array(array(
        'value' => 'json',
        'format' => 'text_plain',
      ),
      ),
    );

    $bean->save();
  }

}
