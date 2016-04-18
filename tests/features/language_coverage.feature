@api
Feature: Webtools Language Coverage (LACO) service can check the language coverage of site pages
  In order to have a clear view of the language coverage
  As an external LACO client
  I can check the language coverage of site pages

  Scenario: Ordinary site pages have the same coverage as the enabled languages on the site.
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    Then I should get the following language coverage responses:
      | path          | language | response |
      | user          | en       | 200      |
      | user          | fr       | 200      |
      | user          | de       | 404      |
      | user          | pl       | 404      |
      | user/password | en       | 200      |
      | user/password | fr       | 200      |
      | user/password | de       | 404      |
      | user/password | pl       | 404      |
      | admin         | en       | 403      |
      | admin         | fr       | 403      |
      | admin         | de       | 404      |
      | admin         | pl       | 404      |
      | admin_en      | en       | 403      |
      | admin_fr      | fr       | 403      |
      | admin_de      | de       | 404      |
      | admin_pl      | pl       | 404      |

  Scenario: Content language coverage depends on its actual translations.
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    And I am viewing a multilingual "page" content:
      | language | title             |
      | en       | Title in English  |
      | fr       | Titre en Français |
    Then I should get the following language coverage responses:
      | path                               | language | response |
      | content/title-english              | en       | 200      |
      | content/title-english              | fr       | 200      |
      | content/title-english_en           | en       | 200      |
      | content/title-english_fr           | fr       | 200      |
      | content/title-english?text=abc     | en       | 200      |
      | content/title-english_en?text=abc  | en       | 200      |
      | content/title-english_fr?text=abc  | fr       | 200      |
      | content/title-english              | pl       | 404      |
      | content/title-english              | de       | 404      |
      | content/title-english?text=abc     | de       | 404      |
      | content/title-english_en?text=abc  | de       | 404      |
      | content/title-english_fr?text=abc  | de       | 404      |
      | not-existing-path                  | en       | 404      |
