@api @javascript @standard_ec_resp
Feature: Embedded videos
  In order to make my website more attractive
  As a contributor
  I can embed videos from Youtube, AV portal, Dailymotion or Vimeo in my content

  Background:
    Given the module is enabled
      | modules           |
      | ec_embedded_video |
    And I am logged in as a user with the 'administrator' role

  Scenario: As an administrator I can add Youtube videos.
    Given I go to "admin/structure/types/manage/page/fields"
    And I fill in "edit-fields-add-new-field-label" with "YTvideo"
    And I select "Multimedia asset" from "edit-fields-add-new-field-type"
    And I wait for AJAX to finish
    And I select "Media browser" from "edit-fields-add-new-field-widget-type"
    And I press "Save"
    Then I should see "FIELD SETTINGS"
    And I press "Save field settings"
    Then I should see "Updated field YTvideo field settings."
    And I check the box "Web"
    And I check the box "Video"
    And I check the box "YouTube videos"
    And I press "Save settings"
    Then I should see "Saved YTvideo configuration."

  Scenario: Youtube videos are displayed in privacy enhanced mode.
    Given I go to "node/add/page"
    And I fill in the content's title with "YTvideo"
    And I click "Browse"
    Then the media browser opens
    And I fill in "File URL or media resource" with "https://www.youtube.com/embed/1W7NlAfTZU4"
    And I press "Next"
    Then I should see "File name"
    And I press "Save"
    Then the media browser closes
    And I press "Save"
    And the response should contain "https://www.youtube-nocookie.com"

  Scenario: As an administrator I can disable privacy enhanced mode.
    Given I go to "admin/structure/file-types/manage/video/file-display"
    And I click "YouTube Video"
    Then I should see "Use privacy enhanced (no cookie) mode"
    And I uncheck "Use privacy enhanced (no cookie) mode"
    And I press "Save configuration"
    Then I should see "Your settings have been saved."
    And I go to "node/add/page"
    And I fill in the content's title with "YTvideo" 
    And I click "Browse"
    Then the media browser opens
    And I fill in "File URL or media resource" with "https://www.youtube.com/embed/1W7NlAfTZU4"
    And I press "Next"
    Then I should see "File name"
    And I press "Save"
    Then the media browser closes
    And I press "Save"
    And the response should contain "https://www.youtube.com"
