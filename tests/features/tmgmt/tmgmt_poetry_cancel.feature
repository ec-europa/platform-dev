@api @poetry_mock @i18n
Feature: TMGMT Poetry features
  In order request new translations for nodes/taxonomies with Poetry service.
  As an Administrator
  I want to be able to cancel languages in translation requests.

  Background:
    Given the module is enabled
      |modules                |
      |tmgmt_poetry_mock      |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | pt-pt     |
      | fr        |
    And I am logged in as a user with the 'administrator' role

  @theme_wip
  Scenario: Cancel main language in translation request
    Given I am viewing a multilingual "page" content:
      | language | title      | body                    |
      | en       | Nice title | Last change column test |
    Then break
    When I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I check the box on the "Portuguese" row
    And I press "Request translation"
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    And I go to "admin/poetry_mock/dashboard"
    And I click "Send 'ONG' status" in the "en->fr" row
    And I click "Send 'ONG' status" in the "en->pt-pt" row
    Then I should see the success message "The status request was sent. Check the translation page."

    When I click "Send 'CNL' status" in the "en->fr" row
    And I click "Check the translation page"
    Then I should see "None" in the "French" row

    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->pt-pt" row
    And I click "Check the translation page"
    And I click "Needs review" in the "Portuguese, Portugal" row
    And I press "Save as completed"
    Then I should see "[PT-PT] Nice title" in the "Portuguese, Portugal" row

    # Check job items
    When I go to "admin/tmgmt/recent-changes"
    And I click "View" in the "Nice title [fr]" row
    Then I should see "Aborted" in the "French" row
    Then I should see "Accepted" in the "Portuguese, Portugal" row

  @theme_wip
  Scenario: Cancel secondary language in translation request
    Given I am viewing a multilingual "page" content:
      | language | title            | body                    |
      | en       | Nice title            | Last change column test |
    And I click "Translate" in the "primary_tabs" region
    Then I should not see "Request addition of new languages"

    When I check the box on the "French" row
    And I check the box on the "Portuguese" row
    And I press "Request translation"
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    And I go to "admin/poetry_mock/dashboard"
    And I click "Send 'ONG' status" in the "en->fr" row
    And I click "Send 'ONG' status" in the "en->pt-pt" row
    Then I should see the success message "The status request was sent. Check the translation page."

    When I click "Send 'CNL' status" in the "en->pt-pt" row
    And I click "Check the translation page"
    Then I should see "None" in the "Portuguese, Portugal" row

    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Check the translation page"
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see "[FR] Nice title" in the "French" row

    # Check job items
    When I go to "admin/tmgmt/recent-changes"
    And I click "View" in the "Nice title" row
    Then I should see "Accepted" in the "French" row
    Then I should see "Aborted" in the "Portuguese, Portugal" row
