@api @javascript @communities @internalMail
Feature: User notifications
  In order to allow users to stay informed of new content
  As a site administrator
  I want to make sure auhtenticated users can subscribe to content on the site

  Background:
    Given users:
      | name          | mail                 | pass         | roles              |
      | administrator | adminis@example.com  | password123  | administrator      |
      | authuser      | authuser@example.com | password456  | authenticated user |
    And these featureSet are enabled
      | featureSet     |
      | Notifications  |
    And these modules are enabled
      | modules    |
      | mailsystem |
    And platform is configured to use the internal mail handling
    And 'Article' content:
      | title       | author        | workbench_moderation_state_new | workbench_moderation_state | language | status |
      | Article sub | administrator | published                      | published                  | en       | 1      |
    And I am logged in as "authuser"

  Scenario: As an Authorized user I can subscribe to a content, content type and content type by user
    Given I visit the "Article" content with title "Article sub"
    And I click "Subscribe"
    And I check the box "Subscribe to this page"
    And I check the box "To Article content"
    And I check the box "To Article content by"
    And I press the "Save" button
    And I go to "user"
    And I click "Subscriptions"
    Then I should see the text "1" in the "Pages/Threads" row
    Then I should see the text "2" in the "Content types" row
    When I click "Pages/Threads"
    Then I should see the text "Article sub"

  Scenario: As an Authorized user I receive an email when a content I am subscribed to is updated
    Given I visit the "Article" content with title "Article sub"
    And I click "Subscribe"
    And I check the box "Subscribe to this page"
    And I press the "Save" button
    When I am logged in as "administrator"
    And I visit the "Article" content with title "Article sub"
    And I click "New draft"
    And I fill in the rich text editor "Body" with "New body text"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press the "Save" button
    And I am on "admin/config/system/cron"
    And I press the "Run cron" button
    Then the e-mail has been sent
    And the sent e-mail has the following properties:
      | from        | EC-FP-INTERNET-SERVICES-DO-NOT-REPLY@ec.europa.eu |
      | to          | authuser@example.com                              |
      | subject     | NextEuropa updates : Article sub                  |

  Scenario: As an Authorized user I can unsubscribe from a content I was subscribed to.
    Given I visit the "Article" content with title "Article sub"
    And I click "Subscribe"
    And I check the box "Subscribe to this page"
    And I press the "Save" button
    And I go to "user"
    And I click "Subscriptions"
    When I click "Pages/Threads"
    Then I should see the text "Article sub"
    And I uncheck the box on the "Article sub" row
    And I press the "Save" button
    Then I should see the text "There are no available subscribed pages."

  Scenario: As an Authorized user I can unsubscribe from a content type I was subscribed to.
    Given I visit the "Article" content with title "Article sub"
    And I click "Subscribe"
    And I check the box "To Article content"
    And I press the "Save" button
    And I go to "user"
    And I click "Subscriptions"
    When I click "Content types"
    Then I should see the text "Article"
    And I uncheck the box on the "Article" row
    And I press the "Save" button
    Then the checkbox "edit-0-checkboxes-article-1" is unchecked

  Scenario: As an Authorized user I can disable and enable my subscriptions
    Given I go to "/user"
    And I click "Subscriptions"
    And I click "Delivery of notifications"
    And I select the radio button "No"
    And I press the "Save notifications" button
    Then I should see the text "The changes have been saved."
    And the radio button "No" is selected
    When I select the radio button "Yes"
    And I press the "Save notifications" button
    Then I should see the text "The changes have been saved."
    And the radio button "Yes" is selected

  Scenario:
