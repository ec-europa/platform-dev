@api @javascript
Feature: Multiuser blog
  In order to allow users to create a blog
  As a user of the site
  I want to be able create blog post and comment on them

  Background:
    Given the module is enabled
      | modules         |
      | multi_user_blog |

  Scenario Outline: A user see published post on the blog list and the user blog tab and rate the post.
    Given users:
     | name             | mail                      | pass        | roles       |
     | contributor_user | contributor_user@user.com | password123 | contributor |
    And I am logged in as "contributor_user"
    And I am on "node/add/blog-post"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Post" with "<body>"
    And I click "Revision information"
    And I select "Needs Review" from "edit-workbench-moderation-state-new"
    And I press "Save"
    Then I should see the text "Blog post <title> has been created."
    Then I am logged in as a user with the "administrator" role
    And I am on "admin/workbench/moderate-all"
    And I click "<title>"
    And I select "Published" from "edit-state"
    And I press "Apply"
    Then I should see the text "Revision state: Published"
    Then I am logged in as "contributor_user"
    And I click "My account"
    And I click "Blog"
    Then I should see the text "<title>"
    And I click "<title>"
    Then I should see the text "<title>"
    And I should see the text "<body>"
    And I click "rate-button-4"
    Then I am logged in as a user with the "administrator" role
    And I click "Blogs"
    Then I should see the text "<title>"
    And I should see the text "<body>"
    And I click "<title>"
    And I click "Voting results"
    Then I should see "1" in the ".tableheader-processed .row-3" element

    Examples:
      | title                  | body                |
      | Created by contributor | Body by contributor |

  Scenario Outline: A contributor and a editor user can create blog posts and an administrator can publish them.
    Given I am logged in as a user with the "<role>" role
    And I am on "node/add/blog-post"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Post" with "<body>"
    And I click "Revision information"
    And I select "Needs Review" from "edit-workbench-moderation-state-new"
    And I press "Save"
    Then I should see the text "Blog post <title> has been created."
    Then I am logged in as a user with the "administrator" role
    And I am on "admin/workbench/moderate-all"
    And I click "<title>"
    And I select "Published" from "edit-state"
    And I press "Apply"
    Then I should see the text "Revision state: Published"

    Examples:
      | role          | title                    | body                  |
      | contributor   | Created by contributor   | Body by contributor   |
      | editor        | Created by editor        | Body by editor        |

  Scenario Outline: An administrator, contributor and editor user can create, edit and delete their own blog posts.
    Given I am logged in as a user with the "<role>" role
    And I am on "node/add/blog-post"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Post" with "<body>"
    And I press "Save"
    Then I should see the text "Blog post <title> has been created."
    And I click "Edit draft"
    And I fill in "Title" with "<title> - Update"
    And I press "Save"
    Then I should see the text "Blog post <title> - Update has been updated."
    And I click "Edit draft"
    And I press "Delete"
    Then I press "Delete"
    Then I should see the text "Blog post <title> - Update has been deleted."

    Examples:
      | role          | title                    | body                  |
      | administrator | Created by administrator | Body by administrator |
      | contributor   | Created by contributor   | Body by contributor   |
      | editor        | Created by editor        | Body by editor        |
