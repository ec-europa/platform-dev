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
   * List of Bean created during test execution.
   *
   * @var \Bean[]
   */
  protected $beans = [];

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
    $this->variableContext->setVariable('nexteuropa_webtools_smartloader_prurl', $this->smartloadurl);
  }

  /**
   * Create a Webtools blocks.
   *
   * @param string $name
   *   Name of the block webtools.
   *
   * @Given a map webtools :name exists
   *
   * @Then I create a new map webtools :name
   */
  public function aWebtoolsMapExists($name) {
    $values = array(
      'delta' => $name,
      'label' => $name,
      'title' => $name . " Title",
      'type' => 'webtools',
      'view_mode' => 'default',
      'data' => array('view_mode' => 'default'),
      'field_json_object' => array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => '{"service":"map","custom":"//europa.eu/webtools/showcase/demo/map/samples/demo.js"}',
          ),
        ),
      ),
      'field_custom_js_link' => array(
        LANGUAGE_NONE => array(
          0 => array(
            'url' => 'http://europa.eu/webtools/showcase/demo/map/samples/demo.js',
            'title' => '',
            'attributes' => array(),
          ),
        ),
      ),
    );

    $bean = bean_create($values);
    $this->beans[] = $bean->delta;
    $bean->save();
  }

  /**
   * Revert to previous settings after scenario execution.
   *
   * @AfterScenario
   */
  public function removeWebtools() {
    // Remove the beans.
    foreach ($this->beans as $bean) {
      bean_delete(bean_load_delta($bean));
    }
  }

}
