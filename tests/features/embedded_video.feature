@api @javascript
Feature: Embedded videos
  In order to make my website more attractive
  As a contributor
  I can embed videos from Youtube, AV portal, Dailymotion or Vimeo in my content

  Background:
    Given the module is enabled
      | modules           |
      | ec_embedded_video |
    And I am logged in as a user with the 'contributor' role