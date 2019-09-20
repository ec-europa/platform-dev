@api @javascript @communities @theme_wip @maximizedwindow
Feature: Multisite registration og
  In order to add registration option to different content types
  As different types of users
  I want to be able to add a registration field in an article, register users and manage registrations

  Background:
    Given I am logged in as a user with the 'administrator' role
    And   the module is enabled
      | modules                         |
      | multisite_registration_core     |
      | multisite_registration_og       |
    And I am viewing a "community" content:
      | title                          | Public community 1  |
      | workbench_moderation_state     | published           |
      | workbench_moderation_state_new | published           |


  Scenario: as administrator I can add a registration field to a content type
    Given I am on "/admin/structure/types/manage/article/fields"
    When  I fill in "New field label" with "Registration field test"
    And   I select "registration" from "edit-fields-add-new-field-type"
    And   I press "Save"
    And   I go to "/admin/structure/types/manage/article/fields/field_registration_field_test"
    Then  I should see the text "Registration field test"
    When  I check "Enable"
    And   I fill in "Spaces allowed" with "1"
    And   I check "Allow multiple registrations"
    And   I check "authenticated user"
    And   I check "administrator"
    And   I check "contributor"
    And   I check "editor"
    And   I select "multisite_registration" from "edit-field-registration-field-test-und-0-registration-type"
    And   I press "Save settings"
    Then  I should see the text "Saved Registration field test configuration"
    When  I go to "/node/add/article"
    Then  I should see "Registration field test"
    And   I should see "multisite_registration"

  Scenario: as administrator I can enable registration when I create a new content with registration field
    Given I am on "/node/add/article"
    Then  I should see "Registration field test"
    And   I should see "multisite_registration"
    When  I fill in the content's title with "Registration Article"
    When  I select "multisite_registration" from "Registration field test"
    And   I click "Publishing options"
    And   I select "Published" from "Moderation state"
    And   I press "Save"
    And   I should see the text "Article Registration Article has been created"
    And   I should see the text "Revision state: Published"
    Given I am logged in as a user with the 'contributor' role
    When  I go to "/community/articles/registration-article"
    And   I click "Register"
    Then  I should see "This registration is for:"

  Scenario: as administrator I can disable registration when I create a new content with registration field
    Given I am on "/node/add/article"
    Then  I should see "Registration field test"
    When  I fill in the content's title with "Registration Article"
    When  I select "-- Disable Registrations --" from "Registration field test"
    And   I click "Publishing options"
    And   I select "Published" from "Moderation state"
    And   I press "Save"
    And   I should see the text "Article Registration Article has been created"
    And   I should see the text "Revision state: Published"
    Given I am logged in as a user with the 'contributor' role
    When  I go to "/community/articles/registration-article"
    And   should not see "Register"

  # In ec_europa user is registered, but we cannot see the blocks for "Registered user" and "Registration management"
  Scenario: as authenticated user I can register myself or other user in a content
    Given I am viewing an "article" content:
      | title              | Registration Article     |
      | body               | registration body        |
      | status             | 1                        |
      | moderation state   | published                |
      | revision state     | published                |
    Given I am logged in as a user with the 'contributor' role and I have the following fields:
      | username | contributor |
      | name | contributor |
      | mail | contributor@test.com |
    When  I go to "/community/articles/registration-article"
    Then  I should see the text "Registration Article"
    And   I should see "Register"
    When  I click "Register"
    And   I select "Other account" from "This registration is for:"
    And   I fill in "User" with "contributor"
    And   I press "Save Registration"
    Then  I should see the text "Registration has been saved"
    When  I go to "/community/articles/registration-article"
    Then  I should see the text "Registered user"
    And   I should see the text "Registration management"
    Then  I should see "Cancel my registration"
    Given I am logged in as a user with the "administrator" role
    When  I go to "/community/articles/registration-article"
    And   I click "Manage Registrations"
    And   I click "Registrations"
    Then  I should see the text "List of registrations for Registration Article"
    And   I should see the link "contributor@test.com"

  # In ec_europa user is registered, but we cannot see the blocks for "Registered user" and "Registration management"
  Scenario: as authenticated user I can register other person by email in a content
    Given I am viewing an "article" content:
      | title              | Registration Article     |
      | body               | registration body        |
      | status             | 1                        |
      | moderation state   | published                |
      | revision state     | published                |
    Given I am logged in as a user with the 'contributor' role and I have the following fields:
      | username | contributor |
      | name | contributor |
      | mail | contributor@test.com |
    When  I go to "/community/articles/registration-article"
    Then  I should see the text "Registration Article"
    And   I should see "Register"
    When  I click "Register"
    And   I select "Other person" from "This registration is for:"
    And   I fill in "Email" with "test@test.com"
    And   I press "Save Registration"
    Then  I should see the text "Registration has been saved"
    When  I go to "/community/articles/registration-article"
    Given I am logged in as a user with the "administrator" role
    When  I go to "/community/articles/registration-article"
    And   I click "Manage Registrations"
    And   I click "Registrations"
    Then  I should see the text "List of registrations for Registration Article"
    And   I should see the link "test@test.com"

  # In ec_europa user is registered, but we cannot see the blocks for "Registered user" and "Registration management"
  Scenario: user cancels registration in a content
    Given I am viewing an "article" content:
      | title              | Registration Article  |
      | author             | admin                 |
      | body               | registration body     |
      | status             | 1                     |
      | moderation state   | published             |
      | revision state     | published             |
    Given I am logged in as a user with the 'contributor' role and I have the following fields:
      | username | contributor          |
      | name     | contributor          |
      | mail     | contributor@test.com |
    When  I go to "/community/articles/registration-article"
    When  I click "Register"
    And   I select "Other account" from "This registration is for:"
    And   I fill in "User" with "contributor"
    And   I press "Save Registration"
    When  I go to "/community/articles/registration-article"
    Then  I should see "Cancel my registration"
    When  I click "Cancel my registration"
    Then  I should see the text "Are you sure you want to delete registration"
    When  I press "Delete"
    Given I am logged in as a user with the "administrator" role
    When  I go to "/community/articles/registration-article"
    And   I click "Manage Registrations"
    And   I click "Registrations"
    Then  I should see the text "There are no registrants for Registration Article"

  Scenario: anonymous user without permission can access content and see registered users, but he cannot register himself
    Given I am viewing an "article" content:
      | title              | Registration Article  |
      | author             | admin                 |
      | body               | registration body     |
      | status             | 1                     |
      | moderation state   | published             |
      | revision state     | published             |
    Given I am not logged in
    When  I go to "/community/articles/registration-article"
    And   I should not see the text "Registration management"
    And   I should not see the text "Register"

  # In ec_europa user is registered, but we cannot see the blocks for "Registered user" and "Registration management"
  Scenario: authenticated user without permission can access content and see registered users, but he cannot register himself
    Given I am viewing an "article" content:
      | title              | Registration Article  |
      | author             | admin                 |
      | body               | registration body     |
      | status             | 1                     |
      | moderation state   | published             |
      | revision state     | published             |
    Given I am logged in as a user with the 'contributor' role and I have the following fields:
      | username | contributor          |
      | name     | contributor          |
      | mail     | contributor@test.com |
    When  I go to "/community/articles/registration-article"
    When  I click "Register"
    And   I select "Other account" from "This registration is for:"
    And   I fill in "User" with "contributor"
    And   I press "Save Registration"
    And   I click "Log out"
    Given I am not logged in
    When  I go to "/community/articles/registration-article"
    And   I should not see the text "Registration management"
    But   I should see the text "Registered user"
    But   I should see the text "contributor"

  Scenario: authenticated user with permission to register cannot register in a content in which the close date has already finished
    Given I am logged in as a user with the 'administrator' role
    Given I am viewing an "article" content:
      | title              | Registration Article  |
      | author             | admin                 |
      | body               | registration body     |
      | status             | 1                     |
      | moderation state   | published             |
      | revision state     | published             |
    When  I go to "/community/articles/registration-article"
    And   I click "Manage Registrations"
    And   I click "Settings"
    And   I fill in "edit-scheduling-open-datepicker-popup-0" with "2017-10-30"
    And   I fill in "edit-scheduling-open-timeEntry-popup-1" with "10:00:00"
    And   I fill in "edit-scheduling-close-datepicker-popup-0" with "2017-10-31"
    And   I fill in "edit-scheduling-close-timeEntry-popup-1" with "10:00:00"
    And   I press "Save Settings"
    Given I am logged in as a user with the 'contributor' role and I have the following fields:
      | username | contributor2          |
      | name     | contributor2          |
      | mail     | contributor2@test.com |
    When  I go to "/community/articles/registration-article"
    Then  I should see "Register"
    When  I click "Register"
    Then  I should see the text "Sorry, registrations are no longer available"
