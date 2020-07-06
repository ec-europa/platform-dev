@api
Feature: Webtools feature
  In order to use widgets (charts, maps, social tools and more) on the website with the Webtools service
  As an administrator
  I want to be able to create, edit and delete block Webtools

  Background:
    Given these modules are enabled
      | modules                   |
      | nexteuropa_webtools       |
      | nexteuropa_trackedchanges |
    And a valid Smartload Url has been configured

  @api @standard_ec_resp @javascript @wip
  Scenario: Insert a webtools block into a content and delete a block 'Map'
    Given I am logged in as a user with the 'administrator' role
    And I go to "block/add/webtools"
    And I fill in "Label" with "Block Map Webtools"
    And I fill in "Title" with "Block Map Webtools Title"
    And I fill in "JSON Object" with "{\"service\":\"map\",\"version\":\"2.0\",\"efbdata\":{\"year\":\"1998-2019\"}}"
    And I press "Save"
    Then I should see the text "webtools Block Map Webtools Title has been created."
    And the response should contain "{\"service\":\"map\",\"version\":\"2.0\",\"efbdata\":{\"year\":\"1998-2019\"}}"
    And the response should contain "contextual-links-wrapper"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content
    Then I go to "node/add/page"
    And I fill in the content's title with "Basic page with a Map"
    And I select "Full HTML + Change tracking" from "Text format"
    And I click the "Insert internal content" button in the "Body" WYSIWYG editor
    Then I should see the "CKEditor" modal dialog from the "Body" WYSIWYG editor with "Insert internal content" title
    When I click the "Insert internal blocks" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    And I wait for AJAX to finish
    When I click "Default" in the "Block Map Webtools" row
    And I wait for AJAX to finish
    And I press "Save"
    Then I should see the success message "Basic page with a Map has been created."
    And the response should contain "{\"service\":\"map\",\"version\":\"2.0\",\"efbdata\":{\"year\":\"1998-2019\"}}"
    And the response should contain "contextual-links-wrapper"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Map Webtools" row
    Then I should see "Are you sure you want to delete Block Map Webtools Title?"
    When I press "Delete"
    Then I should see the success message "webtools Block Map Webtools Title has been deleted."

  @api
  Scenario: Create and delete a block 'Chart'
    When I am logged in as a user with the 'administrator' role
    And I go to "block/add/webtools"
    And I fill in "Label" with "Block Chart Webtools"
    And I fill in "Title" with "Block Chart Webtools Title"
    And I fill in "JSON Object" with "{\"service\":\"charts\",\"provider\":\"highcharts\"}"
    And I press "Save"
    Then I should see the text "webtools Block Chart Webtools Title has been created."
    And the response should contain "{\"service\":\"charts\",\"provider\":\"highcharts\"}"
    And the response should contain "contextual-links-wrapper"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Chart Webtools" row
    Then I should see "Are you sure you want to delete Block Chart Webtools Title?"
    When I press "Delete"
    Then I should see the text "webtools Block Chart Webtools Title has been deleted."

  @api
  Scenario: Create and delete a block 'Social bookmark'
    When I am logged in as a user with the 'administrator' role
    And I go to "block/add/webtools"
    And I fill in "Label" with "Block Social bookmark Webtools"
    And I fill in "Title" with "Block Social bookmark Webtools Title"
    And I fill in "JSON Object" with "{\"service\":\"sbkm\",\"to\":[\"twitter\",\"facebook\",\"linkedin\",\"googleplus\"],\"selection\":false}"
    And I press "Save"
    Then I should see the text "webtools Block Social bookmark Webtools Title has been created."
    And the response should contain "{\"service\":\"sbkm\",\"to\":[\"twitter\",\"facebook\",\"linkedin\",\"googleplus\"],\"selection\":false}"
    And the response should contain "contextual-links-wrapper"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block Social bookmark Webtools" row
    Then I should see "Are you sure you want to delete Block Social bookmark Webtools Title?"
    When I press "Delete"
    Then I should see the text "webtools Block Social bookmark Webtools Title has been deleted."

  @api
  Scenario: Create and delete a block 'Social Media Kit'
    When I am logged in as a user with the 'administrator' role
    And I go to "block/add/webtools"
    And I fill in "Label" with "Block SMK Webtools"
    And I fill in "Title" with "Block SMK Webtools Title"
    And I fill in "JSON Object" with "{\"service\":\"twitter\",\"type\":\"user\",\"screen_name\":\"EU_Commission\",\"include_rts\":true}"
    And I press "Save"
    Then I should see the text "webtools Block SMK Webtools Title has been created."
    And the response should contain "{\"service\":\"twitter\",\"type\":\"user\",\"screen_name\":\"EU_Commission\",\"include_rts\":true}"
    And the response should contain "contextual-links-wrapper"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content
    When I go to "admin/content/blocks"
    And I click "delete" in the "Block SMK Webtools" row
    Then I should see "Are you sure you want to delete Block SMK Webtools Title?"
    When I press "Delete"
    Then I should see the text "webtools Block SMK Webtools Title has been deleted."

  @api
  Scenario: A user without permission 'Add js or css url to webtools' can not add custom css and js links
    Given Role 'editor' has permission 'administer beans'
    When I am logged in as a user with the 'editor' role
    And I go to "block/add/webtools"
    Then I should see the text "Create webtools block"
    And I should not see "File" in the ".group-custom-js-settings" element
    And I should not see "External link" in the ".group-custom-js-settings" element
    And I should not see "External link" in the ".group-custom-css-settings" element
 
  @api
  Scenario: A user with permission 'Add js or css url to webtools' can add custom css and js links
    Given Role 'editor' has permission 'upload webtools custom js'
    And Role 'editor' has permission 'administer beans'
    And Role 'editor' has permission 'view bean page'
    When I am logged in as a user with the 'editor' role
    And I go to "block/add/webtools"
    And I should see "File" in the ".group-custom-js-settings" element
    And I should see "External link" in the ".group-custom-js-settings" element
    And I should see "External link" in the ".group-custom-css-settings" element
    Then I fill in "Label" with "Block Map Webtools"
    And I fill in "Title" with "Block Map Webtools Title"
    And I fill in "JSON Object" with "{\"service\":\"map\",\"version\":\"2.0\",\"efbdata\":{\"year\":\"1998-2019\"}}"
    And I fill in "edit-field-custom-js-link-und-0-url" with "https://ec.europa.eu/test_cem/index.js"
    And I fill in "edit-field-custom-css-link-und-0-url" with "https://ec.europa.eu/test_cem/style.css"
    And I press "Save"
    Then I should see the text "webtools Block Map Webtools Title has been created."
    And the response should contain "{\"service\":\"map\",\"version\":\"2.0\",\"efbdata\":{\"year\":\"1998-2019\"},\"custom\":[\"//ec.europa.eu/test_cem/index.js\",\"//ec.europa.eu/test_cem/style.css\"]}"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content
