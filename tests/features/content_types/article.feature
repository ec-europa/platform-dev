@api
Feature: Article content type
  In order to manage articles on the website
  As an editor
  I want to be able to create, edit and delete articles

  @api
  Scenario: Create an article
    Given "Tags" terms:
      | name              | weight | description   |
      | State aid         | -10    | A term.       |
      | Corporate tax law | 5      | A fine term.  |
    Given I am viewing an "article" content:
      | title            | EC decides tax advantages for Fiat are illegal                        |
      | body             | Commissioner states tax rulings are not in line with state aid rules. |
      | tags             | State aid, Corporate tax law                                          |
      | moderation state | published                                                             |
    Then I should see the link "State aid"
    And I should see the link "Corporate tax law"
    And I should see the heading "EC decides tax advantages for Fiat are illegal"
    And I should see the text "Commissioner states tax rulings are not in line with state aid rules."
    And I should see the text "Published by Anonymous"
