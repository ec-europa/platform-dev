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

  Scenario: Files can be translated in available languages
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    When I go to "file/add"
    And I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And I press "Next"
    And I select the radio button "Public local files served by the webserver."
    And I press "Next"
    And I fill in "File name" with "English File name"
    And I fill in "Alt Text" with "English Alt Text"
    And I fill in "Title Text" with "English Title Text"
    And I fill in "Caption" with "English Caption"
    And I press "Save"
    Then I should see the success message "Image English File name was uploaded."
    When I click "English File name"
    Then I should see the heading "English File name"
    When I click "Translate" in the "primary_tabs" region
    And I click "add" in the "French" row
    And I fill in "File name" with "French File name"
    And I fill in "Alt Text" with "French Alt Text"
    And I fill in "Title Text" with "French Title Text"
    And I fill in "Caption" with "French Caption"
    And I press "Save"
    Then I should see the success message "Image French File name has been updated."
    And I should see the heading "French File name"
    And the response should contain "alt=\"French Alt Text\""
    And the response should contain "title=\"French Title Text\""
    And I should see "French Caption"

  Scenario: Custom URL suffix language negotiation is applied by default on new content.
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    And I am viewing a multilingual "page" content:
      | language | title                                  |
      | en       | Custom URL suffix language negotiation |
      | fr       | Suffix de language negotiation French  |
      | de       | Suffix Sprache Verhandlung German      |
    Then I should be on "content/custom-url-suffix-language-negotiation_en"
    When I click "English" in the "header_top" region
    Then I should be on the language selector page
    When I click "Français"
    Then I should be on "content/custom-url-suffix-language-negotiation_fr"
    When I click "Français" in the "header_top" region
    Then I should be on the language selector page
    When I click "Deutsch"
    Then I should be on "content/custom-url-suffix-language-negotiation_de"

  Scenario: Enable multiple languages
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    When I go to "admin/config/regional/language"
    Then I should see "English"
    And I should see "French"
    And I should see "German"

  Scenario: Check the base path doesn't change when changing language prefix
    Given the site front page is set to "admin/fake-url"
    And the "en" language "prefix" is set to "en-prefix"
    And the cache has been cleared
    When I go to "admin/config/system/site-information"
    Then I should be on "admin/config/system/site-information"
    # We check that path prefix set earlier does not bleeds into the site base path.
    And I should not see "en-prefix" in the ".form-item-site-frontpage span.field-prefix" element
    When I click "Home"
    Then I should be on "admin/fake-url_en-prefix"

  Scenario: Path alias must be synchronized through all translations of
  content when it is manually defined and the configuration is maintained
  when I come back on the content edit form
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    And I am viewing a multilingual "page" content:
      | language | title            |
      | en       | Title in English |
      | fr       | Title in French  |
    When I click "English" in the "header_top" region
    And I click "Français"
    Then I should be on "content/title-english_fr"
    When I click "New draft"
    And I uncheck the box "edit-path-pathauto"
    And I fill in "URL alias" with "page-alias-for-all-languages"
    And I select "published" from "Moderation state"
    And I press "Save"
    Then I should be on "page-alias-for-all-languages_fr"
    When I click "Français" in the "header_top" region
    And I click "English"
    Then I should be on "page-alias-for-all-languages_en"
    When I click "New draft"
    Then I should not see the box "edit-path-pathauto" checked
    And the "URL alias" field should contain "page-alias-for-all-languages"