@api
Feature: Text formats configuration
  In order to input text in the website
  As a user
  I need specific text formats to be available and correctly configured

  Background:
    Given I am logged in as a user with the 'administrator' role

  @api
  Scenario: Text formats should be available
    When I go to "admin/config/content/formats"
    Then I should see "Full HTML"
    And I should see "Filtered HTML"
    And I should see "Basic HTML"
    And I should see "Plain text"
