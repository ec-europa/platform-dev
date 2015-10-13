<?php

/**
 * @file
 * Contains \FeatureContext.
 */

use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\NodeElement;
use Behat\Mink\Exception\ExpectationException;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Contains generic step definitions.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  /**
   * Checks that a 403 Access Denied error occurred.
   *
   * @Then I should get an access denied error
   */
  public function assertAccessDenied() {
    $this->assertSession()->statusCodeEquals(403);
  }

  /**
   * Checks that the given select field has the options listed in the table.
   *
   * @Then I should have the following options for :select:
   */
  public function assertSelectOptions($select, TableNode $options) {
    // Retrieve the specified field.
    if (!$field = $this->getSession()->getPage()->findField($select)) {
      throw new ExpectationException("Field '$select' not found.", $this->getSession());
    }

    // Check that the specified field is a <select> field.
    $this->assertElementType($field, 'select');

    // Retrieve the options table from the test scenario and flatten it.
    $expected_options = $options->getColumnsHash();
    array_walk($expected_options, function (&$value) {
      $value = reset($value);
    });

    // Retrieve the actual options that are shown in the page.
    $actual_options = $field->findAll('css', 'option');

    // Convert into a flat list of option text strings.
    array_walk($actual_options, function (&$value) {
      $value = $value->getText();
    });

    // Check that all expected options are present.
    foreach ($expected_options as $expected_option) {
      if (!in_array($expected_option, $actual_options)) {
        throw new ExpectationException("Option '$expected_option' is missing from select list '$select'.", $this->getSession());
      }
    }
  }

  /**
   * Checks that the given select field doesn't have the listed options.
   *
   * @Then I should not have the following options for :select:
   */
  public function assertNoSelectOptions($select, TableNode $options) {
    // Retrieve the specified field.
    if (!$field = $this->getSession()->getPage()->findField($select)) {
      throw new ExpectationException("Field '$select' not found.", $this->getSession());
    }

    // Check that the specified field is a <select> field.
    $this->assertElementType($field, 'select');

    // Retrieve the options table from the test scenario and flatten it.
    $expected_options = $options->getColumnsHash();
    array_walk($expected_options, function (&$value) {
      $value = reset($value);
    });

    // Retrieve the actual options that are shown in the page.
    $actual_options = $field->findAll('css', 'option');

    // Convert into a flat list of option text strings.
    array_walk($actual_options, function (&$value) {
      $value = $value->getText();
    });

    // Check that none of the expected options are present.
    foreach ($expected_options as $expected_option) {
      if (in_array($expected_option, $actual_options)) {
        throw new ExpectationException("Option '$expected_option' is unexpectedly found in select list '$select'.", $this->getSession());
      }
    }
  }

  /**
   * Checks that the given element is of the given type.
   *
   * @param NodeElement $element
   *   The element to check.
   * @param string $type
   *   The expected type.
   *
   * @throws ExpectationException
   *   Thrown when the given element is not of the expected type.
   */
  public function assertElementType(NodeElement $element, $type) {
    if ($element->getTagName() !== $type) {
      throw new ExpectationException("The element is not a '$type'' field.", $this->getSession());
    }
  }

  /**
   * Disabled and uninstall modules.
   *
   * @AfterScenario
   */
  public function cleanModule() {
    if (isset($this->modules) && !empty($this->modules)) {
      // Disable and uninstall any modules that were enabled.
      module_disable($this->modules);
      $res = drupal_uninstall_modules($this->modules);
      unset($this->modules);
    }
  }

  /**
   * Enables one or more modules.
   *
   * Provide modules data in the following format:
   *
   * | modules  |
   * | blog     |
   * | book     |
   *
   * @param TableNode $modules_table
   *   The table listing modules.
   *
   * @Given the/these module/modules is/are enabled
   */
  public function enableModule(TableNode $modules_table) {
    $rebuild = FALSE;
    $message = array();
    foreach ($modules_table->getHash() as $row) {
      if (!module_exists($row['modules'])) {
        if (!module_enable($row)) {
          $message[] = $row['modules'];
        }
        else {
          $this->modules[] = $row['modules'];
          $rebuild = TRUE;
        }
      }
    }

    if (!empty($message)) {
      throw new \Exception(sprintf('Modules "%s" not found', implode(', ', $message)));
    }
    else {
      if ($rebuild) {
        drupal_flush_all_caches();
      }
      return TRUE;
    }
  }



  /**
   * Check the languages order in the language selector page.
   *
   * @Then the language options on the language selector page should be
   */
  public function assertContentLanguageSelectorPageOptions() {
    $pattern = "English";
    //$this->assertElementContainsText("css=#actions li.crm-contact-user-record", "Create User Record", "Create User Record link not in action menu of new contact");
  }


    /**
     * @Then I should see :arg1 in the language selector page
     */
    public function iShouldSeeInTheLanguageSelectorPage($arg1)
    {
        //$this->assertSession()->pageTextMatches("/".$arg1."/");
        //$this->assertSession()->pageTextMatches('/English(.*)Français(.*)Italiano/');

        $text = '<li class="lang-select-page__served">English</li><li><a href="([^"]*)"[^>]* class="active">Français';
        $text = '/<li class="lang-select-page__served">English<\/li><li><a href="(.*)" class="active">Français<\/a><\/li><li><a href="(.*)" class="active">Italiano<\/a><\/li>/';
        //$text = '/(.*)Italiano/';
        
        //$this->assertSession()->responseContains($text);
        
        /*
        $debug = print_r($this->assertSession()->session->getPage()->getContent(), TRUE);
        $handle = fopen("/ec/dev/server/fpfis/webroot/sources/champcy/tmp/file.txt", "w");
        fwrite($handle, $debug);
        fclose($handle);
        */
        
        $session = $this->getSession();
        $actual = $session->getPage()->getContent();
        //$actual = $this->assertSession()->session->getPage()->getContent();
        $regex = $text;
        $message = sprintf('The string "%s" was not found anywhere in the HTML response of the current page.', $text);

        //$this->assert((bool) preg_match($regex, $actual), $message);
        
        if (! preg_match($regex, $actual) )
          throw new Exception(sprintf('The string "%s" was not found anywhere in the HTML response of the current page.', $text));
        
        //return new Then("I should see text matching \"$arg1\"");
        //throw new PendingException();
    }

    /**
     * @Then the language options on the page content language switcher should be :active_language non clickable followed by :language_order links
     */
    public function theLanguageOptionsOnThePageContentLanguageSwitcherShouldBe($active_language, $language_order)
    {
      $pattern = '/<li class="lang-select-page__served">'.$active_language.'<\/li>';
      $languages = explode(",", $language_order);
      foreach($languages as $language) {
        $pattern .= '<li><a href="(.*)" class="active">'.$language.'<\/a><\/li>';  
      }
      $pattern .= "/i";
      
      $session = $this->getSession();
      $pageContent = $session->getPage()->getContent();

      if (! preg_match($pattern, $pageContent) )
        throw new Exception(sprintf('The page content language switcher is not set to %s and not followed by the language links %s.', $active_language, $language_order));
    }



}
