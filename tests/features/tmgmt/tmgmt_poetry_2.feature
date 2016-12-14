@api @poetry @i18n
Feature: TMGMT Poetry features
  In order request new translations for nodes/taxonomies with Poetry service.
  As an Administrator
  I want to be able to create/manage translation requests.

  Background:
    Given I am logged in as a user with the "administrator" role
    And the module is enabled
      |modules                |
      |tmgmt_poetry_mock      |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |
      | de        |
      | it        |

  Scenario: Checking the counter init request.
    Given I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I fill in "Body" with "Page body content"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-fr"
    And I press "Request translation"
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has the codeDemandeur "ABCD"
    And the translation request has the sequence "NEXT_EUROPA_COUNTER"
