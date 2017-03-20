@communities
Feature: Jenkins test
  In order to test exception on Jenkins, This test is designed to always fail

  @api
  Scenario: Groups list
    Given I am logged in as a user with the 'administrator' role
    When I go to "communities_directory"
    Then I should see the heading "Mahna Mahna to too to to"