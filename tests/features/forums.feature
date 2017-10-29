@api
Feature: Forums
  In order to test forums feature functionality
  As an administrator
  I want to use the forum feature

  Background:
    Given the module is enabled
      | modules |
      | forum |
    And I am logged in as a user with the 'administrator' role

  @api
  Scenario: Setting up forum structure.Visit the Forums page to set up containers and forums to hold your discussion topics.
    Given I go to "/admin/structure/forum_en"
    And I should see the text "Forums contain forum topics. Use containers to group related forums."
    And I should see the text "General discussion"
    Then I click "Add container"
    And I should see the text "Use containers to group related forums."
    And I fill in "Container name" with "Container name test"
    And I select "General discussion" from "Parent"
    And I press the "Save" button
    And I should see the text "Created new forum container"
    And I should see the text "test"
    And I should see the text "edit container"
    Then I go to "/admin/structure/forum_en"
    And I should see the text "Forums contain forum topics. Use containers to group related forums."
    Then I click "Add forum"
    And I should see the text "A forum holds related forum topics."
    And I fill in "Forum name" with "Forum name test"
    And I select "General discussion" from "Parent"
    And I press the "Save" button
    And I should see the text "Created new forum"
    And I should see the text "test"
    And I should see the text "edit forum"
  @api
  Scenario: Starting a discussion. The Forum topic link on the Add new content page creates the first post of a new threaded discussion, or thread.
    Given I go to "/forums/general-discussion_en"
    And I should see the text "test"
    And I should see the text "Forum name test"
    Then I go to "/forums/forum-name-test_en"
    And I should see the text "Add new Forum topic"
    Then I click "Add new Forum topic"
    And I should see the text "Create Forum topic"
    And I fill in "Subject" with "Subject test"
    And I select "General discussion" from "Forums"
    And I press the "Save" button
    And I should see the text "Subject test"
    And I should see the text "Forum topic subject test has been created."
    #And can add a new comment
    And I fill in "Subject" with "Subject comment test"
    And I fill in "Comment" with "Comment test content"
    And I press the "Save" button
    And I should see the text "Your comment has been posted."
    And I should see the text "Subject comment test"

  @api
  Scenario: Navigation. Enabling the Forum module provides a default Forums menu item in the navigation menu that links to the Forums page.
    Given I go to "/admin/structure/menu/manage/navigation_en"
    And I should see the text "Forum topic"
    And I should see the text "Forums"

  @api
  Scenario: Moving forum topics. A forum topic (and all of its comments) may be moved between forums by selecting a different forum while editing a forum topic. When moving a forum topic between forums, the Leave shadow copy option creates a link in the original forum pointing to the new location.
    Given I go to "/admin/structure/forum_en"
    #Forum 1
    Then I go to "/admin/structure/forum_en"
    And I should see the text "Forums contain forum topics. Use containers to group related forums."
    Then I click "Add forum"
    And I should see the text "A forum holds related forum topics."
    And I fill in "Forum name" with "Forum name test"
    And I select "General discussion" from "Parent"
    And I press the "Save" button
    And I should see the text "Created new forum"
    And I should see the text "test"
    And I should see the text "edit forum"
    #Forum 2
    Then I click "Add forum"
    And I should see the text "A forum holds related forum topics."
    And I fill in "Forum name" with "Forum name test 2"
    And I select "General discussion" from "Parent"
    And I press the "Save" button
    And I should see the text "Created new forum"
    And I should see the text "test"
    And I should see the text "edit forum"
    #Topic on forum 1
    Then I go to "/forums/forum-name-test_en"
    Then I click "Add new Forum topic"
    And I should see the text "Create Forum topic"
    And I fill in "Subject" with "Subject test"
    And I press the "Save" button
    And I should see the text "Subject test"
    And I should see the text "Forum topic subject test has been created."
    #Move leaving a shadow copy
    Then I click "Edit"
    And I should see the text "Edit Forum topic Subject test"
    Then I check "Leave shadow copy"
    And I select "Forum name test 2" from "Forums"
    And I press the "Save" button
    And I should see the text "Forum topic subject test has been updated."
    #Issue https://www.drupal.org/node/1123866
    #Then I go to "/forums/forum-name-test_en"
    #And I should see the text "This topic has been moved"
    #Then I go to "/forums/forum-name-test-2_en"
    #And I should see the text "Subject test"
  @api
  Scenario: Locking and disabling comments. Selecting Closed under Comment settings while editing a forum topic will lock (prevent new comments on) the thread. Selecting Hidden under Comment settings while editing a forum topic will hide all existing comments on the thread, and prevent new ones.
    Given I go to "/forums/general-discussion_en"
    Then I click "Add new Forum topic"
    #New forum topic
    And I should see the text "Create Forum topic"
    And I fill in "Subject" with "Subject test"
    And I press the "Save" button
    And I should see the text "Subject test"
    And I should see the text "Forum topic subject test has been created."
    #New comment
    And I fill in "Subject" with "Subject comment test"
    And I fill in "Comment" with "Comment test content"
    And I press the "Save" button
    And I should see the text "Your comment has been posted."
    #Close comments
    Then I click "Edit"
    When I select the radio button "Closed Users cannot post comments, but existing comments will be displayed." with the id "edit-comment-1"
    And I press the "Save" button
    And I should see the text "Forum topic Subject test has been updated."
    And I should not see the text "Add new comment"
    #Hide comments
    Then I click "Edit"
    When I select the radio button "Hidden Comments are hidden from view." with the id "edit-comment-0"
    And I press the "Save" button
    And I should see the text "Forum topic Subject test has been updated."
    And I should not see the text "Replies"
