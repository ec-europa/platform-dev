@api
Feature: Administrators can check information on status page
  In order to know site status
  As an administrator
  I can access to the status page

Scenario: FusionMap library is found
  Given the module is enabled
    |modules       |
    |multisite_maps|
  And I am logged in as an administrator
  When I am on "admin/reports/status"
  Then I should see "FusionMaps PHP file found." in the "table.system-status-report" element
  And I should not see "FusionMaps SWF file not found." in the "table.system-status-report" element

Scenario: Show git informations in report
  In order to identify the test environment
  As an acceptance tester
  I need to be able to see the git branch and latest commit message

  Given I am logged in as an administrator
  Given a file named "continuousphp.package" with:
    """
      {"build_id":"1439fb37-6ba2-44f1-9a04-0db661589364","ref":"refs\/tags\/2.1.39","commit":"a6e6719f52250422dbe8e80e39494199d97754c0"}
    """
  When I visit "admin/reports/status"
  Then I should see "Git ref" in the "table.system-status-report" element
  Then I should see "refs/tags/2.1.39" in the "table.system-status-report" element
  # Test that the commit is shown and links to Github.
  And I should see "Git commit" in the "table.system-status-report" element
  When I click 'a6e6719f52250422dbe8e80e39494199d97754c0'
  Then I should see the text "NEXTEUROPA-6056"
