<?php

/**
 * @file
 * Contains \FeatureContext.
 */

use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Hook\Scope\AfterStepScope;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\TableNode;
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
   * Usage example:
   *   Then I should have the following options for "edit-operation":
   *     | options               |
   *     | editorial team member |
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
   * Usage example:
   *   Then I should not have the following options for "edit-operation":
   *     | options               |
   *     | editorial team member |
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
   *   AfterStep hook scope object.
   *
   * @throws \Exception
   *   Print out descriptive error message by throwing an exception.
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
   *   Fully namespaced class name.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *   Throw exception if class specified has not been found.
   *
   * @Then the class :arg1 exists in my codebase
   */
  public function assertClassExists($class_name) {
    if (!class_exists($class_name)) {
      throw new ExpectationException("Class '{$class_name}' not found.", $this->getSession());
    }
  }

  /**
   * Make a user with the OG role in the group (create it if it doesn't exist).
   *
   * @Given I am a/an :roles user, member of entity :entity_name of type :entity_type as :group_role
   */
  public function iAmMemberOfEntityHavingRole($roles, $group_role, $entity_name, $entity_type) {
    // Create the user.
    $account = (object) array(
      'name' => $this->getRandom()->name(8),
      'mail' => $this->getRandom()->name(8) . '@example.com',
      'pass' => $this->getRandom()->name(16),
      'role' => $roles,
      'field_terms_and_conditions' => 'Terms and conditions have been accepted',
    );
    $this->userCreate($account);
    $roles = array_map('trim', explode(',', $roles));
    foreach ($roles as $role) {
      if (!in_array($role, array('authenticated', 'authenticated user'))) {
        $this->getDriver()->userAddRole($account, $role);
      }
    }
    // Try to use an existing 'entity' node.
    try {
      $entity = $this->getNodeByTitle($entity_type, $entity_name);
    }
    catch (ExpectationException $e) {
      $entity = FALSE;
    }
    // Create the group, if doesn't exist.
    if (!$entity) {
      $entity = $this->nodeCreate((object) array(
        'status' => TRUE,
        'uid' => 1,
        'type' => $entity_type,
        'title' => $entity_name,
      ));
    }
    $this->addMembertoGroup($account, $group_role, $entity);
    // Authenticate.
    $this->login();
  }

  /**
   * Adds a member to an organic group with the specified role.
   *
   * @param object $account
   *   The user to be added in group.
   * @param string $group_role
   *   The machine name of the group role.
   * @param object $group
   *   The group node.
   * @param string $group_type
   *   (optional) The group's entity type.
   *
   * @throws \Exception
   *    Print out descriptive error message by throwing an exception.
   */
  protected function addMembertoGroup($account, $group_role, $group, $group_type = 'node') {
    list($gid, ,) = entity_extract_ids($group_type, $group);
    $membership = og_group($group_type, $gid, array(
      'entity type' => 'user',
      'entity' => $account,
    ));
    if (!$membership) {
      throw new \Exception("The Organic Group membership could not be created.");
    }
    // Add role for membership.
    $roles = og_roles($group_type, $group->type, $gid);
    $rid = array_search($group_role, $roles);
    if (!$rid) {
      throw new \Exception("'$group_role' is not a valid group role.");
    }
    og_role_grant($group_type, $gid, $account->uid, $rid);
  }

  /**
   * Loads a node by its title.
   *
   * @param string $type
   *   The node type.
   * @param string $title
   *   The node title.
   *
   * @return \stdClass
   *   The node object.
   *
   * @throws ExpectationException
   *   When no node is found.
   */
  protected function getNodeByTitle($type, $title) {
    if (!($node = node_load_multiple(array(), array(
      'type' => $type,
      'title' => $title,
    ), TRUE))
    ) {
      throw new ExpectationException("There's no '$type' node entitled '$title'.", $this->getSession());
    }
    $node = reset($node);
    return $node;

  }

  /**
   * Check if given field is translatable.
   *
   * @param string $field_name
   *   Field machine name.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *   Throw exception if field is not translatable.
   *
   * @Given the :field_name field is translatable
   */
  public function assertFieldIsTranslatable($field_name) {
    $info = field_info_field($field_name);
    if (!isset($info['translatable']) || !$info['translatable']) {
      throw new ExpectationException("Field '{$field_name}' is not translatable.", $this->getSession());
    }
  }

  /**
   * Checks, that elements are highlighted on page.
   *
   * @Then I should see highlighted elements
   */
  public function iShouldSeeHighlightedElements() {
    // div.ICE-Tracking is the css definition that highlights page elements.
    $this->assertSession()->elementExists('css', 'div.ICE-Tracking');
  }

  /**
   * Checks that no elements are highlighted on page.
   *
   * @Then I should not see highlighted elements
   */
  public function iShouldNotSeeHighlightedElements() {
    // div.ICE-Tracking is the css definition that highlights page elements.
    $this->assertSession()->elementNotExists('css', 'div.ICE-Tracking');
  }

  /**
   * Assert that the given form element is disabled.
   *
   * @Then the :label checkbox should be disabled
   * @Then the :label form element should be disabled
   */
  public function assertDisabledElement($label) {
    if (!$this->assertSession()->fieldExists($label)->hasAttribute('disabled')) {
      throw new ExpectationException("Form element '{$label}' is not disabled", $this->getDriver());
    }
  }

  /**
   * Reinitialize some Community environment settings.
   *
   * @AfterFeature @cleanCommunityEnvironment
   */
  public static function cleanCommunityEnvironment() {

    // Delete community's variables.
    $feature = features_load_feature('nexteuropa_communities');
    if (isset($feature->info['features']['variable'])) {
      foreach ($feature->info['features']['variable'] as $varname) {
        variable_del($varname);
      }
    }

    // Delete community's menu_links.
    if (isset($feature->info['features']['menu_links'])) {
      foreach ($feature->info['features']['menu_links'] as $menulinks) {
        menu_link_delete(NULL, $menulinks);
      }
    }

    // Delete community's menu_custom.
    if (isset($feature->info['features']['menu_custom'])) {
      foreach ($feature->info['features']['menu_custom'] as $menucustom) {
        $menu = menu_load($menucustom);
        menu_delete($menu);
      }
    }

    drupal_flush_all_caches();
  }

  /**
   * Create a new revision for content of given type and title.
   *
   * @Given I create a new revision for :arg1 content with title :arg2
   */
  public function createNewRevision($type, $title) {
    $node = $this->getNodeByTitle($type, $title);
    $node->revision = TRUE;
    node_save($node);
  }

  /**
   * Revert given content to its first revision.
   *
   * @Given I revert the :arg1 content with title :arg2 to its first revision
   */
  public function revertContentToFirstRevision($type, $title) {
    $node = $this->getNodeByTitle($type, $title);
    $revisions = node_revision_list($node);
    ksort($revisions);
    $node_revision = array_shift($revisions);
    $node_revision = node_load($node->nid, $node_revision->vid);
    $node_revision->revision = TRUE;
    node_save($node_revision);
  }

  /**
   * Assert field language given field name, content type and content title.
   *
   * @Then I should only have :arg1 in :arg2 for :arg3 published content with title :arg4
   */
  public function assertFieldLanguageForPublishedContentWithTitle($field_name, $language, $type, $title) {
    $node = $this->getNodeByTitle($type, $title);

    $query = db_select("field_data_{$field_name}", 'f')
      ->fields('f', ['language', 'entity_id'])
      ->condition('entity_type', 'node')
      ->condition('language', $language, '!=')
      ->condition('bundle', $type)
      ->condition('entity_id', $node->nid)
      ->countQuery();

    $results = $query->execute()->fetchField();
    if ($results > 0) {
      throw new ExpectationException("Other languages than '{$language}' have been found for '{$field_name}' field.", $this->getSession());
    }
  }

  /**
   * Wait $sec seconds before going to the next step.
   *
   * @Then I wait :sec seconds
   */
  public function wait($sec) {
      sleep($sec);
  }

}