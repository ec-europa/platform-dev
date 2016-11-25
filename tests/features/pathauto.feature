@api
Feature: Pathauto
  In order to manage automatic aliases on the website
  As an administrator
  I want to be able to set up patterns for automatic alias creation.

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: Using the All parent terms uri token on node with a term reference field
    Given there is a single tag field in the article content type
    Given the term ballsports with the parent term sport in the vocabulary tags exists
    Given the term football with the parent term ballsports in the vocabulary tags exists
    When I go to "admin/config/search/path/patterns"
    And I fill in "Pattern for all language neutral Article paths" with "[node:field-tag:parents-uri]/[node:source:title]"
    And I press the "Save" button
    Then I go to "node/add/article"
    And I fill in "Title" with "TestArticle"
    And I fill in "Tag" with "football"
    And I press "Save"
    Then I should be on "sport/ballsports/football/testarticle"
