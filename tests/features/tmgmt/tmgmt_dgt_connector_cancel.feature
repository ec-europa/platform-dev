@api @poetry_mock @i18n @poetry
Feature: TMGMT Poetry features
  In order to manage Carts translations with Poetry service
  As an Administrator
  I want to be able to cancel translation requests

  Background:
    Given the module is enabled
      | modules                  |
      | tmgmt_dgt_connector_cart |
    And I am logged in as a user with the 'administrator' role
    And the following languages are available:
      | languages |
      | en        |
      | es        |
      | fr        |
    And I change the variable "nexteuropa_poetry_notification_username" to "foo"
    And I change the variable "nexteuropa_poetry_notification_password" to "bar"
    And I change the variable "nexteuropa_poetry_service_username" to "bar"
    And I change the variable "nexteuropa_poetry_service_password" to "foo"
    And I change the variable "nexteuropa_poetry_service_wsdl" to "http://localhost:28080/wsdl"
    And Poetry service uses the following settings:
    """
      username: foo
      password: bar
    """
    And the following Poetry settings:
    """
        address: http://localhost:28080/wsdl
        method: requestService
    """
    And Poetry will return the following "response.status" message response:
    """
    identifier:
      code: WEB
      year: 2017
      number: 1234
      version: 0
      part: 0
      product: TRA
    status:
      -
        type: request
        code: '0'
        date: 06/10/2017
        time: 02:41:53
        message: OK
    """

  Scenario: I can add contents to cart.
    Given I go to "admin/tmgmt/dgt_cart"
    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body | status |
      | en       | My page 1 | Short body    | 1      |
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I check the box on the "Spanish" row
    And I press "Send to cart"
    Then I should see the success message "1 content source was added into the cart."

    When I click "cart" in the "front_messages" region
    Then I should see "Target languages: FR, ES"

    When I click "Send" in the "Target languages: FR, ES" row
    And I press "Delete"
    And I press "Confirm"
    Then I should see "Deleted the translation job"

    When I visit the "page" content with title "My page 1"
    And I click "Translate" in the "primary_tabs" region
    Then I should not see the link "In progress"
    And I should see "Not translated" in the "Spanish" row
