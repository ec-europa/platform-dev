@api @communitites
Feature: Composer
  In order to write modern and efficient PHP code
  As an developer
  I want to be able to use Composer as a dependency manager.

Scenario: Site loads Composer dependencies correctly
  Given I am on the homepage
  Then the class "GuzzleHttp\Client" exists in my codebase
