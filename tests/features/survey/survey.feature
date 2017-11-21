@api
Feature: Survey Standard test
  In order to protect the integrity of the website
  As a product owner
  I want to make sure only authenticated users can create surveys

Scenario: Testing survey standard main page from nav-bar menu

  Given these modules are enabled
    | modules                     |
    | survey_standard             |

  And I am logged in as a user with the "administrator" role
  And I am on the homepage
  Then I should see the link "Surveys"
  And I click "Surveys"
  Then I should see "Participate or review surveys"

Scenario Outline: Make sure we can create Survey
  Given I am logged in as a user with the "administrator" role
  And I visit "/node/add/webform_en"
  Then I enter "<title>" for "Title"
  And I fill in "Body" with "<content>"
  And I press "Save"
  Then the response should contain "<expected>"

  Examples:
    | title          | content                                    | expected                                        |
    | The right way  | BDD TEST SURVEY PAGE                       | The right way                                   |

 @javascript
Scenario: Make sure we can create Survey from Create content drop-down Menu

    Given these modules are enabled
      | modules                     |
      | survey_standard             |

    And I am logged in as a user with the "administrator" role
    And I visit "/survey"
    Then the response status code should be 200
    When I should see the link "Create content"
    Then I should see the link "Survey"
    And I click "Survey"
    And I should see "Create Survey"
