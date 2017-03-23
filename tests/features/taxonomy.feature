@api @communitites
Feature: Taxonomy
  In order to manage the taxonomy on the website
  As an administrator
  I want to be able to create, edit and delete taxonomy

  Scenario: Administrator user creates a new vocabulary and adds a new group and terms.
    Given I am logged in as a user with the 'administrator' role
    And the vocabulary "Vocabulary Test" is created
    And the group "Vertical tab" named "Group Test" in the vocabulary "Vocabulary Test" exists
    And the field "Long text" named "Field Test" grouped in "Group Test" in the vocabulary "Vocabulary Test" exists
    And the term "Term Test" in the vocabulary "Vocabulary Test" exists
    When I go to "admin/structure/taxonomy/vocabulary_test"
    And I click "Add term"
    And I fill in "Name" with "Term Test 2"
    And I press the "Save" button
    Then I should see the success message "Created new term Term Test 2."
