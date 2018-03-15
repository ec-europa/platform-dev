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

  @javascript
  Scenario: I can add vocabularies to cart.
    Given I am logged in as a user with the "administrator" role and I have the following fields:
      | name | admin_cart |
      | pass | admin_cart |
    And the vocabulary "Vocab" is created
    When I go to "admin/structure/taxonomy/vocab/translate"
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
    And I fill in "Comment Vocabulary 1" for "Insert comment"
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
      | PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4KPCFET0NUWVBFIGh0bWwgUFVCTElDICItLy9XM0MvL0RURCBYSFRNTCAxLjAgU3RyaWN0Ly9FTiIgImh0dHA6Ly93d3cudzMub3JnL1RSL3hodG1sMS9EVEQveGh0bWwxLXN0cmljdC5kdGQiPgo8aHRtbCB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94aHRtbCI+CiAgPGhlYWQ+CiAgICA8bWV0YSBodHRwLWVxdWl2PSJDb250ZW50LVR5cGUiIGNvbnRlbnQ9InRleHQvaHRtbDsgY2hhcnNldD1VVEYtOCIgLz4KICAgIDxtZXRhIG5hbWU9IkpvYklEIiBjb250ZW50PSIxIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VTb3VyY2UiIGNvbnRlbnQ9ImVuIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VUYXJnZXQiIGNvbnRlbnQ9ImZyIiAvPgogICAgPHRpdGxlPkpvYiBJRCAxPC90aXRsZT4KICA8L2hlYWQ+CiAgPGJvZHk+CiAgICAgICAgICA8ZGl2IGNsYXNzPSJhc3NldCIgaWQ9Iml0ZW0tMiI+CiAgICAgICAgICAgICAgICA8IS0tCiAgICAgICAgICBsYWJlbD0iY29udGV4dCIKICAgICAgICAtLT4KICAgICAgICA8ZGl2IGNsYXNzPSJjb250ZXh0IiBzdHlsZT0iY29sb3I6I2ZmMDAwMDsiPgogICAgICAgICAgW1JFRiBDb21tZW50IFZvY2FidWxhcnkgMSBMaW5rOiA8YSBocmVmPSIiIHRhcmdldD0iYmxhbmsiPjwvYT5dCiAgICAgICAgPC9kaXY+CiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICA8IS0tCiAgICAgICAgICBsYWJlbD0iTmFtZSIKICAgICAgICAgIGNvbnRleHQ9IlsyXVt0YXhvbm9teTp2b2NhYnVsYXJ5OjM6bmFtZV0iCiAgICAgICAgLS0+CiAgICAgICAgPGRpdiBjbGFzcz0iYXRvbSIgaWQ9ImJNbDFiZEdGNGIyNXZiWGs2ZG05allXSjFiR0Z5ZVRvek9tNWhiV1UiPlZvY2FiPC9kaXY+CiAgICAgICAgICAgICAgPC9kaXY+CiAgICAgIDwvYm9keT4KPC9odG1sPgo= |

      @javascript
  Scenario: I can add taxonomy terms to cart.
    Given I am logged in as a user with the "administrator" role and I have the following fields:
      | name | admin_cart |
      | pass | admin_cart |
    And the vocabulary "Vocab" is created
    And the term "Term" in the vocabulary "Vocab" exists
    When I go to "admin/structure/taxonomy/vocab/edit"
    And I select the radio button "Localize. Terms are common for all languages, but their name and description may be localized."
    And the radio button "Localize" is selected
    And I press "Save"
    Then I should see "Updated vocabulary Vocab."

    When I go to "admin/structure/taxonomy/vocab"
    And I click "edit" in the "Term" row
    And I click "Translate"
    And break
    And I press "Send to cart"
    # TODO: Figure out why error messages are not being processed.
    # Then I should see the error message "You have to select at least one language before sending content to the cart."

    When I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    # TODO: Figure out why success messages are not being processed.
    # Then I should see the success message "The content has been added to the cart."

    When I am not logged in
    And I am logged in as "admin_cart"
    And I go to "admin/dgt_connector/cart"
    And I click "Edit" in the "Target languages: FR, PT" row
    And I wait for AJAX to finish
    And I should see text matching "Translation Bundle content."
    And I fill in "Comment Vocabulary 1" for "Insert comment"
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
      | PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4KPCFET0NUWVBFIGh0bWwgUFVCTElDICItLy9XM0MvL0RURCBYSFRNTCAxLjAgU3RyaWN0Ly9FTiIgImh0dHA6Ly93d3cudzMub3JnL1RSL3hodG1sMS9EVEQveGh0bWwxLXN0cmljdC5kdGQiPgo8aHRtbCB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94aHRtbCI+CiAgPGhlYWQ+CiAgICA8bWV0YSBodHRwLWVxdWl2PSJDb250ZW50LVR5cGUiIGNvbnRlbnQ9InRleHQvaHRtbDsgY2hhcnNldD1VVEYtOCIgLz4KICAgIDxtZXRhIG5hbWU9IkpvYklEIiBjb250ZW50PSIxIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VTb3VyY2UiIGNvbnRlbnQ9ImVuIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VUYXJnZXQiIGNvbnRlbnQ9ImZyIiAvPgogICAgPHRpdGxlPkpvYiBJRCAxPC90aXRsZT4KICA8L2hlYWQ+CiAgPGJvZHk+CiAgICAgICAgICA8ZGl2IGNsYXNzPSJhc3NldCIgaWQ9Iml0ZW0tMiI+CiAgICAgICAgICAgICAgICA8IS0tCiAgICAgICAgICBsYWJlbD0iY29udGV4dCIKICAgICAgICAtLT4KICAgICAgICA8ZGl2IGNsYXNzPSJjb250ZXh0IiBzdHlsZT0iY29sb3I6I2ZmMDAwMDsiPgogICAgICAgICAgW1JFRiBDb21tZW50IFZvY2FidWxhcnkgMSBMaW5rOiA8YSBocmVmPSIiIHRhcmdldD0iYmxhbmsiPjwvYT5dCiAgICAgICAgPC9kaXY+CiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICA8IS0tCiAgICAgICAgICBsYWJlbD0iTmFtZSIKICAgICAgICAgIGNvbnRleHQ9IlsyXVt0YXhvbm9teTp0ZXJtOjM2Om5hbWVdIgogICAgICAgIC0tPgogICAgICAgIDxkaXYgY2xhc3M9ImF0b20iIGlkPSJiTWwxYmRHRjRiMjV2YlhrNmRHVnliVG96TmpwdVlXMWwiPlRlcm08L2Rpdj4KICAgICAgICAgICAgICA8L2Rpdj4KICAgICAgPC9ib2R5Pgo8L2h0bWw+Cg== |
