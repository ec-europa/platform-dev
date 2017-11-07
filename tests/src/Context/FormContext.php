<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FormContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Mink\Exception\ElementNotFoundException;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Form context.
 */
class FormContext extends RawDrupalContext {

  /**
   * Checks, that form element with specified label is visible on page.
   *
   * @Then /^(?:|I )should see an? "(?P<label>[^"]*)" form element$/
   */
  public function assertFormElementOnPage($label) {
    $element = $this->getSession()->getPage();
    $nodes = $element->findAll('css', '.form-item label');
    foreach ($nodes as $node) {
      if ($node->getText() === $label) {
        if ($node->isVisible()) {
          return;
        }
        else {
          throw new \Exception("Form item with label \"$label\" not visible.");
        }
      }
    }
    throw new ElementNotFoundException($this->getSession(), 'form item', 'label', $label);
  }

  /**
   * Checks, that form element with specified label and type is visible on page.
   *
   * @Then /^(?:|I )should see an? "(?P<label>[^"]*)" (?P<type>[^"]*) form element$/
   */
  public function assertTypedFormElementOnPage($label, $type) {
    $container = $this->getSession()->getPage();
    $pattern = '/(^| )form-type-' . preg_quote($type) . '($| )/';
    $label_nodes = $container->findAll('css', '.form-item label');
    foreach ($label_nodes as $label_node) {
      if ($label_node->getText() === $label
        && preg_match($pattern, $label_node->getParent()->getAttribute('class'))
        && $label_node->isVisible()) {
        return;
      }
    }
    throw new ElementNotFoundException($this->getSession(), $type . ' form item', 'label', $label);
  }

  /**
   * Checks, that element with specified CSS is not visible on page.
   *
   * @Then /^(?:|I )should not see an? "(?P<label>[^"]*)" form element$/
   */
  public function assertFormElementNotOnPage($label) {
    $element = $this->getSession()->getPage();
    $nodes = $element->findAll('css', '.form-item label');
    foreach ($nodes as $node) {
      if ($node->getText() === $label && $node->isVisible()) {
        throw new \Exception();
      }
    }
  }

  /**
   * Checks the visibility of the form element with label and type.
   *
   * @Then /^(?:|I )should not see an? "(?P<label>[^"]*)" (?P<type>[^"]*) form element$/
   */
  public function assertTypedFormElementNotOnPage($label, $type) {
    $container = $this->getSession()->getPage();
    $pattern = '/(^| )form-type-' . preg_quote($type) . '($| )/';
    $label_nodes = $container->findAll('css', '.form-item label');
    foreach ($label_nodes as $label_node) {
      if ($label_node->getText() === $label
        && preg_match($pattern, $label_node->getParent()->getAttribute('class'))
        && $label_node->isVisible()) {
        throw new ElementNotFoundException($this->getSession(), $type . ' form item', 'label', $label);
      }
    }
  }

  /**
   * Selects option in select field using javascript.
   *
   * Selects option in select field with specified id|name|label|value.
   * This method uses javascript to allow selection of options that may be
   * overridden by javascript libraries, and thus hide the element.
   *
   * Source: @link https://github.com/gambry/behat-contexts @endlink .
   *
   * @When /^(?:|I )select "(?P<option>(?:[^"]|\\")*)" from "(?P<select>(?:[^"]|\\")*)" with javascript$/
   */
  public function selectOptionWithJavascript($select, $option) {
    $select = $this->fixStepArgument($select);
    $option = $this->fixStepArgument($option);
    $page = $this->getSession()->getPage();
    // Find field.
    $field = $page->findField($select);
    if (NULL === $field) {
      throw new ElementNotFoundException($this->getSession(), 'form field', 'id|name|label|value', $select);
    }
    // Find option.
    $opt = $field->find('named', array(
      'option',
      $option,
    ));
    if (NULL === $opt) {
      throw new ElementNotFoundException($this->getSession(), 'select option', 'value|text', $option);
    }
    // Merge new option in with old handling both multiselect and single select.
    $value = $field->getValue();
    $newValue = $opt->getAttribute('value');
    if (is_array($value)) {
      if (!in_array($newValue, $value)) {
        $value[] = $newValue;
      }
    }
    else {
      $value = $newValue;
    }
    $valueEncoded = json_encode($value);
    // Inject this value via javascript.
    $fieldID = $field->getAttribute('ID');
    $script = <<<EOS
			(function($) {
				$("#$fieldID")
					.val($valueEncoded)
					.change()
					.trigger('liszt:updated')
					.trigger('chosen:updated');
			})(jQuery);
EOS;
    $this->getSession()->getDriver()->executeScript($script);
  }

  /**
   * Returns fixed step argument (with \\" replaced back to ").
   *
   * Source: @link https://github.com/gambry/behat-contexts @endlink .
   *
   * @param string $argument
   *   The argument.
   *
   * @return string
   *   The return.
   */
  protected function fixStepArgument($argument) {
    return str_replace('\\"', '"', $argument);
  }

}
