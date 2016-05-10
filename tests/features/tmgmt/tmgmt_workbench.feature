@api @i18n
Feature: TMGMT Workbench features
  In order to request a new translation for moderated content
  As a Translation manager user
  I want to be have TMGMT and Workbench Moderation integrated correctly

  Background:
    Given the module is enabled
      |modules           |
      |tmgmt_workbench      |
    And the following languages are available:
      | languages |
      | en        |
      | fr        |
      | it        |

  Scenario: NEXTEUROPA-9945: When requesting a translation from the node's "Translate" page I only create "workbench_moderation" job items.
    Given I am logged in as a user with the 'administrator' role
    And I am viewing a multilingual "page" content:
      | language | title                        | status |
      | en       | This title is in English     | 1      |
    Then I should see the heading "This title is in English"
    And I should see the link "Translate" in the "primary_tabs" region
    And I click "Translate" in the "primary_tabs" region
    Then I should see the text "Translation of a piece of content is only available if its latest revision is in the following states: validated, published"
    And I should see the text "The current piece of content's moderation state is: published"
    And I should see "Not translated" in the "French" row
    And I should see "Not translated" in the "Italian" row
    And I select the radio button "" with the id "edit-languages-it"
    And I press the "Request translation" button
    Then I am on a translation job page with "workbench_moderation" job items

  Scenario: NEXTEUROPA-10448: When viewing translation overview page I only see moderated nodes.
    Given I am logged in as a user with the 'administrator' role
    And I am viewing a multilingual "page" content:
      | language | title                        | status |
      | en       | This title is in English     | 1      |
    Then I click "Translation" in the "admin_menu" region
    And I click "Sources"
    Then I should see the text "Moderated content overview"
    And I should see "published" in the "This title is in English" row
    Then I click "Node"
    Then I should see the text "Node overview (Entity)"
    Then I am viewing an "Editorial team" content with the title "New Editorial section"
    Then I click "Translation" in the "admin_menu" region
    And I click "Sources"
    Then I should not see "New Editorial team"
