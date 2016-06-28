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
    And I fill in "Title" with "The right way is the right way"
    And I click the "Insert internal links" button in the "edit-field-ne-body-und-0-value" WYSIWYG editor
    Then I should see the "cke_editor_edit-field-ne-body-und-0-value_dialog" modal dialog from the "edit-field-ne-body-und-0-value" WYSIWYG editor with "Insert internal links" title
    And I wait for AJAX to finish
    When I click the "Full content" link in the "cke_editor_edit-field-ne-body-und-0-value_dialog" modal dialog from the "edit-field-ne-body-und-0-value" WYSIWYG editor
    Then I should see "<p>[node:1:view-mode:full]{Global editorial team as Full content}</p>" in the "edit-field-ne-body-und-0-value" WYSIWYG editor
    When I click "Disable rich-text"
    And I fill in "Body" with "<p>[node:999:view-mode:full]{Global editorial team as Full content}</p>"
    And I press "Save"
    And I click "Edit draft"
    And I press "Delete"
    And I press "Delete"
    And I go to "admin/reports/dblog"
    Then I should see text matching "Nexteuropa Tokens"
