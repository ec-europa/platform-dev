@api @ec_resp
Feature: Administrators can check information on Recent log messages page
  In order to monitors the website
  As an administrator
  I can access to the Recent log messages page

@api  @javascript
Scenario: Filter log messages
  Given I am logged in as a user with the 'administrator' role
  When I go to "admin/reports/dblog"
  Then I click on element "#dblog-filter-form a.fieldset-title"
  And I click on element "#edit-severity"
  And I select "info" from "Severity"
  And I press "Filter"
  Then I should see "Session opened for" in the "user" row
  