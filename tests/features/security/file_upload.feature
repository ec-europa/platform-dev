@api
Feature: File Vulnerability
  In order to control the file uploads
  As an Administrator
  I need to test if uploaded files are secure

  Background:
    Given I am logged in as a user with the 'administrator' role

  @javascript
  Scenario: Check file extension and mime type match.
    When I request to change the variable "file_entity_max_filesize" to "1 KB"
    And I go to "media/browser_en?render=media-popup&types[]=audio&types[]=image&types[]=video&types[]=document&file_directory=&id=media_wysiwyg&plugins=&max_filesize=1MB"
    And I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And I press "Upload"
    Then I should see the message "The specified file logo.png could not be uploaded. The file is 6.23 KB exceeding the maximum file size of 1 KB."
