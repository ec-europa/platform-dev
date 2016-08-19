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
    When I go to "/admin/structure/types/manage/article/fields"
    And I fill in "edit-fields-add-new-field-label" with "Test Maxlength"
    And I fill in "edit-fields-add-new-field-field-name" with "test_maxlength"
    And I select "Content" from "edit-fields-add-new-field-parent"
    And I select "Long text" from "edit-fields-add-new-field-type"
    And I select "Text area (multiple rows)" from "edit-fields-add-new-field-widget-type"
    And I press "Save"
    Then I press "Save field settings"
    And I should see the success message "Updated field Test Maxlength field settings."
    Then I fill in "edit-instance-widget-settings-maxlength-js" with "10"
    And I check "Truncate html"
    And I press "Save settings"
    When I am logged in as a user with the 'contributor' role
    And I go to "/node/add/article"
    And I fill in "Title" with "Page title"
    And I fill in "Test Maxlength" with "&&&&&&&&&&"
    Then I press "Save"
    And I should see the success message "Article Page title has been created."
    And I should not see "cannot be longer than"
    When I am logged in as a user with the 'administrator' role
    When I go to "/node/add/article"
    And I fill in "Title" with "Page title"
    And I fill in "Test Maxlength" with "AAAAAAAAAAAA"
    Then I press "Save"
    And I should see the success message "Article Page title has been created."
    And I should not see "cannot be longer than"
