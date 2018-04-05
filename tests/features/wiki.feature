@api
Feature: Wiki
  In order to allow users to create and use the wiki
  As a site administrator
  I want to make sure authenticated users with proper permissions can create wiki pages

  Background:
    Given these featureSet are enabled
      | featureSet     |
      | Wiki           |

  Scenario: Anonymous user cannot create wiki pages
    Given I am an anonymous user
    When I go to "node/add/wiki"
    Then I should see the text "Access Denied"

  Scenario: Contributor user can create and wiki pages
    Given I am logged in as a user with the "contributor" role
    When I go to "node/add/wiki"
    And I fill in "Title" with "New Wiki Page"
    And I press the "Save" button
    And I go to "content/new-wiki-page_en"
    Then I should see the text "New Wiki Page"
    When I click "Edit draft"
    And I fill in "Title" with "Edited Wiki page"
    And I press the "Save" button
    And I go to "content/edited-wiki-page_en"
    Then I should see the text "Edited Wiki Page"
