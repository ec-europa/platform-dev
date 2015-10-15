@api
Feature: Content level language switcher tests
  In order to read a content in different languages
  As an anonymous user
  I want to be able have access to the translations of a content

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |

  Scenario: Content can be translated in available languages
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
      | fr       | Ce titre est en Français     |
      | de       | Dieser Titel ist auf Deutsch |
    Then I should see the heading "This title is in English"
    And I should see the link "Français"
    And I should see the link "Deutsch"


Scenario Outline: Anonymous user can see the content level language selector
  Given I am an anonymous user
  When I go to "<url>"
  Then I should see an ".block-language-selector-page" element 

  Examples:
  | url                |
  | content/english_en |
  | content/english_fr |

Scenario Outline: Anonymous user can see the available translations of a content
  Given I am an anonymous user
  When I go to "<url>"
  Then the language options on the page content language switcher should be "<active_language>" non clickable followed by "<language_order>" links

  Examples:
  | url                | active_language | language_order    |
  | content/english_en | english         | français,italiano |
  | content/english_fr | français        | english,italiano  |  
