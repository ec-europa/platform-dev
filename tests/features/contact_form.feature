@api
Feature: Contact Form
  In order to allow sending emails to user without knowing their mail address
  As a citizen of the European Union
  I want to be able to access contact forms

Scenario: Anonymous user can see the contact page
  Given I am not logged in
  And the module is enabled
  | modules          |
  | contact_form     |
  When I am on "contact"
  Then I should see "Contact - European Commission" in the "html head title" element
  When I fill in "Your name" with "Chuck"
  And I fill in "Your e-mail address" with "Norris"
  And I fill in "Subject" with "Complaint"
  And I fill in "Message" with "I am not happy with this contact page"
  And I press the "Send message" button
  Then I should see the following success messages:
    | success messages                        |
    | Your message has been sent.             |


