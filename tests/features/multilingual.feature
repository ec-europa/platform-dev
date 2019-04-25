@api
Feature: Multilingual features
  In order to easily understand the content of the European Commission
  As a citizen of the European Union
  I want to be able to read content in my native language

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
      | it        |

  @theme_wip
  # It is in wip for the europa theme because it implies a step referring a
  # region. This must be evaluate deeper before being able to know how to deal with.
  Scenario: Content can be translated in available languages
    Given I am viewing a multilingual "page" content:
      | language | title                                    |
      | en       | Content can be translated in English     |
      | fr       | Contenu peut être traduit en Français    |
      | de       | Dieser Titel ist auf Deutsch             |
    Then I should see the heading "Content can be translated in English"
    And I click "English" in the "header_top" region
    Then I should be on the language selector page
    And I click "Français"
    Then I should see the heading "Contenu peut être traduit en Français"
    And I click "Français" in the "header_top" region
    Then I should be on the language selector page
    When I click "Deutsch"
    And I should see the heading "Dieser Titel ist auf Deutsch"
    And I click "Deutsch"
    Then I should be on the language selector page
    And I click "English"
    Then I should see the heading "Content can be translated in English"

  @theme_wip
  # It is in wip for the europa theme because it implies a step referring a
  # region. This must be evaluate deeper before being able to know how to deal with.
  Scenario: Path aliases are not deleted when translating content via translation management
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                                       |
      | en       | Path aliases are not deleted in English     |
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "German" row
    And I press the "Request translation" button
    And I select "Translator A" from "Translator"
    And I press the "Submit to translator" button
    Then I should see the following success messages:
      | success messages                        |
      | The translation job has been submitted. |
    And I click "Translation"
    Then I should see "Path aliases are not deleted in English"
    And I click "manage" in the "Path aliases are not deleted in English" row
    And I click "view" in the "In progress" row
    And I fill in "Translation" with "Dieser Titel ist auf Deutsch"
    And I press the "Save" button
    And I click "reviewed" in the "The translation of Path aliases are not deleted in English to German is finished and can now be reviewed." row
    And I press the "Save as completed" button
    Then I should see "The translation for Path aliases are not deleted in English has been accepted."
    And I visit "content/path-aliases-are-not-deleted-english_en"
    And I should see the heading "Path aliases are not deleted in English"
    And I visit "content/path-aliases-are-not-deleted-english_de"
    And I should see the heading "Dieser Titel ist auf Deutsch"

  @theme_wip
  # It is in wip for the europa theme because it implies a step referring a
  # region. This must be evaluate deeper before being able to know how to deal with.
  Scenario: I can re-import a translation by re-submitting the translation job.
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "German" row
    And I press the "Request translation" button
    And I select "Translator A" from "Translator"
    And I press the "Submit to translator" button
    Then I should see the following success messages:
      | success messages                        |
      | The translation job has been submitted. |
    And I click "In progress" in the "German" row
    And I fill in "Translation" with "Dieser Titel ist auf Deutsch"
    And I press the "Save" button
    And I click "Needs review" in the "German" row
    And I press the "Save as completed" button
    Then I click "View published" in the "primary_tabs" region
    And I click "Deutsch"
    Then I should see the heading "Dieser Titel ist auf Deutsch"
    And I click "Translate" in the "primary_tabs" region
    And I click "edit" in the "German" row
    And I press the "Delete translation" button
    And I press the "Delete" button
    Then I should see "Not translated" in the "German" row
    And I re-import the latest translation job for "page" with title "This title is in English"
    And I click "Translate" in the "primary_tabs" region
    Then I should see "Published" in the "German" row
    And I should see "Dieser Titel ist auf Deutsch" in the "German" row

  @theme_wip
  # It is in wip for the europa theme because it implies a step referring a
  # region. This must be evaluate deeper before being able to know how to deal with.
  Scenario: I can create a translation job via a Behat step.
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                    |
      | en       | This title is in English |
    Then I should not see the link "Français" in the "content" region
    And I create the following job for "page" with title "This title is in English"
      | source language | en                          |
      | target language | fr                          |
      | translator      | Translator A                |
      | title_field     | Ce titre est en Français    |
    Then the translation job is in "Active" state
    And the translation job items are in "Needs review" state
    And the current translation job is accepted
    And I click "View"
    Then I should see the link "Français" in the "content" region
    And I click "Français" in the "content" region
    Then I should see "Ce titre est en Français"

  Scenario: Multilingual view on language neutral content
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/config/regional/translate/translate"
    And I fill in "String contains" with "Body"
    And I press "Filter"
    And I click "edit" in the "body:article:label" row
    And I fill in "French" with "Corps du texte"
    And I fill in "Italian" with "Corpo del testo"
    And I press "Save translations"
    Then I should see the following success messages:
      | success messages           |
      | The string has been saved. |
    When I go to "admin/structure/types/manage/article/display_en"
    And I select "above" from "edit-fields-body-label"
    And I press "Save"
    Then I should see the following success messages:
      | success messages               |
      | Your settings have been saved. |
    When I go to "node/add/article"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "This is a new article title"
    And I fill in "Body" with "This is a new article body"
    And I press "Save"
    And I select "Published" from "Moderation state"
    And I press "Apply"
    And I go to "content/new-article-title_it"
    Then I should see "Corpo del testo"

  Scenario: NEPT-495: Reverting from a translated revision to a non translated one will not
            leave leftovers in the field table.
    Given "page" content:
      | title           |
      | Page in English |
    And I create a new revision for "page" content with title "Page in English"
    And I create the following translations for "page" content with title "Page in English":
      | language | title          |
      | fr       | Page in French |
      | de       | Page in German |
    And I revert the "page" content with title "Page in English" to its first revision
    Then I should only have "title_field" in "en" for "page" published content with title "Page in English"

