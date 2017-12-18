@api
Feature: All sites should have a default configuration

  Scenario: Monday is the first day of the week
    Given I am logged in as a user with the "administrator" role
    When I am on "admin/config/regional/settings_en"
    Then "Monday" is selected in the "First day of week" options list
