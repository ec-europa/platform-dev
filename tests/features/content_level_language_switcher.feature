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
    And "page" content:
      | language | title     | 
      | en       | english1  |
      | fr       | français1 |      

  Scenario Outline: Check background
    Given I am an anonymous user
    When I go to "<url>"
    And I should see "english1"
    Then I should see an ".block-language-selector-page" element

    Examples:
    | url                 |
    | content/english1_en |
    | content/english1_fr |


  Scenario: Custom URL suffix language negotiation is applied by default on new content.
    Given I am logged in as a user with the 'administrator' role
    And I am viewing a multilingual "page" content:
      | language | title            |
      | en       | Title in English |
      | fr       | Title in French  |
      | de       | Title in German  |
    Then I should see the heading "Title in English"



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
