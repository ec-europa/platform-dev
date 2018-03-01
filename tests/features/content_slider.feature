@api @javascript
Feature: Creating a slider as administrator
  In order to create a slider on the website
  As an administrator
  I want to be able to create and configure a slider

  Background:
    Given the module is enabled
      | modules           |
      | ec_content_slider |
    And I am logged in as a user with the 'administrator' role

  Scenario:
    Given I am on "admin/structure/types/manage/page/fields"
    And I select "Image: field_slide (Slide)" from "edit-fields-add-existing-field-field-name"
    And I press "Save"
    Then I should see "Basic page settings"
    And I press "edit-submit"
    Then I should see "field_slide"
    And I clone view "view_ec_content_slider" as "cloned_view_ec_content_slider"
    And I add "cloned_view_ec_content_slider-block" view to "homepage" context section "content"
    And I am on "node/add/page"
    And I fill in "Title" with "Slider title test 1"
    And I attach the file "/tests/files/logo.png" to "edit-field-slide-und-0-upload"
    And I click "Draft (Current)"
    And I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see "Basic page Slider title test 1 has been created."
    And I am on "node/add/page"
    And I fill in "Title" with "Slider title test 2"
    And I attach the file "/tests/files/logo.png" to "edit-field-slide-und-0-upload"
    And I click "Draft (Current)"
    And I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see "Basic page Slider title test 2 has been created."
    And I am on "/"
    Then I should see "Slider title test 2"
    Then I wait 6 seconds
    Then I should see "Slider title test 1"
