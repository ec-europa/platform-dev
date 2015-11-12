@api
Feature: Translation management features
  In order to manage multilingual content
  As a site administrator
  I want to be able to manage and import content translations

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    And local translator "Translator A" is available

  Scenario: Path aliases are not deleted when translating content via translation management
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I check the box "edit-languages-de"
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
