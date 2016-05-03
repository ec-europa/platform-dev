@api
Feature: Nexteuropa Newsroom
  Testing Nexteuropa Newsroom feature

  Background:
    Given these modules are enabled
      | modules             |
      | nexteuropa_newsroom |

  Scenario: Checks access to newsroom settings
    Given I am logged in as a user with the "administrator" role
    When I visit "admin/config/content/newsroom"
    Then I should see the text "Universe ID value"

  Scenario: Saves Universe ID and builds importers
    Given I am logged in as a user with the "administrator" role
    When I visit "admin/config/content/newsroom"
    And I fill in "newsroom_universe_id" with "dae"
    And I press "Save configuration"
    Then I should see "The configuration options have been saved."
    When I press "Rebuild importers"
    Then I should see "Newsroom importers have been successfully recreated."

  Scenario: Checks generated importers
    Given I am logged in as a user with the "administrator" role
    When I visit "import"
    Then I should see "Newsroom Items Multilanguage"
    And I should see "Newsroom Services Multilingual"
    And I should see "Newsroom Topics Multilingual"
    And I should see "Newsroom Type Multilingual"
