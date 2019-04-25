@api @communities
Feature: Communities
  In order to effectively manage groups of people
  As a site administrator
  I want to be able to add, edit and delete communities

  Scenario: Groups list
    Given I am logged in as a user with the 'administrator' role
    When I go to "communities_directory"
    Then I should see the heading "Groups list"
    And I should see the link "all communities"
    And I should see the link "my communities"
    When I click "Create a new community"
    Then I should see the heading "Create Community"

   Scenario: Check nexteuropa module activation
    Given I run drush pmi nexteuropa_core
    Then drush output should contain "not installed"
    Given I run drush pmi nexteuropa_multilingual
    Then drush output should contain "not installed"
    Given I run drush pmi nexteuropa_communities
    Then drush output should contain "nexteuropa_communities was not found"
