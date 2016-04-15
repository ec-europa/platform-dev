@api @poetry
Feature: TMGMT Poetry features
  In order request a new translation for the Portuguese language
  As a Translation manager user
  I want to be able to create a translation request for the Portuguese language (from Portugal)

  Background:
    Given the module is enabled
      |modules           |
      |tmgmt_poetry      |
      |tmgmt_poetry_test |
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |

  @javascript
  Scenario: Create a request translation for French and Portuguese
    Given local translator "TMGMT Poetry: Test translator" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-pt-pt"
   # And I check the box "edit-languages-pt-pt"
    And I press the "Request translation" button
    And I select "TMGMT Poetry: Test translator" from "Translator"
    And I wait for AJAX to finish
    Then I should see "Contact usernames"
    And I should see "Organization"
