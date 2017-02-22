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
      | it        |
    Then I should get the following language coverage responses:
      | path          | language | response | message |
      | user          | en       | 200      | Process boot, Language suffix not found, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access OK |
      | user          | fr       | 200      | Process boot, Language suffix not found, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access OK |
      | user          | de       | 404      | Process boot, Language suffix not found, URL alias not found, Language de not available or not enabled |
      | user          | pl       | 404      | Process boot, Language suffix not found, URL alias not found, Language pl not available or not enabled |
      | user/password | en       | 200      | Process boot, Language suffix not found, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access OK |
      | user/password | fr       | 200      | Process boot, Language suffix not found, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access OK |
      | user/password | de       | 404      | Process boot, Language suffix not found, URL alias not found, Language de not available or not enabled |
      | user/password | pl       | 404      | Process boot, Language suffix not found, URL alias not found, Language pl not available or not enabled |
      | admin         | en       | 403      | Process boot, Language suffix not found, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access forbidden |
      | admin         | fr       | 403      | Process boot, Language suffix not found, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access forbidden |
      | admin         | de       | 404      | Process boot, Language suffix not found, URL alias not found, Language de not available or not enabled |
      | admin         | pl       | 404      | Process boot, Language suffix not found, URL alias not found, Language pl not available or not enabled |
      | admin_en      | en       | 403      | Process boot, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access forbidden |
      | admin_fr      | fr       | 403      | Process boot, URL alias not found, Process init, Language suffix not found, URL alias not found, Menu item access forbidden |
      | admin_de      | de       | 404      | Process boot, URL alias not found, Language de not available or not enabled |
      | admin_pl      | pl       | 404      | Process boot, URL alias not found, Language pl not available or not enabled |

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
      | content/title-english_it           | it       | 404      |
      | content/title-english?text=abc     | en       | 200      |
      | content/title-english_en?text=abc  | en       | 200      |
      | content/title-english_fr?text=abc  | fr       | 200      |
      | content/title-english              | pl       | 404      |
      | content/title-english              | de       | 404      |
      | content/title-english?text=abc     | de       | 404      |
      | content/title-english_en?text=abc  | de       | 404      |
      | content/title-english_fr?text=abc  | de       | 404      |
      | not-existing-path                  | en       | 404      |
