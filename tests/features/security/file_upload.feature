@api
Feature: File Vulnerability
  In order to control the file uploads
  As an Administrator
  I need to test if uploaded files are secure

  Scenario: Check file extension and mime type match.
    Given I am logged in as a user with the "administrator" role
    When I go to "node/add/article"
    And I fill in "Title" with "Article with image and caption"
    And I attach the file "/tests/files/fake_jpg.jpg" to "edit-field-image-und-0-upload"
    And I press "Save"
    Then I should see the error message "The specified file fake_jpg.jpg could not be uploaded. The file extension 'jpg' does not match the file mime type 'image/png'. Contact the site administrator for more information."
