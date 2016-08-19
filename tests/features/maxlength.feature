Feature: Check the feature Maxlength
  In order to check the functionality of limiting and validating their maximum length in the edit form.
  As an administrator
  I want to check the maxlength.

  @api
  Scenario: Administrator user can check the maxlength counts without the tags and specifics characters
    Given the module is enabled
      | modules                 |
      | multisite_maxlength     |
    Given I am logged in as a user with the 'administrator' role
    When I go to "/admin/structure/types/manage/article/fields"
    And I fill in "edit-fields-add-new-field-label" with "Test Maxlength"
    And I select "Long text" from "edit-fields-add-new-field-type"
    And I select "Text area (multiple rows)" from "edit-fields-add-new-field-widget-type"
    And I click "Save"
    Then I click "Save field settings"
    And I should see the success message "Updated field teste field settings."
    Then I fill in "edit-instance-widget-settings-maxlength-js" with "10"
    And I select the radio button "Truncate html"
    And I click "Save settings"
    Then I am logged in as a user with the 'contributor' role
    And I go to "/node/add/article"
    And I fill in "Title" with "Page title"
    And I fill in "&&&&&&&&&&" with "Test Maxlength"
    Then I click "Save"
    And I should see the success message "Article Page title has been created."
    And I should not see "cannot be longer than"


