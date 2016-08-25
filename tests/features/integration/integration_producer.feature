@api @integration
Feature: Integration producer
  In order to share my content with other websites
  As a site administrator
  I can push content published on my website to the central Integration server

Background:
  Given these modules are enabled
    | modules                |
    | nexteuropa_integration |
    | integration_producer   |
  And the following languages are available:
    | languages |
    | en        |
    | pt-pt     |
  And the Integration producer is configured
  And I am logged in as a user with the 'administrator' role

Scenario: pt-pt translation will be pushed to the central Integration server as pt
  When I am viewing a multilingual "page" content:
    | language | title               |
    | en       | Title in English    |
    | pt-pt    | Título em Português |
  And I run drush "integration-export http_mock test_news"
  Then the central Integration server received content in the following languages:
    | language | title               |
    | en       | Title in English    |
    | pt       | Título em Português |

Scenario: content in main language pt-pt will be pushed to the central Integration server as pt
    When I am viewing a multilingual "page" content:
      | language | title               |
      | pt-pt    | Título em Português |
    And I run drush "integration-export http_mock test_news"
    Then the central Integration server received content in the following languages:
      | language | title               |
      | pt       | Título em Português |
