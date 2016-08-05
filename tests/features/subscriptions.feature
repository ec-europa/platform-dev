@api
Feature: Subscription
  In order to manage my subscriptions on the website
  As an authenticated user
  I want to be able to subscribe to content and manage subscriptions.

  Background:
    Given I am logged in as a user with the 'administrator' role
    And the module is enabled
      |modules                      |
      |multisite_notifications_core |
  @javascript
  Scenario: Create a page and have someone register to it
    And I go to "admin/config/system/site-information_en"
    Then I fill in "E-mail address" with "automated-notifications@nomail.ec.europa.eu"
    And I select "01000" from "classification"
    And I press "Save configuration"
    Then I go to "node/add/page"
    And I fill in "Title" with "New page"
    And I press "Save"
    And I select "Published" from "Moderation state"
    Then I press "Apply"
    Then I am logged in as a user with the "authenticated" role
    And I am on "content/new-page"
    And I click "Subscribe"
    And I check "subscriptions[1]"
    And I press "Save"
    Then I go to "user"
    And I click "Subscriptions" in the "primary_tabs" region
   # We cannot locate a row with a slash in its name..
   # Then I should see "1" in the "Pages/Thread" row
    Then I am logged in as a user with the 'administrator' role
    And I am on "content/new-page"
    Then I click "New draft" in the "primary_tabs" region
    And I fill in "Title" with "New Page title"
    And I select "Basic HTML" from "Text format"
    And I fill in "Body" with "A body text"
    And I press "Save"
    And I select "Published" from "Moderation state"
    Then I press "Apply"
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I go to "admin/reports/dblog"
    Then I should see text matching "Subscriptions sent 1 single and 0 digest..."
@javascript
  Scenario: Check administration pages are available
    When I go to "admin/config/system/subscriptions_en"
    Then I should see "Content settings"
    And I should see "Taxonomy settings"
    And I should see "Display settings"
    And I should see "Mail settings"
    Then I fill in "Blocked nodes" with "1"
    And I press "Save configuration"
    Then I should see "The configuration options have been saved."
    Then I am logged in as a user with the "authenticated" role
    Then I go to "node/1"
    Then I break
  And I should not see "subscribe"

