@api @poetry
Feature: TMGMT Auto accept features
  In order to test the file plugin with auto accept enabled.
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
  Scenario: Validate max field length when TMGMT Auto accept is enabled.
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/config/regional/tmgmt_translator/manage/tmgmt_dgt_connector"
    And I check the box "Auto accept finished translations"
    And I fill in "Counter" with "NEXT_EUROPA_COUNTER"
    And I fill in "Requester code" with "WEB"
    And I fill in "Callback User" with "drupal_callback_user"
    And I fill in "Callback Password" with "drupal_callback_password"
    And I fill in "Poetry User" with "poetry_user"
    And I fill in "Poetry Password" with "poetry_password"
    And I fill in "Website identifier" with "my-website"
    And I fill in "Responsable" with "DIGIT"
    And I fill in "DG Author" with "IE/CE/DIGIT"
    And I fill in "Requester" with "IE/CE/DIGIT/A/3"
    And I fill in "Author" with "limaari"
    And I fill in "Secretaire" with "limaari"
    And I fill in "Contact" with "limaari"
    And I fill in "Responsible" with "limaari"
    And I fill in "Email to" with "limaari@sapo.pt"
    And I fill in "Email CC" with "limaari@sapo.pt"
    And I press the "Save translator" button
    Then I should see the success message "The configuration options have been saved."

    When I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "English title to validate the field while sending to translation with auto accept enabled."
    And I fill in "Body" with "The title max length is 255 characters, if this limit is exceeded an error will be through before trying to save the data in database, due to the validation on the needsReview process which check the translation data against field limit."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the message "Job has been successfully sent for translation."

    When I visit the "page" content with title "Tile max chars is 255."
    And I click "Translate" in the "primary_tabs" region
    And I click "In progress" in the "French" row
    When I fill in the following:
      | edit-title-field0value-translation   | FR MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX CHARACTERs 255 MAX END! |
    And I press "Save"
    Then I should see the message "Translation cannot be longer than 255 characters but is currently 258 characters long."
