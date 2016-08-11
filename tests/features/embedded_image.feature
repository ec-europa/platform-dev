@api @javascript
Feature: Embedded images
  In order to make my website more attractive
  As a contributor
  I can embed images from Flickr in my content

Background:
  Given the module is enabled
  |modules       |
  |ec_embedded_image|
  And a valid Flickr API key & secret have been configured
  And there is a media gallery content type with a field to embed images from flickr
  And I am logged in as a user with the 'contributor' role

Scenario Outline: Embed Flickr photoset via media asset field

  Examples:
  | url                                                |
  | https://www.flickr.com/photos/junku/sets/303691/   |
  | https://www.flickr.com/photos/junku/albums/303691/ |
