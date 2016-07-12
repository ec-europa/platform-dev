@api @poetry @i18n
Feature: TMGMT Poetry features
  In order request a new translation for the Portuguese language
  As a Translation manager user
  I want to be able to create a translation request for the Portuguese language (from Portugal)

  Background:
    Given the module is enabled
      |modules                |
      |tmgmt_poetry_mock      |
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |
      | de        |
      | it        |

  @javascript
  Scenario: Create a request translation for French and Portuguese
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-pt-pt"
    And I press the "Request translation" button
    And I select "TMGMT Poetry Test translator" from "Translator"
    And I wait
    Then I should see "Contact usernames"
    And I should see "Organization"

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
    And I should see "WEB/2016/63904/0/0/TRA" in the "Title in English 1 English French" row
    And I should see "The translation of Title in English 1 to Italian is finished and can now be reviewed." in the "Title in English 1 English Italian" row
    And I should see "WEB/2016/63904/0/0/TRA" in the "Title in English 1 English Italian" row
    And I should see "The translation of Title in English 2 to French is finished and can now be reviewed." in the "Title in English 2 English French" row
    And I should see "WEB/2016/63904/0/0/TRA" in the "Title in English 1 English French" row
    And I should not see "_POETRY_"
    Given the translation job with label "Title in English 1" and target language "fr" is accepted
    And I am on "admin/tmgmt/recent-changes"
    Then I should see "The translation for Title in English 1 has been accepted."
    And I should see "The translation of Title in English 1 to French is finished and can now be reviewed."

  @javascript
  Scenario: Request main job before other translations + request a new translation.
    Given I am logged in as a user with the 'administrator' role
    And I go to "admin/poetry_mock/setup"
    And I press "Set variable"
    Then I should see "Variable is configured properly."
    And I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Page for main and sub jobs"
    And I fill in "Body" with "Here is the content of the page for main and sub jobs."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-fr"
    And I press "Request translation"
    And I select "TMGMT Poetry Test translator" from "Translator"
    And I wait
    And I check the box "settings[languages][it]"
    And I press "Submit to translator"
    Then I should not see an "#edit-languages-fr.form-radio" element
    But I should see an "#edit-languages-fr.form-checkbox" element
    And I should see "In progress" in the "French" row
    And I should see "In progress" in the "Italian" row
    And I store node ID of translation request page
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->it" row
    And I click "Needs review" in the "Italian" row
    And I press "Save as completed"
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see "None" in the "Italian" row

  Scenario: A request for translation that is not submitted won't generate a job item.
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                     |
      | en       | English  Title NoJobItem  |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-pt-pt"
    And I press the "Request translation" button
    And I move backward one page
    Then I should not see the link "In progress"

  @javascript
  Scenario: Test not sending one job and moving to another job.
    Given I am logged in as a user with the 'administrator' role
    And I go to "admin/poetry_mock/setup"
    And I press "Set variable"
    Then I should see "Variable is configured properly."
    And I go to "node/add/page"
    And I fill in "Title" with "Original version"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-fr"
    And I press "Request translation"
    Then I go to "node/add/page"
    And I fill in "Title" with "A second original version"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-fr"
    And I press "Request translation"
    And I select "TMGMT Poetry Test translator" from "Translator"
    And I wait
    And I press "Submit to translator"
    Then I should not see an "#edit-languages-fr.form-radio" element
    But I should see an "#edit-languages-fr.form-checkbox" element
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see an "#edit-languages-fr.form-radio" element
    But I should not see an "#edit-languages-fr.form-checkbox" element

  @javascript
  Scenario: Test rejection of a translation.
    Given I am logged in as a user with the 'administrator' role
    And I go to "admin/poetry_mock/setup"
    And I press "Set variable"
    Then I should see "Variable is configured properly."
    And I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Original version"
    And I fill in "Body" with "Here is the content of the page for original version."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-fr"
    And I press "Request translation"
    And I select "TMGMT Poetry Test translator" from "Translator"
    And I wait
    And I store job ID of translation request page
    And I press "Submit to translator"
    Then I should not see an "#edit-languages-fr.form-radio" element
    But I should see an "#edit-languages-fr.form-checkbox" element
    And I should see "In progress" in the "French" row
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Reject translation" in the "en->fr" row
    Then I should see "None" in the "French" row
    And I go to stored job Id translation request page
    And I should see "Aborted" in the "Original version" row