@api @i18n @poetry
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
    Then I should see the success message "1 content source was added into the cart."

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
    Then I should see the success message "1 content source was added into the cart."

    When I create a multilingual "Test" menu item pointing to "http://example.com" for the menu "test"
    And I go to "admin/structure/menu/manage/test"
    # TODO: Remove the following two steps and configure link properly on creation
    And I click "edit"
    And I press "Save"
    And I click "translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see the success message "1 content source was added into the cart."

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
  Scenario: I can add vocabularies to cart.
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
    Then I should see the success message "1 content source was added into the cart."

    When I go to "admin/structure/taxonomy/vocab"
    And I click "edit" in the "Term" row
    And I click "Translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    And I should see "1 content source was added into the cart."

    When I click "cart" in the "messages" region
    And I click "Send" in the "Target languages: FR, PT" row
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the message "Job has been successfully sent for translation."
    And I should see text matching "Vocab \(taxonomy\:vocabulary\:\d\) and 1 more"

  @javascript
  Scenario: I can add blocks and beans to cart.
    Given I go to "admin/config/regional/entity_translation"
    And I click "Translatable entity types"
    And I check the box "Block"
    And I press "Save configuration"
    Then I should see the message "The configuration options have been saved."

    When I create the new block type "New bean"
    And I go to "admin/structure/block-types"
    # It does not work without drush cc all
    And I run drush "cc" "all"
    And I click "manage fields" in the "New bean" row
    And I click "replace"
    And I check the box "Replace title with a field instance"
    And I press "Save settings"
    And I wait for the end of the batch job
    And I go to "/block/add"
    # When there is only one bean it goes directly to that bean's creation page
    # And I click "New bean"
    And I fill in "Label" with "Label for New bean Block"
    And I fill in "Title" with "Title for New bean Block"
    And I press "Save"
    Then I should see "New bean Title for New bean Block has been created."

    When I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see "1 content source was added into the cart."

    When I go to "/admin/structure/block/add"
    And I fill in "Block title" with "Title for New block"
    And I fill in "Block description" with "Description for New block"
    And I fill in the rich text editor "Block body" with "Body for New block."
    And I click "Not translatable, Not restricted"
    And I check the box "Make this block translatable"
    And I press the "Save and translate" button
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see "1 content source was added into the cart."

    When I click "cart" in the "front_messages" region
    And I click "Send" in the "Target languages: FR, PT" row
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the message "Job has been successfully sent for translation."
    And I should see text matching "Title for New bean Block and 1 more"

    # Delete created bean and blocks
    When I go to "admin/structure/block-types"
    And I click "Delete" in the "New bean" row
    And I press the "Delete" button
    And I go to "admin/structure/block"
    And I click "delete" in the "Description for New block" row
    And I press "Delete"
    Then I should see the message "The block Description for New block has been removed."

  Scenario: I can add views to cart.
    When I go to "admin/structure/views/view/core_content_administration/translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see the success message "1 content source was added into the cart."

    When I click "cart" in the "messages" region
    And I should see "Manage content (views:views:core_content_administration)" in the "views" row

  @javascript
  Scenario: I can add a Locale default to cart.
    When I go to "admin/tmgmt/sources/locale_default"
    And I check the box on the "An AJAX HTTP error occurred." row
    And I click "Operations"
    And I wait for AJAX to finish
    And I check the box "French"
    And I press "Send to cart"
    Then I should see the message "1 content source was added into the cart."

    When I click "cart" in the "messages" region
    And I click "Edit" in the "An AJAX HTTP error occurred." row
    And I wait for AJAX to finish
    Then I should see "Origin: misc/drupal.js" in the ".form-type-textarea > div > textarea" element

  Scenario: I can add metatags to cart.
    Given the module is enabled
      | modules |
      | metatag |
    When I go to "admin/config/search/metatags/config/global/translate"
    And I check the box on the "French" row
    And I check the box on the "Portuguese, Portugal" row
    And I press "Send to cart"
    Then I should see "1 content source was added into the cart."
