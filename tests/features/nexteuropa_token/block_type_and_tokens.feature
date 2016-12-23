@api
Feature: Test the creation of new block type (bean) and the display of them in a page using tokens.

  Background:
    Given I am logged in as a user with the 'administrator' role
    Given the module is enabled
      | modules                  |
      | nexteuropa_webtools      |

  Scenario: Add a new block type
    Given the cache has been cleared
    When I create the new block type "Behat For The Win"
    Then I update the administrator role permissions
    And I go to "/block/add"
    Then I should see "Behat For The Win"
    When I go to "admin/structure/block-types"
    And I click "Delete" in the "Behat For The Win" row
    And I press the "Delete" button
    Then the response status code should be 200

  @javascript
  Scenario: Create a page with a new block type token
    Given the cache has been cleared
    When I create the new block type "Block type For Behat"
    Then I update the administrator role permissions
    And I go to "/block/add"
    Then I should see "Block type For Behat"
    When I go to "/block/add"
    And I click "Block type For Behat"
    And I fill in "Label" with "Label For Behat test on the block"
    And I fill in "Title" with "Title For Behat test on the block"
    And I press "Save"
    Then I should see "Block type For Behat Title For Behat test on the block has been created."
    When I go to "/node/add/page"
    And I fill in "Title" with "This is a page with a new block type in a token"
    And I select "Full HTML" from "Text format"
    And I click the "Insert internal content" button in the "Body" WYSIWYG editor
    Then I should see the "CKEditor" modal dialog from the "Body" WYSIWYG editor with "Insert internal content" title
    When I click the "Insert internal blocks" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    And I wait for AJAX to finish
    When I click "Default" in the "Title For Behat test on the block" row
    And I wait for AJAX to finish
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I should see "Title For Behat test on the block"
    When I go to "admin/structure/block-types"
    And I click "Delete" in the "Block type For Behat" row
    And I press the "Delete" button
    Then I should see "Block types"
    And I should not see "Block type For Behat"
    When I go to "admin/content"
    And the cache has been cleared
    And I click "This is a page with a new block type in a token"
    Then I should not see "Title For Behat test on the block"
