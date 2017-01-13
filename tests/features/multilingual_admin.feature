@api
Feature: Content translation
  In order to translate my content
  As an administrator
  I want to be able to manage content and translations for fields.

  Scenario: Content page does not show mixed content language
    Given the following languages are available:
      | languages |
      | en        |
      | de        |
    Given I am logged in as a user with the 'administrator' role
    And the "body" field is translatable
    When I go to "node/add/page"
    And I fill in "Title" with "English title"
    And I press "Save"
    And I select "Validated" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I click "add"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Deutsch title"
    And I fill in "Body" with "Deutsch Body not for English version."
    And I press "Save"
    And I click "English" in the "content" region
    Then I should not see the text "Deutsch Body not for English version."
