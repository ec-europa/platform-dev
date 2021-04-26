@api @javascript @standard_ec_resp
Feature: Embedded videos
  In order to make my website more attractive
  As a contributor
  I can embed videos from Youtube, AV portal, Dailymotion or Vimeo in my content

  Background:
    Given the module is enabled
      | modules           |
      | ec_embedded_video |
      | field_ui          |

 Scenario Outline: Embed youtube video via media web tab
    Given I am logged in as a user with the 'administrator' role
    When I go to "file/add/web"
    And I fill in "File URL" with "<url>"
    Then I press "Next"
    And I fill in "File name" with "<title>"
    And I press "Save"
    And I click "<title>"
    Then I should see the "<provider>" video iframe

    Examples:
      | provider    | title                                            | url                                                                      |
      | youtube     | Interview with Dries Buytaert, founder of Drupal | https://www.youtube.com/watch?v=i8AENFzUTHk                              |
      | dailymotion | x4gj1bp                                          | http://www.dailymotion.com/video/x4gj1bp                                 |
      | Vimeo       | A successful build in Jenkins                    | https://vimeo.com/129687265                                              |
      | AV portal   | STOCKSHOTS                                       | https://ec.europa.eu/avservices/video/player.cfm?sitelang=en&ref=I143092 |

  Scenario: As an administrator I can add Youtube videos.
    Given I am logged in as a user with the 'administrator' role
    And I go to "admin/structure/types/manage/page/fields"
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
    Given I am logged in as a user with the 'administrator' role
    Given I change the variable "field_sql_storage_skip_writing_unchanged_fields" to "FALSE"
    And I go to "node/add/page"
    And I fill in the content's title with "YTvideo"
    And I click "Browse"
    Then the media browser opens
    And I fill in "File URL or media resource" with "https://www.youtube.com/embed/1W7NlAfTZU4"
    And I press "Next"
    Then I should see "File name"
    And I click on element "#media-browser-page #edit-submit"
    And I wait for AJAX to finish
    Then the media browser closes
    And I wait for AJAX to finish
    And I press "Save"
    And the response should contain "https://www.youtube-nocookie.com"

  Scenario: As an administrator I can disable privacy enhanced mode.
    Given I am logged in as a user with the 'administrator' role
    Given I change the variable "field_sql_storage_skip_writing_unchanged_fields" to "FALSE"
    And I go to "admin/structure/file-types/manage/video/file-display"
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
    And I click on element "#media-browser-page #edit-submit"
    And I wait for AJAX to finish
    Then the media browser closes
    And I wait for AJAX to finish
    And I press "Save"
    And the response should contain "https://www.youtube.com"
