@api
Feature: Multisite Drupal Toolbox
  In order to use all tools proposed by the Multisite Toolbox
  As a user
  I check all tools of this toolbox

  Scenario Outline:: Alert message - User that can see it
    Given I am logged in as a user with the '<role>' role
    When I run drush alert_message enable
    And I run drush "vset alert_message_body 'Alert Message for Administrator'"
    And I am on the homepage
    Then I should see the warning message "Alert Message for Administrator"
    When I run drush alert_message disable
    And I am on the homepage
    Then I should not see the warning message "Alert Message for Administrator"

    Examples:
      | role          |
      | administrator |

  Scenario Outline:: Alert message - User that can not see it
    Given I am logged in as a user with the '<role>' role
    When I run drush alert_message enable
    And I run drush "vset alert_message_body 'Alert Message for Administrator'"
    And I am on the homepage
    Then I should not see the warning message "Alert Message for Administrator"
    When I run drush alert_message disable
    And I am on the homepage
    Then I should not see the warning message "Alert Message for Administrator"

    Examples:
      | role                  |
      | anonymous user        |
      | authenticated user    |
      | editorial team member |
      | contributor           |
      | editor                |
