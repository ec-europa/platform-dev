@api
Feature: Integration Layer Consumer
  In order to use content from other sources
  As a site administrator
  I can pull content from the Integration Layer backend

Background:
  Given these modules are enabled
    | modules                |
    | nexteuropa_integration |
    | integration_consumer   |
  And the following languages are available:
    | languages |
    | en        |
    | pt-pt     |
  And the integration layer consumer is configured
  And I am logged in as a user with the 'administrator' role

Scenario: content with pt language code on Integration Layer will be pulled into Drupal as pt-pt
  When the integration layer backend publishes the following news with id "foo":
    | language | title                | body               |
    | en       | Title in English     | Body in English    |
    | pt       | Título em Português  | Corpo em Português |
  And I run drush "integration-import test_consumer"
  Then the integration layer consumer imported the item with id "foo" as the following page:
    | language | title                | body               |
    | en       | Title in English     | Body in English    |
    | pt-pt    | Título em Português  | Corpo em Português |
