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
      | fr     |

  Scenario: Map Portuguese translator settings
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/tmgmt_translator/manage/tmgmt_poetry_test_translator"
    And I fill in "edit-settings-feedback-contacts-to" with "test@test.com"
    And I fill in "edit-settings-feedback-contacts-cc" with "test@test.com"
    And I fill in "edit-settings-remote-languages-mappings-pt-pt" with "pt"
    And I press the "Save translator" button
    Then I should see the success message "The configuration options have been saved."

    @javascript
  Scenario: Create a request translation for French and Portuguese
    Given local translator "TMGMT Poetry: Test translator" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-pt-pt"
    And I press the "Request translation" button
    And I select "TMGMT Poetry: Test translator" from "Translator"
    And I wait for AJAX to finish
    Then I should see "Contact usernames"
    And I should see "Organization"
    When I check the box "edit-settings-languages-fr"
    And I press the "Submit to translator" button
    Then I should see the following success messages:
      | success messages                                     |
      | Job has been successfully submitted for translation. |
    And I should see "In progress" in the "French" row
    And I should see "In progress" in the "Portuguese, Portugal" row
    When I click "In progress" in the "French" row
    Then I should see "You are not authorized to access this page."
    Then I receive the translation of this job item
    Then I should see "This title is in English French"
    When I click "Cancel"
    Then I should see "Needs review" in the "French" row
    When I click "Needs review" in the "French" row
    Then I fill in "edit-title-field0value-translation" with "Voici ma traduction française"
    And I press "Save as completed"
    Then I should see "Voici ma traduction française" in the "French" row
    When I click "View published" in the "primary_tabs" region
    Then I should see "This title is in English"
    When I click "Français"
    Then I should see "Voici ma traduction française"
    When I click "New draft" in the "primary_tabs" region
    Then I fill in "Title" with "This is the title of the validated node"
      Then break
#    And I select "validated" from "edit-workbench-moderation-state-new"
#    And I press "Save"
#      Then break
#    Then I click "Translate" in the "primary_tabs" region
#    And I select the radio button "" with the id "edit-languages-pt-pt"
#    And I press the "Request translation" button
#      Then break
#    And I select "TMGMT Poetry: Test translator" from "Translator"
#    And I press the "Submit to translator" button
#    Then I should see the following success messages:
#      | success messages                                     |
#      | Job has been successfully submitted for translation. |
#    When I click "In progress" in the "Portuguese, Portugal" row
#    Then break
#    Then I receive the translation of this job item
#    Then I should see "This is the title of the validated node Portuguese, Portugal"
#    Then I press "Save as completed"
#Then break
#    And I click "In progress" in the "French" row
#    Then I receive the translation of this job item
#    Then I should see "This is the title of the validated node French"
#    When I press "Save as completed"
#Then break
#    Then I click "View published" in the "primary_tabs" region
#    And I click "Français"
#    Then break
#    Then I should see "Voici ma traduction française"