@api
Feature: Editorial workflow - Admin
  In order to control the editorial's functionality
  As an Administrator
  I want to be able to configure roles/permissions on user.

  Background:
    Given I am logged in as a user with the 'administrator' role
    And users:
      | field_firstname | field_lastname | name           | mail                       | status |
      | Editorial       | User           | editorial_user | eu_initial@example.com | 1      |

  Scenario: Add/remove the "editorial team member" role by adding/removing OG membership to a user from the profile edit form.
    When I go to "admin/people"
    And I click "edit" in the "Editorial User" row
    And I fill in "edit-og-user-node-und-0-admin-0-target-id" with "Global editorial team (1)"
    And I fill in "edit-mail" with "eu_updated@example.com"
    And I press "Save"
    Then I should see "The changes have been saved."
    When I click "edit" in the "Editorial User" row
    Then the "editorial team member" checkbox should be checked
    And the "E-mail address" field should contain "eu_updated@example.com"
    And I fill in "edit-og-user-node-und-0-admin-0-target-id" with ""
    And I press "Save"
    Then I should see "The changes have been saved."
    When I click "edit" in the "Editorial User" row
    Then the "editorial team member" checkbox should not be checked

  Scenario: Add/remove the "editorial team member" role by adding/removing OG membership to a user from the OG people forms.
    When I go to "group/node/1/admin/people/add-user"
    And I fill in "edit-name" with "editorial_user"
    And I press "Add users"
    Then I should see the message "Editorial User has been added to the group Global editorial team."
    When I go to "admin/people"
    And I click "edit" in the "Editorial User" row
    Then the "editorial team member" checkbox should be checked
    When I go to "group/node/1/admin/people"
    And I click "remove" in the "Editorial User" row
    And I press "Remove"
    Then I should see the message "The membership was removed."
    When I go to "admin/people"
    And I click "edit" in the "Editorial User" row
    Then the "editorial team member" checkbox should not be checked

  Scenario: Add/remove the "editorial team member" role by blocking/unblocking the OG membership.
    When I go to "group/node/1/admin/people/add-user"
    And I fill in "edit-name" with "editorial_user"
    And I press "Add users"
    Then I should see the message "Editorial User has been added to the group Global editorial team."
    When I go to "group/node/1/admin/people"
    And I click "edit" in the "Editorial User" row
    And I select "Blocked" from "Status"
    And I press "Update membership"
    Then I should see the message "The membership has been updated."
    When I go to "admin/people"
    And I click "edit" in the "Editorial User" row
    Then the "editorial team member" checkbox should not be checked
    When I go to "group/node/1/admin/people"
    And I click "edit" in the "Editorial User" row
    And I select "Active" from "Status"
    And I press "Update membership"
    Then I should see the message "The membership has been updated."
    When I go to "admin/people"
    And I click "edit" in the "Editorial User" row
    Then the "editorial team member" checkbox should be checked
