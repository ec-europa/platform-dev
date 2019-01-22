<?php

namespace Drupal\nexteuropa\Context;

use Behat\MinkExtension\Context\RawMinkContext;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Extension for performing CKEditor related actions.
 */
class CKEditorContext extends RawMinkContext {

  /**
   * The variable for TokenContext.
   *
   * @var \Drupal\nexteuropa\Context\TokenContext
   */
  private $tokenContext;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    // This allows to use the object TokenContext on this context.
    $this->tokenContext = $environment->getContext('Drupal\nexteuropa\Context\TokenContext');
  }

  /**
   * Fills in a specific value in a rich text editor (CKEditor).
   *
   * @Given I fill in the rich text editor :arg1 with :arg2
   */
  public function iFillInTheRichTextEditorWith($arg1, $arg2) {
    /** @var \Behat\Mink\Element\NodeElement $field */
    $field = $this->getSession()->getPage()->findField($arg1);

    if (NULL === $field) {
      throw new \Exception(sprintf('Unable to find field "%s"', $arg1));
    }

    $id = $field->getAttribute('id');

    $args = [
      'ckeditor_instance_id' => $id,
      'value' => $arg2,
    ];

    $args_as_js_object = json_encode($args);

    $this->getSession()->executeScript(
      "args = {$args_as_js_object};" .
      "CKEDITOR.instances[args.ckeditor_instance_id].setData(args.value);"
    );
  }

  /**
   * Fills in value with a token in a rich text editor (CKEditor).
   *
   * It uses a method from Drupal\nexteuropa\Context\TokenContext to handle the
   * replacement of the token.
   *
   * @When I fill in the rich text editor :arg1 with token :arg2
   */
  public function iFillInTheRichTextEditorWithToken($arg1, $arg2) {
    $this->iFillInTheRichTextEditorWith($arg1, $this->tokenContext->replaceToken($arg2));
  }

}
