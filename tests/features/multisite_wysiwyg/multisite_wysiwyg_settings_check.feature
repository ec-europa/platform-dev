@api
Feature: Testing settings options for the Multisite WYSIWYG module.
  In order to check if settings for Multisite WYSIWYG are working correctly
  As an administrator
  I want to be able to see perform available actions and check their results.

  Background:
    Given I am logged in as a user with the 'administrator' role
    And the module is enabled
      | modules                   |
      | nexteuropa_trackedchanges |

  Scenario: Checking WYSIWYG enabling and disabling change tracking on given WYSIWYG profile
    When I go to "admin/config/content/wysiwyg/tracked_changes/setup"
    And I click "enable tracked changes buttons" in the "Full HTML" row
    Then I should see "Enabled" in the "Full HTML" row
    And I should see the message "Change tracking enabled on full_html WYSIWYG profile"
    When I click "disable tracked changes buttons" in the "Full HTML" row
    Then I should see "Disabled" in the "Full HTML" row
    And I should see the message "Change tracking disabled on full_html WYSIWYG profile"

  @javascript
  Scenario: Checking if WYSIWYG options are applied to CKEditor
    When I go to "admin/config/content/wysiwyg/tracked_changes/setup"
    And I click "enable tracked changes buttons" in the "Full HTML" row
    Then I should see "Enabled" in the "Full HTML" row
    And I should see the message "Change tracking enabled on full_html WYSIWYG profile"
    And I check the box "Disable on create content pages."
    And I check the box "Enable tracking on edit content pages."
    And I press "Save configuration"
    And I go to "node/add/page"
    And I fill in "Title" with "This is a page i want to reference"
    And I select "Full HTML" from "Text format"
    Then I should not see the "Start tracking changes" button in the "Body" WYSIWYG editor
    When I press "Save"
    And I click "Edit draft"
    And I select "Full HTML" from "Text format"
    Then I should see the "Stop tracking changes" button in the "Body" WYSIWYG editor
    And I go to "admin/config/content/wysiwyg/tracked_changes/setup"
    When I click "disable tracked changes buttons" in the "Full HTML" row
    Then I should see "Disabled" in the "Full HTML" row
    When I go to "node/add/page"
    And I fill in "Title" with "This is a new page i want to reference"
    Then I should not see the "Start tracking changes" button in the "Body" WYSIWYG editor
    When I press "Save"
    And I click "Edit draft"
    And I select "Full HTML" from "Text format"
    Then I should not see the "Start tracking changes" button in the "Body" WYSIWYG editor
