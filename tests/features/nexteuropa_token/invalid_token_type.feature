@api
Feature: Prevent using not defined token types in Nexturopa Tokens
  In order to check that we are not using token types that are not defined
  As an administrator
  I should not see any token warning in the status report page

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: Status report doesn't show any Token warning
    When I go to "admin/reports/status"
    And I should not see "The following token types are not defined but have tokens"
