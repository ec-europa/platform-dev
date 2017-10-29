@api
Feature: Contact module
  In order to test fields are filled and valid
  As an administrator user
  I want to be able to verify contact data and send a contact mail

  Background:
    Given the module is enabled
      | modules |
      | contact |
    Given I am logged in as a user with the 'administrator' role

  Scenario: Test that existing email adress is filled in for authenticated users
    Given I go to "/user"
    And I click "Edit"
    Then the "E-mail address *" field should not contain ""
    When I fill in "E-mail address *" with ""
    And I press the "Save" button
    Then I should see the text "E-mail address field is required."

  Scenario: Test that existing name is required in for authenticated users
    Given I go to "/user"
    And I click "Edit"
    When I fill in "First name *" with "test"
    When I fill in "Last name *" with "test"
    Then the "name" field should not contain ""
    When I fill in "name" with ""
    And I press the "Save" button
    Then I should see the text "Username field is required."

  Scenario: Test that email must be valid
    Given I go to "/user"
    And I click "Edit"

    Then I fill in "E-mail address *" with "plainaddress"
    And I press the "Save" button
    Then I should see the text "The e-mail address plainaddress is not valid."

    Then I fill in "E-mail address *" with "#@%^%#$@#$@#.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address #@%^%#$@#$@#.com is not valid."

    Then I fill in "E-mail address *" with "@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address @example.com is not valid."

    Then I fill in "E-mail address *" with "Joe Smith <email@example.com>"
    And I press the "Save" button
    Then I should see the text "The e-mail address Joe Smith <email@example.com> is not valid."

    Then I fill in "E-mail address *" with "email.example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address email.example.com is not valid."

    Then I fill in "E-mail address *" with "email@example@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address email@example@example.com is not valid."

    Then I fill in "E-mail address *" with ".email@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address .email@example.com is not valid."

    Then I fill in "E-mail address *" with "email.@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address email.@example.com is not valid."

    Then I fill in "E-mail address *" with "email..email@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address email..email@example.com is not valid."

    Then I fill in "E-mail address *" with "あいうえお@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address あいうえお@example.com is not valid."

    Then I fill in "E-mail address *" with "email@example.com (Joe Smith)"
    And I press the "Save" button
    Then I should see the text "The e-mail address email@example.com (Joe Smith) is not valid."

    Then I fill in "E-mail address *" with "email@example"
    And I press the "Save" button
    Then I should see the text "The e-mail address email@example is not valid."

    Then I fill in "E-mail address *" with "email@-example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address email@-example.com is not valid."

    Then I fill in "E-mail address *" with "email@111.222.333.44444"
    And I press the "Save" button
    Then I should see the text "The e-mail address email@111.222.333.44444 is not valid."

    Then I fill in "E-mail address *" with "email@example..com"
    And I press the "Save" button
    Then I should see the text "The e-mail address email@example..com is not valid."

    Then I fill in "E-mail address *" with "Abc..123@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address Abc..123@example.com is not valid."

    Then I fill in "E-mail address *" with "”(),:;<>[\]@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address ”(),:;<>[\]@example.com is not valid."

    Then I fill in "E-mail address *" with "just”not”right@example.com"
    And I press the "Save" button
    Then I should see the text "The e-mail address just”not”right@example.com is not valid."

  Scenario: Verify that mail is sent after the captcha is filled in when anonymous
    #Anonymous user permission to see contact form
    Given I go to "/admin/people/permissions_en"
    Then I check "edit-1-access-user-contact-forms"
    And I press the "Save permissions" button
    Then I should see the text "The changes have been saved."
    When I go to "/user"
    And I click "Edit"
    Then I check "Personal contact form"
    When I fill in "First name *" with "test"
    When I fill in "Last name *" with "test"
    And I fill in "Username" with "test"
    And I press the "Save" button
    Then I should see the text "Contact"
    Then I should see the text "The changes have been saved."
    #Disable captcha while testing
    When I am on "/admin/config/people/captcha_en"
    And I select "- No challenge -" from "edit-captcha-form-id-overview-captcha-captcha-points-contact-personal-form-captcha-type"
    And I press the "Save configuration" button
    Then I should see the text "The CAPTCHA settings have been saved."
    #Test the form submission
    Given I am not logged in
    When I am on "/user/11/contact_en"
    When I fill in "Your name" with "name"
    And I fill in "Your e-mail address" with "test@test.com"
    And I fill in "Subject" with "Subject"
    And I fill in "Message" with "Message"
    And I press the "Send message" button
    Then I should see the text "Your message has been sent."
