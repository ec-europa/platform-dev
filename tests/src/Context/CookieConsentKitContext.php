<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\MinkExtension\Context\RawMinkContext;
use PHPUnit\Framework\Assert;

/**
 * Context for steps and assertions for nexteuropa_cookie_consent_kit module.
 */
class CookieConsentKitContext extends RawMinkContext {

  /**
   * The Smartloader Protocol-Relative URL.
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
   * Configures the cck feature of the nexteuropa_cookie_consent_kit module.
   *
   * @Given the cookie consent kit feature has been configured correctly
   */
  public function aValidCookieConsentKitHasBeenConfigured() {
    $this->variableContext->setVariable('cce_basic_config_webtools_smartloader', 'https://europa.eu/webtools/load.js');
    $this->variableContext->setVariable('nexteuropa_cookie_consent_kit_display_cookie_banner', 1);
  }

  /**
   * Checks that one cookie consent kit is available on the current page.
   *
   * @Then /^I should have one cookie consent popup on the page$/
   */
  public function assertOneCookieConsent() {
    $cck = [];
    $xpath = '//script[@type = "application/json"]';

    /** @var \Behat\Mink\Element\NodeElement $element */
    foreach ($this->getSession()->getPage()->findAll('xpath', $xpath) as $element) {
      // @codingStandardsIgnoreStart.
      $data = json_decode($element->getText());
      // @codingStandardsIgnoreEnd
      if (!empty($data) && !empty($data->utility) && $data->utility === 'cck') {
        $cck[] = $data;
      }
    }
    Assert::assertCount(1, $cck);
  }

}
