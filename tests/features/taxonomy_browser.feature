@api
Feature: Taxonomy browser
  In order to test ‘Taxonomy browser’ feature
  As an administrator
  I want to make sure ‘Taxonomy browser’ allows creating blocks with taxonomy vocabularies and filter by terms

  Background:
    Given I am logged in as a user with the 'administrator' role

  @api @theme_wip
  Scenario: Administrator user creates a new view to show the taxonomy block.
    Given a content view with machine name "view_articles" is available
    When I go to "/admin/structure/views/view/view_articles"
    Then the response status code should be 200
    Then I should see the text "Master details"
    #Page display
    And I press the "edit-displays-top-add-display-page" button
    Then I should see the text "Page details"
    When I go to "/admin/structure/views/nojs/display/view_articles/page_1/path_en"
    Then I should see the text "Page: The menu path or URL of this view"
    And I fill in "edit-path" with "/view-articles"
    And I press the "Apply" button
    Then I should see the text "* All changes are stored temporarily. Click Save to make your changes permanent. Click Cancel to discard your changes."
    #Configure contextual
    When I go to "/admin/structure/views/nojs/add-item/view_articles/default/argument_en"
    Then I check "Content: Has taxonomy term ID (with depth)"
    And I press the "Add and configure contextual filters" button
    When I select the radio button "Provide default value"
    And I fill in "Fixed value" with "fixed_value"
    Then I check "Override title"
    And I fill in "edit-options-title" with "%1"
    And I press the "Apply" button
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
    #Add the block to a region
    Given I visit "/admin/config/taxonomy_browser/settings_en"
    And the checkbox "edit-taxonomy-browser-vocabulary-2" is checked
    When I visit "/admin/structure/block_en"
    Then I should see the text "taxonomy_browser: Tags"
    When I go to "/admin/structure/block/manage/taxonomy_browser/taxonomy_browser_vocabulary_2/configure_en"
    When I select "Sidebar Left" from "Ec_resp (default theme)"
    And I press "Save block"
    Then I should see the text "The block configuration has been saved."
    #Add some content
     And 'Article' content:
    | title           | author        | workbench_moderation_state_new | workbench_moderation_state | language | status | field_tags |
    | economic test 1 | administrator | published                      | published                  | en       | 1      | economic   |
    | economic test 2 | administrator | published                      | published                  | en       | 1      | economic   |
    | sport test 1    | administrator | published                      | published                  | en       | 1      | sport      |
    #Test it
    When I go to "/view-articles"
    Then I should see the text "Tags"
    And I should see the text "economic"
    And I should see the text "sport"
    Then I click "economic"
    And the response should contain "<h1 class=\"field-content\">economic</h1>"
    And the response should contain "<a href=\"/content/economic-test-1_en\">economic test 1</a>"
    And the response should contain "<a href=\"/content/economic-test-2_en\">economic test 2</a>"
    And the response should not contain "<h1 class=\"field-content\">sport</h1>"
    And the response should not contain "<a href=\"/content/sport-test-1_en\">sport test 1</a>"
    Then I click "sport"
    And the response should contain "<h1 class=\"field-content\">sport</h1>"
    And the response should contain "<a href=\"/content/sport-test-1_en\">sport test 1</a>"
    And the response should not contain "<h1 class=\"field-content\">economic</h1>"
    And the response should not contain "<a href=\"/content/economic-test-1_en\">economic test 1</a>"
    And the response should not contain "<a href=\"/content/economic-test-2_en\">economic test 2</a>"
