@api @javascript @communities
Feature: Wiki
  In order to allow users to create and use the wiki on communities profile
  As a site administrator
  I want to make sure auhtenticated users with proper permissions can create wiki pages on their communities

  Background:
    Given users:
      | name          | mail                 | pass         | roles         |
      | administrator | admin@ecample.com    | password123  | administrator |
      | contribuser   | contrib@example.com  | password456  | contributor   |
    And these featureSet are enabled
      | featureSet     |
      | Wiki           |
    And 'Community' content:
      | title             | author        | workbench_moderation_state_new | workbench_moderation_state | language | status |
      | Community Example | administrator | published                      | published                  | en       | 1      |

  @theme_wip
  Scenario: An administrator user can create a wiki on a community
    When I am logged in as "administrator"
    And I use device with "1920" px and "1080" px resolution
    And I go to "community/community-example"
    And I click "Create content"
    And I click "Wiki" in the "sidebar_left" region
    Then I should see the text "Title"
    When I fill in "Title" with "New Wiki Page"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press the "Save" button
    And I go to "community/community-example"
    And I click "Wikis" in the "sidebar_left" region
    Then I should see the text "New Wiki Page"

  Scenario: A contributor user added to a community can create a wiki on that community
    When I am logged in as "contribuser"
    And I have the "member" role in the "Community Example" group
    And I use device with "1920" px and "1080" px resolution
    And I go to "community/community-example"
    And I click "Create content"
    And I click "Wiki" in the "sidebar_left" region
    Then I should see the text "Title"
    When I fill in "Title" with "New Wiki Page"
    And I press the "Save" button
    And I am logged in as "administrator"
    And I go to "community/community-example/wiki/new-wiki-page"
    And I select "Published" from "Moderation state"
    And I press the "Apply" button
    And I am logged in as "contribuser"
    And I go to "community/community-example"
    And I click "Wikis" in the "sidebar_left" region
    Then I should see the text "New Wiki Page"
