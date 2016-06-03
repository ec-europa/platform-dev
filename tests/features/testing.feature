@api
Feature: Testing
  In order to run simpletests
  As an administrator
  I want to be able to access to page listing tests

@api
Scenario: Administrator user can see the testing page
  Given the module is enabled
    |modules|
    |simpletest|
  Given I am logged in as a user with the 'administrator' role
  When I visit "admin/config/development/testing"
  Then I should see the text "Select the test(s) or test group(s) you would like to run, and click Run tests."