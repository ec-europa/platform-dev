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

  @api @wip
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

  @api
  Scenario: Insert a webtools block into a content
    Given a webtools "Block Test" exists
    When I go to "node/add/page"

