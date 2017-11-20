@api
Feature: Automated logout
  In order to automate the action to log out from the platform
  As an administrator
  I want to make sure the session timeout works correctly to logout users automatically.

  Scenario: Administrator logout
    Given I am logged in as a user with the 'administrator' role
    Then  I should see the text "log out"
    Then  I should see the text "Welcome"
    When  I go to "/admin/content_en"
    Then  I should see the text "Manage content"
    When  I change the variable "autologout_timeout" to "3"
    When  I change the variable "autologout_padding" to "1"
    And   I wait 1 seconds
    When  I go to "/admin/content_en"
    Then  I should see the text "Manage content"
    And   I wait 5 seconds
    When  I go to "/admin/content_en"
    Then  I should get an access denied error
    And   I should not see the text "Manage content"
