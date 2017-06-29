<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MultilingualContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\TableNode;

/**
 * Behat step definitions for the NextEuropa Multilingual module.
 */
class MultilingualContext extends RawDrupalContext implements DrupalSubContextInterface {
  use \Drupal\nexteuropa\Context\ContextUtil;
  /**
   * Published workbench moderation state.
   *
   * @see workbench_moderation_state_none()
   */
  const MODERATION_PUBLISHED = 'published';

  /**
   * {@inheritdoc}
   */
  protected $drupal;

  /**
   * List of translators created during test execution.
   *
   * @var array
   */
  protected $translators = [];

  /**
   * List of TMGMT translation jobs created during test execution.
   *
   * @var \TMGMTJob[]
   */
  protected $jobs = [];

  /**
   * Latest created translation job during test execution.
   *
   * @var \TMGMTJob
   */
  protected $latestJob;

  /**
   * Settings that may be changed during test execution.
   *
   * @var array
   */
  protected $settings = [];

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
   * Create a node along with its translations.
   *
   * Currently it supports only title and body fields since that is enough to
   * cover basic multilingual behaviors, such as URL aliasing or field
   * translation.
   *
   * Below an example of this step usage:
   *
   *    And I am viewing a multilingual "page" content:
   *      | language | title            | body            |
   *      | en       | Title in English | Body in English |
   *      | fr       | Title in French  | Body in French  |
   *      | de       | Title in German  | Body in German  |
   *
   * @param string $type
   *    Content type machine name.
   * @param TableNode $table
   *    List of available languages and field translations.
   *
   * @return object
   *    The created node object.
   *
   * @throws \InvalidArgumentException
   *    Thrown if the specified content type does not support field translation.
   *
   * @Given I create the following multilingual :arg1 content:
   */
  public function createMultilingualContent($type, TableNode $table) {
    if (!entity_translation_node_supported_type($type)) {
      throw new \InvalidArgumentException("'$type' is not a translatable content type.");
    }

    $translations = [];
    foreach ($table->getHash() as $row) {
      $node = (object) $row;
      $node->type = $type;
      $node->status = TRUE;
      // If the node is managed by Workbench Moderation, mark it as published.
      if (workbench_moderation_node_moderated($node)) {
        $node->workbench_moderation_state_new = self::MODERATION_PUBLISHED;
      }
      $translations[$node->language] = $node;
    }

    // Consider the first defined language as the default one.
    $node = array_shift($translations);
    $node = $this->nodeCreate($node);

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
      $fields = (array) $node_translation;
      $this->saveNodeTranslation($node, $language, $fields);
    }
    return $node;
  }

  /**
   * Add a translation to an existing node.
   *
   * @param string $type
   *    Content type machine name.
   * @param string $title
   *    Source node title.
   * @param TableNode $table
   *    List of available languages and field translations.
   *
   * @Then I create the following translations for :type content with title :arg2:
   */
  public function createTranslationForContentWithTitle($type, $title, TableNode $table) {
    $node = $this->getNodeByTitle($type, $title);
    foreach ($table->getHash() as $row) {
      if (!isset($row['language']) || empty($row['language'])) {
        throw new \InvalidArgumentException("You must specify a translation language.");
      }
      $this->saveNodeTranslation($node, $row['language'], $row);
    }
  }

  /**
   * Get a node by specifying its type and title.
   *
   * @param string $label
   *    Moderation state label.
   *
   * @return string
   *    Moderation state machine name.
   */
  protected function getModerationStateMachineName($label) {
    $states = [];
    foreach (workbench_moderation_states() as $state) {
      $states[$state->label] = $state->name;
    }
    if (!isset($states[$label])) {
      throw new \InvalidArgumentException("Property 'moderation state' not valid, must be chosen among: " . implode(', ', array_keys($states)));
    }
    return $states[$label];
  }

  /**
   * Save a translation for an existing node.
   *
   * @param object $node
   *    Node object.
   * @param string $language
   *    Language for which to create the translation for.
   * @param array $fields
   *    Translation fields.
   * @param int|null $vid
   *    Node revision ID to which to apply the translation.
   * @param string $moderation_state
   *    Moderation state.
   */
  public function saveNodeTranslation($node, $language, array $fields, $vid = NULL, $moderation_state = self::MODERATION_PUBLISHED) {
    $handler = entity_translation_get_handler('node', $node);

    $translation = [
      'translate' => 0,
      'status' => TRUE,
      'source' => $node->language,
      'uid' => $node->uid,
      'created' => $node->created,
      'changed' => $node->changed,
      'language' => $language,
    ];

    $node_wrapper = entity_metadata_wrapper('node', $node);
    $node_wrapper->language($language)->title_field = $fields['title'];
    if (!empty($fields['field_ne_body'])) {
      $node_wrapper->language($language)->field_ne_body->set(array('value' => $fields['field_ne_body']));
    }
    elseif (!empty($fields['body'])) {
      $node_wrapper->language($language)->body->set(array('value' => $fields['body']));
    }

    // Assign translated body field, if any.
    $handler->setTranslation($translation, $node_wrapper->value());
    $node_wrapper->save();

    // Workbench Moderation disables pathauto after node has been published.
    // Enforcing it here will ensure a consistent behavior.
    $node->path['pathauto'] = 0;

    // Save node (new translation).
    node_save($node);
  }

  /**
   * Create a node along with its translations and visit its node page.
   *
   * @param string $type
   *    Content type machine name.
   * @param TableNode $table
   *    List of available languages and title translations.
   *
   * @throws \InvalidArgumentException
   *    Thrown if the specified content type does not support field translation.
   *
   * @see NextEuropaMultilingualSubContext::createMultilingualContent()
   *
   * @Given I am viewing a multilingual :arg1 content:
   */
  public function iAmViewingMultilingualContent($type, TableNode $table) {
    $node = $this->createMultilingualContent($type, $table);

    // Get node path without any base path by setting 'base_url' and 'absolute'.
    $path = url('node/' . $node->nid, array('base_url' => '', 'absolute' => TRUE));
    // Visit newly created node page.
    $this->visitPath($path);
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
   * @Given :plugin translator :name is available
   */
  public function isTranslatorAvailable($name, $plugin) {
    /** @var \TMGMTTranslatorController $controller */
    $controller = entity_get_controller('tmgmt_translator');
    $machine_name = strtolower(str_replace(' ', '_', $name));
    if (!tmgmt_translator_exists($machine_name)) {
      $values = [
        "name" => $machine_name,
        "label" => $name,
        "description" => "",
        "weight" => 0,
        "plugin" => $plugin,
        "settings" => [
          "auto_accept" => FALSE,
          "allow_all" => TRUE,
        ],
      ];
      $translator = $controller->create($values);
      $controller->save($translator);
      $this->translators[] = $translator;
    }
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
   * Get the id of the parent job.
   *
   * @param int $tjiid
   *    Job Item id.
   *
   * @return int|FALSE
   *    Parent Job id or FALSE if none was found.
   */
  public function getParentJobId($tjiid) {
    return db_select('tmgmt_job_item', 't')
      ->fields('t', ['tjid'])
      ->condition('t.tjiid', $tjiid)
      ->execute()
      ->fetchField();
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

  /**
   * Assert re-importing latest translation job.
   *
   * @param string $type
   *    Content type machine name.
   * @param string $title
   *    Content type in default language.
   *
   * @Then I re-import the latest translation job for :type with title :title
   */
  public function importLatestTranslationJobForContent($type, $title) {
    $node = $this->getNodeByTitle($type, $title);
    $result = db_select('tmgmt_job_item', 't')
      ->fields('t', ['tjiid'])
      ->condition('t.item_type', 'node')
      ->condition('t.item_id', $node->nid)
      ->orderBy('t.tjiid', 'DESC')
      ->range(0, 1)
      ->execute()
      ->fetchAssoc();
    if ($result) {
      $tjiid = array_shift($result);
      $job_item = tmgmt_job_item_load($tjiid);
      if (!$job_item) {
        throw new \InvalidArgumentException("No translation job found for node of type '{$type}' and title '{$title}'.");
      }
      $controller = $job_item->getSourceController();
      $controller->saveTranslation($job_item);
    }
    else {
      throw new \InvalidArgumentException("No translation job found for node of type '{$type}' and title '{$title}'.");
    }
  }

  /**
   * Create a translation job for an already existing piece of content.
   *
   * @param string $type
   *    The node type.
   * @param string $title
   *    The node title.
   * @param \Behat\Gherkin\Node\TableNode $table
   *    Properties table, "source language" and "target language" are required.
   *
   * @Given I create the following job for :type with title :title
   * @Given I create a translation job for :type with title :title and the following properties:
   */
  public function createTranslationJobForContentWithTitleAndProperties($type, $title, TableNode $table) {
    $node = $this->getNodeByTitle($type, $title);
    $properties = $table->getRowsHash();
    if (!isset($properties['source language'])) {
      throw new \InvalidArgumentException('Property "source language" is required.');
    }
    if (!isset($properties['target language'])) {
      throw new \InvalidArgumentException('Property "target language" is required.');
    }
    if (!isset($properties['translator'])) {
      throw new \InvalidArgumentException('Property "translator" is required.');
    }
    if (!isset($properties['plugin'])) {
      $properties['plugin'] = 'entity';
    }
    $reference = isset($properties['reference']) ? $properties['reference'] : NULL;

    $source = $properties['source language'];
    $target = $properties['target language'];
    $translator = $this->getTranslatorByName($properties['translator']);
    unset($properties['source language'], $properties['target language'], $properties['translator'], $properties['reference']);

    $job = tmgmt_job_create($source, $target, 1);
    $job->label = $node->title;
    $job->translator = $translator->name;
    $job->reference = $reference;
    $job->settings = [];
    $job->addItem($properties['plugin'], 'node', $node->nid);
    if (!$job->save()) {
      throw new \InvalidArgumentException('Error occurred while saving the translation job.');
    }

    $data = array_filter(tmgmt_flatten_data($job->getData()), '_tmgmt_filter_data');
    $tdata = [];
    foreach ($data as $key => $value) {
      $parts = tmgmt_ensure_keys_array($key);
      $field_name = $parts[1];
      $tdata[$key]['#text'] = isset($properties[$field_name]) ? $properties[$field_name] : "[{$job->target_language}]" . ' ' . $value['#text'];
    }
    $job->submitted('Test translation created.');
    $job->addTranslatedData(tmgmt_unflatten_data($tdata));

    $this->latestJob = $job;
    $this->jobs[] = $this->latestJob;
  }

  /**
   * Remove translation jobs created during scenarios execution.
   *
   * @AfterScenario
   */
  public function removeTranslationJobs() {
    if (isset($this->jobs)) {
      /** @var \TMGMTJobController $controller */
      $controller = entity_get_controller('tmgmt_job');
      /** @var \TMGMTJob $translator */
      foreach ($this->jobs as $job) {
        $controller->delete([$job->identifier()]);
      }
    }
  }

  /**
   * Assert current translation job state.
   *
   * @param string $expected
   *    Expected state in human readable format.
   *
   * @Then the translation job is in :expected state
   */
  public function assertCurrentTranslationJobState($expected) {
    $job = $this->getLatestTranslationJob();
    $actual = $job->getState();
    if ($actual != $this->getTranslationJobState($expected)) {
      $states = tmgmt_job_states();
      throw new \InvalidArgumentException("Translation job not in the expected '{$expected}' state. Current state is '{$states[$actual]}'");
    }
  }

  /**
   * Assert current translation job items state.
   *
   * @param string $expected
   *    Expected state in human readable format.
   *
   * @Then the translation job items are in :expected state
   */
  public function assertCurrentTranslationJobItemsState($expected) {
    $job = $this->getLatestTranslationJob();
    foreach ($job->getItems() as $item) {
      $actual = $item->getState();
      if ($actual != $this->getTranslationJobItemState($expected)) {
        $states = tmgmt_job_item_states();
        throw new \InvalidArgumentException("Translation job item not in the expected '{$expected}' state. Current state is '{$states[$actual]}'");
      }
    }
  }

  /**
   * Accept translations for current translation job.
   *
   * @Then the current translation job is accepted
   * @Then the translation job is accepted
   */
  public function acceptCurrentTranslationJob() {
    $job = $this->getLatestTranslationJob();
    foreach ($job->getItems() as $item) {
      $item->acceptTranslation();
    }
  }

  /**
   * Accept all job items for a given translation job.
   *
   * @param string $label
   *    Job label.
   * @param string $language
   *    Target language code.
   *
   * @Given the translation job with label :label and target language :language is accepted
   */
  public function acceptTranslationJobByLabelAndTargetLanguage($label, $language) {
    $jobs = tmgmt_job_load_multiple([], [
      'label' => $label,
      'target_language' => $language,
    ]);
    if (!$jobs) {
      throw new \InvalidArgumentException("Translation job with label '{$label}'
       and target language '{$language}' not found.");
    }
    /** @var \TMGMTJob $job */
    $job = array_shift($jobs);
    foreach ($job->getItems() as $item) {
      $item->acceptTranslation();
    }
  }

  /**
   * Get moderation state machine name by labeland languages settings.
   *
   * @Given :field for language :langcode is set to :value
   */
  public function setLanguageSetting($field, $value, $langcode) {

    if ($field == 'language') {
      throw new \InvalidArgumentException("Field '{$field}' can not be changed.");
    }

    $query = "SELECT * FROM {languages} WHERE language = :lang";
    $language = db_query($query, array(':lang' => $langcode))->fetchObject();

    if (empty($language)) {
      throw new \InvalidArgumentException("Language '{$langcode}' does not exists.");
    }

    $this->settings['language'] = array(
      'field' => $field,
      'value' => $language->$field,
      'langcode' => $langcode,
    );

    $this->updateLanguage($field, $value, $langcode);

  }

  /**
   * Get a node by specifying its type and title.
   *
   * @param string $type
   *    The node type.
   * @param string $title
   *    The node title.
   *
   * @return object
   *    The node object.
   */
  protected function getNodeByTitle($type, $title) {
    $nodes = node_load_multiple([], ['title' => $title, 'type' => $type], TRUE);
    if ($nodes) {
      return array_shift($nodes);
    }
    throw new \InvalidArgumentException("Node of type '{$type}' and title '{$title}' not found.");
  }

  /**
   * Get a node revision by specifying its type and title.
   *
   * @param string $type
   *    The node type.
   * @param string $title
   *    The node title.
   *
   * @return object
   *    The node object.
   */
  protected function getNodeRevisionByTitle($type, $title) {
    $query = db_select('node', 'n');
    $query->addJoin('LEFT', 'node_revision', 'nr', 'nr.nid = n.nid');
    $result = $query->fields('nr', ['nid', 'vid'])
      ->condition('n.type', $type)
      ->condition('nr.title', $title)
      ->orderBy('nr.vid')
      ->execute()
      ->fetch();
    if ($result) {
      return node_load($result->nid, $result->vid, TRUE);
    }
    throw new \InvalidArgumentException("Node revision of type '{$type}' and title '{$title}' not found.");
  }

  /**
   * Get translator by machine name.
   *
   * @param string $name
   *    Human readable labels will be converted into machine name-like syntax.
   *
   * @return \TMGMTTranslator
   *    Translator object.
   *
   * @see NextEuropaMultilingualSubContext::isTranslatorAvailable()
   */
  protected function getTranslatorByName($name) {
    $name = strtolower(str_replace(' ', '_', $name));
    $translator = tmgmt_translator_load($name);
    if ($translator) {
      return $translator;
    }
    throw new \InvalidArgumentException("Translator with machine name '{$name}' not found.");
  }

  /**
   * Get latest saved translation job.
   *
   * @return \TMGMTJob
   *    Translation job object.
   */
  protected function getLatestTranslationJob() {
    if ($this->latestJob) {
      return $this->latestJob;
    }
    throw new \InvalidArgumentException("No translation job found, create a translation job during the scenario execution first.");
  }

  /**
   * Get translation job state value given its human readable label.
   *
   * @param string $state
   *    State human readable label.
   *
   * @return int
   *    Translation job state value.
   */
  protected function getTranslationJobState($state) {
    $states = [
      'Unprocessed' => TMGMT_JOB_STATE_UNPROCESSED,
      'Active' => TMGMT_JOB_STATE_ACTIVE,
      'Rejected' => TMGMT_JOB_STATE_REJECTED,
      'Aborted' => TMGMT_JOB_STATE_ABORTED,
      'Finished' => TMGMT_JOB_STATE_FINISHED,
    ];
    if (isset($states[$state])) {
      return $states[$state];
    }
    throw new \InvalidArgumentException("Translation job state labeled '{$state}' does not exists.");
  }

  /**
   * Get translation job item state value given its human readable label.
   *
   * @param string $state
   *    State human readable label.
   *
   * @return int
   *    Translation job item state value.
   */
  protected function getTranslationJobItemState($state) {
    $states = [
      'In progress' => TMGMT_JOB_ITEM_STATE_ACTIVE,
      'Needs review' => TMGMT_JOB_ITEM_STATE_REVIEW,
      'Accepted' => TMGMT_JOB_ITEM_STATE_ACCEPTED,
      'Aborted' => TMGMT_JOB_ITEM_STATE_ABORTED,
    ];
    if (isset($states[$state])) {
      return $states[$state];
    }
    throw new \InvalidArgumentException("Translation job item state labeled '{$state}' does not exists.");
  }

  /**
   * Update language in database.
   *
   * @param string $field
   *    The field to change.
   * @param string $value
   *    The new value.
   * @param string $langcode
   *    The code of the language to bee changed.
   */
  protected function updateLanguage($field, $value, $langcode) {
    db_update('languages')
      ->fields(array($field => $value))
      ->condition('language', $langcode)
      ->execute();
  }

  /**
   * Revert to previous settings after scenario execution.
   *
   * @AfterScenario
   */
  public function revertSettings() {
    if (!empty($this->settings)) {
      if (isset($this->settings['language'])) {
        $lang = $this->settings['language'];
        $this->updateLanguage($lang['field'], $lang['value'], $lang['langcode']);
      }
    }
  }

}
