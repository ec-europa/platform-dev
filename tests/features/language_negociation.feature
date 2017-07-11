@api
Feature: Second favorite language tests
  In order to be accessible to European citizens,
  Users should be able to switch content to their favorite language.

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
      | pt-pt     |
      | bg        |

  Scenario Outline: Check the role of the second favorite language on the language fallback
    Given I am viewing a multilingual "page" content:
      | language | title                    |
      | en       | This title is in English |
      | fr       | Ce titre est en Français |
      | pt-pt    | Este titulo e Portugues  |
    When I go to "<url><favorite>"
    Then I should see the heading "<title>"

    Examples:
    | url                      | favorite            | title                    |
    | content/title-english_en |                     | This title is in English |
    | content/title-english_bg |                     | This title is in English |
    | content/title-english_bg | ?2nd-language=pt-pt | Este titulo e Portugues  |
    | content/title-english_bg | ?2nd-language=de    | This title is in English |

  Scenario: Check that a user can view a page even if the language prefix was changed
    Given "prefix" for language "pt-pt" is set to "pt"
    And I am viewing a multilingual "page" content:
      | language | title               |
      | en       | An English title    |
      | pt-pt    | Um titulo Portugues |
    And I click "Português" in the "content" region
    Then I should not see the text "Page not found"
