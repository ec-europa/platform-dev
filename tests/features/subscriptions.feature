@api
Feature: Subscription
  In order to be notified on content created or updated on the website
  As an authenticated user
  I want to be able to subscribe to content and manage subscriptions.

  Background:
    Given I am logged in as a user with the 'administrator' role
    And the module is enabled
      |modules                      |
      |multisite_notifications_core |

  @javascript @theme_wip
  # It is in wip for the europa theme because it implies a step referring a
  # region. This must be evaluate deeper before being able to know how to deal with.
  Scenario: Create a page and have someone subscribe to it
    And I go to "admin/config/system/site-information_en"
    When I fill in "E-mail address" with "automated-notifications@nomail.ec.europa.eu"
    And I select "01000" from "classification"
    And I press "Save configuration"
    When I go to "node/add/page"
    And I fill in "Title" with "New page"
    And I press "Save"
    And I select "Published" from "Moderation state"
    When I press "Apply"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I go to "admin/reports/dblog"
    Then I should not see text matching "Subscriptions sent"
    Then I am logged in as a user with the "authenticated" role
    And I am on "content/new-page"
    And I click "Subscribe"
    And I check "subscriptions[1]"
    And I press "Save"
    When I go to "user"
    And I click "Subscriptions" in the "primary_tabs" region
  #  Then I should see "1" in the "Pages/Thread" row
    When I am logged in as a user with the 'administrator' role
    And I am on "content/new-page"
    And I click "New draft" in the "primary_tabs" region
    And I fill in "Title" with "New Page title"
    And I select "Basic HTML" from "Text format"
    And I fill in "Body" with "A body text"
    And I press "Save"
    And I select "Validated" from "Moderation state"
    When I press "Apply"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I go to "admin/reports/dblog"
    Then I should not see text matching "Subscriptions sent"
    When I am on "content/new-page"
    And I click "View draft" in the "primary_tabs" region
    And I select "Published" from "Moderation state"
    When I press "Apply"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I go to "admin/reports/dblog"
    Then I should see text matching "Subscriptions sent"

  @javascript
  Scenario: Have someone subscribe to Basic page content
    And I go to "admin/config/system/site-information_en"
    When I fill in "E-mail address" with "automated-notifications@nomail.ec.europa.eu"
    And I select "01000" from "classification"
    And I press "Save configuration"
    Then I am logged in as a user with the "authenticated" role
    And I am on "user"
    And I click "Subscriptions"
    And I click "Content types"
    # Check "Basic page" option
    And I check "edit-0-checkboxes-page-1"
    And I press "Save"
    When I am logged in as a user with the 'administrator' role
    When I go to "node/add/page"
    And I fill in "Title" with "Another page"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    When I press "Save"
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I go to "admin/reports/dblog"
    Then I should see text matching "Subscriptions sent"

  Scenario: Check administration pages are available
    When I go to "admin/config/system/subscriptions_en"
    Then I should see "Content settings"
    And I should see "Taxonomy settings"
    And I should see "Display settings"
    And I should see "Mail settings"

  Scenario: Block a given page from subscriptions
    When I am viewing my page with the title "A new page title"
    And I remember the node ID of this page
    When I go to "admin/config/system/subscriptions_en"
    And I insert in Blocked nodes the node ID
    And I press "Save configuration"
    Then I should see "The configuration options have been saved."
    And I go to the page of the node I remembered
    Then I should see "A new page title"
    And I should not see "subscribe"

