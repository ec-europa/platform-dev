@api
Feature: Content type administration features
  In order to easily structure the content of the European Commission
  As an administrator
  I want to be able to create, customize and delete content types

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: As administrator, I create a custom content type translated through
    entity translation, using workbench moderation and having 2 fields "Body" and
    "Select option". I should be able to create a content with it
    When I go to "admin/structure/types/add"
    And I fill in "Name" with "Groovy type"
    And I fill in "Machine-readable name" with "groovy_type"
    And I fill in "Description" with "A Groovy type for a groovy test"
    And I uncheck the box "Published"
    And I uncheck the box "Promoted to front page"
    But I check the box "Create new revision"
    And I check the box "Enable moderation of revisions"
    And I select the radio button "Enabled, with field translation" with the id "edit-language-content-type-4"
    And I press the "Save and add fields" button for saving the "groovy_type" content type
    Then I should be on "admin/structure/types/manage/groovy-type/fields_en"
    And I should see the success message "The content type Groovy type has been added."
    And I should see "Body"
    When I fill in "edit-fields-add-new-field-label" with "Select an option"
    And I fill in "edit-fields-add-new-field-field-name" with "select_an_option"
    And I select "list_text" from "edit-fields-add-new-field-type"
    And I select "options_buttons" from "edit-fields-add-new-field-widget-type"
    And I press the "Save" button for saving the "field_select_an_option" field for the "groovy_type" content type
    And I fill in "edit-field-settings-allowed-values" with:
    """
    Option 1
    Option 2
    """
    And I press the "Save field settings" button
    And I check the box "edit-field-translatable"
    And I press the "Save settings" button
    Then I should see the success message "Saved Select an option configuration."
    When I go to "node/add/groovy-type"
    And I fill in "Title" with "Lorem ipsum dolor sit amet"
    And I fill in "Body" with "<p>Consectetur adipiscing elit.</p>"
    And I select the radio button "Option 1" with the id "edit-field-select-an-option-und-option-1"
    And I press "Save"
    Then I should see the heading "Lorem ipsum dolor sit amet"
    And the response should contain "<p>Consectetur adipiscing elit.</p>"
    And the response should contain "Option 1"

