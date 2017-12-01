@api
Feature: newsletter feature
  In order to add newsletter subscriptions functionality
  As a user
  I want to be able to manage newsletters and subscribe to them

  Background:
    Given the module is enabled
      | modules               |
      | bounce                |
      | mailsystem            |
      | mimemail              |
      | simplenews            |
      | simplenews_statistics |
      | newsletters           |

  Scenario: manage suscriptions
    Given I am logged in as a user with the 'administrator' role
    And   I go to "/admin/config/services/simplenews/add_en"
    When  I fill in "Name" with "Newsletter behat category"
    And   I fill in "Description" with "Description of Newsletteer behat category"
    When  I check the box "Subscription block"
    And   I press "Save"
    And   I go to "/admin/config/services/simplenews"
    Then  I should see the "edit newsletter category" in the "Newsletter behat category" row

  @javascript
  Scenario: create newsletter
    Given I am logged in as a user with the 'administrator' role
    When  I go to "node/add/simplenews"
    Then  I should see the text "Create Simplenews newsletter"
    When  I fill in "title" with "Newsletter behat"
    And   I fill in the rich text editor "Body" with "body for Newsletter behat"
    And   I select the radio button "NextEuropa newsletter"
    And   I press "Save"
    Then  I should see the text "Simplenews newsletter Newsletter behat has been created"

  Scenario: browse and request subscription to Newsletter for logged users
    Given I am logged in as a user with the 'administrator' role and I have the following fields:
      | mail | admin@test.com |
    When  I go to "/my_subscriptions"
    Then  I should see the link "Newsletters"
    And   I click "Newsletters"
    Then  I should see the heading "Newsletters"
    When  I check the box "NextEuropa newsletter"
    And   I press "Update"
    Then  I should see the text "The newsletter subscriptions for admin@test.com have been updated"

  Scenario: browse and request subscription to Newsletter for anonymous users
    Given I am not logged in
    When  I click "Newsletters"
    Then  I should see the heading "Newsletters"
    When  I check the box "NextEuropa newsletter"
    And   I fill in "E-mail" with "test@test.com"
    And   I press "Subscribe"
    Then  I should see the text "You will receive a confirmation e-mail shortly containing further instructions on how to complete your subscription"
