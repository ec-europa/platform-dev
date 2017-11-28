@api @communities
Feature: multisite_forum_community
  In order to test multisite forum community feature functionality
  As an administrator
  I want to use the multisite forum community feature



  Scenario: Test testDiscussionOGCreation
    Given the module is enabled
    | modules |
    #forum dependencies or https://www.drupal.org/project/drupal/issues/2209577
    #and https://www.drupal.org/forum/support/post-installation/2012-04-15/problem-with-setting-up-forums
    | forum |
    | multisite_forum_community |
    Given users:
     | name  | mail               | pass         | roles       |
     | user1 | user1@example.com  | password123  | administrator |
     | user2 | user2@example.com  | password456  | administrator |
    #Test initialization
    Given I am logged in as a user with the 'administrator' role
    When I go to "/admin/structure/types/manage/discussion/fields"
    And I should see the text "og_group_ref"
    And I should see the text "group_content_access"
    #Create content of community type.
    Given I am logged in as "user1"
    When I go to "/node/add/community"
    And I fill in "Title" with "Sample Community"
    And I fill in "Body" with "Community body"
    And I press the "Save" button
    And I should see the text "Community Sample Community has been created."
    And I select "Published" from "edit-state"
    And I press the "Apply" button
    And I should see the text "Sample Community"
    #Check if group manager has link to forum management page.
    Given I have the "community_manager" role in the "Sample Community" group
    When I go to "/node/1/group"
    Then I should see the text "Sample Community"
    And I should see the text "Forums"
    And I should see the text "Manage manage group forums."
    #Manager can access forum management page.
    Given I go to "/group/node/1/admin/forum"
    Then the response status code should be 200
    And I should see the text "Forums"
    #Manager can access forum term creation page.
    Given I go to "/group/node/1/admin/forum/add/forum"
    Then the response status code should be 200
    And I should see the text "Forums"
    And I should see the text "Forum name"
    And I fill in "Forum name" with "Forum name test"
    And I press the "Save" button
    Then I should see the text "Created new forum Forum name test."
    #Manager can access forum term editing page.
    Given I go to "/group/node/1/admin/forum/edit/forum/37"
    Then the response status code should be 200
    And I should see the text "Edit forum"
    And I should see the text "Forum name"
    And I should see the text "Forum name test"
    And I fill in "Forum name" with "Forum name test 2"
    And I press the "Save" button
    And I should see the text "The forum Forum name test 2 has been updated."
    #Manager can post a forum topic.
    Given I go to "/node/add/discussion"
    And I fill in "Title" with "Discussion test 1"
    And I fill in "Body" with "Discussion test 1 body"
    And I select "General discussion" from "Forums"
    And I press the "Save" button
    And I should see the text "Discussion Discussion test 1 has been created."
    #Manager can edit is own forum topics
    Given I go to "/node/2/edit"
    And I should see the text "Edit Discussion Discussion test 1"
    And I fill in "Title" with "Discussion test 1 edit"
    And I fill in "Body" with "Discussion test 1 body edit"
    And I press the "Save" button
    Then the response should contain "Discussion <em class=\"placeholder\">Discussion test 1 edit</em> has been updated.</div>"
    #The user 2 is not a group member.
    Given I go to "/group/node/1/admin/people"
    And I should see the text "user1"
    And I should not see the text "user2"
    #Make the user2 a member
    Given I go to "/user/7/edit"
    And I fill in "edit-field-firstname-und-0-value" with "user2"
    And I fill in "edit-field-lastname-und-0-value" with "user2"
    And I select "Sample Community" from "edit-og-user-node-und-0-default"
    And I press the "Save" button
    And I should see the text "The changes have been saved."
    #The user 2 is a group member.
    Given I go to "/group/node/1/admin/people"
    And I should see the text "user1"
    And I should see the text "user2"
    #The user 2 can view the group.
    When I am logged in as "user2"
    Given I have the "administrator member" role in the "Sample Community" group
    Given I go to "/node/1"
    Then the response status code should be 200
    And I should see the text "Sample Community"
    #Check if group member can access forum topic creation page.
    Given I go to "/group/node/1/admin/forum"
    Then the response status code should be 200
    And I should see the text "Forums"
    And I should see the text "Add forum"
