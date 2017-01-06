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

  Scenario: Create a page with a new block type token
    Given the cache has been cleared
    When I create the new block type "Behat For The Win"
    Then I update the administrator role permissions
    And I go to "/block/add"
    Then I should see "Behat For The Win"
    When I go to "/block/add"
    And I click "Behat For The Win"
    And I fill in "Label" with "Behat for the win block"
    And I fill in "Title" with "Behat for the win block"
    And I press "Save"
    Then I should see "Behat For The Win Behat for the win block has been created."
    When I go to "/node/add/page"
    And I fill in "Title" with "This is a page with a new block type in a token"
    And I fill in "Body" with "[bean:1:view-mode:default]"
    And I select "Full HTML" from "Text format"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I should not see "[bean:1:view-mode:default]"
    When I go to "admin/structure/block-types"
    And I click "Delete" in the "Behat For The Win" row
    And I press the "Delete" button
    Then the response status code should be 200
    When I go to "admin/content"
    And the cache has been cleared
    And I click "This is a page with a new block type in a token"
    Then I should see "[bean:1:view-mode:default]"
