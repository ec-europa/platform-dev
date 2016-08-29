@api
Feature: Content editing
  In order to manage the content on the website
  As an editor
  I want to be able to create, edit and delete content

  Background:
    Given I am logged in as a user with the 'administrator' role


  @api @javascript
  Scenario: Upload an image with format and alt text
    When I go to "node/add/page"
    And I select "Full HTML + Change tracking" from "Text format"
    And I fill in "Title" with "Title with tracking "
    And I click the "Add media" button in the "edit-field-ne-body-und-0-value" WYSIWYG editor
    And I switch to the frame "mediaBrowser"
    And I attach the file "/profiles/multisite_drupal_standard/themes/ec_resp/logo.png" to "files[upload]"
    And I press "Next"
    Then I should see "Destination"
    When I select the radio button "Public local files served by the webserver."
    And I press "Next"
    Then I should see a "#edit-submit" element
    And I press "Save"
    And I switch to the frame "mediaStyleSelector"
    And I should see "Choose the type of display you would like for this file"
    And I click the fake "Submit" button
    And I switch out of all frames
    And I wait for AJAX to finish
    # Save the whole node.
    And I press "edit-submit"
    # See the image in the node
    Then I should see the "img" element in the "content" region

