@api @javascript
Feature: User notifications
  In order to allow users to stay informed of new content
  As a site administrator
  I want to make sure auhtenticated users can subscribe to content on the site

  Background:
    Given users:
      | name          | mail                 | pass         | roles              |
      | administrator | admin@ecample.com    | password123  | administrator      |
      | authuser      | authuser@example.com | password456  | authenticated user |
    And these featureSet are enabled
      | featureSet     |
      | Notifications  |
    And 'Article' content:
      | title       | author        | workbench_moderation_state_new | workbench_moderation_state | language | status |
      | Article sub | administrator | published                      | published                  | en       | 1      |
    Given I am not logged in
    And I go to "/user"
    And I fill in "Username" with "authuser"
    And I fill in "Password" with "password456"
    And I press the "Log in" button

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

  Scenario: As an Authorized user I can unsubscribe from a content, content type or content type by user.
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

  Scenario: As an Authorized user I can disable and enable my subscriptions
    When I go to "/user"
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

  @prueba
  Scenario: As and Authorized user I can configure my subscription settings
    When I go to "/user"
    And I click "Subscriptions"
    Then I should see the link "Overview"
    And I should see the text "Delivery of notifications"
    And I should see the text "Settings"
    When I click "Settings"
    Then I should see the text "Auto-Subscribe"
    And I should see the text "Preferences"
    And I should see the text "Visibility of Controls"
    When I click "Visibility of controls"
    Then I should see the text "Send interval"
    And I should see the "Save settings" button
    And I should see the "Save notifications" button

