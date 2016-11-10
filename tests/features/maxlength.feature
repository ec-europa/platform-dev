@group:default
@api
Feature: Check the feature Maxlength
  In order to provides to fields of a content type the functionality of limiting and validating their maximum length in the edit form, before submission.
  As an administrator, Contributor and Editor User
  I want to control the maximum length in the input on the form before and after submission.

  Background:
    Given the module is enabled
      | modules                 |
      | multisite_maxlength     |

  Scenario: Contributor User can check the maxlength counts (without the tags and specific characters).
    Given I am logged in as a user with the 'administrator' role
    When I create a new "text_long" field named "test_maxlength" on "article"
    When I go to "/admin/structure/types/manage/article/fields/test_maxlength"
    And I fill in "Maximum length" with "10"
    And I check "Truncate html"
    And I press "Save settings"
    Then I should see the success message "Saved test_maxlength configuration."
    When I am logged in as a user with the 'contributor' role
    And I go to "/node/add/article"
    And I fill in "Title" with "Page title"
    And I fill in "test_maxlength" with "&&&&&&&&&&"
    And I press "Save"
    Then I should see the success message "Article Page title has been created."
    And I should not see "cannot be longer than"

  Scenario: Administrator User can check his bypass.
    Given I am logged in as a user with the 'administrator' role
    When I create a new "text_long" field named "test_maxlength" on "article"
    When I go to "/admin/structure/types/manage/article/fields/test_maxlength"
    And I fill in "Maximum length" with "10"
    And I check "Truncate html"
    And I press "Save settings"
    Then I should see the success message "Saved test_maxlength configuration."
    When I am logged in as a user with the 'administrator' role
    And I go to "/node/add/article"
    And I fill in "Title" with "Page title"
    And I fill in "test_maxlength" with "AAAAAAAAAAAA"
    And I press "Save"
    Then I should see the success message "Article Page title has been created."
    And I should not see "cannot be longer than"

