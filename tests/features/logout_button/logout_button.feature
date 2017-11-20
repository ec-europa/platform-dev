@api
Feature: Logout button in main pages
  In order to check that there is a functional log out button in main pages
  As a registered user
  I want to be able to log out from the logout button in main pages

  Scenario Outline: Logged users can log out through the Log out button
    Given I am logged in as a user with the "<role>" role
    And   I am on the homepage
    Then  I should see the text "Log out"
    When  I click "Log out"
    Then  I should see the text "login"
    And   I should not see the text "Log out"

    Examples:
    | role          |
    | administrator |
    | editor        |
    | contributor   |


  Scenario: Anonymous user cannot see the Log out button
    Given I am not logged in
    And   I am on the homepage
    Then  I should not see the text "Log out"
