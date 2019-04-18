@api @poetry_mock @i18n
Feature: TMGMT Poetry features
  In order request new translations for nodes/taxonomies with Poetry service.
  As an Administrator
  I want to be able to create/manage translation requests.

  Background:
    Given the module is enabled
      |modules                |
      |tmgmt_poetry_mock      |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | pt-pt     |
      | fr        |
      | de        |
      | it        |

  @javascript @maximizedwindow @theme_wip
  Scenario: Test creation of translation jobs for vocabularies and terms using TMGMT.
    Given I am logged in as a user with the "administrator" role
    And the vocabulary "Vocabulary Test" is created
    And the term "Term Test" in the vocabulary "Vocabulary Test" exists
    When I go to "admin/structure/taxonomy/vocabulary_test/edit"
    And I select the radio button "Localize. Terms are common for all languages, but their name and description may be localized."
    And I press "Save and translate"
    Then I should see the success message "Updated vocabulary Vocabulary Test."

    When I check the box on the "Italian" row
    And I press "Request translation"
    Then I should see the success message "One job needs to be checked out."

    When I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the success message containing "Job has been successfully submitted for translation. Project ID is:"

    When I click "List"
    And I click "Term Test"
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    Then I should see the success message "One job needs to be checked out."

    When I fill in "Date" with a relative date of "+10" days
    And I press "Submit to translator"
    Then I should see the success message containing "Job has been successfully submitted for translation. Project ID is:"

    When I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->it" row
    Then I should see the success message "Translation was received. Check the translation page."

    When I click "Check the translation page"
    And I click "review" in the "Italian" row
    And I press "Save as completed"
    Then I should see "translated" in the "Italian" row

    When I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    Then I should see the success message "Translation was received. Check the translation page."

    When I click "Check the translation page"
    And I click "review" in the "French" row
    And I press "Save as completed"
    Then I should see "translated" in the "French" row

 