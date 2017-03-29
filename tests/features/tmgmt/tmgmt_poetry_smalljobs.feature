@api @poetry_mock @i18n @poetry
Feature: TMGMT Poetry features
  In order request new translations for nodes with Poetry service.
  As an Administrator
  I want to be able to create/manage translation requests.

  Background:
    Given the module is enabled
      |modules                |
      |tmgmt_poetry_mock      |
      |tmgmt_poetry_smalljobs |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |

  @javascript
  Scenario: I can translate deveral entities with Small Jobs.
    Given I am logged in as a user with the "administrator" role
    And I am viewing a multilingual "page" content:
      | language | title   |
      | en       | My page |
    When I click "Translate" in the "primary_tabs" region
    And I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."