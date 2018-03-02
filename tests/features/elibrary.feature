@api
Feature: E-Library
  In order to allow to store documents in digital form
  As an administrator i
  I want to be able to propose and publish documents
  And as a contributor
  I want to be able to propose

  Background:
    Given the module is enabled
      | modules        |
      | e_library_core |

  Scenario: A administrator can propose
    Given  I am logged in as a user with the 'administrator' role
    When I am on "node/add/document"
    And I fill in "Title" with "Document title"
    And I attach the file "/tests/files/logo.png" to "edit-field-document-und-0-upload"
    And I press "Save"
    Then I should see "Document Document title has been created."
    Then I am on "admin/workbench"
    And I click "My Edits"
    And I click "Document title"
    Then I should see "Revision state: Draft"
    Then I select "Published" from "edit-state"
    And I press "Apply"
    Then I should see "Revision state: Published"
