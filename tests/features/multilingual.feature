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

  Scenario: Content can be translated in available languages
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
      | fr       | Ce titre est en Français     |
      | de       | Dieser Titel ist auf Deutsch |
    Then I should see the heading "This title is in English"
    And I click "English" in the "header_top" region
    Then I should be on the language selector page
    And I click "Français"
    Then I should see the heading "Ce titre est en Français"
    And I click "Français" in the "header_top" region
    Then I should be on the language selector page
    When I click "Deutsch"
    And I should see the heading "Dieser Titel ist auf Deutsch"
    And I click "Deutsch"
    Then I should be on the language selector page
    And I click "English"
    Then I should see the heading "This title is in English"

  Scenario: Custom URL suffix language negotiation is applied by default on new content.
    Given I am logged in as a user with the 'administrator' role
    And I am viewing a multilingual "page" content:
      | language | title            |
      | en       | Title in English |
      | fr       | Title in French  |
      | de       | Title in German  |
    Then I should be on "content/title-english_en"
    And I click "English" in the "header_top" region
    Then I should be on the language selector page
    And I click "Français"
    Then I should be on "content/title-english_fr"
    And I click "Français" in the "header_top" region
    Then I should be on the language selector page
    And I click "Deutsch"
    Then I should be on "content/title-english_de"

  Scenario: Enable multiple languages
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/language"
    Then I should see "English"
    And I should see "French"
    And I should see "German"

  @cleanEnvironment
  Scenario: Enable language suffix and check the base path
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/language/configure"
    And I check the box "edit-language-enabled-nexteuropa-multilingual-url-suffix"
    And I uncheck the box "edit-language-enabled-locale-url"
    And I press the "Save settings" button
    Then I should see the success message "Language negotiation configuration saved."
    When I go to "admin/config/regional/language/edit/en"
    And I fill in "edit-prefix" with "en-prefix"
    And I press the "Save language" button
    And I go to "admin/config/system/site-information"
    And I fill in "edit-site-frontpage" with "admin/fake-url"
    And I select "01000" from "edit-classification"
    And I press the "Save configuration" button
    Then I should see the success message "The configuration options have been saved."
    And the cache has been cleared
    And I should not see "admin/fake-url" in the ".form-item-site-frontpage span.field-prefix" element
    And I should not see "en-prefix" in the ".form-item-site-frontpage span.field-prefix" element
    When I go to "admin/config/regional/language/edit/en"
    And I fill in "edit-prefix" with "en"
    And I press the "Save language" button

  Scenario: Path aliases are not deleted when translating content via translation management
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-de"
    And I press the "Request translation" button
    And I select "Translator A" from "Translator"
    And I press the "Submit to translator" button
    Then I should see the following success messages:
      | success messages                        |
      | The translation job has been submitted. |
    And I click "Translation"
    Then I should see "This title is in English"
    And I click "manage" in the "This title is in English" row
    And I click "view" in the "In progress" row
    And I fill in "Translation" with "Dieser Titel ist auf Deutsch"
    And I press the "Save" button
    And I click "reviewed" in the "The translation of This title is in English to German is finished and can now be reviewed." row
    And I press the "Save as completed" button
    Then I should see "The translation for This title is in English has been accepted."
    And I click "This title is in English"
    And I should be on "content/title-english_en"
    And I should see the heading "This title is in English"
    And I visit "content/title-english_de"
    And I should see the heading "Dieser Titel ist auf Deutsch"

    @run
  Scenario: I can re-import a translation by re-submitting the translation job.
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-de"
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

  Scenario: I can access an overview of recent translation jobs.
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I create the following multilingual "page" content:
      | language | title              | body              |
      | en       | Title in English 1 | Body in English 1 |
      | de       | Title in German 1  | Body in German 1  |
    And I create the following multilingual "page" content:
      | language | title              | body              |
      | en       | Title in English 2 | Body in English 2 |
      | it       | Title in Italian 2 | Body in Italian 2 |
      | de       | Title in German 2  | Body in German 2  |
    And I create the following job for "page" with title "Title in English 1"
      | source language | en                                      |
      | target language | fr                                      |
      | translator      | Translator A                            |
      | title_field     | Title in French 1                       |
      | reference       | MAIN_4_POETRY_WEB/2016/63904/0/0/TRA    |
    And I create the following job for "page" with title "Title in English 1"
      | source language | en                                      |
      | target language | it                                      |
      | translator      | Translator A                            |
      | title_field     | Title in Italian 1                      |
      | reference       | SUB_4_POETRY_WEB/2016/63904/0/0/TRA     |
    And I create the following job for "page" with title "Title in English 2"
      | source language | en                                      |
      | target language | fr                                      |
      | translator      | Translator A                            |
      | title_field     | Title in French 2                       |
      | reference       | SUB_4_POETRY_WEB/2016/63904/0/0/TRA     |
    And I am on "admin/tmgmt/recent-changes"
    Then I should see "The translation of Title in English 1 to French is finished and can now be reviewed." in the "Title in English 1 English French" row
    And I should see "WEB/2016/63904/0/0/TRA " in the "Title in English 1 English French" row
    And I should see "The translation of Title in English 1 to Italian is finished and can now be reviewed." in the "Title in English 1 English Italian" row
    And I should see "WEB/2016/63904/0/0/TRA " in the "Title in English 1 English Italian" row
    And I should see "The translation of Title in English 2 to German is finished and can now be reviewed." in the "Title in English 2 English German" row
    And I should see "WEB/2016/63904/0/0/TRA " in the "Title in English 1 English German" row
    And I should not see "MAIN_"
    And I should not see "SUB_"
    Given the translation job with label "Title in English 1" and target language "fr" is accepted
    And I am on "admin/tmgmt/recent-changes"
    Then I should see "The translation for Title in English 1 has been accepted."
    And I should see "The translation of Title in English 1 to French is finished and can now be reviewed."
