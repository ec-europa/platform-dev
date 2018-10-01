@api @communities @javascript @maximizedwindow
Feature: Wiki communities
  In order to allow users to create and use the wiki on communities profile
  As a site administrator
  I want to make sure authenticated users with proper permissions can create wiki pages on their communities

  Background:
    Given these featureSet are enabled
      | featureSet     |
      | Wiki           |
    And "community" content:
      | title             | workbench_moderation_state_new | status | language |
      | Community Example | published                      | 1      | en      |

  @ec_resp_theme
  Scenario: An administrator user can create a wiki on a community
    Given I am logged in as a user with the "administrator" role
    When I go to "community/community-example"
    And I click "Create content"
    And I click "Wiki" in the "sidebar_left" region
    And I fill in "Title" with "New Wiki Page"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press the "Save" button
    And I go to "community/community-example"
    And I click "Wikis" in the "sidebar_left" region
    Then I should see the text "New Wiki Page"

  @ec_europa_theme
  Scenario: An administrator user can create a wiki on a community
    Given I am logged in as a user with the "administrator" role
    When I go to "community/community-example"
    And I click "Wiki" in the "sidebar_left" region
    And I fill in "Title" with "New Wiki Page"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press the "Save" button
    And I go to "community/community-example/wiki"
    Then I should see the text "New Wiki Page"

  @ec_resp_theme
  Scenario: A contributor user added to a community can create a wiki on that community
    Given users:
      | name             | roles       |
      | contributor_user | contributor |
    And I am logged in as "contributor_user"
    And I have the "member" role in the "Community Example" group
    When I go to "community/community-example"
    And I click "Create content"
    And I click "Wiki" in the "sidebar_left" region
    And I fill in "Title" with "New Wiki Page"
    And I press the "Save" button

    When I am logged in as a user with the "administrator" role
    And I go to "community/community-example/wiki/new-wiki-page"
    And I select "Published" from "Moderation state"
    And I press the "Apply" button

    When I am logged in as "contributor_user"
    And I go to "community/community-example"
    And I click "Wikis" in the "sidebar_left" region
    Then I should see the text "New Wiki Page"

  @ec_europa_theme
  Scenario: A contributor user added to a community can create a wiki on that community
    Given users:
      | name             | roles       |
      | contributor_user | contributor |
    And I am logged in as "contributor_user"
    And I have the "member" role in the "Community Example" group
    When I go to "community/community-example"
    And I click "Wiki" in the "sidebar_left" region
    And I fill in "Title" with "New Wiki Page"
    And I press the "Save" button

    When I am logged in as a user with the "administrator" role
    And I go to "community/community-example/wiki/new-wiki-page"
    And I select "Published" from "Moderation state"
    And I press the "Apply" button

    When I am logged in as "contributor_user"
    And I go to "community/community-example/wiki"
    Then I should see the text "New Wiki Page"
