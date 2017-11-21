@api
Feature: Logout button in main pages
  In order to check that there is a functional log out button in main pages
  As a registered user
  I want to be able to log out from the logout button in main pages

  Background:
    Given I am viewing an "page" content:
      | title              | Page test      |
      | body               | page test body |
      | status             | 1              |
      | moderation state   | published      |
      | revision state     | published      |
    Given I am viewing an "article" content:
      | title              | Article test      |
      | body               | article test body |
      | status             | 1              |
      | moderation state   | published      |
      | revision state     | published      |

  Scenario Outline: Logged users can log out through the Log out button
    Given I am logged in as a user with the "<role>" role
    And   I am on "<page>"
    Then  I should see the text "Log out"
    When  I click "Log out"
    Then  I should see the text "login"
    And   I should not see the text "Log out"

    Examples:
      | page                  | role          |
      | homepage              | administrator |
      | homepage              | editor        |
      | homepage              | contributor   |
      | /user                 | administrator |
      | /user                 | editor        |
      | /user                 | contributor   |
      | /admin/workbench      | administrator |
      | /admin/workbench      | editor        |
      | /admin/workbench      | contributor   |
      | /content/page_test    | administrator |
      | /content/page_test    | editor        |
      | /content/page_test    | contributor   |
      | /content/article_test | administrator |
      | /content/article_test | editor        |
      | /content/article_test | contributor   |

  Scenario Outline: Anonymous user cannot see the Log out button
    Given I am not logged in
    And   I am on "<page>"
    Then  I should not see the text "Log out"

    Examples:
      | page                  |
      | homepage              |
      | /user                 |
      | /admin/workbench      |
      | /content/page_test    |
      | /content/article_test |
