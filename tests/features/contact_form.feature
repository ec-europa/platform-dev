@api
Feature: Contact Form
  In order to allow sending emails to user without knowing their mail address
  As a citizen of the European Union
  I want to be able to access contact forms

  Background:
    Given the module is enabled
      | modules |
      | contact_form |

  @javascript @theme_wip
  # Failed with the EUROPA theme because of the bug covered by the ticket NEPT-1216.
  Scenario: Anonymous user can see the contact page
    Given I am not logged in
    And the module is enabled
      | modules      |
      | contact_form |
    When I am on "contact"
    Then I should see "Contact - European Commission" in the "title" tag
    When I fill in "Your name" with "Chuck"
    And I fill in "Your e-mail address" with "chuck.norris@improbabledommainname.com"
    And I fill in "Subject" with "Complaint"
    And I fill in "Message" with "I am not happy with this contact page"
    And I press the "Send message" button
    Then I should see the following error messages:
      | error messages                   |
      | Math question field is required. |

  @javascript @theme_wip
  # Failed with the EUROPA theme because of the bug covered by the ticket NEPT-1216.
  Scenario: Administrator user can submit the contact page
    Given I am logged in as a user with the administrator role
    And the module is enabled
      | modules      |
      | contact_form |
    When I am on "contact"
    Then I should see "Contact - European Commission" in the "title" tag
    And I should not see an "Your e-mail address" text form element
    And I should not see an "Your name" text form element
    When I fill in "Subject" with "Complaint"
    And I fill in "Message" with "I am not happy with this contact page"
    And I press the "Send message" button
    Then I should see the following success messages:
      | success messages              |
      | Your message has been sent. |

  @theme_wip
  # Wip for the europa theme because it implies a step referring a region.
  Scenario: Test that existing information is filled in for authenticated users
    Given users:
     | name               | mail                      | pass         | roles              |
     | authenticated_user | authenticated@user.com    | password123  | authenticated user |
    And I am logged in as "authenticated_user"
    When I am on "contact"
    Then I should see "authenticated@user.com" in the "content"
    And I should see "authenticated_user" in the "content"

  Scenario Outline: Test that email must be valid
    Given I am not logged in
    When I am on "contact"
    And I fill in "edit-mail" with "<mail>"
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

  Scenario: Verify that mail is sent when anonymous (captcha disabled)
    #Disable captcha while testing
    Given I am logged in as a user with the 'administrator' role
    When I am on "/admin/config/people/captcha_en"
    And I select "- No challenge -" from "edit-captcha-form-id-overview-captcha-captcha-points-contact-site-form-captcha-type"
    And I press the "Save configuration" button
    Then I should see the text "The CAPTCHA settings have been saved."
    #Test the form submission
    Given I am not logged in
    When I am on "contact"
    When I fill in "Your name" with "name"
    And I fill in "Your e-mail address" with "test@test.com"
    And I fill in "Subject" with "Subject"
    And I fill in "Message" with "Message"
    And I press the "Send message" button
    Then I should see the text "Your message has been sent."
