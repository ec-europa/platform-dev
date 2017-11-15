@api @javascript
Feature: Wiki
  In order to allow users to create and use the wiki
  As a site administrator
  I want to make sure auhtenticated users with proper permissions can create wiki pages

  Background:
    Given users:
      | name          | mail                 | pass         | roles         |
      | administrator | admin@ecample.com    | password123  | administrator |
      | contribuser   | contrib@example.com  | password456  | contributor   |
    And these featureSet are enabled
      | featureSet     |
      | Wiki           |

  Scenario: Anonymous user cannot create wiki pages
    Given I am an anonymous user
    When I go to "node/add/wiki"
    Then I should see the text "Access Denied"

  Scenario: Contributor user can create and wiki pages
    Given I am logged in as "contribuser"
    When I go to "node/add/wiki"
    Then I should see the text "Title"
    When I fill in "Title" with "New Wiki Page"
    And I press the "Save" button
    And I go to "content/new-wiki-page_en"
    Then I should see the text "New Wiki Page"
    When I click "Edit draft"
    Then I should see the text "Title"
    When I fill in "Title" with "Edited Wiki page"
    And I press the "Save" button
    And I go to "content/edited-wiki-page_en"
    Then I should see the text "Edited Wiki Page"