@api
Feature: E-Library
  In order to allow to store documents in digital form
  As an administrator
  I want to be able to propose and publish documents
  And as a contributor
  I want to be able to propose

  Background:
    Given the module is enabled
      | modules            |
      | e_library_core     |
      | e_library_standard |

  Scenario: An administrator can propose and publish a document
    Given  I am logged in as a user with the 'administrator' role
    When I am on "node/add/document"
    And I fill in "Title" with "Document title"
    And I attach the file "/tests/files/logo.png" to "edit-field-document-und-0-upload"
    And I press "Save"
    Then I should see "Document Document title has been created."
    When I am on "admin/workbench"
    And I click "My Edits"
    And I click "Document title"
    Then I should see "Revision state: Draft"
    When I select "Published" from "edit-state"
    And I press "Apply"
    Then I should see "Revision state: Published"
    Then I click "New draft"
    And I press the "Delete" button
    Then I should see "Are you sure you want to delete"
    And I press the "Delete" button
    Then I should see "has been deleted."

  Scenario: A contributor can propose a document and an administrator can publish it and the contributor can see it in the elibrary list
    Given users:
     | name             | mail                 | pass        | roles       |
     | contributor_user | contributor@user.com | password123 | contributor |
    And I am logged in as "contributor_user"
    When I am on "node/add/document"
    And I fill in "Title" with "Document title"
    And I attach the file "/tests/files/logo.png" to "edit-field-document-und-0-upload"
    And I press "Save"
    Then I should see "Document Document title has been created."
    When I am logged in as a user with the 'administrator' role
    And I am on "admin/workbench/moderate-all"
    And I click "Document title"
    Then I should see "Revision state: Draft"
    When I select "Published" from "edit-state"
    And I press "Apply"
    Then I should see "Revision state: Published"
    When the cache has been cleared
    And I am logged in as "contributor_user"
    And I am on "e_library"
    And I click "E-library"
    Then I should see "Document title"
    When I click "Document title"
    Then I click "New draft"
    And I press the "Delete" button
    Then I should see "Are you sure you want to delete"
    And I press the "Delete" button
    Then I should see "has been deleted."

  Scenario: Show image when the display checkbox is checked
    Given  I am logged in as a user with the 'administrator' role
    When I am on "node/add/document"
    And I fill in "Title" with "Document title"
    And I attach the file "/tests/files/logo.png" to "edit-field-document-und-0-upload"
    And I press "Save"
    Then I should see "Document Document title has been created."
    And I click "Edit draft"
    And I check "edit-field-document-und-0-display"
    And I press "Save"
    Then I should see the link "logo.png"
    And I click "Edit draft"
    And I uncheck "edit-field-document-und-0-display"
    And I press "Save"
    Then I should not see the link "logo.png"
    And I click "Edit draft"
    And I press the "Delete" button
    Then I should see "Are you sure you want to delete"
    And I press the "Delete" button
    Then I should see "has been deleted."
