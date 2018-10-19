@api
Feature:
  In order to optimize the search in a site
  Or to create custom search pages and facets
  As a site owner
  I can add apachesolr support to my site

  Background:
    Given these modules are enabled
      | modules     |
      | solr_config |
    And the apachesolr integration is configured
    And I am logged in as a user with the "administrator" role
    And there are no nodes to index in apachesolr

  Scenario: Administrators cannot access the solr configuration.
    When I go to "admin/config/search/apachesolr/settings/solr/edit"
    Then I should see the text "Access denied"

  Scenario: Administrators can access the facet configuration page.
    When I go to "admin/config/search/apachesolr/settings/solr/facets"
    Then I should see the text "Settings for: localhost server"

  Scenario: Create a draft.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I run cron
    Then the apachesolr server was not instructed to index any node

  Scenario: Immediately publish a new page.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I run cron
    Then the apachesolr server was instructed to index a page node with title "Page title"

  Scenario: Moderate a page.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Needs Review" from "state"
    And I press the "Apply" button
    And I run cron
    Then the apachesolr server was not instructed to index any node

  Scenario: Publish a page with moderation.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    And I run cron
    Then the apachesolr server was instructed to index a page node with title "Page title"

  Scenario: Withdraw a published page.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I click "Unpublish this revision"
    And I press the "Unpublish" button
    And I run cron
    Then the apachesolr server was instructed to remove a node from the index

  Scenario: Create draft of a an editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I uncheck the box "Published"
    And I press "Save"
    And I run cron
    Then the apachesolr server was not instructed to index any node

  Scenario: Immediately publish a new editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    And I run cron
    Then the apachesolr server was instructed to index a editorial_team node with title "NextEuropa Platform Core"

  Scenario: Publish an existing draft of an editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I check the box "Published"
    And I press "Save"
    And I run cron
    Then the apachesolr server was instructed to index a editorial_team node with title "NextEuropa Platform Core"

  Scenario: Edit an existing draft of an editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I fill in "Name" with "NextEuropa Platform Core Next generation"
    And I press "Save"
    And I run cron
    Then the apachesolr server was not instructed to index any node

  Scenario: Withdraw a published editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    And I click "Edit"
    And I uncheck the box "Published"
    And I press "Save"
    And I run cron
    Then the apachesolr server was instructed to remove a node from the index
