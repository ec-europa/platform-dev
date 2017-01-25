@api @wip
Feature: Editorial workflow - Admin
  In order to control the editorial's functionality
  As an Administrator
  I want to be able to configure roles/permissions on user.

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario Outline: Add/remove the Editorial Group Membership to an user.
    When I go to "admin/people"
    And I click "edit" in the "<username>" row
    And I fill in "edit-og-user-node-und-0-admin-0-target-id" with "Global editorial team (1)"
    And I press "Save"
    Then I should see "The changes have been saved."
    When I click "edit" in the "<name>" row
    Then the "editorial team member" checkbox should be checked
    And I fill in "edit-og-user-node-und-0-admin-0-target-id" with ""
    And I press "Save"
    Then I should see "The changes have been saved."
    When I click "edit" in the "<name>" row
    Then the "editorial team member" checkbox should not be checked

    Examples:
      | username                | name              |
      | user_administrator      | John Smith        |
      | user_contributor        | John Doe          |
      | user_editor             | John Blake        |
