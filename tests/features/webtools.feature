@api
Feature: Webtools feature
  In order to use widgets (charts, maps, social tools and more) on the website with the Webtools service
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
    And the response should contain "contextual-links-wrapper"
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Map Webtools" row
    Then I should see "Are you sure you want to delete Block Map Webtools Title?"
    When I press "Delete"
    Then I should see the success message "webtools Block Map Webtools Title has been deleted."

  @api @javascript
  Scenario: Insert a webtools block into a content by using the 2 full HTML text formats
    Given a map webtools "Block Webtools" exists
    And I use device with "1920" px and "1080" px resolution
    When I go to "node/add/page"
    And I fill in "Title" with "Basic page with a Map"
    And I select "Full HTML" from "Text format"
    And I click the "Insert internal content" button in the "Body" WYSIWYG editor
    Then I should see the "CKEditor" modal dialog from the "Body" WYSIWYG editor with "Insert internal content" title
    When I click the "Insert internal blocks" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    And I wait for AJAX to finish
    When I click "Default" in the "Block Webtools" row
    And I wait for AJAX to finish
    And I press "Save"
    Then I should see the success message "Basic page with a Map has been created."
    And the response should contain "<script type=\"application/json\">{\"service\":\"map\",\"custom\":\"//europa.eu/webtools/showcase/demo/map/samples/demo.js\"}</script>"
    And the response should contain "contextual-links-wrapper"

  @api
  Scenario: Create and delete a block 'Basic map'
    When I go to "block/add/webtools"
    And I fill in "Label" with "Block Basic Map Webtools"
    And I fill in "Title" with "Block Basic Map Webtools Title"
    And I fill in "JSON Object" with "{\"service\": \"map\",\"map\": {\"zoom\": \"15\",\"center\": [\"50.5037\",\"4.2258\"],\"background\": [\"osmec\"]}}"
    And I press "Save"
    Then I should see the text "webtools Block Basic Map Webtools Title has been created."
    And the response should contain "<script type=\"application/json\">{\"service\": \"map\",\"map\": {\"zoom\": \"15\",\"center\": [\"50.5037\",\"4.2258\"],\"background\": [\"osmec\"]}}</script>"
    And the response should contain "contextual-links-wrapper"
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Basic Map Webtools" row
    Then I should see "Are you sure you want to delete Block Basic Map Webtools Title?"
    When I press "Delete"
    Then I should see the text "webtools Block Basic Map Webtools Title has been deleted."

  @api
  Scenario: Create and delete a block 'Chart'
    When I go to "block/add/webtools"
    And I fill in "Label" with "Block Chart Webtools"
    And I fill in "Title" with "Block Chart Webtools Title"
    And I fill in "JSON Object" with "{\"service\": \"charts\",\"provider\": \"highcharts\",\"data\": \"//europa.eu/webtools/showcase/demo/charts/wikis/airport-transport-of-passenger-in-the-eu-2014-options.json\"}"
    And I press "Save"
    Then I should see the text "webtools Block Chart Webtools Title has been created."
    And the response should contain "<script type=\"application/json\">{\"service\": \"charts\",\"provider\": \"highcharts\",\"data\": \"//europa.eu/webtools/showcase/demo/charts/wikis/airport-transport-of-passenger-in-the-eu-2014-options.json\"}</script>"
    And the response should contain "contextual-links-wrapper"
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Chart Webtools" row
    Then I should see "Are you sure you want to delete Block Chart Webtools Title?"
    When I press "Delete"
    Then I should see the text "webtools Block Chart Webtools Title has been deleted."

  @api
  Scenario: Create and delete a block 'Social bookmark'
    When I go to "block/add/webtools"
    And I fill in "Label" with "Block Social bookmark Webtools"
    And I fill in "Title" with "Block Social bookmark Webtools Title"
    And I fill in "JSON Object" with "{\"service\": \"sbkm\",\"to\": [\"twitter\",\"facebook\",\"linkedin\",\"googleplus\"],\"selection\": false}"
    And I press "Save"
    Then I should see the text "webtools Block Social bookmark Webtools Title has been created."
    And the response should contain "<script type=\"application/json\">{\"service\": \"sbkm\",\"to\": [\"twitter\",\"facebook\",\"linkedin\",\"googleplus\"],\"selection\": false}</script>"
    And the response should contain "contextual-links-wrapper"
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Social bookmark Webtools" row
    Then I should see "Are you sure you want to delete Block Social bookmark Webtools Title?"
    When I press "Delete"
    Then I should see the text "webtools Block Social bookmark Webtools Title has been deleted."

  @api
  Scenario: Create and delete a block 'Social Media Kit'
    When I go to "block/add/webtools"
    And I fill in "Label" with "Block SMK Webtools"
    And I fill in "Title" with "Block SMK Webtools Title"
    And I fill in "JSON Object" with "{\"service\": \"twitter\",\"type\": \"user\",\"screen_name\": \"EU_Commission\",\"include_rts\": true}"
    And I press "Save"
    Then I should see the text "webtools Block SMK Webtools Title has been created."
    And the response should contain "<script type=\"application/json\">{\"service\": \"twitter\",\"type\": \"user\",\"screen_name\": \"EU_Commission\",\"include_rts\": true}</script>"
    And the response should contain "contextual-links-wrapper"
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block SMK Webtools" row
    Then I should see "Are you sure you want to delete Block SMK Webtools Title?"
    When I press "Delete"
    Then I should see the text "webtools Block SMK Webtools Title has been deleted."
