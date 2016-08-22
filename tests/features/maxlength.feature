Feature: Check the feature Maxlength
  In order to check the functionality of limiting and validating their maximum length in the edit form.
  As an administrator
  I want to check the maxlength.

  @api
  Scenario: Contributor User can check the maxlength counts (without the tags and specifics characters) and Administrator User can check his bypass.
    Given the module is enabled
      | modules                 |
      | multisite_maxlength     |
    And I am logged in as a user with the 'administrator' role
    When I create a new "text_long" field named "test_maxlength" on "article"
    When I go to "/admin/structure/types/manage/article/fields/test_maxlength"
    And I fill in "edit-instance-widget-settings-maxlength-js" with "10"
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
    When I am logged in as a user with the 'administrator' role
    And I go to "/node/add/article"
    And I fill in "Title" with "Page title"
    And I fill in "test_maxlength" with "AAAAAAAAAAAA"
    And I press "Save"
    Then I should see the success message "Article Page title has been created."
    And I should not see "cannot be longer than"
