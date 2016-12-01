@api
Feature: Page Layout
  In order to respect standard templates
  As a citizen of the European Union
  I want to be able to see components in the right regions

  Background:
    Given I am not logged in

  Scenario: Anonymous user can see the links in header and footer
    When I am on "/"
    Then I should see "Legal notice" in the ".region-header-top" element

  Scenario Outline: Anonymous user can see the links in header and footer
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

  Scenario Outline: Anonymous user can see the page title
    When I am on "<page>"
    Then I should see "<text>" in the "html head title" element

    # Test the page head title in different pages
    Examples:
      | page       | text                                        |
      | /          | Welcome to NextEuropa - European Commission |
      | search     | Search - European Commission                |
      | contact    | Contact - European Commission               |
      | user       | User account - European Commission          |
