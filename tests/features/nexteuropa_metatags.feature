@api
Feature: Check Nexteuropa Metatags
  In order to check if Metatags is avalaible for user.
  As an administrator
  I want to check Metatags is configured.

  Background:
    Given the module is enabled
      | modules             |
      | nexteuropa_metatags |

  Scenario: Check that user roles have the appropriate permissions
    Given I am logged in as a user with the 'administrator' role
    Then I check that "user_administrator" have the permission for "edit meta tags"
    And I check that "user_administrator" have the permission for "administer meta tags"
    And I check that "user_contributor" have the permission for "edit meta tags"
    And I check that "user_contributor" have not the permission for "administer meta tags"
    And I check that "user_editor" have the permission for "edit meta tags"
    And I check that "user_editor" have not the permission for "administer meta tags"
