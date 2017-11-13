@api
Feature: Contact module
  In order to test fields are filled and valid
  As an administrator user
  I want to be able to verify contact data and send a contact mail

  Background:
    Given the module is enabled
      | modules |
      | contact_form |

  Scenario: Test that existing email adress is filled in for authenticated users
    Given I am logged in as a user with the "authenticated user" role
    Given I go to "/user"
    And I click "Edit"
    Then the "E-mail address *" field should not contain ""
    When I fill in "E-mail address *" with ""
    And I press the "Save" button
    Then I should see the text "E-mail address field is required."

  Scenario: Test that existing name is filled in for authenticated users
    Given I am logged in as a user with the "authenticated user" role
    Given I go to "/user"
    And I click "Edit"
    #Then the "First name *" field should not contain ""
    When I fill in "First name *" with ""
    And I press the "Save" button
    Then I should see the text "First name field is required."

  Scenario Outline: Test that email must be valid
    Given I am not logged in
    Then I go to "/contact"
    Then I fill in "edit-mail" with "<mail>"
    And I press the "Send message" button
    Then I should see the text "You must enter a valid e-mail address."

    Examples:
    | mail                          |
    | plainaddress                  |
    | #@%^%#$@#$@#.com              |
    | @example.com                  |
    | Joe Smith <email@example.com> |
    | email.example.com             |
    | email@example@example.com     |
    | .email@example.com            |
    | email.@example.com            |
    | email..email@example.com      |
    | あいうえお@example.com           |
    | email@example.com (Joe Smith) |
    | email@example                 |
    | email@-example.com            |
    | email@111.222.333.44444       |
    | email@example..com            |
    | Abc..123@example.com          |
    | ”(),:;<>[\]@example.com       |
    | just”not”right@example.com    |

  Scenario: Verify that mail is sent after the captcha is filled in when anonymous
    #Disable captcha while testing
    Given I am logged in as a user with the 'administrator' role
    When I am on "/admin/config/people/captcha_en"
    And I select "- No challenge -" from "edit-captcha-form-id-overview-captcha-captcha-points-contact-site-form-captcha-type"
    And I press the "Save configuration" button
    Then I should see the text "The CAPTCHA settings have been saved."
    #Test the form submission
    Given I am not logged in
    When I am on "/contact"
    When I fill in "Your name" with "name"
    And I fill in "Your e-mail address" with "test@test.com"
    And I fill in "Subject" with "Subject"
    And I fill in "Message" with "Message"
    And I press the "Send message" button
    Then I should see the text "Your message has been sent."
