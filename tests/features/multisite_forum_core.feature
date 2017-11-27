@api
Feature: multisite_forum_core
  In order to test multisite forum core feature functionality
  As an administrator
  I want to use the multisite forum core feature

  Background:
    Given the module is enabled
      | modules |
      | multisite_forum_core |
    Given I am logged in as a user with the 'administrator' role

  @api
  Scenario: Initializes taxonomies and content type.
    Given the vocabulary forums exists
    Given I go to "/admin/structure/taxonomy/forums"
    And I should see the text "Forums"
    And I should see the text "No terms available"
    Then I should be able to edit a discussion
    Given I go to "/admin/structure/types/manage/discussion"
    And I should see the text "discussion"
    And I should see the text "A <em>discussion</em> starts a new discussion thread within a forum."
    Given I go to "/admin/structure/types/manage/discussion/fields"
    #field with machine name"
    And I should see the text "taxonomy_forums"
  @api
  Scenario: Tests discussions.
    Given users:
       | name  | mail               | pass         | roles       |
       | user1 | user1@example.com  | password123  | contributor |
       | user2 | user2@example.com  | password456  | contributor |
    Then I go to "/admin/structure/taxonomy/forums/add_en"
    And I fill in "Name" with "SimpleTest Forum"
    And I fill in "Description" with "Test forum"
    And I press the "Save" button
    And I should see the text "Created new term SimpleTest Forum."
    When I am logged in as "user1"
    # User can post a forum topic.
    Given I go to "/node/add/discussion"
    And I should see the text "Create Discussion"
    And I fill in "title" with "discussion test"
    And I select "SimpleTest Forum" from "Forums"
    And I press the "Save" button
    And I should see the text "discussion test"
    And I should see the text "Discussion discussion test has been created."
    #Check user can edit and delete his own post.
    Then I click "Edit"
    And I should see the text "Edit Discussion discussion test"
    And I press the "Delete" button
    And I should see the text "Are you sure you want to delete discussion test?"
    And I press the "Delete" button
    And I should see the text "Welcome to NextEuropa"
    And I should see the text "Discussion discussion test has been deleted."
    #Check if user cannot edit post of another user.
    When I am logged in as "user1"
    Given I go to "/node/add/discussion"
    And I should see the text "Create Discussion"
    And I fill in "title" with "discussion test"
    And I select "SimpleTest Forum" from "Forums"
    And I press the "Save" button
    And I should see the text "discussion test"
    And I should see the text "Discussion discussion test has been created."
    #Check if user cannot edit post of another user.
    When I am logged in as "user2"
    Given I go to "/discussion/discussion-test"
    Then the response should not contain "nav nav-tabs nav-justified tabs-primary"
    Given I go to "/node/4/edit_en"
    Then the response status code should be 403
