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
    And I am logged in as a user with the "cem" role

  @resetPoetryNumero
  Scenario: Checking a wrong configuration.
    When I go to "admin/config/regional/tmgmt_translator/manage/tmgmt_poetry_test_translator"
