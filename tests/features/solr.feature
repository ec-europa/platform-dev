@api @javascript @maximizedwindow @reset-nodes
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

  @moderated-content
  Scenario: Create a draft.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was not instructed to index any node

  @moderated-content
  Scenario: Immediately publish a new page.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was instructed to index a page node with title "Page title"

  @moderated-content
  Scenario: Moderate a page.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Needs Review" from "state"
    And I press the "Apply" button
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was not instructed to index any node

  @moderated-content
  Scenario: Publish a page with moderation.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was instructed to index a page node with title "Page title"

  @moderated-content
  Scenario: Withdraw a published page.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I click "Unpublish this revision"
    And I press the "Unpublish" button
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was instructed to remove a node from the index

  @non-moderated-content
  Scenario: Create draft of a an editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was not instructed to index any node

  @non-moderated-content
  Scenario: Immediately publish a new editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was instructed to index a editorial_team node with title "NextEuropa Platform Core"

  @non-moderated-content
  Scenario: Publish an existing draft of an editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I click "Publishing options"
    And I check the box "Published"
    And I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was instructed to index a editorial_team node with title "NextEuropa Platform Core"

  @non-moderated-content
  Scenario: Edit an existing draft of an editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I fill in "Name" with "NextEuropa Platform Core Next generation"
    And I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was not instructed to index any node

  @non-moderated-content
  Scenario: Withdraw a published editorial team.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    And I click "Edit"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the apachesolr server was instructed to remove a node from the index
