@api @javascript
Feature: Scheduler features
  In order to moderate contents
  As an administrator
  I want to be able to schedule state transitions for contents

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: User can schedule a date to publish a content
    When I go to "node/add/page"
    And I fill in "Title" with "Next content"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "publish_on[date]" with "2000-12-31"
    And I fill in "publish_on[time]" with "23:59:59"
    And I press the "Save" button
    And I should see the text "The 'publish on' date must be in the future"
    And I change the variable "scheduler_publish_past_date_page" to "schedule"
    And I press the "Save" button
    Then I should see the text "This post is unpublished and will be published 2000-12-31 23:59:00."
    And I should see the text "Revision state: Draft"
    And I run cron
    And I visit the "page" content with title "Next content"
    Then I should see the text "Revision state: Published"
    Then I click "New draft"
    And I fill in "Title" with "New revision"
    And I click "Metadata"
    And I click "Scheduling options"
    And I fill in "revision_publish_on[date]" with current day
    And I fill in "revision_publish_on[time]" with future time
    And I press the "Save" button
    And I should see the text "Revision state: Draft"
    And I wait 70 seconds
    And I am on "admin/config/system/cron_en"
    And I press "Run cron"
    And I visit the "page" content with title "New revision"
    Then I should see the text "Revision state: Published"
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
