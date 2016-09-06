@api
Feature: Webtools as administrator
  In order to manage Webtools on the website
  As an administrator
  I want to be able to create, edit and delete block Webtools

  Background:
    Given these modules are enabled
      | modules             |
      | nexteuropa_webtools |
    And a valid Smartload Url has been configured
    And I am logged in as a user with the 'administrator' role

  @api
  Scenario: Create and delete a block 'Map'
    When I go to "block/add/webtools"
    And I fill in "Label" with "Block Map Webtools"
    And I fill in "Title" with "Block Map Webtools Title"
    And I fill in "JSON Object" with "{\"service\":\"map\"}"
    And I fill in "URL" with "http://europa.eu/webtools/showcase/demo/map/samples/demo.js"
    And I press "Save"
    Then I should see the success message "webtools Block Map Webtools Title has been created."
    And the response should contain "<script type=\"application/json\">{\"service\":\"map\",\"custom\":\"//europa.eu/webtools/showcase/demo/map/samples/demo.js\"}</script>"
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Map Webtools" row
    Then I should see "Are you sure you want to delete Block Map Webtools Title?"
    When I press "Delete"
    Then I should see the success message "webtools Block Map Webtools Title has been deleted."

  @api @javascript
  Scenario: Insert a webtools block into a content
    Given a map webtools "Block Webtools" exists
    # When I go to "node/add/page"
    # And I fill in "Title" with "Basic page with a Map"
    # And I click the "Insert internal content" button in the "edit-field-ne-body-und-0-value" WYSIWYG editor
    # And I wait for AJAX to finish
    # And I click the "Advanced" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    # And I click the "Insert internal blocks" link in the "cke_editor_edit-field-ne-body-und-0-value_dialog" modal dialog from the "edit-field-ne-body-und-0-value" WYSIWYG editor
    # And I wait for AJAX to finish
    # And I click "Default" in the "Block Map Webtools Title" row
    # And I click the "Default" link in the "cke_editor_edit-field-ne-body-und-0-value_dialog" modal dialog from the "edit-field-ne-body-und-0-value" WYSIWYG editor
    # And I press "Ok"
    # Then I should see "Block Test Title as Default"
