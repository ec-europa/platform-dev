@group:default
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
    And I am logged in as a user with the 'administrator' role

  Scenario: pt-pt translation will be pushed to the central Integration server as pt
    Given the following Integration Layer node producer is created:
    """
      name: test_news
      bundle: page
      resource: news
      mapping:
        title_field: title
        field_ne_body: body
    """
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
    Given the following Integration Layer node producer is created:
    """
      name: test_news
      bundle: page
      resource: news
      mapping:
        title_field: title
        field_ne_body: body
    """
    When I am viewing a multilingual "page" content:
      | language | title               |
      | pt-pt    | Título em Português |
    And I run drush "integration-export http_mock test_news"
    Then the central Integration server received content in the following languages:
      | language | title               |
      | pt       | Título em Português |

  Scenario: producers will produce a valid document for content containing title, body and taxonomy term reference.
    Given "tags" terms:
      | name  |
      | Tag 1 |
      | Tag 2 |
    And "article" content:
      | title           | body           | field_tags   |
      | Article title 1 | Article body 1 | Tag 1, Tag 2 |
    And "article" content:
      | title           | body           |
      | Article title 2 | Article body 2 |
    When the following Integration Layer resource schema is created:
    """
      name: article
      fields:
        title: Title
        body: Body
        tags: Tags
    """
    And the following Integration Layer node producer is created:
    """
      name: article
      bundle: article
      resource: article
      mapping:
        title: title
        body: body
        field_tags: tags
    """
    Then the "article" producer builds the following document for the "article" with title "Article title 1":
    """
      version: v1
      default_language: und
      type: article
      languages:
        - und
      fields:
        title:
          und:
            - Article title 1
        body:
          und:
            - Article body 1
        tags:
          und:
            - Tag 1
            - Tag 2
    """
    And the "article" producer builds the following document for the "article" with title "Article title 2":
    """
      version: v1
      default_language: und
      type: article
      languages:
        - und
      fields:
        title:
          und:
            - Article title 2
        body:
          und:
            - Article body 2
    """
