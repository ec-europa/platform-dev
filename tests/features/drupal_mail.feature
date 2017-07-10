@api @internalMail
Feature: Drupal Mail features
  In order to check if a mail was sent correctly
  As an Administrator
  I want to be able to catch the mail and verify its properties

  Background:
    Given platform is configured to use the internal mail handling
    And users:
      | name  | mail         | roles        |
      | foo   | foo@bar.com  | contributor  |

  @theme_wip
  Scenario: Checking the basic mail functionality for requesting new password by using the username as identifier.
    When I go to "/user"
    And I click "Request new password" in the "primary_tabs" region
    And I fill in "Username or e-mail address" with "foo"
    And I press "E-mail new password"
    Then I should see the success message "Further instructions have been sent to your e-mail address."
    And the e-mail has been sent
    And the sent e-mail has the following properties:
      | from        | admin@example.com                                   |
      | to          | foo@bar.com                                         |
      | subject     | Replacement login information for foo at NextEuropa |
