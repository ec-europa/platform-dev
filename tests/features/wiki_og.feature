@api @javascript @maximizedwindow
Feature: Community Wiki
  In order to access Communities Wikis
  As a group user
  I want to access wiki post

  Background:
    Given I run drush pmi nexteuropa_communities
    And the module is enabled
      | modules                   |
      | wiki_og                   |
    And I am logged in as a user with the "administrator" role
    And I go to "node/add/community"
    And I fill in "Title" with "Community test"
    And I click "Publishing options"
    And I select "Published" from "edit-workbench-moderation-state-new"
    And I press "Save"
    Then I should see "Community test"
    And I click "Create content"
    And I click "Wiki" in the "sidebar_left" region
    And I fill in "Title" with "Wiki test"
    And I click "Publishing options"
    And I select "Published" from "edit-workbench-moderation-state-new"
    And I press "Save"
    Then I should see "Wiki test"

  Scenario: A user with "access content" permissions should see the wiki list
    # Remove "access content" permissions from anonymous user
    Given I am an anonymous user
    When I go to "community/community-test/wiki"
    Then I should see "Wiki test"

  Scenario: A user without "access content" permissions should not see the wiki list
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/people/permissions/1"
    And I uncheck "edit-1-access-content"
    And I press "Save permissions"
    Then I should see "The changes have been saved."
    Then I am an anonymous user
    And I go to "community/community-test/wiki"
    Then I should see "Access denied"

