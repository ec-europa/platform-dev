@api @javascript
Feature: Scheduler features
  In order to moderate contents
  As an administrator
  I want to be able to schedule state transitions for contents

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: User can schedule a draft to publish a content and wont be published
    When I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I click "Publishing options"
    When I select "Draft" from "Moderation state"
    And I press the "Save" button
    And I should see the text "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the text "The current status draft is not allowed to be published, you will need to update the status."
    And I should see the text "Revision state: Draft"
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I visit the "page" content with title "Next content"
    Then I should see the text "Revision state: Draft"

  Scenario: User can schedule a date to unpublish a content
    When I go to "node/add/page"
    And I fill in "Title" with "Old content"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "unpublish_on[date]" with "2000-12-31"
    And I fill in "unpublish_on[time]" with "23:59:59"
    And I press the "Save" button
    Then I should see the text "The 'unpublish on' date must be in the future"
    When I fill in "unpublish_on[date]" with "2100-12-31"
    And I press the "Save" button
    Then I should see the text "Revision state: Published"
    When I change the unpublishing date of the "page" node with title "Old content" to "-1 day"
    And I run cron
    And I visit the "page" content with title "Old content"
    Then I should see the text "Revision state: Expired"

  Scenario: User can schedule a date to publish a content with default configuration
    When I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I click "Publishing options"
    When I select "Validated" from "Moderation state"
    And I press the "Save" button
    And I should see the text "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the text "This post is unpublished and will be published 2000-12-31 23:59:00."
    And I should see the text "Revision state: Validated"
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I visit the "page" content with title "Next content"
    Then I should see the text "Revision state: Published"

Scenario: User can create a new revision and schedule its publication  with default configuration
    When I should see the text "The configuration options have been saved."
    Then I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Publishing options"
    When I select "Published" from "Moderation state"
    And I press the "Save" button
    Then I should see the text "Basic page Next content has been created."
    Then I click "New draft"
    And I fill in "Title" with "Next revision"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "revision_publish_on[date]" with current day
    And I fill in "revision_publish_on[time]" with future time
    And I click "Publishing options"
    And I select "Validated" from "Moderation state"
    And I press the "Save" button
    Then I should see the text "Revision state: Validated"
    And I wait 60 seconds
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the cache has been cleared
    And I visit the "page" content with title "Next revision"
    Then I should see the text "Revision state: Published"

 Scenario: User can schedule a date to publish a content after configuring allowed status
    When I go to "admin/config/content/scheduler/scheduler_workbench"
    And I check the box "Validated"
    And I press "Save configuration"
    Then I should see the text "The configuration options have been saved."
    Then I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I click "Publishing options"
    When I select "Validated" from "Moderation state"
    And I press the "Save" button
    And I should see the text "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the text "This post is unpublished and will be published 2000-12-31 23:59:00."
    And I should see the text "Revision state: Validated"
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I visit the "page" content with title "Next content"
    Then I should see the text "Revision state: Published"

Scenario: User can create a new revision and schedule its publication after configuring allowed status
    When I go to "admin/config/content/scheduler/scheduler_workbench"
    And I check the box "Validated"
    And I press "Save configuration"
    Then I should see the text "The configuration options have been saved."
    Then I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Publishing options"
    When I select "Published" from "Moderation state"
    And I press the "Save" button
    Then I should see the text "Basic page Next content has been created."
    Then I click "New draft"
    And I fill in "Title" with "Next revision"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "revision_publish_on[date]" with current day
    And I fill in "revision_publish_on[time]" with future time
    And I click "Publishing options"
    And I select "Validated" from "Moderation state"
    And I press the "Save" button
    Then I should see the text "Revision state: Validated"
    And I wait 60 seconds
    Then I am on "admin/config/system/cron_en"
    And I press "Run cron"
    Then the cache has been cleared
    And I visit the "page" content with title "Next revision"
    Then I should see the text "Revision state: Published"
