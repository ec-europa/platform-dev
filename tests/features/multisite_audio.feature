@api
Feature: Multisite Audio
  In order to use allow administrators to attach audio files to nodes and reproduce playlists
  As an administrator
  I want to be able to create, edit and delete block Webtools

  Background:
    Given the module is enabled
      | modules |
      | multisite_audio |
    Given I am logged in as a user with the 'administrator' role

  Scenario: Add audio field to a page content type and create a node with an audio file attached
    When I go to "/admin/structure/types/manage/page/fields_en"
    And I fill in "edit-fields-add-new-field-label" with "multisite audio test"
    And I fill in "edit-fields-add-new-field-field-name" with "multisite_audio_test"
    And I select "Audio" from "edit-fields-add-new-field-type"
    And I select "Audio Upload" from "edit-fields-add-new-field-widget-type"
    And I press the "Save" button
    Then I should see "FIELD SETTINGS"
    Then I should see "Upload destination"
    And I press the "Save field settings" button
    Then I should see "Updated field multisite audio test field settings."
    Then I should see "BASIC PAGE SETTINGS"
    Then I should see "These settings apply only to the multisite audio test field when used in the Basic page type."
    Then I should see "multisite audio test FIELD SETTINGS"
    Then I check "Enable Display field"
    Then I check "Files displayed by default"
    And I press the "Save settings" button
    Then I should see "Saved multisite audio test configuration."
    When I go to "/node/add/page_en"
    Then I should see "Create Basic page"
    Then I should see "Title"
    Then I should see "multisite audio test"
    And I fill in "Title" with "multisite audio test title"
    When I attach the file "/srv/httpd/sites/ec_behat25/tests/files/european-anthem-2012-v2.mp3" to "edit-field-multisite-audio-test-und-0-upload"
    And I press the "Save" button
    Then I should see "multisite audio test title"
    Then I should see "Basic page multisite audio test title has been created."
    When I go to "/content/multisite-audio-test-title_en"
    And the response should contain "jp-audio"
    And the response should contain "jp-play"
