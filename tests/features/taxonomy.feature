Feature: Taxonomy
  In order to manage the taxonomy on the website
  As an administrator
  I want to be able to create, edit and delete taxonomy

  @api
  Scenario: Administrator user creates a new vocabulary and adds a new group and terms.
    Given I am logged in as a user with the 'administrator' role
    And I create a new vocabulary "Vocabulary Test"
    And I create a new group "Vertical tab" named "Group Test" in the vocabulary "Vocabulary Test"
    And I create a new field "Long text" named "Field Test" grouped in "Group Test" in the vocabulary "Vocabulary Test"
    And I create a new term "Term Test" in the vocabulary "Vocabulary Test"
    When I go to "admin/structure/taxonomy/vocabulary_test"
    And I click "Add term"
    And I fill in "Name" with "Term Test 2"
    And I press the "Save" button
    Then I should see the success message "Created new term Term Test 2."
