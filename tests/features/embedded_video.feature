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

  Scenario Outline: Embed youtube video via media web tab
    When I go to "file/add/web"
    And I fill in "File URL" with "<url>"
    Then I press "Next"
    And I fill in "File name" with "<title>"
    And I fill in "Video Description" with "text"
    And I press "Save"
    And I click "<title>"
    Then I should see the "<provider>" video iframe

    Examples:
      | provider    | title                                            | url                                                                      |
      | youtube     | Interview with Dries Buytaert, founder of Drupal | https://www.youtube.com/watch?v=i8AENFzUTHk                              |
      | dailymotion | x4gj1bp                                          | http://www.dailymotion.com/video/x4gj1bp                                 |
      | Vimeo       | A successful build in Jenkins                    | https://vimeo.com/129687265                                              |
      | AV portal   | STOCKSHOTS                                       | https://ec.europa.eu/avservices/video/player.cfm?sitelang=en&ref=I143092 |
