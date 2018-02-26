@api @poetry_mock @i18n @poetry @theme_wip
Feature: TMGMT Poetry Cart features
  In order to request Carts translations with Poetry service.
  As an Administrator
  I want to be able to create/manage translation cart.

  Background:
    Given the module is enabled
      | modules                  |
      | tmgmt_dgt_connector_cart |
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
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

  @javascript
  Scenario: I can add contents to cart.
    Given I am logged in as a user with the "administrator" role and I have the following fields:
      | name | admin_cart |
      | pass | admin_cart |
    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body | status |
      | en       | My page 1 | Short body    | 1      |
    And I click "Translate" in the "primary_tabs" region
    And I press "Send to cart"
    Then I should see the error message "You have to select at least one language before sending content to the cart."

    When I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see the success message "The content has been added to the cart."

    When I am not logged in
    And I am logged in as "admin_cart"
    And I go to "admin/dgt_connector/cart"
    And I click "Edit" in the "Target languages: FR, PT" row
    And I wait for AJAX to finish
    And I should see text matching "Translation Bundle content."
    And I fill in "Comment Page 1" for "Insert comment"
    And I press "Submit changes"
    And I wait for AJAX to finish
    Then I should see the message "Your changes have been successfully submitted."

    When I click "Close Window"
    And I click "Send" in the "Target languages: FR, PT" row
    # Checkout page
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
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
    And I press "Submit to translator"
    Then Poetry service received request should contain the following text:
      | W1JFRiBDb21tZW50IFBhZ2UgMS |
