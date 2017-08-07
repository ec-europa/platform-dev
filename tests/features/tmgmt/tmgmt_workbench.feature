@api @theme_wip
# They are all in wip for the europa theme because it implies a step referring a
# region. This must be evaluate deeper before being able to know how to deal with.
Feature: TMGMT Workbench features
  In order to request a new translation for moderated content
  As a Translation manager user
  I want to be have TMGMT and Workbench Moderation integrated correctly

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
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

  Scenario: NEXTEUROPA-9861: Translations requested from a validated revision should be applied to that revision only.
    Given local translator "Translator A" is available
    And I am logged in as a user with the "administrator" role
    And I am viewing a multilingual "page" content:
      | language | title                |
      | en       | Title in English 1.0 |
      | fr       | Title in French 1.0  |
    Then the url should match "(.)*content/title-english-10_en"
    And I click "New draft"
    And I fill in "Title" with "Title in English 1.1"
    And I select "Validated" from "Moderation state"
    And I press the "Save" button
    And I visit the "page" content with title "Title in English 1.0"
    Then the url should match "(.)*content/title-english-10_en"
    And I click "Translate" in the "primary_tabs" region
    Then I should see "Title in English 1.1" in the "English" row
    And I create the following job for "page" with title "Title in English 1.0"
      | source language | en                   |
      | target language | fr                   |
      | plugin          | workbench_moderation |
      | translator      | Translator A         |
      | title_field     | Title in French 1.1  |
    And the current translation job is accepted
    And I click "Log out"
    And I visit the "page" content with title "Title in English 1.0"
    Then the url should match "(.)*content/title-english-10_en"
    And I should see the heading "Title in English 1.0"
    And I click "Français" in the "content" region
    Then I should see the heading "Title in French 1.0"
    And the url should match "(.)*content/title-english-10_fr"
    And I click "English" in the "content" region
    Then I am logged in as a user with the "administrator" role
    And I visit the "page" content with title "Title in English 1.0"
    Then I click "View draft"
    And I should see the heading "Title in English 1.1"
    Then I select "Published" from "Moderation state"
    And I press the "Apply" button
    And I visit the "page" content with title "Title in English 1.1"
    Then I should see the heading "Title in English 1.1"
    And I should see the link "Français" in the "content" region
    And I click "Français" in the "content" region
    Then I should see "Title in French 1.1"

  Scenario: NEXTEUROPA-9861: Translations requested from a published revision should be applied to that revision only.
    Given local translator "Translator A" is available
    And I am viewing a multilingual "page" content:
      | language | title                |
      | en       | Title in English 2.0 |
    Then I should not see the link "Français" in the "content" region
    And the url should match "(.)*content/title-english-20_en"
    And I create the following job for "page" with title "Title in English 2.0"
      | source language | en                   |
      | target language | fr                   |
      | plugin          | workbench_moderation |
      | translator      | Translator A         |
      | title_field     | Title in French 2.0  |
    And the current translation job is accepted
    And I visit the "page" content with title "Title in English 2.0"
    And I should see the heading "Title in English 2.0"
    And the url should match "(.)*content/title-english-20_en"
    Then I should see the link "Français" in the "content" region
    And I click "Français" in the "content" region
    Then I should see "Title in French 2.0"
    And the url should match "(.)*content/title-english-20_fr"

  Scenario: NEXTEUROPA-9998: When submitting a new translated revision for a sub job, the URL of the published node is not modified.
    Given local translator "Translator A" is available
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I fill in "Title" with "Original version"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I select "Translator A" from "Translator"
    And I press "Submit to translator"
    Then I click "In progress" in the "French" row
    And I press "Save"
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    And I visit the "page" content with title "Original version"
    Then the url should match "(.)*content/original-version_en"
    Then I click "New draft" in the "primary_tabs" region
    And I fill in "Other different Title" for "Title"
    And I press "Save"
    And I select "Validated" from "Moderation state"
    And I press "Apply"
    And I click "View published" in the "primary_tabs" region
    Then the url should match "(.)*content/original-version_en"

  Scenario: Check the translation messages.
    Given I am logged in as a user with the 'administrator' role
    And local translator "Translator A" is available
    When I go to "node/add/page"
    And I fill in "Title" with "Title of the Basic page"
    And I press "Save"
    And I click "Translate" in the "primary_tabs" region
    Then I should see the text "The current piece of content's moderation state is: draft"
    And I should see the text "Current moderation state does not allow to request a translation for this content."
    When I click "Moderate" in the "primary_tabs" region
    And I select "Validated" from "state"
    And I press the "Apply" button
    And I click "Translate" in the "primary_tabs" region
    Then I should see the text "The current piece of content's moderation state is: validated"
    And I should not see the text "Current moderation state does not allow to request a translation for this content."
    When I check the box on the "French" row
    And I press "Request translation"
    And I select "Translator A" from "Translator"
    And I press "Submit to translator"
    Then I should not see the text "Current moderation state does not allow to request a translation for this content."
