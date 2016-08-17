@api
Feature: Integration Layer Producer
  In order to share my content with other websites
  As a site administrator
  I can push content published on my website to the Integration Layer

Background:
  Given these modules are enabled
    | modules                |
    | nexteuropa_integration |
    | integration_producer   |
  And the following languages are available:
    | languages |
    | en        |
    | pt-pt     |
  And the integration layer producer is configured
  And I am logged in as a user with the 'administrator' role

Scenario: pt-pt Drupal language code will be pushed to Integration Layer as pt
  When I am viewing a multilingual "page" content:
    | language | title             |
    | en       | Title in English  |
    | pt-pt    | Título em Inglês  |
  And I run drush "integration-export http-mock test-news"
  Then the integration layer received content in the following languages:
    | language |
    | en       |
    | pt       |
