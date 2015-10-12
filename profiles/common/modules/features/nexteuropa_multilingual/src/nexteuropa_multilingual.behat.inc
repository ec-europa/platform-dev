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
   * Contains original values of "language_content_type_TYPE" variables.
   *
   * @see contentTypeSupportsFieldTranslation()
   * @see resetLanguageContentTypeValues()
   *
   * @var array
   */
  protected $languageContentTypeValues = array();

  /**
   * Contains original language negotiation variables values.
   *
   * @see contentTypeSupportsFieldTranslation()
   * @see resetLanguageContentTypeValues()
   *
   * @var array
   */
  protected $languageNegotiationValues = array();

  /**
   * Constructs a NextEuropaMultilingualSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
    $this->languageNegotiationValues = array(
      'language_negotiation_language' => array(),
      'language_negotiation_language_content' => array(),
      'language_negotiation_language_url' => array(),
    );
  }

  /**
   * Set field translation for specified content type.
   *
   * @param string $type
   *    Content type machine name.
   *
   * @see resetLanguageContentTypeValues()
   *
   * @Given :type content type supports field translation
   */
  public function contentTypeSupportsFieldTranslation($type) {
    $this->languageContentTypeValues[$type] = variable_get('language_content_type_' . $type, 0);
    multisite_config_service('entity_translation')->enableEntityTranslation($type);
  }

  /**
   * Set NextEuropa Multilingual URL suffix as default negotiation method.
   *
   * @see resetLanguageNegotiationMethods()
   *
   * @Given URL language suffix negotiation is enabled
   */
  public function urlLanguageSuffixNegotiationIsEnabled() {
    foreach ($this->languageNegotiationValues as $variable_name => $variable_value) {
      $this->languageNegotiationValues[$variable_name] = variable_get($variable_name, array());
    }
    multisite_config_service('locale')->setLanguageNegotiation('nexteuropa_multilingual_url_suffix', LANGUAGE_TYPE_INTERFACE);
    multisite_config_service('locale')->setLanguageNegotiation('nexteuropa_multilingual_url_suffix', LANGUAGE_TYPE_CONTENT);
    multisite_config_service('locale')->setLanguageNegotiation('nexteuropa_multilingual_url_suffix', LANGUAGE_TYPE_URL);
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
      $row['type'] = $type;
      $translations[$row['language']] = (object) $row;
    }

    // Consider the first defined language as the default one.
    $node = array_shift($translations);
    $node = $this->nodeCreate($node);
    $translation = array(
      'translate' => 0,
      'status' => TRUE,
      'source' => $node->language,
    );

    foreach ($translations as $language => $node_translation) {
      $translation_handler = entity_translation_get_handler('node', $node);
      $translation_handler->loadTranslations();

      $translation['uid'] = $node->uid;
      $translation['created'] = $node->created;
      $translation['changed'] = $node->changed;
      $translation['language'] = $language;

      $values = array();
      $values['title_field'][$language][0]['value'] = $node_translation->title;

      // Add the new translation and store it.
      $translation_handler->setTranslation($translation, $values);

      // Preserve original language setting.
      $node->field_language = $node->language;
      $node->language = $node->translations->original;

      // Save entity.
      node_save($node);
    }

    // Explicitly create URL aliases for all node translations.
    $data = array('node' => $node);
    pathauto_create_alias('node', 'update', "node/$node->nid", $data);

    // Visit newly created node page.
    $this->getSession()->visit($this->locatePath("node/$node->nid"));
  }

  /**
   * Reset "language_content_type_TYPE" variables values.
   *
   * @AfterScenario
   */
  public function resetLanguageContentTypeValues() {
    foreach ($this->languageContentTypeValues as $type => $value) {
      variable_set('language_content_type_' . $type, $value);
    }
  }

  /**
   * Reset original language negotiation methods.
   *
   * @AfterScenario
   */
  public function resetLanguageNegotiationMethods() {
    foreach ($this->languageNegotiationValues as $variable_name => $variable_value) {
      if ($variable_value) {
        variable_set($variable_name, $variable_value);
      }
    }
  }

}
