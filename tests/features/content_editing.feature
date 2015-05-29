Feature: Content editing
  In order to manage the content on the website
  As an editor
  I want to be able to create, edit and delete content

  @api
  Scenario: Align content to the right
    Given I am logged in as a user with the 'administrator' role
    When I go to "node/add/page"
    And I fill in "Title" with "The right way is the right way"
    And I fill in "Body" with "<p style=\"text-align: right;\">The right way</p>"
    And I press "Save"
    Then the response should contain "<p style=\"text-align: right;\">The right way</p>"
