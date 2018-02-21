@api @javascript @communities
Feature: Wiki communities
  In order to allow users to create and use the wiki on communities profile
  As a site administrator
  I want to make sure auhtenticated users with proper permissions can create wiki pages on their communities

  Background:
    Given these featureSet are enabled
      | featureSet     |
      | Wiki           |
    And "community" content:
      | title             | workbench_moderation_state_new | status | language |
      | Community Example | published                      | 1      | en      |

  @theme_wip
  Scenario: An administrator user can create a wiki on a community
    Given I am logged in as a user with the "administrator" role
    And I use device with "1920" px and "1080" px resolution
    When I go to "community/community-example"
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
    Given I am logged in as a user with the 'contributor' role
    And I have the "member" role in the "Community Example" group
    And I use device with "1920" px and "1080" px resolution
    When I go to "community/community-example"
    And I click "Create content"
    And I click "Wiki" in the "sidebar_left" region
    Then I should see the text "Title"
    When I fill in "Title" with "New Wiki Page"
    And I press the "Save" button
    Given I am logged in as a user with the "administrator" role
    When I go to "community/community-example/wiki/new-wiki-page"
    And I select "Published" from "Moderation state"
    And I press the "Apply" button
    Given I am logged in as a user with the "contributor" role
    When I go to "community/community-example"
    And I click "Wikis" in the "sidebar_left" region
    Then I should see the text "New Wiki Page"
