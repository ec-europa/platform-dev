Feature: Taxonomy
  In order to manage the taxonomy on the website
  As an administrator
  I want to be able to create, edit and delete taxonomy

  @api
  Scenario: Administrator user creates a new vocabulary and adds a new group and terms.
    Given I am logged in as a user with the 'administrator' role
    And I create a new vocabulary "vocabulary_test"
    And I create a new group "tab" named "group_test" in the vocabulary "vocabulary_test"
    And I create a new field "text_long" named "field_test" grouped in "group_test" in the vocabulary "vocabulary_test"
    And I create a new term "term_test" in the vocabulary "vocabulary_test"
    When I go to "admin/structure/taxonomy/vocabulary_test"
    And I click "Add term"
    And I fill in "Name" with "Term Test 2"
    And I press the "Save" button
    Then I should see the success message "Created new term Term Test 2."
