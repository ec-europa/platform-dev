@api @poetry_mock @i18n @poetry
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
    Given I change the variable "nexteuropa_poetry_notification_username" to "foo"
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
    When I press "Send to cart"
    Then I should see the error message "You have to select at least one language before sending content to the cart."
    When I check the box on the "French" row
    When I check the box on the "Portuguese, Portugal" row
    When I press "Send to cart"
    Then I should see the success message "The content has been added to the cart."
    When I am not logged in
    When I am logged in as "admin_cart"
    And I go to "admin/dgt_connector/cart"
    Then I should see text matching "Languages: FR, PT"
    When I click "edit" in the "Type: node | Title: My page 1" row
    And I wait for AJAX to finish
    And I should see text matching "Translation Bundle content."
    And I fill in "http://example.com" for "Insert URL"
    And I fill in "Comment 1" for "Insert comment"
    And I press "Submit changes"
    And I wait for AJAX to finish
    Then I should see the message "Your changes have been successfully submitted."
    When I click "Close Window"
    And I check the radio button in the "Type: node | Title: My page 1" row
    And I press "Send bundles"
    And I press "Confirm"
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
      | <documentSourceFile>PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4NCjwhRE9DVFlQRSBodG1sIFBVQkxJQyAiLS8vVzNDLy9EVEQgWEhUTUwgMS4wIFN0cmljdC8vRU4iICJodHRwOi8vd3d3LnczLm9yZy9UUi94aHRtbDEvRFREL3hodG1sMS1zdHJpY3QuZHRkIj4NCjxodG1sIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hodG1sIj4NCiAgPGhlYWQ+DQogICAgPG1ldGEgaHR0cC1lcXVpdj0iQ29udGVudC1UeXBlIiBjb250ZW50PSJ0ZXh0L2h0bWw7IGNoYXJzZXQ9VVRGLTgiIC8+DQogICAgPG1ldGEgbmFtZT0iSm9iSUQiIGNvbnRlbnQ9IjEiIC8+DQogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VTb3VyY2UiIGNvbnRlbnQ9ImVuIiAvPg0KICAgIDxtZXRhIG5hbWU9Imxhbmd1YWdlVGFyZ2V0IiBjb250ZW50PSJmciIgLz4NCiAgICA8dGl0bGU+Sm9iIElEIDE8L3RpdGxlPg0KICA8L2hlYWQ+DQogIDxib2R5Pg0KICAgICAgICAgIDxkaXYgY2xhc3M9ImFzc2V0IiBpZD0iaXRlbS0yIj4NCiAgICAgICAgICAgICAgICA8IS0tDQogICAgICAgICAgbGFiZWw9ImNvbnRleHQiDQogICAgICAgIC0tPg0KICAgICAgICA8ZGl2IGNsYXNzPSJjb250ZXh0IiBzdHlsZT0iY29sb3I6I2ZmMDAwMDsiPg0KICAgICAgICAgIFtSRUYgQ29tbWVudCAxIExpbms6IDxhIGhyZWY9Imh0dHA6Ly9leGFtcGxlLmNvbSIgdGFyZ2V0PSJibGFuayI+aHR0cDovL2V4YW1wbGUuY29tPC9hPl0NCiAgICAgICAgPC9kaXY+DQogICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgPCEtLQ0KICAgICAgICAgIGxhYmVsPSJUaXRsZSINCiAgICAgICAgICBjb250ZXh0PSJbMl1bdGl0bGVfZmllbGRdWzBdW3ZhbHVlXSINCiAgICAgICAgLS0+DQogICAgICAgIDxkaXYgY2xhc3M9ImF0b20iIGlkPSJiTWwxYmRHbDBiR1ZmWm1sbGJHUmRXekJkVzNaaGJIVmwiPk15IHBhZ2UgMTwvZGl2Pg0KICAgICAgICAgICAgICAgICAgICAgICAgICA8IS0tDQogICAgICAgICAgbGFiZWw9IkJvZHkiDQogICAgICAgICAgY29udGV4dD0iWzJdW2ZpZWxkX25lX2JvZHldWzBdW3ZhbHVlXSINCiAgICAgICAgLS0+DQogICAgICAgIDxkaXYgY2xhc3M9ImF0b20iIGlkPSJiTWwxYlptbGxiR1JmYm1WZlltOWtlVjFiTUYxYmRtRnNkV1UiPlNob3J0IGJvZHk8L2Rpdj4NCiAgICAgICAgICAgICAgPC9kaXY+DQogICAgICA8L2JvZHk+DQo8L2h0bWw+DQo=</documentSourceFile> |
