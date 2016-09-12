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
    And I use device with "1920" px and "1080" px resolution
    When I go to "node/add/page"
    And I fill in "Title" with "Basic page with a Map"
    And I click the "Insert internal content" button in the "Body" WYSIWYG editor
    Then I should see the "CKEditor" modal dialog from the "Body" WYSIWYG editor with "Insert internal content" title
    When I click the "Insert internal blocks" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    And I wait for AJAX to finish
    When I click "Default" in the "Block Webtools" row
    And I wait for AJAX to finish
    And I press "Save"
    Then I should see the success message "Basic page with a Map has been created."
    And the response should contain "<script type=\"application/json\">{\"service\":\"map\",\"custom\":\"//europa.eu/webtools/showcase/demo/map/samples/demo.js\"}</script>"
