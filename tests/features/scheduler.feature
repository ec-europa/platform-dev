@api @run
Feature: Scheduler features
  In order to moderate contents
  As an administrator
  I want to be able to schedule state transitions for contents

  Background:
    Given I am logged in as a user with the 'administrator' role
    And I change the variable "scheduler_publish_enable_page" to 1
    And I change the variable "scheduler_unpublish_enable_page" to 1
    And I change the variable "scheduler_use_vertical_tabs_page" to 1

  Scenario: User can schedule a date to publish a content
    When I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I press the "Save" button
    Then I should see the error message "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the message "This post is unpublished and will be published 2000-12-31 23:59:59."
    And I should see the text "Revision state: Draft"
    And I am on "admin/config/system/cron"
    And I press "Run cron"
    And I visit the "page" content with title "Next content"
    Then I should see the text "Revision state: Published"

  @wip
  Scenario: User can schedule a date to unpublish a content
    When I go to "node/add/page"
    And I fill in "Title" with "Old content"
    # And I click "Publishing options"
    And I select "Published" from "Moderation state"
    # And I click "Scheduling options"
    And I fill in "unpublish_on[date]" with "2000-12-31"
    And I fill in "unpublish_on[time]" with "23:59:59"
    And I press the "Save" button
    Then I should see the error message "The 'unpublish on' date must be in the future"
    When I fill in "unpublish_on[date]" with "2100-12-31"
    And I press the "Save" button
    Then I should see the text "Revision state: Published"
    When I make dates from "unpublish_on" in db table "scheduler" to be in past
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I visit the "page" content with title "Old content"
    Then I should see the text "Revision state: Expired"
