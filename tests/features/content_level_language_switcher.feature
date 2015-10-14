Feature: Content level language switcher tests
  In order to read a content in different languages
  As an anonymous user
  I want to be able have access to the translations of a content

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
