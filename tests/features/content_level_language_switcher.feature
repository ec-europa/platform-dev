Feature: Content level language switcher tests
  In order to read a content in different languages
  As an anonymous user
  I want to be able have access to the translations of a content

Scenario Outline: Anonymous user can see the content level language selector
  Given I am an anonymous user
  When I go to "<url>"
  Then I should see an ".block-language-selector-page" element 

  Examples:
  | url       | active_language | language_order                      |
  | node/2_en | english         | [ french,deutsch,italiano ]         |
  | node/2_bg | bg              | [ english,french,deutsch,italiano ] |
  | node/2_de | deutsch         | [ english,french,italiano ]         |
  | node/2_fr | french          | [ english,deutsch,italiano ]        |

Scenario Outline: Anonymous user can see the available translations of a content
  Given I am an anonymous user
  When I go to "<url>"
  Then I should see an ".block-language-selector-page" element

  Examples:
  | url       | active_language | language_order                      |
  | node/2_en | english         | [ french,deutsch,italiano ]         |
  | node/2_bg | bg              | [ english,french,deutsch,italiano ] |
  | node/2_de | deutsch         | [ english,french,italiano ]         |
  | node/2_fr | french          | [ english,deutsch,italiano ]        |
