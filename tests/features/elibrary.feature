@api @javascript
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
    Then I am on "admin/workbench/moderate-all"
    And I click "Document title"
    Then I should see "Revision state: Draft"
    Then I select "Published" from "edit-state"
    And I press "Apply"
    Then I should see "Revision state: Published"

  Scenario: An editor can propose a document and an administrator can publish it and the contributor can see it in the elibrary list
    Given users:
     | name             | mail                 | pass        | roles       |
     | contributor_user | contributor@user.com | password123 | contributor |
    And I am logged in as "contributor_user"
    When I am on "node/add/document"
    And I fill in "Title" with "Document title"
    And I attach the file "/tests/files/logo.png" to "edit-field-document-und-0-upload"
    And I click "Revision information"
    Then I select "Needs Review" from "edit-workbench-moderation-state-new"
    And I press "Save"
    Then I should see "Document Document title has been created."
    Then I am logged in as a user with the 'administrator' role
    And I am on "admin/workbench/moderate-all"
    And I click "Document title"
    Then I should see "Revision state: Needs Review"
    Then I select "Published" from "edit-state"
    And I press "Apply"
    Then I should see "Revision state: Published"
    Then I am logged in as "contributor_user"
    And the cache has been cleared
    And I click "E-library"
    Then I should see "Document title"
    And I click "Document title"
    Then I should see "Document title"



