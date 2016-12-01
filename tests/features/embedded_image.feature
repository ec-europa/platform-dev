@api @javascript @wip
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
  When I go to "node/add/test-media-gallery"
  And I fill in "title" with "<title>"
  And I click "Browse"
  Then the media browser opens
  When I fill in "File URL or media resource" with "<url>"
  And I press "Next"
  And I press "Save"
  Then the media browser closes
  And I see the "Flickr set" preview
  When I press "Save"
  Then I should see the success message "Media Gallery <title> has been created."

  Examples:
  | title              | url                                                                 |
  | Old Flickr set URL | https://www.flickr.com/photos/69583224@N05/sets/72157669193515074   |
  | New Flickr set URL | https://www.flickr.com/photos/69583224@N05/albums/72157669193515074 |

Scenario Outline: Error when an invalid Flickr url is filled in
  When I go to "node/add/test-media-gallery"
  And I fill in "title" with "<title>"
  And I click "Browse"
  Then the media browser opens
  When I fill in "File URL or media resource" with "<url>"
  And I press "Next"
  Then I should see the error message "Unable to handle the provided embed string or URL."

  Examples:
    | title              | url                                       |
    | Invalid Flickr URL | https://www.flickr.com/thisisnotavalidurl |
