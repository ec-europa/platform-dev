@api
Feature: Page Layout
  In order to respect standard templates
  As a citizen of the European Union
  I want to be able to see components in the right regions

  @api
  Scenario Outline: Anonymous user can see the links in header and footer
  Given I am not logged in
  When I am on the homepage
  Then I should see "<text>" in the "<element>" element

  # Test all links in header and footer  
  Examples:
    | text                     | element                  |
    | Legal notice             | .region-header-top       |
    | Cookies                  | .region-header-top       |
    | Contact on Europa        | .region-header-top       |
    | Search on Europa         | .region-header-top       |
    | Last update              | .region-footer           |
    | Top                      | .region-footer           |
    | Legal notice             | .region-footer           |
    | Cookies                  | .region-footer           |
    | Contact on Europa        | .region-footer           |
    | Search on Europa         | .region-footer           |


  @api
  Scenario Outline: Anonymous user can see the page title
  Given I am not logged in
  When I am on "<page>"
  Then I should see "<text>" in the "html head title" element

  # Test the page head title in different pages 
  Examples:
    | page       | text                                        |
    | /          | Welcome to NextEuropa - European Commission |
    | contact    | Contact - European Commission               |
    | user       | User account - European Commission          |

  @api
  Scenario Outline: Anonymous user can see the search page title
    Given the module is enabled
      | modules     |
      | apachesolr  |
    And I am not logged in
    When I am on "<page>"
    Then I should see "<text>" in the "html head title" element
      # Test the page head title presence on search page
    Examples:
      | page       | text                                      |
      | search     | Search - European Commission              |