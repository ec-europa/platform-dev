Feature: Administrators can check information on status page
  In order to know site status
  As an administrator
  I can access to the status page

@api
Scenario: FusionMap library is found
  Given the module is enabled
    |modules       |
    |multisite_maps|
  And I am logged in as an administrator
  When I am on "admin/reports/status"
  Then I should see "FusionMaps PHP file found." in the "table.system-status-report" element
  And I should not see "FusionMaps SWF file not found." in the "table.system-status-report" element
