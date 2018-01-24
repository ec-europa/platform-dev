@api @poetry_mock @i18n @poetry
Feature: TMGMT Poetry Cart features
  In order to request Carts translations with Poetry service.
  As an Administrator
  I want to be able to create/manage translation cart.

  Background:
    Given the module is enabled
      | modules                  |
      | tmgmt_poetry_mock        |
      | tmgmt_dgt_connector_cart |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |

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
    And I press "Submit to translator"
