@api
Feature: TMGMT Poetry features
  In order request a new translation for portuguese language
  As a Translation manager user
  I want to be able create a translation request in Portuguese (to Portugal) language

  Background:
    Given the module is enabled
      |modules|
      |tmgmt_poetry|
      |tmgmt_poetry_test|
    Given the following languages are available:
      | languages |
      | en        |
      | pt-pt     |

  Scenario: Map the translator setting PT in the
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/tmgmt_translator/manage/tmgmt_poetry_test_translator"
    And I fill in "edit-settings-feedback-contacts-to" with "test@test.com"
    And I fill in "edit-settings-feedback-contacts-cc" with "test@test.com"
    And I fill in "edit-settings-remote-languages-mappings-pt-pt" with "pt"
    And I press the "Save translator" button
    Then I should see the success message "The configuration options have been saved."

  Scenario: Create a request tanslation PT
    Given local translator "Translator PT-PT" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-pt-pt"
    And I press the "Request translation" button
    And I select "TMGMT Poetry: Test translator" from "Translator"
    And I press the "Submit to translator" button
    Then I should see the following success messages:
      | success messages                                     |
      | Job has been successfully submitted for translation. |