Feature: Blocks display
  In order to respect standard templates
  As a citizen of the European Union
  I want to be able to read links blocks in header and footer


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
