@api @poetry @i18n
Feature: TMGMT Poetry permissions features
  In order to configure the DGT connector.
  As a CEM agent
  I should be able to browse and fill configuration pages for the connector.

  Background:
    Given I am logged in as a user with the "cem" role
    And the module is enabled
      |modules                       |
      |nexteuropa_dgt_connector      |

    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
    And I go to "admin/config/regional/tmgmt_translator/manage/poetry"

  Scenario Outline: Configuration fields are mandatory.

    Then I should see "<field_name>"
    And I press "Save translator"
    Then I should see "<field_name> field is required."
    Examples:
      | field_name         |
      | Counter            |
      | Requester code     |
      | Callback User      |
      | Callback Password  |
      | Poetry User        |
      | Poetry Password    |
      | Responsable        |
      | DG Author             |
      | Requester          |
      | Secretaire         |
      | Contact            |
      | Author             |
      | Responsible        |
      | Email to           |
      | Email CC           |

    Scenario: I should be able to fill in the configuration form and be notified
      when server config is missing
      When I fill in "Counter" with "NEXT_EUROPA_COUNTER"
      And I fill in "Requester code" with "WEB"
      And I fill in "Callback User" with "drupal_callback_user"
      And I fill in "Callback Password" with "drupal_callback_password"
      And I fill in "Poetry User" with "poetry_user"
      And I fill in "Poetry Password" with "poetry_password"
      And I fill in "Website identifier" with "my-website"
      And I fill in "Responsable" with "DIGIT"
      And I fill in "DG Author" with "IE/CE/DIGIT"
      And I fill in "Requester" with "IE/CE/DIGIT/A/3"
      And I fill in "Author" with "leperde"
      And I fill in "Secretaire" with "leperde"
      And I fill in "Contact" with "leperde"
      And I fill in "Responsible" with "leperde"
      And I fill in "Email to" with "delphine.lepers@badaboum.com"
      And I fill in "Email CC" with "delphine.lepers@badaboum.com"
      And I press "Save translator"
      Then I should see "The DGT webservice address is not set. Please contact your support team."
      And I should see "The credentials for your Drupal service are not correctly set. Please contact COMM EUROPA MANAGEMENT."
      And I should see "The credentials for your DGT service are not correctly set. Please contact COMM EUROPA MANAGEMENT."
