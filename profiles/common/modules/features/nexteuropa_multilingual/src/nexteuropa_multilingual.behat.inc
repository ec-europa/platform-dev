<?php

/**
 * @file
 * Contains \NextEuropaMultilingualSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\TableNode;

/**
 * Behat step definitions for the NextEuropa Multilingual module.
 */
class NextEuropaMultilingualSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * {@inheritdoc}
   */
  protected $drupal;

  /**
   * Constructs a NextEuropaMultilingualSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Create a node along with its translations and visit its node page.
   *
   * Currently it supports only the title field since that is enough to cover
   * basic multilingual behaviors, such as URL aliasing or field translations.
   *
   * Below an example of this step usage:
   *
   *    And I am viewing a multilingual "page" content:
   *      | language | title            |
   *      | en       | Title in English |
   *      | fr       | Title in French  |
   *      | de       | Title in German  |
   *
   * @param string $type
   *    Content type machine name.
   * @param TableNode $table
   *    List of available languages and title translations.
   *
   * @throws \InvalidArgumentException
   *    Thrown if the specified content type does not support field translation.
   *
   * @Given I am viewing a multilingual :arg1 content:
   */
  public function iAmViewingMultilingualContent($type, TableNode $table) {
    if (!entity_translation_node_supported_type($type)) {
      throw new \InvalidArgumentException("'$type' is not a translatable content type.");
    }

    $translations = array();
    foreach ($table->getHash() as $row) {
      $node = (object) $row;
      $node->type = $type;
      $node->status = TRUE;
      // If the node is managed by Workbench Moderation, mark it as published.
      if (workbench_moderation_node_moderated($node)) {
        $node->workbench_moderation_state_new = workbench_moderation_state_published();
      }
      $translations[$node->language] = $node;
    }

    // Consider the first defined language as the default one.
    $node = array_shift($translations);
    $node = $this->nodeCreate($node);
    $translation = array(
      'translate' => 0,
      'status' => TRUE,
      'source' => $node->language,
    );

    // Apply Pathauto settings.
    $node->path['pathauto'] = $this->isPathautoEnabled('node', $node, $node->language);

    // Preserve original language setting.
    $node->field_language = $node->language;

    // Set language.
    $node->language = $node->translations->original;

    // Save node (first language).
    node_save($node);

    // Add others languages.
    foreach ($translations as $language => $node_translation) {
      $handler  = entity_translation_get_handler('node', $node);

      $translation['uid'] = $node->uid;
      $translation['created'] = $node->created;
      $translation['changed'] = $node->changed;
      $translation['language'] = $language;

      $values = array();
      // Title field.
      $values['title_field'][$language][0]['value'] = $node_translation->title;

      $handler->setTranslation($translation, $values);
      // Set translation language.
      $handler->setFormLanguage($language);

      // Save node (new translation).
      node_save($node);
    }

    // Get node path without any base path by setting 'base_url' and 'absolute'.
    $path = url('node/' . $node->nid, array('base_url' => '', 'absolute' => TRUE));
    // Visit newly created node page.
    $this->visitPath($path);
  }

  /**
   * Returns whether or not Pathauto is enabled for the given entity.
   *
   * @param string $entity_type
   *   The entity type.
   * @param mixed $entity
   *   The entity.
   * @param string $langcode
   *   The language code for the entity.
   *
   * @return bool
   *   TRUE if Pathauto is enabled, FALSE if not.
   *
   * @see pathauto_field_attach_form()
   */
  protected function isPathautoEnabled($entity_type, $entity, $langcode) {
    list($id, , $bundle) = entity_extract_ids($entity_type, $entity);
    if (!isset($entity->path['pathauto'])) {
      if (!empty($id)) {
        module_load_include('inc', 'pathauto');
        $uri = entity_uri($entity_type, $entity);
        $path = drupal_get_path_alias($uri['path'], $langcode);
        $pathauto_alias = pathauto_create_alias($entity_type, 'return', $uri['path'], array($entity_type => $entity), $bundle, $langcode);
        return $path != $uri['path'] && $path == $pathauto_alias;
      }
      else {
        return TRUE;
      }
    }
    return $entity->path['pathauto'];
  }

  /**
   * Assert that we are on the language selector page.
   *
   * @Then I should be on the language selector page
   */
  public function assertLanguageSelectorPage() {
    $this->assertSession()->elementExists('css', '#language-selector-site-language-list-page');
  }

  /**
   * Create a TMGMT local translator.
   *
   * @param string $name
   *    Local translator human readable name.
   *
   * @Given local translator :name is available
   */
  public function localTranslatorIsAvailable($name) {
    /** @var \TMGMTTranslatorController $controller */
    $controller = entity_get_controller('tmgmt_translator');
    $values = [
      "name" => strtolower(str_replace(' ', '_', $name)),
      "label" => $name,
      "description" => "",
      "weight" => 0,
      "plugin" => "local",
      "settings" => [
        "auto_accept" => FALSE,
        "allow_all" => TRUE,
      ],
    ];
    $translator = $controller->create($values);
    $controller->save($translator);
    $this->translators[] = $translator;
  }

  /**
   * Remove translators created during scenarios execution.
   *
   * @AfterScenario
   */
  public function removeTranslators() {
    if (isset($this->translators)) {
      /** @var \TMGMTTranslatorController $controller */
      $controller = entity_get_controller('tmgmt_translator');
      /** @var \TMGMTTranslator $translator */
      foreach ($this->translators as $translator) {
        $controller->delete([$translator->identifier()]);
      }
    }
  }

  /**
   * Check that the current job has only items of a specific source plugin.
   *
   * @Then I am on a translation job page with :arg1 job items
   */
  public function assertJobWithJobItemsPlugin($plugin) {

    // We can't simply use Drupal's menu_get_item() because of caching reasons.
    $job_id = $this->getTranslationJobItemFromUrl();
    if (!$job_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a translation job page.");
    }

    $job = tmgmt_job_load($job_id);
    if (!$job) {
      throw new \InvalidArgumentException("Translation job with ID {$job_id} not found.");
    }

    /** @var \TMGMTJobItem $job_item */
    foreach ($job->getItems() as $job_item) {
      if (!$job_item->plugin == $plugin) {
        throw new \InvalidArgumentException("Plugin mismatch: the current job item has plugin set to {$job_item->plugin}.");
      }
    }
  }

  /**
   * Validate current job using poetry test.
   *
   * @Then I receive the translation of :arg1 job item
   */
  public function receiveJobTranslationFromPoetryTest() {

    $url = $this->getSession()->getCurrentUrl();
    // We can't simply use Drupal's menu_get_item() because of caching reasons.
    $job_id = $this->getTranslationJobSubItemFromUrl();
    if (!$job_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a translation job page.");
    }
    else {
      // Get node path w/o any base path by setting 'base_url' and 'absolute'.
      $path = url('tmgmt_poetry_test/receivetranslation/' . $job_id, array(
        'base_url' => '',
        'absolute' => TRUE,
      ));
      // Visit newly created node page.
      $this->visitPath($path);
      $this->visitPath($url);
    }
  }

  /**
   * Get translation job ID from current page's URL.
   *
   * @return int|FALSE
   *    Translators job ID, FALSE if none found.
   */
  protected function getTranslationJobItemFromUrl() {
    $url = $this->getSession()->getCurrentUrl();
    preg_match_all('/admin\/tmgmt\/jobs\/(\d*)/', $url, $matches);
    return isset($matches[1][0]) ? $matches[1][0] : FALSE;
  }

  /**
   * Get translation job item ID from current page's URL.
   *
   * @return int|FALSE
   *    Translators job ID, FALSE if none found.
   */
  protected function getTranslationJobSubItemFromUrl() {
    $url = $this->getSession()->getCurrentUrl();
    preg_match_all('/admin\/tmgmt\/items\/(\d*)/', $url, $matches);
    return isset($matches[1][0]) ? $matches[1][0] : FALSE;
  }

}
