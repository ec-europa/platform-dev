@api
Feature: Page content type
  In order to manage articles on the website
  As an editor
  I want to be able to create, edit and delete articles

  @api
  Scenario: Create a page
    Given "Tags" terms:
      | name              | weight | description   |
      | State aid         | -10    | A term.       |
      | Corporate tax law | 5      | A fine term.  |
    And I am logged in as a user with the 'editor' role
    When I go to "node/add/page"
    And I fill in "Title" with "EC decides tax advantages for Fiat are illegal"
    And I fill in "Body" with "Commissioner states tax rulings are not in line with state aid rules."
    And I fill in "Tags" with "State aid, Corporate tax law"
    And I press the "Save" button
    Then I should see the success message "Basic page EC decides tax advantages for Fiat are illegal has been created."
    And I should see the link "State aid"
    And I should see the link "Corporate tax law"
    And I should see the heading "EC decides tax advantages for Fiat are illegal"
    And I should see the text "Commissioner states tax rulings are not in line with state aid rules."