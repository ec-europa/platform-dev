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
    And I am logged in as a user with the "administrator" role and I have the following fields:
      | name | admin_cart |
      | pass | admin_cart |

  @javascript
  Scenario: I can add contents to cart.
    Given I go to "admin/tmgmt/dgt_cart"
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

    When I click "cart" in the "front_messages" region
    Then I should see "Target languages: FR, PT"

    When I am not logged in
    And I am logged in as "admin_cart"
    And I click "Translation" in the "admin_menu"
    And I click "Small Jobs Cart" in the "back_primary_tabs"
    And I click "Edit" in the "Target languages: FR, PT" row
    And I wait for AJAX to finish
    Then I should see text matching "Translation Bundle content."

    When I fill in "Comment Page 1" for "Insert comment"
    And I press "Submit changes"
    And I wait for AJAX to finish
    Then I should see the message "Your changes have been successfully submitted."

    When I click "Close Window"
    And I click "Send" in the "Target languages: FR, PT" row
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then Poetry service received request should contain the following text:
      | W1JFRiBDb21tZW50IFBhZ2UgMS |

  @javascript @remove-menus
  Scenario: I can add menu and menu items to cart.
    Given I create a multilingual "test" menu called "Test menu"
    When I go to "admin/structure/menu/manage/test/translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see the success message "The content has been added to the cart."

    When I create a multilingual "Test" menu item pointing to "http://example.com" for the menu "test"
    And I go to "admin/structure/menu/manage/test"
    # TODO: Remove the following two steps and configure link properly on creation
    And I click "edit"
    And I press "Save"
    And I click "translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see the success message "The content has been added to the cart."

    When I click "cart" in the "messages" region
    And I click "Send" in the "Target languages: FR, PT" row
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the message "Job has been successfully sent for translation."
    And I should see text matching "Test menu \(menu\:menu\:test\) and 1 more"

  @javascript
  Scenario: I can add vocabolaries to cart.
    Given the vocabulary "Vocab" is created
    And the term "Term" in the vocabulary "Vocab" exists
    When I go to "admin/structure/taxonomy/vocab/edit"
    And I select the radio button "Localize. Terms are common for all languages, but their name and description may be localized."
    And the radio button "Localize" is selected
    And I press "Save"
    Then I should see "Updated vocabulary Vocab."

    When I go to "admin/structure/taxonomy/vocab/translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see the success message "The content has been added to the cart."

    When I go to "admin/structure/taxonomy/vocab"
    And I click "edit" in the "Term" row
    And I click "Translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    And I should see "The content has been added to the cart."

    When I click "cart" in the "messages" region
    And I click "Send" in the "Target languages: FR, PT" row
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the message "Job has been successfully sent for translation."
    And I should see text matching "Vocab \(taxonomy\:vocabulary\:\d\) and 1 more"
