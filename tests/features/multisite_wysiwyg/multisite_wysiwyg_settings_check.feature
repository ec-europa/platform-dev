Feature: Testing settings options for the Multisite WYSIWYG module.
  In order to check if settings for Multisite WYSIWYG are working correctly
  As an administrator
  I want to be able to see perform available actions and check their results.

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: Checking WYSIWYG enabling and disabling change tracking on given WYSIWYG profile
    When I go to "admin/config/content/multisite_wysiwyg/setup"
    And I select "Enable change tracking" from "Select operation"
    And I select "Full HTML" from "Select profile"
    And I press "Submit"
    Then I should see "Enabled" in the "Full HTML" row
    And I select "Disable change tracking" from "Select operation"
    And I select "Full HTML" from "Select profile"
    And I press "Submit"
    Then I should see "Disabled" in the "Full HTML" row

  @javascript
  Scenario: Checking if WYSIWYG options are applied to CKeditor
    When I go to "admin/config/content/multisite_wysiwyg/setup"
    And I select "Enable change tracking" from "Select operation"
    And I select "Full HTML" from "Select profile"
    And I press "Submit"
    Then I should see "Enabled" in the "Full HTML" row
    And I check the box "edit-multisite-wysiwyg-dis-change-track-on-create"
    And I check the box "edit-multisite-wysiwyg-en-change-track-on-edit"
    And I press "Save configuration"
    And I go to "node/add/page"
    Then I should not see the "Start tracking changes" button in the "edit-field-ne-body-und-0-value" WYSIWYG editor
    When I select "Basic HTML" from "Text format"
    And I fill in "Title" with "This is a page i want to reference"
    And I fill in "Body" with "Here is the content of the referenced page."
    And I press "Save"
    And I click "Edit draft"
    And I select "Full HTML" from "Text format"
    Then I should see the "Stop tracking changes" button in the "edit-field-ne-body-en-0-value" WYSIWYG editor
