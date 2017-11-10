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

  Scenario: As an administrator I can configure the visibility of controls
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

  Scenario: As an administrator I can configure new time intervals
    Given I am logged in as "administrator"
    And I go to "admin/config/system/subscriptions/intervals"
    And I fill in "intervals" with "604800|Weekly"
    And I press the "Save" button
    When I am logged in as "authuser"
    And I go to "/user"
    And I click "Subscriptions"
    And I click "Settings"
    Then I should have the following options for "Send interval":
      | options             |
      | Weekly              |

  Scenario: As an administrator I can configure the subscriptions defaults for content types, categories and groups.
    Given I am logged in as "administrator"
    When I go to "admin/config/system/subscriptions/userdefaults/type"
    Then I should see the text "Article"
    And I should not see an "edit-0-send-updates-article-1" form element
    And I should not see an "edit-0-send-comments-article-1" form element
    When I check the box "edit-0-checkboxes-article-1"
    And I press the "Save" button
    Then the checkbox "edit-0-send-updates-article-1" is checked
    And the checkbox "edit-0-send-comments-article-1" is checked
    When I go to "admin/config/system/subscriptions/userdefaults/taxa"
    Then I should see the text "economic"
    And I should not see an "edit-2-0-send-updates-35-1" form element
    And I should not see an "edit-2-0-send-comments-35-1" form element
    When I check the box "edit-2-0-checkboxes-35-1"
    And I press the "Save" button
    Then the checkbox "edit-2-0-send-updates-35-1" is checked
    And the checkbox "edit-2-0-send-comments-35-1" is checked
    Given 'Community' content:
      | title             | author        | workbench_moderation_state_new | workbench_moderation_state | language | status |
      | Example Community | administrator | published                      | published                  | en       | 1      |
    When I go to "admin/config/system/subscriptions/userdefaults/og"
    Then I should see the text "Example Community"
    # Checkboxes cannot be checked because we don't have node ID of the content

  @prueba
  Scenario: Check administration pages are available
    Given I am logged in as "administrator"
    When I go to "admin/config/system/subscriptions"
    Then I should see the text "Content settings"
    And I should see the text "Taxonomy settings"
    And I should see the text "Display settings"
    And I should see the text "Mail settings"

  Scenario: As an administrator I can configure the restricted and blocked content types
    Given I am logged in as "administrator"
    And I go to "admin/config/system/subscriptions"
    And I select "Article" from "Blocked content types"
    And I press the "Save configuration" button
    When I go to "admin/config/system/subscriptions/userdefaults/type"
    Then I should see the "span" element with the "title" attribute set to "This content type is blocked." in the "page" region
    Given I go to "admin/config/system/subscriptions"
    And I select "Article" from "Unlisted content types"
    And I select "<none>" from "Blocked content types"
    And I press the "Save configuration" button
    When I am logged in as "authuser"
    And I go to "community/articles/article-sub"
    And I click "Subscribe"
    Then I should not see the text "To Article content"