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
      | <documentSourceFile>PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4KPCFET0NUWVBFIGh0bWwgUFVCTElDICItLy9XM0MvL0RURCBYSFRNTCAxLjAgU3RyaWN0Ly9FTiIgImh0dHA6Ly93d3cudzMub3JnL1RSL3hodG1sMS9EVEQveGh0bWwxLXN0cmljdC5kdGQiPgo8aHRtbCB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94aHRtbCI+CiAgPGhlYWQ+CiAgICA8bWV0YSBodHRwLWVxdWl2PSJDb250ZW50LVR5cGUiIGNvbnRlbnQ9InRleHQvaHRtbDsgY2hhcnNldD1VVEYtOCIgLz4KICAgIDxtZXRhIG5hbWU9IkpvYklEIiBjb250ZW50PSIxIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VTb3VyY2UiIGNvbnRlbnQ9ImVuIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VUYXJnZXQiIGNvbnRlbnQ9ImZyIiAvPgogICAgPHRpdGxlPkpvYiBJRCAxPC90aXRsZT4KICA8L2hlYWQ+CiAgPGJvZHk+CiAgICAgICAgICA8ZGl2IGNsYXNzPSJhc3NldCIgaWQ9Iml0ZW0tMiI+CiAgICAgICAgICAgICAgICA8IS0tCiAgICAgICAgICBsYWJlbD0iY29udGV4dCIKICAgICAgICAtLT4KICAgICAgICA8ZGl2IGNsYXNzPSJjb250ZXh0IiBzdHlsZT0iY29sb3I6I2ZmMDAwMDsiPgogICAgICAgICAgW1JFRiBDb21tZW50IDEgTGluazogPGEgaHJlZj0iaHR0cDovL2xvY2FsaG9zdC9lY2V1cm9wYS9wbGF0Zm9ybS1kZXYvYnVpbGQvY29udGVudC9teS1wYWdlLTFfZW4iIHRhcmdldD0iYmxhbmsiPmh0dHA6Ly9sb2NhbGhvc3QvZWNldXJvcGEvcGxhdGZvcm0tZGV2L2J1aWxkL2NvbnRlbnQvbXktcGFnZS0xX2VuPC9hPl0KICAgICAgICA8L2Rpdj4KICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIDwhLS0KICAgICAgICAgIGxhYmVsPSJUaXRsZSIKICAgICAgICAgIGNvbnRleHQ9IlsyXVt0aXRsZV9maWVsZF1bMF1bdmFsdWVdIgogICAgICAgIC0tPgogICAgICAgIDxkaXYgY2xhc3M9ImF0b20iIGlkPSJiTWwxYmRHbDBiR1ZmWm1sbGJHUmRXekJkVzNaaGJIVmwiPk15IHBhZ2UgMTwvZGl2PgogICAgICAgICAgICAgICAgICAgICAgICAgIDwhLS0KICAgICAgICAgIGxhYmVsPSJCb2R5IgogICAgICAgICAgY29udGV4dD0iWzJdW2ZpZWxkX25lX2JvZHldWzBdW3ZhbHVlXSIKICAgICAgICAtLT4KICAgICAgICA8ZGl2IGNsYXNzPSJhdG9tIiBpZD0iYk1sMWJabWxsYkdSZmJtVmZZbTlrZVYxYk1GMWJkbUZzZFdVIj5TaG9ydCBib2R5PC9kaXY+CiAgICAgICAgICAgICAgPC9kaXY+CiAgICAgIDwvYm9keT4KPC9odG1sPgo=</documentSourceFile> |
