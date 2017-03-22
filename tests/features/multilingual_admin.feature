@api
Feature: Content translation
  In order to translate my content
  As an administrator
  I want to be able to manage content and translations for fields.

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: Content page does not show mixed content language
    Given the following languages are available:
      | languages |
      | en        |
      | de        |
    And the "field_ne_body" field is translatable
    When I go to "node/add/page"
    And I fill in "Title" with "English title"
    And I press "Save"
    And I select "Validated" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I click "add"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Deutsch title"
    And I fill in "Body" with "Deutsch Body not for English version."
    And I press "Save"
    And I click "English" in the "content" region
    Then I should not see the text "Deutsch Body not for English version."

   @javascript @maximizedwindow @wip
  Scenario: Make sure that I can add "title_field" fields to a view when the Estonian language is enabled.
    Given the following languages are available:
      | languages |
      | en        |
      | et        |
    And a content view with machine name "testing_view" is available
    When I visit "admin/structure/views/view/testing_view/edit"
    And I click "views-add-field"
    And I wait for AJAX to finish
    And I check the box "Entity translation: Body: translated"
    And I press the "Add and configure fields" button
    And I wait for AJAX to finish
    And I press the "Apply" button
    And I wait for AJAX to finish
    And I press the "Save" button
    Then I should see "The view testing_view has been saved."
    And the response should contain "/admin/structure/views/nojs/config-item/testing_view/default/field/field_ne_body_et_en"

  Scenario: Check the default message in workbench moderation
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    And I am viewing a multilingual "page" content:
      | language | title            |
      | en       | Title in English |
      | fr       | Title in French  |
    When I click "New draft" in the "primary_tabs" region
    Then I should see the text "The state of the content Title in English and all its validated translations English French will be updated!"

  Scenario: Check the customizable message in workbench moderation
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    And I request to change the variable nexteuropa_multilingual_warning_message_languages to "New Message!"
    And the cache has been cleared
    And I am viewing a multilingual "page" content:
      | language | title            |
      | en       | Title in English |
      | fr       | Title in French  |
    When I click "New draft" in the "primary_tabs" region
    Then I should see the text "New Message!"
