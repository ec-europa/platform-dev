@api @javascript @maximizedwindow
Feature: Community Content
  In order to access Communities content
  As a user
  I need to have access to view content

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

  Scenario Outline: A user with "access content" permissions should see the wiki list
    Given I am logged in as a user with the "administrator" role
    And I visit the "community" content with title "Community test"
    And I click "Create content"
    And I click "<link>" in the "sidebar_left" region
    And I fill in "Title" with "<title>"
    And I click on the element with xpath "//a[text()='Community']"
    And I select "Public - accessible to all site users" from "Group content visibility"
    And I click "Publishing options"
    And I select "Published" from "edit-workbench-moderation-state-new"
    And I press "Save"
    When I go to "admin/people/permissions/1"
    And I check "edit-1-access-content"
    And I press "Save permissions"
    Then I should see "The changes have been saved."
    Then I am an anonymous user
    And I go to "<content_path>"
    Then I should see "<title>"
      Examples:
      | link   |  title        | content_path                  |
      | Wiki   |  Wiki test    | community/community-test/wiki |

  Scenario Outline: A user without "access content" permissions should not see the wiki list
    Given I am logged in as a user with the "administrator" role
    When I visit the "community" content with title "Community test"
    And I click "Create content"
    And I click "<link>" in the "sidebar_left" region
    And I fill in "Title" with "<title>"
    And I click "Publishing options"
    And I select "Published" from "edit-workbench-moderation-state-new"
    And I press "Save"
    When I go to "admin/people/permissions/1"
    And I uncheck "edit-1-access-content"
    And I press "Save permissions"
    Then I should see "The changes have been saved."
    Then I am an anonymous user
    And I go to "<content_path>"
    Then I should see "Access denied"
      Examples:
      | link   |  title        | content_path                  |
      | Wiki   |  Wiki test    | community/community-test/wiki |
