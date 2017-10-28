@api
Feature: Taxonomy browser
  In order to test ‘Taxonomy browser’ feature
  As an administrator
  I want to make sure ‘Taxonomy browser’ allows creating blocks with taxonomy vocabularies

  Background:
    Given I am logged in as a user with the 'administrator' role
    When I visit "/admin/config/taxonomy_browser/settings_en"
    When I check "edit-taxonomy-browser-vocabulary-2"
    And  I press "Save configuration"
    Then I should see the text "The configuration options have been saved."

  @api
  Scenario: Administrator user creates a new view to show the taxonomy block.
    Given a content view with machine name "view_articles" is available
    When I go to "/admin/structure/views/view/view_articles"
    Then the response status code should be 200
    Then I should see the text "Master details"
    #Configure contextual
    When I go to "/admin/structure/views/nojs/add-item/view_articles/default/argument_en"
    Then I check "Content: Has taxonomy term ID (with depth)"
    And I press the "Add and configure contextual filters" button
    When I select the radio button "Provide default value"
    And I fill in "Fixed value" with "fixed_value"
    Then I check "Override title"
    And I fill in "edit-options-title" with "%1"
    And I press the "Apply" button
    And the module is enabled
      | modules         |
      | easy_breadcrumb |
    #Configure header
    When I go to "/admin/structure/views/nojs/add-item/view_articles/default/header_en"
    Then I check "edit-name-viewsview"
    And I press the "Add and configure header" button
    And I select "View: taxonomy_browser_header - Display: default" from "View to insert"
    Then I check "Inherit contextual filters"
    And I press the "Apply" button
    When I go to "/admin/structure/views/nojs/add-item/view_articles/default/field_en"
    Then I check "edit-name-nodetitle"
    And I press the "Add and configure fields" button
    And I press the "Apply" button
    Then I should see the text "* All changes are stored temporarily. Click Save to make your changes permanent. Click Cancel to discard your changes."
    And I press the "Save" button
    Then I should see the text "has been saved."

  @api
  Scenario: Administrator user activates the vocabulary on taxonomy browser page and configures the block.
    When I visit "/admin/config/taxonomy_browser/settings_en"
    Then I should see the text "Taxonomy vocabularies"
    Then I should see the text "classification"
    Then I should see the text "Tags"
    And I check "edit-taxonomy-browser-vocabulary-1"
    And I click "configure block"
    Then I should see the text "Configure block"
    And I should see the text "Block title"
    And I fill in "Block title" with "Vocabulary Test block"
    And I press the "Save" button
    Then I should see the text "The block configuration has been saved."
    When I go to "admin/structure/block_en"
    Then I should see the text "taxonomy_browser: Tags"

  @api
  Scenario: Administrator user can delete block.
    Given I visit "/admin/config/taxonomy_browser/settings_en"
    And I uncheck "edit-taxonomy-browser-vocabulary-2"
    Then  I press "Save configuration"
    And I should see the text "The configuration options have been saved."

  @api
  Scenario: Administrator user can add the block to a region
    Given I visit "/admin/config/taxonomy_browser/settings_en"
    And the checkbox "edit-taxonomy-browser-vocabulary-2" is checked
    When I visit "/admin/structure/block_en"
    Then I should see the text "taxonomy_browser: Tags"
    When I go to "/admin/structure/block/manage/taxonomy_browser/taxonomy_browser_vocabulary_2/configure_en"
    When I select "content" from "Ec_resp (default theme)"
    And I press "Save block"
    Then I should see the text "The block configuration has been saved."

  @api
  Scenario: Testing the block appears
    When I am on the homepage
    Then I should see the text "Tags"
    Then I should see the text "economic"
    Then I should see the text "sport"

  @api
  Scenario: Testing the filtering
    When I am on the homepage
    And I click "economic"
    Then I should see the text "The requested page could not be found."
    And I click "sport"
    Then I should see the text "The requested page could not be found."
