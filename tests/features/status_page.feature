@api
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
  Then I should see "FusionMaps PHP file found." in the "nept_element:system-status-report" element
  And I should not see "FusionMaps SWF file not found." in the "nept_element:system-status-report" element


@api
Scenario: Show git informations in report
  In order to identify the test environment
  As an acceptance tester
  I need to be able to see the git branch and latest commit message

  Given I am logged in as an administrator
  Given a file named ".commit" with:
    """
      cacf5a1ae174810f50575478206055bd5668e058
    """
  Given a file named ".version" with:
    """
     2.1.39
    """
  When I visit "admin/reports/status"
  Then I should see "Platform Tag" in the "nept_element:system-status-report" element
  Then I should see "2.1.39" in the "nept_element:system-status-report" element
  # Test the absence of the file file with the installtion date
  Then I should see "Installation time" in the "nept_element:system-status-report" element
  Then I should see "Information not available on the server." in the "nept_element:system-status-report" element
  # Test that the commit is shown and links to Github.
  Then I should see "Commit number" in the "nept_element:system-status-report" element
  When I click 'cacf5a1ae174810f50575478206055bd5668e058'
  Then I should see the text "NEPT-1615"