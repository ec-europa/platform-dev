<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Drupal\DrupalExtension\Context\DrupalContext as DrupalExtensionDrupalContext;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\Element;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\hasKey;

/**
 * Provides step definitions for interacting with Drupal.
 */
class DrupalContext extends DrupalExtensionDrupalContext {
  use \Drupal\nexteuropa\Context\ContextUtil;

  /**
   * The last node id before a scenario starts.
   *
   * @var int
   */
  protected $maxNodeId;


  /**
   * The variable context.
   *
   * @var VariableContext
   */
  protected $variableContext;

  /**
   * Stores languages modified during test execution.
   *
   * @var array
   *
   * @see DrupalContext::setLanguageProperty()
   */
  protected $modifiedLanguages = [];

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
   * Temporarily set site frontpage path.
   *
   * @Given the site front page is set to :path
   */
  public function setFrontpagePath($path) {
    $this->variableContext->setVariable('site_frontpage', $path);
  }

  /**
   * Set language property on given language.
   *
   * @Given the :code language :property is set to :value
   */
  public function setLanguageProperty($code, $property, $value) {
    $languages = language_list();

    assert($languages, hasKey($code), "Language {$code} is not enabled.");
    $language = (array) $languages[$code];
    assert($language, hasKey($property), "Language property {$property} does not exists.");
    $this->modifiedLanguages[$code] = $language;

    $language[$property] = $value;
    db_update('languages')
      ->fields($language)
      ->condition('language', $code)
      ->execute();
  }

  /**
   * Reset languages modified during scenario execution.
   *
   * @see DrupalContext::setLanguageProperty()
   *
   * @afterScenario
   */
  public function resetLanguages() {
    foreach ($this->modifiedLanguages as $code => $language) {
      db_update('languages')
        ->fields($language)
        ->condition('language', $code)
        ->execute();
    }
  }

  /**
   * Visit a node page given its type and title.
   *
   * @param string $type
   *   The node type.
   * @param string $title
   *   The node title.
   *
   * @Then I visit the :type content with title :title
   */
  public function visitContentPage($type, $title) {
    $nodes = node_load_multiple([], ['title' => $title, 'type' => $type], TRUE);
    if (!$nodes) {
      throw new \InvalidArgumentException("Node of type '{$type}' and title '{$title}' not found.");
    }
    // Get node path without any base path by setting 'base_url' and 'absolute'.
    $node = array_shift($nodes);
    $path = 'node/' . $node->nid;
    cache_clear_all($path, 'cache_path');
    drupal_static_reset('drupal_lookup_path');
    $path = url($path, ['base_url' => '', 'absolute' => TRUE]);
    // Visit newly created node page.
    $this->visitPath($path);
  }

  /**
   * Check a radio button selected by its id.
   *
   * @param string $id
   *   The id of the element.
   *
   * @see \Drupal\DrupalExtension\Context\MinkContext::assertSelectRadioById
   *
   * @When I select the radio button with the id :id
   */
  public function assertSelectRadioById($id) {
    $element = $this->getSession()->getPage();
    $radiobutton = $element->findById($id);
    if ($radiobutton === NULL) {
      throw new \Exception(sprintf(
        'The radio button with "%s" was not found on the page %s',
        $id,
        $this->getSession()->getCurrentUrl()
      ));
    }
    $value = $radiobutton->getAttribute('value');
    $radiobutton->selectOption($value, FALSE);
  }

  /**
   * Remember the last node id.
   *
   * @BeforeScenario @reset-nodes
   */
  public function rememberCurrentLastNode() {
    $query = db_select('node');
    $query->addExpression('MAX(nid)');
    $max_node_id = $query->execute()->fetchField();

    if (NULL === $max_node_id) {
      $this->maxNodeId = 0;
    }
    else {
      $this->maxNodeId = intval($max_node_id);
    }
  }

  /**
   * Removes any nodes created after the last node id remembered.
   *
   * @AfterScenario @reset-nodes
   */
  public function resetNodes() {
    if (!isset($this->maxNodeId)) {
      return;
    }

    $all_nodes_after_query = (new \EntityFieldQuery())
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('nid', $this->maxNodeId, '>');

    $all_nodes_after = $all_nodes_after_query->execute();
    $all_nodes_after = reset($all_nodes_after);
    if (is_array($all_nodes_after)) {
      entity_delete_multiple('node', array_keys($all_nodes_after));
    }
    unset($this->maxNodeId);
  }

  /**
   * Create a node along with workbench moderation state.
   *
   * Currently it supports only title and body fields since that is enough to
   * cover basic multilingual behaviors, such as URL aliasing or field
   * translation.
   *
   * Below an example of this step usage:
   *
   *  Given the following contents using "Full HTML + Change tracking"
   *  for WYSIWYG fields:
   *   | language | title         | body         | moderation state | type    |
   *   | und      | Content title | Content body | validated        | article |
   *   | en       | Content title | Content body | validated        | page    |
   *
   * @param string $text_format
   *   The filter format name or its machine name.
   * @param \Behat\Gherkin\Node\TableNode $table
   *   List of available content property.
   *
   * @return array
   *   Array containing the created node objects.
   *
   * @Given the following contents using :arg1 for WYSIWYG fields:
   */
  public function theFollowingContentsUsingForWysiwygFields($text_format, TableNode $table) {
    $nodes = array();

    $filters = filter_formats();
    foreach ($filters as $machine_name => $filter) {
      if ($filter->name == $text_format) {
        $text_format = $machine_name;
        break;
      }
    }

    foreach ($table->getHash() as $row) {
      $state = $row['moderation state'];
      unset($row['moderation state']);

      if (isset($row['Body'])) {
        $value = $row['Body'];
        unset($row['Body']);

        $field_instance = field_info_instance('node', 'field_ne_body', $row['type']);

        if ($field_instance) {
          $row['field_ne_body:value'] = $value;
          $row['field_ne_body:format'] = $text_format;
        }
        else {
          $row['body:value'] = $value;
          $row['body:format'] = $text_format;
        }
      }

      $node = (object) $row;
      // If the node is managed by Workbench Moderation, mark it as published.
      if (workbench_moderation_node_moderated($node)) {
        $node->workbench_moderation_state_new = $state;
      }

      $handler = entity_translation_get_handler('node', $node);
      $handler->setActiveLanguage($node->language);
      $node = $this->nodeCreate($node);
      $node->path['pathauto'] = $this->isPathautoEnabled('node', $node, $node->language);

      // Preserve original language setting.
      $node->field_language = $node->language;

      node_save($node);
      $nodes[] = $node;
    }
    return $nodes;
  }

  /**
   * Puts field inside the specific field group for a given parameters.
   *
   * @When I put the field :field_name inside the field group :group_name of an entity :entity_type type of :bundle using the view mode :view_mode
   */
  public function iPutFieldInToFieldGroup($field_name, $group_name, $entity_type, $bundle, $view_mode) {
    $groups = field_group_read_groups(array(
      'entity_type' => $entity_type,
      'bundle'      => $bundle,
      'mode'   => $view_mode,
    ));

    if (isset($groups[$entity_type][$bundle][$view_mode][$group_name])) {
      $group = $groups[$entity_type][$bundle][$view_mode][$group_name];
      $group->children[] = $field_name;
      field_group_group_save($group);
    }
  }

  /**
   * Assert a text does not appear in a certain tag with a certain attribute.
   *
   * @Then I should not see (the text ):text in the :tag element with the :attribute attribute set to :value
   */
  public function assertTextNotInElement($text, $tag, $attribute, $value) {
    $elements = $this->getElementsByAttribute($this->getSession()->getPage(), $tag, $attribute, $value);

    $text_found = FALSE;
    foreach ($elements as $element) {
      if (strpos($element->getText(), $text) !== FALSE) {
        $text_found = TRUE;
        break;
      }
    }

    if ($text_found) {
      throw new \Exception(sprintf('The text "%s" was found in the "%s" element with the "%s" attribute set to "%s" on the page %s', $text, $tag, $attribute, $value, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Assert a text does appear in a certain tag with a certain attribute.
   *
   * @Then I should see (the text ):text in the :tag element with the :attribute attribute set to :value
   */
  public function assertTextInElement($text, $tag, $attribute, $value) {
    $elements = $this->getElementsByAttribute($this->getSession()->getPage(), $tag, $attribute, $value);

    $text_found = FALSE;
    foreach ($elements as $element) {
      if (strpos($element->getText(), $text) !== FALSE) {
        $text_found = TRUE;
        break;
      }
    }

    if (!$text_found) {
      throw new \Exception(sprintf('The text "%s" was not found in the "%s" element with the "%s" attribute set to "%s" on the page %s', $text, $tag, $attribute, $value, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Retrieve a table row containing specified text from a given element.
   *
   * @param \Behat\Mink\Element\Element $source_element
   *   The element where to search for the tag.
   * @param string $tag
   *   The tag to search for.
   * @param string $attribute
   *   The name of the attribute.
   * @param string $value
   *   The value of the attribute.
   *
   * @return array
   *   An array of elements filtered by an attribute value.
   *
   * @throws \Exception
   */
  public function getElementsByAttribute(Element $source_element, $tag, $attribute, $value) {
    $elements = $source_element->findAll('css', $tag);
    $found_elements = array();
    if (empty($elements)) {
      throw new \Exception(sprintf('The element "%s" was not found on the page %s', $tag, $this->getSession()->getCurrentUrl()));
    }
    foreach ($elements as $element) {
      $attr = $element->getAttribute($attribute);
      if ($attr === $value) {
        $found_elements[] = $element;
      }
    }
    if (empty($found_elements)) {
      throw new \Exception(sprintf('No element "%s" with the attribute "%s" set to "%s" was not found on the page %s', $tag, $attribute, $value, $this->getSession()->getCurrentUrl()));
    }
    return $found_elements;
  }

  /**
   * Creates content of the given type and a moderation state.
   *
   * @param string $type
   *   The created content type.
   * @param string $state
   *   The moderation state of the created content.
   * @param \Behat\Gherkin\Node\TableNode $fields
   *   The values set for the content fields.
   *   The table contains 2 column: one for the field name and one
   *   for the field value.
   *
   * @Given I am viewing a/an :type( content) with :state moderation state:
   */
  public function assertViewingNodeWithModerationState($type, $state, TableNode $fields) {
    $node = (object) array(
      'type' => $type,
      'workbench_moderation_state_new' => $state,
    );
    foreach ($fields->getRowsHash() as $field => $value) {
      $node->{$field} = $value;
    }

    $saved = $this->nodeCreate($node);

    // Set internal browser on the node.
    $this->getSession()->visit($this->locatePath('/node/' . $saved->nid));
  }

}
