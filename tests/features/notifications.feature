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

  Scenario: As and Authorized user I can configure my subscription settings
    Given I go to "/user"
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

  Scenario: As an administrator I can configure the overview tab of the subscriptions
    Given I am logged in as "administrator"
    And I go to "/admin/config/system/subscriptions/userdefaults"
    And I check the box "Hide the Overview page from your users"
    And I press the "Save settings" button
    When I am logged in as "authuser"
    And I go to "/user"
    And I click "Subscriptions"
    Then I should not see the text "Overview"

  Scenario: As an administrator I can configure the users default options
    Given I am logged in as "administrator"
    And I go to "/admin/config/system/subscriptions/userdefaults"
    And I check the box "Auto-subscribe to new content"
    And I check the box "Auto-subscribe to updated content"
    And the checkbox "Auto-subscribe to comments" is unchecked
    And I press the "Save settings" button
    When I am logged in as "authuser"
    And I go to "/user"
    And I click "Subscriptions"
    And I click "Settings"
    Then the checkbox "Auto-subscribe to new content" is checked
    And the checkbox "Auto-subscribe to updated content" is checked
    And the checkbox "Auto-subscribe to comments" is unchecked

  Scenario: As adn administrator I can configure the visibility of controls
    Given I am logged in as "administrator"
    And I go to "/admin/config/system/subscriptions/userdefaults"
    And I select the radio button "Completely inaccessible to the user" with the id "edit-send-interval-visible-3"
    And I select the radio button "Completely inaccessible to the user" with the id "edit-send-updates-visible-3"
    And I select the radio button "Completely inaccessible to the user" with the id "edit-send-comments-visible-3"
    And I press the "Save settings" button
    When I am logged in as "authuser"
    And I go to "/user"
    And I click "Subscriptions"
    And I click "Settings"
    Then I should not see the text "Visibility of controls"