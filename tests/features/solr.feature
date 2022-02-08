@api @ec_europa_theme
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
  @theme_wip
  Scenario: Administrators cannot access the solr configuration.
    When I go to "admin/config/search/apachesolr/settings/solr/edit"
    Then I should see the text "Access denied"
  @theme_wip
  Scenario: Administrators can access the facet configuration page.
    When I go to "admin/config/search/apachesolr/settings/solr/facets"
    Then I should see the text "Settings for: localhost server"
