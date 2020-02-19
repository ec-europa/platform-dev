@api @ec_resp
Feature: Administrators can check information on Recent log messages page
  In order to monitors the website
  As an administrator
  I can access to the Recent log messages page

@api
Scenario: Filter log messages
  Given I am logged in as a user with the 'administrator' role
  When I go to "admin/reports/dblog"
  And I select "info" from "Severity"
  And I press "Filter"
  Then I should see "dblog module installed." in the "system" row
  