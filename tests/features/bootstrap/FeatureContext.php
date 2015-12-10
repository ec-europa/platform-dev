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
   * @return bool
   *   Always returns TRUE.
   *
   * @throws \Exception
   *   Thrown when a module does not exist.
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
   * Reinitialize some environment settings.
   *
   * @AfterScenario @cleanEnvironment
   */
  public static function cleanEnvironment() {
    // Restore homepage.
    variable_set("site_frontpage", "node");

    // Restore default language (en) settings.
    $languages = language_list('enabled', TRUE);
    if (isset($languages['1']['en'])) {
      $language = $languages['1']['en'];

      $language->prefix = '';
      $properties[] = 'prefix';

      $fields = array_intersect_key((array) $language, array_flip($properties));
      // Update language fields.
      db_update('languages')
        ->fields($fields)
        ->condition('language', $language->language)
        ->execute();
    }
  }

  
  /**
   * Enables one or more Feature Set(s).
   *
   * Provide feature set names in the following format:
   *
   * | featureSet  |
   * | Events      |
   * | Links       |
   *
   * @param TableNode $featureset_table
   *   The table listing feature set titles.
   *
   * @Given the/these featureSet/FeatureSets is/are enabled
   */
  public function enableFeatureSet(TableNode $featureset_table) {
    $rebuild = FALSE;
    $message = array();
    $featuresets = feature_set_get_featuresets();
    foreach ($featureset_table->getHash() as $row) {
      foreach ($featuresets as $featureset_available) {
        if ($featureset_available['title'] == $row['featureSet'] && 
        feature_set_status($featureset_available) === FEATURE_SET_DISABLED) {
          if (feature_set_enable_feature_set($featureset_available)){
            $this->features_set[] = $featureset_available;
            $rebuild = true;
          }
          else {
            $message[] = $row['featureSet'];
          }
        }
      }
    }
    if (!empty($message)) {
      throw new \Exception(sprintf('Feature Set "%s" not correctly enabled', implode(', ', $message)));
    }
    else {
      if ($rebuild) {
        drupal_flush_all_caches();
      }
      return TRUE;
    }
  }
  
    /**
   * Disabled and uninstall modules.
   *
   * @AfterScenario
   */
  public function cleanFeatureSet() {
    if (isset($this->features_set) && !empty($this->features_set)) {
      // Disable and uninstall any feature set that were enabled.
      foreach ($this->features_set as $featureset){
        if (isset ($featureset['disable'])){
          $featureset['uninstall'] = $featureset['disable'];
          feature_set_disable_feature_set ($featureset);
        }
      }
      unset($this->features_set);
    }
  }
  
 
  
  /**
   * Creates a language.
   *
   * @param string $langcode
   *   The ISO code of the language to create.
   *
   * @Given the :language language is available
   */
  public function createLanguages($langcode) {
    $this->languageCreate((object) ['langcode' => $langcode]);
  }

}
