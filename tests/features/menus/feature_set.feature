@api
Feature: Feature set menu
  In order to easily enable a feature
  As an administrative user
  I want to have links to the most important pages in my user menu

  @api
  Scenario Outline: Test feature set screen as administrator
    Given I am logged in as a user with the "administrator" role
    When I am on the homepage
    And I click "<link>"
    Then I should see the heading "<heading>"

    Examples:
      | link                     | heading                  |
      | My workbench             | My Workbench             |
      | My account               | Myrrine Augusta          |
      | Manage translation tasks | Manage Translation Tasks |
      | Translate                | Translate                |
      | Log out                  | Welcome to NextEuropa    |
