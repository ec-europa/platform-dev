@api @javascript @communities
Feature: User notifications
  In order to allow users to stay informed of new content
  As a site administrator
  I want to make sure configuration ob subscriptions

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
    And I am logged in as "administrator"
    And I go to "admin/config/system/site-information"
    And I fill in "E-mail address" with "automated-notifications@nomail.ec.europa.eu"
    And I select "01000" from "classification"
    And I press "Save configuration"
    And I am logged in as "authuser"

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

  Scenario: Check administration pages are available
    Given I am logged in as "administrator"
    When I go to "admin/config/system/subscriptions"
    Then I should see the text "Content settings"
    And I should see the text "Taxonomy settings"
    And I should see the text "Display settings"
    And I should see the text "Mail settings"

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

  Scenario: As an administrator I can configure the overview tab of the subscriptions
    Given I am logged in as "administrator"
    And I go to "/admin/config/system/subscriptions/userdefaults"
    And I check the box "Hide the Overview page from your users"
    And I press the "Save settings" button
    When I am logged in as "authuser"
    And I go to "/user"
    And I click "Subscriptions"
    Then I should not see the text "Overview"
    Given I am logged in as "administrator"
    And I go to "/admin/config/system/subscriptions/userdefaults"
    And I uncheck the box "Hide the Overview page from your users"
    And I press the "Save settings" button
    When I am logged in as "authuser"
    And I go to "/user"
    And I click "Subscriptions"
    Then I should see the text "Overview"

  Scenario: As an administrator I can configure the users default options
    Given I am logged in as "administrator"
    And I go to "/admin/config/system/subscriptions/userdefaults"
    And I check the box "Auto-subscribe to new content"
    And I check the box "Auto-subscribe to updated content"
    And the checkbox "Auto-subscribe to comments" is unchecked
    And I uncheck the box "Hide the Overview page from your users"
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
    Given I am logged in as "administrator"
    And I go to "/admin/config/system/subscriptions/userdefaults"
    And I select the radio button "Visible" with the id "edit-send-interval-visible-0"
    And I select the radio button "Visible" with the id "edit-send-updates-visible-0"
    And I select the radio button "Visible" with the id "edit-send-comments-visible-0"

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

  Scenario: As an administrator I can configure the restricted and blocked content types
    Given I am logged in as "administrator"
    And I go to "admin/config/system/subscriptions"
    And I select "Article" from "Blocked content types"
    And I press the "Save configuration" button
    When I go to "admin/config/system/subscriptions/userdefaults/type"
    When I am logged in as "authuser"
    And I go to "community/articles/article-sub"
    Then I should not see the text "Subscribe"
    Given I am logged in as "administrator"
    And I go to "admin/config/system/subscriptions"
    And I select "Article" from "Unlisted content types"
    And I select "<none>" from "Blocked content types"
    And I press the "Save configuration" button
    When I am logged in as "authuser"
    And I go to "community/articles/article-sub"
    And I click "Subscribe"
    Then I should not see the text "To Article content"