@api @javascript
Feature: Create content button
  In order to create content
  As an editor
  I can use the "Create content" selector to create content

  Background:
    Given I am logged in as a user with the 'editor' role

  @ec_resp_theme
  Scenario Outline: An editor can create an article from the Create content selector
    When I go to "node"
    Then I should see the text "Create content"
    And I click "Create content"
    Then I should see the text "<node_type>"
    And I click "<node_type>"
    Then I should see "Create <node_type>"
    And I fill in "Title" with "<title>"
    And I press "Save"
    Then I should see "<title> has been created"

  Examples:
  | node_type      | title      |
  | Article        | Node title |
  | Basic page     | Node title |

  @ec_europa_theme
  Scenario Outline: An editor can create an article from the Create content selector
    When I go to "node"
    Then I should see the text "Create content"
    And I click on selector "#block-multisite-create-button-create-content-button .ecl-select"
    Then I should see the text "<node_type>"
    And I should see "<node_type>"
    And I click on option "<node_type>" from selector "#block-multisite-create-button-create-content-button .ecl-select"
    Then I fill in "Title" with "<title>"
    And I press "Save"
    Then I should see "<title> has been created"

  Examples:
  | node_type      | title      |
  | Article        | Node title |
  | Basic page     | Node title |
