@api @internalMail
Feature: Drupal Mail features
  In order to check if a mail was sent correctly
  As an Administrator
  I want to be able to catch the mail and verify its properties

  Background:
    Given platform is configured to use the internal mail handling

  Scenario: Checking mail action for requesting new password.
    When I go to "/user"
    And I click "Request new password" in the "primary_tabs" region
    And I fill in "Username or e-mail address" with "admin"
    And I press "E-mail new password"
    Then I should see the success message "Further instructions have been sent to your e-mail address."
    And the internal mail handler received the mail
    And the captured mail has the following properties:
      | from        | admin@example.com                                     |
      | to          | admin@example.com                                     |
      | subject     | Replacement login information for admin at NextEuropa |
