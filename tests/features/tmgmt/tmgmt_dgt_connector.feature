@api @poetry_mock @i18n @poetry
Feature: TMGMT Poetry features
  In order to request Carts translations with Poetry service.
  As an Administrator
  I want to be able to create/manage translation requests.

  Background:
    Given the module is enabled
      | modules             |
      | tmgmt_poetry_mock   |
      | tmgmt_dgt_connector |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |
    And I am logged in as a user with the "administrator" role

  @javascript
  Scenario: I can translate contents with Carts.
    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body | status |
      | en       | My page 1 | Short body    | 1      |
    And I click "Translate" in the "primary_tabs" region
    Then I should see "There are 0 items in the translation cart."
    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart."
    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body | status |
      | en       | My page 2 | Short body 2  | 1      |
    And I click "Translate" in the "primary_tabs" region
    Then I should see "There is 1 item in the translation cart."
    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There are 2 items in the translation cart."
    When I click "cart" in the "front_messages" region
    # Cart page
    And I check the box on the "My page 1" row
    And I check the box on the "My page 2" row
    And I select "French" from "Request translation into language/s" with javascript
    And I select "Spanish" from "Request translation into language/s" with javascript
    And I press "Request translation"
    # Checkout page
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    # Then I should not see the error message "There was an error with the SOAP service."


  Scenario: I can translate menus with Carts.
    When I go to "admin/structure/menu/manage/user-menu/translate"
    Then I should see "There are 0 items in the translation cart."
    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart including the current item."
    When I click "cart" in the "messages" region
    And I should see "User menu (menu:menu:user-menu)"

  Scenario: I can translate vocabularies with Carts.
    When I go to "admin/structure/taxonomy/classification/translate"
    Then I should see "There are 0 items in the translation cart."
    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart including the current item."
    When I click "cart" in the "messages" region
    Then I should see "classification (taxonomy:vocabulary:1)"

  Scenario: I can translate terms with Carts.
    When I go to "admin/structure/taxonomy/classification/edit"
    And I select the radio button "Localize. Terms are common for all languages, but their name and description may be localized."
    And I press "Save and translate"
    Then I should see the success message "Updated vocabulary classification."
    And I should see "There are 0 items in the translation cart."
    And I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart including the current item."
    When I click "cart" in the "messages" region
    Then I should see "classification (taxonomy:vocabulary:1)"

  Scenario: I can translate blocks with Carts.
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

  Scenario: I can translate strings with Carts.
    When I go to "admin/tmgmt/sources/locale_default?label=Edit"
    And I check the box on the "Edit" row
    And I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    When I click "cart" in the "messages" region
    Then I should see "Edit"
