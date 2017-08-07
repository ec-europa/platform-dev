@api @javascript @ec_europa_theme
Feature: Europa Search features
  In order to find rapidly contents across the site and Europa on a site using the "ec_europa" theme
  As a anonymous user
  I want to search content from a form available on the site

  @wip
  Scenario: Anonymous user can use the header search form to find contents on Europa and
    the results is displayed on the "Europa Search" interface
    Given I am on the homepage
    And I fill in "Search this website" with "investments"
    And I press "Search"
    # Control that we are on the Europa Search interface and that the search work.
    # We control the minimum to ensure the feature runs correctly.
    Then the url should match "/geninfo/query/resultaction.jsp"
    And the "queryText" field should contain "investments"
    And I should see "Search options"
    And I should not see "No results found"
