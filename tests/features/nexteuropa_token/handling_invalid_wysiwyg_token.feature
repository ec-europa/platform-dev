@api
Feature: Testing wrong token association for Next Europa token module
  In order to check if invalid token is not causing fatal error
  As an administrator
  I want to be able to see appropriate entry in the Drupal watchdog after processing content

  Background:
    Given I am logged in as a user with the 'administrator' role

  @javascript
  Scenario: Checking WYSIWYG elements and processing content to get entry in Drupal watchdog
    When I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "This is a page i want to reference"
    And I fill in "Body" with "Here is the content of the referenced page."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    When I go to "node/add/page"
    And I fill in "Title" with "The right way is the right way"
    And I click the "Insert internal content" button in the "edit-field-ne-body-und-0-value" WYSIWYG editor
    Then I should see the "CKEditor" modal dialog from the "Body" WYSIWYG editor with "Insert internal content" title
    And I wait for AJAX to finish
    When I click the "Full content" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    Then I press "Save"
    Then I should see "This is a page i want to reference"
    And I should see "Here is the content of the referenced page."
    When I click "Edit draft"
    And I click "Disable rich-text"
    Then I should see ":view-mode:full]{This is a page i want to reference as Full content}</p>"
    And I fill in "Body" with "<p>[node:99999:view-mode:full]{A node that does not exist as Full content}</p>"
    And I press "Save"
    And I click "Edit draft"
    And I press "Delete"
    And I press "Delete"
    And I go to "admin/reports/dblog"
    Then I should see text matching "Nexteuropa Tokens"
