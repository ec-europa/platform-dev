@api @javascript
Feature: Test the creation of new contents and the display of them in a page using tokens.

  Background:
    Given I am logged in as a user with the 'administrator' role
    # Necessary to set a wider screen resolution.
    And I use device with "1920" px and "1080" px resolution
    When I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Content to reference in a simple paragraph"
    And I fill in "Body" with "Here is the content of the page referenced in a simple paragraph."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    When I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Content to reference in a table"
    And I fill in "Body" with "Here is the content of the page referenced in a table."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    When I go to "/node/add/page"
    And I fill in "Title" with "This is a page with some content token"
    And I select "Full HTML" from "Text format"
    And I click the "Insert internal content" button in the "Body" WYSIWYG editor
    And I wait for AJAX to finish
    And I click the "Link" link in the "Content to reference in a simple paragraph" row of the "Body" "CKEditor" modal dialog
    And I press "Save"
    Then I should see the link "Content to reference in a simple paragraph"
    When I click "Edit draft"
    And I click the "Table" button in the "Body" WYSIWYG editor
    And I click the "OK" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    And I click the "Insert internal content" button in the "Body" WYSIWYG editor
    And I wait for AJAX to finish
    And I click the "Link" link in the "Content to reference in a table" row of the "Body" "CKEditor" modal dialog
    And I press "Save"
    Then I should see the link "Content to reference in a simple paragraph"

  @ec_resp_theme
  Scenario: Checking a content reference token is correctly displayed whatever its placement with the ec_resp theme
    And I should see the link "Content to reference in a table" in a "table" in the field display ("div.field-name-field-ne-body div.field-items div.field-item")

  @ec_europa_theme
  Scenario: Checking a content reference token is correctly displayed whatever its placement with the ec_europa theme
    And I should see the link "Content to reference in a table" in a "table" in the field display ("div.field-name-field-ne-body div.ecl-field__body div.ecl-editor")
