@api @i18n @poetry
Feature: TMGMT Poetry features
  In order to request Carts translations with Poetry service.
  As an Administrator
  I want to be able to create/manage translation requests.

  Background:
    Given the module is enabled
      | modules             |
      | tmgmt_dgt_connector |
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |
    And I am logged in as a user with the "administrator" role
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
  Scenario: I can translate contents with TMGMT Cart.
    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body |
      | en       | My page 1 | Short body    |
    And I click "Translate" in the "primary_tabs" region
    Then I should see "There are 0 items in the translation cart."

    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart."

    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body |
      | en       | My page 2 | Short body 2  |
    And I click "Translate" in the "primary_tabs" region
    Then I should see "There is 1 item in the translation cart."

    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There are 2 items in the translation cart."

    When I click "cart" in the "front_messages" region
    And I check the box on the "My page 1" row
    And I check the box on the "My page 2" row
    And I select "French" from "Request translation into language/s" with javascript
    And I select "Portuguese, Portugal" from "Request translation into language/s" with javascript
    And I press "Request translation"
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
    Then I should see the success message containing "Job has been successfully sent for translation."

    When I visit the "page" content with title "My page 2"
    And I click "Translate" in the "primary_tabs" region
    And I click "In progress" in the "French" row
    And I press "Save"
    And I click "Needs review" in the "French" row
    When I fill in the following:
      | edit-title-field0value-translation   | FR My Page 2    |
      | edit-field-ne-body0value-translation | FR Short body 2 |
    And I press "Save as completed"
    Then I should see "None" in the "French" row

  Scenario: I can translate menus with TMGMT Cart.
    When I go to "admin/structure/menu/manage/user-menu/translate"
    Then I should see "There are 0 items in the translation cart."

    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart including the current item."

    When I click "cart" in the "messages" region
    And I should see "User menu (menu:menu:user-menu)"

  Scenario: I can translate vocabularies with TMGMT Cart.
    When I go to "admin/structure/taxonomy/classification/translate"
    Then I should see "There are 0 items in the translation cart."

    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart including the current item."

    When I click "cart" in the "messages" region
    Then I should see "classification (taxonomy:vocabulary:1)"

  Scenario: I can translate terms with TMGMT Cart.
    When I go to "admin/structure/taxonomy/classification/edit"
    And I select the radio button "Localize. Terms are common for all languages, but their name and description may be localized."
    And I press "Save and translate"
    Then I should see the success message "Updated vocabulary classification."
    And I should see "There are 0 items in the translation cart."

    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart including the current item."

    When I click "cart" in the "messages" region
    Then I should see "classification (taxonomy:vocabulary:1)"

  Scenario: I can translate blocks with TMGMT Cart.
    When I go to "admin/structure/block/manage/user/login/configure"
    And I check the box "Make this block translatable"
    And I press "Save and translate"
    Then I should see the success message "The block configuration has been saved."
    And I should see "There are 0 items in the translation cart."

    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart including the current item."

    When I click "cart" in the "front_messages" region
    Then I should see "(blocks:user:login)"

  Scenario: I can translate strings with TMGMT Cart.
    When I go to "admin/tmgmt/sources/locale_default?label=Edit"
    And I check the box on the "Edit" row
    And I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."

    When I click "cart" in the "messages" region
    Then I should see "Edit"
