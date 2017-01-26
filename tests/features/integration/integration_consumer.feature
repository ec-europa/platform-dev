@wip
@api @integration
Feature: Integration consumer
  In order to use content from other sources
  As a site administrator
  I can pull content from the central Integration backend

  Background:
    Given these modules are enabled
      | modules                |
      | nexteuropa_integration |
      | integration_consumer   |
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
    And the following Integration Layer node consumer is created:
    """
      name: test_consumer
      backend: http_mock
      bundle: page
      resource: news
      mapping:
        title: title_field
        body: field_ne_body
    """
    And I am logged in as a user with the 'administrator' role

  Scenario: news content with pt language code will be consumed as pt-pt when pt is not available
    Given the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
    When the central Integration server publishes the following news with id "news-pt-pt":
      | language | title                | body               |
      | en       | Title in English     | Body in English    |
      | pt       | Título em Português  | Corpo em Português |
    And I run drush "integration-import test_consumer"
    Then the Integration consumer imported the item with id "news-pt-pt" as the following page:
      | language | title                | body               |
      | en       | Title in English     | Body in English    |
      | pt-pt    | Título em Português  | Corpo em Português |

  Scenario: news content with pt language code will be consumed as pt when pt is available
    Given the following languages are available:
      | languages |
      | en        |
      | pt        |
      | pt-pt     |
    When the central Integration server publishes the following news with id "news-pt":
      | language | title                | body               |
      | en       | Title in English     | Body in English    |
      | pt       | Título em Português  | Corpo em Português |
    And I run drush "integration-import test_consumer"
    Then the Integration consumer imported the item with id "news-pt" as the following page:
      | language | title                | body               |
      | en       | Title in English     | Body in English    |
      | pt       | Título em Português  | Corpo em Português |
