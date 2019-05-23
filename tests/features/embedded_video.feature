@api @javascript
Feature: Embedded videos
  In order to make my website more attractive
  As a contributor
  I can embed videos from Youtube, AV portal, Dailymotion or Vimeo in my content

  Background:
    Given the module is enabled
      | modules           |
      | ec_embedded_video |
    And I am logged in as a user with the 'administrator' role

  Scenario Outline: Embed youtube video via media web tab
    When I go to "node/add/page"
    And I fill in "Title" with "Add media video"
    And I click "Media browser"
    Then The media browser "mediaBrowser" iframe opens
    And I click the "Web" in "media-tabs-wrapper" tab
    And I fill in "File URL or media resource" with "<url>"
    And I submit "media-internet-add-upload" id form
    Then I should see "Video Description"
    And the field "edit-filename-field-en-0-value" is filled with "<title>"
    And I fill in "Video Description" with "text"
    And I press "Save"
    Then I should see "OPTIONS"
    Then The media browser "mediaStyleSelector" iframe opens
    And I click "Submit"
    And I press "Save"
    Then I should see "View draft"
    And I should see "Basic page Add media video has been created"
    Then I should see the "<provider>" video iframe

    Examples:
      | provider    | title                                            | url                                                                      |
      | youtube     | Interview with Dries Buytaert, founder of Drupal | https://www.youtube.com/watch?v=i8AENFzUTHk                              |
      | dailymotion | x4gj1bp                                          | http://www.dailymotion.com/video/x4gj1bp                                 |
      | Vimeo       | A successful build in Jenkins                    | https://vimeo.com/129687265                                              |
      | AV portal   | STOCKSHOTS                                       | https://ec.europa.eu/avservices/video/player.cfm?sitelang=en&ref=I143092 |
