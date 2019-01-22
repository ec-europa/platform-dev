@api @javascript
Feature: Scheduler features
  In order to moderate contents
  As an authenticated user
  I want to be able to schedule state transitions for contents

  Scenario: User can schedule a date to unpublish a content
    Given I am logged in as a user with the 'contributor' role
    When I go to "node/add/page"
    And I fill in "Title" with "Old content"
    And I click "Revision information"
    And I select "Needs Review" from "Moderation state"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "unpublish_on[date]" with "2000-12-31"
    And I fill in "unpublish_on[time]" with "23:59:59"
    And I press the "Save" button
    Then I should see the text "The 'unpublish on' date must be in the future"
    When I fill in "unpublish_on[date]" with "2100-12-31"
    And I press the "Save" button
    Then I should see the text "Revision state: Needs Review"
    Then I am logged in as a user with the 'editor' role
    And I visit the "page" content with title "Old content"
    And I select "Published" from "edit-state"
    And I press the "Apply" button
    Then I am logged in as a user with the 'administrator' role
    And  I change the unpublishing date of the "page" node with title "Old content" to "-1 day"
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I visit the "page" content with title "Old content"
    Then I should see the text "Revision state: Expired"

  Scenario: User without permissions can't schedule a date to publish
    Given I am logged in as a user with the 'editor' role
    When I go to "node/add/page"
    And I click "Metadata"
    Then I should not see the text "Scheduling options"

  Scenario: User can schedule a date to publish a content with default configuration
    Given I am logged in as a user with the 'contributor' role
    When I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I click "Revision information"
    When I select "Draft" from "Moderation state"
    And I press the "Save" button
    And I should see the text "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the text "This post is unpublished and will be published 2000-12-31 23:59:00."
    And I should see the text "Revision state: draft"

  Scenario: User with permissions can schedule a date to publish a content after configuring allowed status
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/content/scheduler/scheduler_workbench"
    And I check the box "Validated"
    And I press "Save configuration"
    Then I should see the text "The configuration options have been saved."
    Then I am logged in as a user with the 'contributor' role
    Then I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I click "Revision information"
    When I select "Draft" from "Moderation state"
    And I press the "Save" button
    And I should see the text "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the text "This post is unpublished and will be published 2000-12-31 23:59:00."
    And I should see the text "Revision state: Draft"

  Scenario: User can schedule a draft to publish a content and wont be published
    Given I am logged in as a user with the 'contributor' role
    When I go to "node/add/page"
    And I fill in "Title" with "Not to be published"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I click "Revision information"
    When I select "Draft" from "Moderation state"
    And I press the "Save" button
    And I should see the text "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the text "The current status is draft and it is not allowed to be published on a future date, you will need to update the status."
    And I should see the text "Revision state: Draft"
    Given I am logged in as a user with the 'administrator' role
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I visit the "page" content with title "Not to be published"
    Then I should see the text "Revision state: Draft"

  Scenario: User can create a new revision and schedule its publication
    Given users:
      | name               | mail         | roles        | status |
      | contributor_user   | foo@bar.com  | contributor  | 1      |
    Then I am logged in as "contributor_user"
    Then I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Revision information"
    When I select "Needs Review" from "Moderation state"
    And I press the "Save" button
    And I should see the text "Basic page Next content has been created."
    Then I am logged in as a user with the 'editor' role
    And I visit the "page" content with title "Next content"
    And I select "Published" from "edit-state"
    And I press the "Apply" button
    Then I am logged in as "contributor_user"
    And I visit the "page" content with title "Next content"
    And I click "New draft"
    And I fill in "Title" with "Next revision"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "revision_publish_on[date]" with current day
    And I fill in "revision_publish_on[time]" with future time
    And I click "Revision information"
    And I select "Needs Review" from "Moderation state"
    And I press the "Save" button
    Then I should see the text "Revision state: Needs Review"
    And I wait 60 seconds
    Then I am logged in as a user with the 'administrator' role
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the cache has been cleared
    And I visit the "page" content with title "Next revision"
    Then I should see the text "Revision state: Published"

  Scenario: User can update the status of an scheduled revision and it will be published
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/content/scheduler/scheduler_workbench"
    And I check the box "Validated"
    And I uncheck the box "Needs Review"
    And I press "Save configuration"
    And I should see the text "The configuration options have been saved."
    Then I am logged in as a user with the 'contributor' role
      Given users:
      | name               | mail         | roles        | status |
     | contributor_user   | foo@bar.com  | contributor  | 1      |
    And I am logged in as "contributor_user"
    And I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Revision information"
    When I select "Needs Review" from "Moderation state"
    And I press the "Save" button
    And I should see the text "Basic page Next content has been created."
    Then I am logged in as a user with the 'editor' role
    And I visit the "page" content with title "Next content"
    And I click "Edit draft"
    And I click "Revision information"
    And I select "Published" from "Moderation state"
    And I press the "Save" button
    And I should see the text "Revision state: Published"
    Then I am logged in as "contributor_user"
    And I visit the "page" content with title "Next content"
    And I click "New draft"
    And I fill in "Title" with "Next revision"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "revision_publish_on[date]" with current day
    And I fill in "revision_publish_on[time]" with future time
    And I click "Revision information"
    And I select "Needs Review" from "Moderation state"
    And I press the "Save" button
    Then I should see the text "Revision state: Needs Review"
    Then I am logged in as a user with the 'editor' role
    And I visit the "page" content with title "Next content"
    And I click "Edit draft"
    And I click "Revision information"
    And I select "Validated" from "Moderation state"
    And I press the "Save" button
    And I wait 60 seconds
    Then I am logged in as a user with the 'administrator' role
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the cache has been cleared
    And I visit the "page" content with title "Next revision"
    Then I should see the text "Revision state: Published"

  Scenario: A user can see the date scheduled for publication
    Given I am logged in as a user with the 'contributor' role
    Then I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Revision information"
    When I select "Draft" from "Moderation state"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2050-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I press the "Save" button
    Then I should see the text "Basic page Next content has been created."
    Then I am logged in as a user with the 'editor' role
    And I visit the "page" content with title "Next content"
    And I click "Moderate"
    Then I should see the text "This revision will be published 2050-12-31 23:59:00"
