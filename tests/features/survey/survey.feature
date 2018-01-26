@api
Feature: Survey Standard test
  In order to protect the integrity of the website
  As a product owner
  I want to make sure only authenticated users can create surveys

  Background:
    And the module is enabled
      | modules         |
      | survey_standard |

  Scenario: Testing survey standard main page from nav-bar menu
    Given I am logged in as a user with the 'administrator' role
    When I am on the homepage
    Then I should see the link "Surveys"
    When I click "Surveys"
    Then I should see "Participate or review surveys"

  Scenario: Make sure we can create Survey
    Given I am logged in as a user with the 'contributor' role
    When I go to "node/add/webform"
    And I fill in "Title" with "The right way"
    And I fill in "Body" with "BDD TEST SURVEY PAGE"
    And I press "Save"
    Then the response should contain "The right way"
