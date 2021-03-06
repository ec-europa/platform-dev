@api @ec_resp
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
    And I fill in the content's title with "This is a page i want to reference"
    And I fill in "Body" with "Here is the content of the referenced page."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    When I go to "node/add/page"
    And I fill in the content's title with "The right way is the right way"
    And I click the "Insert internal content" button in the "edit-field-ne-body-en-0-value" WYSIWYG editor
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
    Then I should not see "[node:99999:view-mode:full]"
    And I click "Edit draft"
    And I press "Delete"
    And I press "Delete"

  @javascript
  Scenario: Checking WYSIWYG tokens substitution
    Given I am viewing an "page" content:
     | title            | This is a page i want to reference                               |
    When I go to "node/add/page"
    And I fill in the content's title with "Node with tokens"
    And I fill in the rich text editor "Body" with token "<a href='[node:last-created-node-id:url]'>Node link</a>[node:last-created-node-id:link]"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I visit the "page" content with title "Node with tokens"
    And I click "Node link"
    And I should see the heading "This is a page i want to reference"
    Then I visit the "page" content with title "Node with tokens"
    And I wait 10 seconds
    And I should see the link "This is a page i want to reference"
    Then I click "This is a page i want to reference"
    And I should see the heading "This is a page i want to reference"
