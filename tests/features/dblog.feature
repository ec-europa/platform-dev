@api @ec_resp
Feature: Administrators can check information on Recent log messages page
  In order to monitors the website
  As an administrator
  I can access to the Recent log messages page

@api  @javascript
Scenario: Filter log messages
  Given I am logged in as a user with the 'administrator' role
  When I go to "admin/reports/dblog"
  And I click on element "#dblog-filter-form a.fieldset-title"
  And I click on element "#edit_severity_chosen ul.chosen-choices"
  And I click on element "#edit_severity_chosen li.active-result[data-option-array-index='5']"
  And I press "Filter"
  Then I should see "Session opened for" in the "user" row
  