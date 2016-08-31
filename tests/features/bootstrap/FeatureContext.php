<?php

/**
 * @file
 * Contains \FeatureContext.
 */

use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Hook\Scope\AfterStepScope;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\Element;
use Behat\Mink\Element\NodeElement;
use Behat\Mink\Exception\ExpectationException;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\PyStringNode;

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
          if (feature_set_enable_feature_set($featureset_available)) {
            $this->features_set[] = $featureset_available;
            $rebuild = TRUE;
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
   * Disables one or more Feature Set(s).
   *
   * Disable any Feature Set that were enabled during Feature test.
   *
   * @AfterScenario
   */
  public function cleanFeatureSet() {
    if (isset($this->features_set) && !empty($this->features_set)) {
      // Disable and uninstall any feature set that were enabled.
      foreach ($this->features_set as $featureset) {
        if (isset($featureset['disable'])) {
          $featureset['uninstall'] = $featureset['disable'];
          feature_set_disable_feature_set($featureset);
        }
      }
      unset($this->features_set);
    }
  }

  /**
   * Check the languages order in the language selector page.
   *
   * @Then the language options on the page content language switcher should be :active_language non clickable followed by :language_order links
   */
  public function theLanguageOptionsOnThePageContentLanguageSwitcherShouldBe($active_language, $language_order) {
    $pattern = '/<li class="lang-select-page__served">' . $active_language . '<\/li>';
    $languages = explode(",", $language_order);
    foreach ($languages as $language) {
      $pattern .= '<li><a href="(.*)" class="active">' . $language . '<\/a><\/li>';
    }
    $pattern .= "/i";

    $session = $this->getSession();
    $page_content = $session->getPage()->getContent();

    if (!preg_match($pattern, $page_content)) {
      throw new Exception(sprintf('The page content language switcher is not set to %s and not followed by the language links %s.', $active_language, $language_order));
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
   * Creates a file with specified name and context in current workdir.
   *
   * @param string $filename
   *   Name of the file (relative path).
   * @param PyStringNode $content
   *   PyString string instance.
   *
   * @Given /^(?:there is )?a file named "([^"]*)" with:$/
   */
  public function aFileNamedWith($filename, PyStringNode $content) {
    $content = strtr((string) $content, array("'''" => '"""'));
    $drupal = $this->getDrupalParameter('drupal');
    file_put_contents($drupal['drupal_root'] . '/' . $filename, $content);
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

  /**
   * Transforms human readable field labels for Articles into machine names.
   *
   * @param TableNode $article_table
   *   The original table.
   *
   * @return TableNode
   *   The transformed table.
   *
   * @Transform rowtable:title,body,tags,moderation state
   */
  public function transformArticleNodeTable(TableNode $article_table) {
    $aliases = array(
      'title' => 'title',
      'body' => 'body',
      'tags' => 'field_tags',
      'moderation state' => 'workbench_moderation_state_new',
    );

    return $this->transformRowTable($article_table, $aliases);
  }

  /**
   * Transforms human readable field labels for Users into machine names.
   *
   * @param TableNode $user_table
   *   The original table.
   *
   * @return TableNode
   *   The transformed table.
   *
   * @Transform rowtable:first name,last name
   */
  public function transformUserTable(TableNode $user_table) {
    $aliases = array(
      'first name' => 'field_firstname',
      'last name' => 'field_lastname',
    );

    return $this->transformRowTable($user_table, $aliases);
  }

  /**
   * Helper method to transform column names in row tables.
   *
   * @param \Behat\Gherkin\Node\TableNode $table_node
   *   The table to transform.
   * @param array $aliases
   *   An associative array of aliases that are uses for the column names. Keyed
   *   by alias, and with the transformed string as value.
   *
   * @return \Behat\Gherkin\Node\TableNode
   *   The transformed table
   *
   * @see self::transformArticleNodeTable()
   */
  protected function transformRowTable(TableNode $table_node, array $aliases) {
    $table = $table_node->getTable();
    array_walk($table, function (&$row) use ($aliases) {
      // The first column of the row contains the field names. Replace the
      // aliased field name with the machine name if it exists.
      if (array_key_exists($row[0], $aliases)) {
        $row[0] = $aliases[$row[0]];
      }
    });

    return new TableNode($table);
  }

  /**
   * Prepare for PHP errors log.
   *
   * @BeforeScenario
   */
  public static function preparePhpErrors(BeforeScenarioScope $scope) {
    // Clear out the watchdog table at the beginning of each test scenario.
    db_truncate('watchdog')->execute();
  }

  /**
   * Check for PHP errors log.
   *
   * @param AfterStepScope $scope
   *    AfterStep hook scope object.
   *
   * @throws \Exception
   *    Print out descriptive error message by throwing an exception.
   *
   * @AfterStep
   */
  public static function checkPhpErrors(AfterStepScope $scope) {
    // Find any PHP errors at the end of the suite
    // and output them as an exception.
    $log = db_select('watchdog', 'w')
      ->fields('w')
      ->condition('w.type', 'php', '=')
      ->execute()
      ->fetchAll();
    if (!empty($log)) {
      $errors = count($log);
      $step_text = $scope->getStep()->getText();
      $step_line = $scope->getStep()->getLine();
      $feature_title = $scope->getFeature()->getTitle();
      $feature_file = $scope->getFeature()->getFile();
      $message = "$errors PHP errors were logged to the watchdog\n";
      $message .= "Feature: '$feature_title' on '$feature_file' line $step_line\n";
      $message .= "Step: '$step_text'\n";
      $message .= "Errors:\n";
      $message .= "----------\n";
      foreach ($log as $error) {
        $error->variables = unserialize($error->variables);
        $date = date('Y-m-d H:i:sP', $error->timestamp);
        $message .= sprintf("Message: %s: %s in %s (line %s of %s).\n", $error->variables['%type'], $error->variables['!message'], $error->variables['%function'], $error->variables['%line'], $error->variables['%file']);
        $message .= "Location: $error->location\n";
        $message .= "Referer: $error->referer\n";
        $message .= "Date/Time: $date\n\n";
      }
      $message .= "----------\n";
      throw new \Exception($message);
    }
  }

  /**
   * Enables translation for a field.
   *
   * @param string $field
   *   The name of the field.
   *
   * @When I enable translation for field :field
   */
  public function enableTranslationForField($field) {
    multisite_config_service('field')->enableFieldTranslation($field);
  }

  /**
   * Assert the given class exists.
   *
   * @param string $class_name
   *    Fully namespaced class name.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *    Throw exception if class specified has not been found.
   *
   * @Then the class :arg1 exists in my codebase
   */
  public function assertClassExists($class_name) {
    if (!class_exists($class_name)) {
      throw new ExpectationException("Class '{$class_name}' not found.", $this->getSession());
    }
  }

  /**
   * Attempts to find and check a checkbox in a table row containing given text.
   *
   * @param string $row_text
   *    Text on the table row.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *    Throw exception if class table row was not found.
   *
   * @Given I check the box on the :row_text row
   */
  public function checkCheckboxOnTableRow($row_text) {
    $page = $this->getSession()->getPage();
    if ($checkbox = $this->getTableRow($page, $row_text)->find('css', 'input[type=checkbox]')) {
      $checkbox->check();
      return;
    }
    throw new ExpectationException(sprintf('Found a row containing "%s", but no "%s" link on the page %s', $row_text, $checkbox, $this->getSession()->getCurrentUrl()), $this->getSession());
  }

  /**
   * Retrieve a table row containing specified text from a given element.
   *
   * @param Element $element
   *    Mink element object.
   * @param string $search
   *    Table row text.
   *
   * @throws \Exception
   *    Throw exception if class table row was not found.
   *
   * @return NodeElement
   *    Table row node element.
   */
  public function getTableRow(Element $element, $search) {
    $rows = $element->findAll('css', 'tr');
    if (empty($rows)) {
      throw new \Exception(sprintf('No rows found on the page %s', $this->getSession()->getCurrentUrl()));
    }
    /** @var NodeElement $row */
    foreach ($rows as $row) {
      if (strpos($row->getText(), $search) !== FALSE) {
        return $row;
      }
    }
    throw new \Exception(sprintf('Failed to find a row containing "%s" on the page %s', $search, $this->getSession()->getCurrentUrl()));
  }

  /**
   * Check if given field is translatable.
   *
   * @param string $field_name
   *    Field machine name.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *    Throw exception if field is not translatable.
   *
   * @Given the :field_name field is translatable
   */
  public function assertFieldIsTranslatable($field_name) {
    $info = field_info_field($field_name);
    if (!isset($info['translatable']) || !$info['translatable']) {
      throw new ExpectationException("Field '{$field_name}' is not translatable.", $this->getSession());
    }
  }

}
