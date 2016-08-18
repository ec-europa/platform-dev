@api
Feature: Integration Consumer
  In order to use content from other sources
  As a site administrator
  I can pull content from the central Integration backend

Background:
  Given these modules are enabled
    | modules                |
    | nexteuropa_integration |
    | integration_consumer   |
  And the Integration consumer is configured
  And I am logged in as a user with the 'administrator' role

Scenario: news content with pt language code will be consumed as pt-pt
  Given the following languages are available:
    | languages |
    | en        |
    | pt-pt     |
  When the central Integration server publishes the following news with id "foo":
    | language | title                | body               |
    | en       | Title in English     | Body in English    |
    | pt       | Título em Português  | Corpo em Português |
  And I run drush "integration-import test_consumer"
  Then the Integration consumer imported the item with id "foo" as the following page:
    | language | title                | body               |
    | en       | Title in English     | Body in English    |
    | pt-pt    | Título em Português  | Corpo em Português |
