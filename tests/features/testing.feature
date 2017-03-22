@api @communitites
Feature: Testing
  In order to run simpletests
  As an administrator
  I want to be able to access to page listing tests

@api
Scenario: Administrator user can see the testing page
  Given the module is enabled
    | modules    |
    | simpletest |

  Given I am logged in as a user with the 'administrator' role
  When I visit "admin/config/development"
  Then I should see the link "Testing"
  And I should see the text "Run tests against Drupal core and your active modules. These tests help assure that your site code is working as designed."