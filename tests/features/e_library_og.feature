@api @javascript @maximizedwindow @communities
Feature: E-Library OG Content
  In order to access E-Library OG content
  As a user
  I need to have access to view content

  Background:
    Given I run drush pmi nexteuropa_communities
    And the module is enabled
      | modules                   |
      |  e_library_og             |
    And I am logged in as a user with the "administrator" role
    And I go to "node/add/community"
    And I fill in "Title" with "Community test"
    And I click "Publishing options"
    And I select "Published" from "edit-workbench-moderation-state-new"
    And I press "Save"
    And the cache has been cleared
    Then I should see "Community test"

  Scenario Outline: A user with "access content" permissions should see the wiki list
    Given I am logged in as a user with the "administrator " role
    And I visit the "community" content with title "Community test"
    And I click "Create content"
    And I click link "<link>" in the "#block-multisite-og-button-og-contextual-links" element
    And I fill in "Title" with "<title>"
    And I attach the file "/tests/files/logo.png" to "edit-field-document-und-0-upload"
    And I click "Publishing options"
    And I select "Published" from "edit-workbench-moderation-state-new"
    And I press "Save"
    When I go to "admin/people/permissions/2"
    And I check "edit-2-access-content"
    And I press "Save permissions"
    Then I should see "The changes have been saved."
    And I go to "admin/reports/status/rebuild"
    And I press "Rebuild permissions"
    And I am logged in as a user with the "authenticated user" role
    And I go to "<content_path>"
    Then I should see "<title>"
      Examples:
      | link     |  title          | content_path                       |
      | Document |  Document test  | community/community-test/e_library |
      
  Scenario Outline: A user without "access content" permissions should not see the wiki list
    Given I am logged in as a user with the "administrator" role
    When I visit the "community" content with title "Community test"
    And I click "Create content"
    And I click link "<link>" in the "#block-multisite-og-button-og-contextual-links" element
    And I fill in "Title" with "<title>"
    And I attach the file "/tests/files/logo.png" to "edit-field-document-und-0-upload"
    And I click "Publishing options"
    And I select "Published" from "edit-workbench-moderation-state-new"
    And I press "Save"
    When I go to "admin/people/permissions/2"
    And I uncheck "edit-2-access-content"
    And I press "Save permissions"
    Then I should see "The changes have been saved."
    And I go to "admin/reports/status/rebuild"
    And I press "Rebuild permissions"
    And I am logged in as a user with the "authenticated user" role
    And I go to "<content_path>"
    Then I should see "Access denied"
      Examples:
      | link     |  title          | content_path                       |
      | Document |  Document test  | community/community-test/e_library |
