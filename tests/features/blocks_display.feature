Feature: Blocks display
  In order to respect standard templates
  As a citizen of the European Union
  I want to be able to read links blocks in header and footer

Scenario: Anonymous user can see the links in header and footer
  Given I am not logged in
  When I am on the homepage
  Then I should see "Legal notice" in the ".region-header-top" element
  Then I should see "Cookies" in the ".region-header-top" element
  Then I should see "Last update" in the ".region-footer" element
  Then I should see "Top" in the ".region-footer" element
  Then I should see "Legal notice" in the ".region-footer" element