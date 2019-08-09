@api @ec_resp
Feature: Feature set menu
  In order to easily enable a feature
  As an administrative user
  I want to have a list of features to be enabled

  @api @ec_europa_theme
  Scenario: Test feature set screen as administrator
    Given I am logged in as a user with the "administrator" role
    When I am on "admin/structure/feature-set_en"
    Then I should see the text "Content slider"
    And I should see the text "Events"
    # Cannot use "Links" label to test if administrator user can see the "Links"
    # feature because it is already elsewhere on the page for another purpose.
    And I should see the text "Allows contributors to store a bookmark/URL to another website they wish to share with visitors."
    And I should see the text "Multi-user blog"
    And I should see the text "Registration"
    And I should see the text "Text collapse"
    And I should see the text "Webtools"
    And I should see the text "Wiki"
    And I should see the text "WYSIWYG Tracked Changes"
    And I should see the text "World Countries"
    And I should see the text "F.A.Q"
    And I should see the text "Press Release"
    And I should see the text "Site activity"
    And I should see the text "Maxlength"
    And I should see the text "News"
    And I should see the text "Newsletters"
    And I should see the text "GIS field"
    And I should see the text "GeoJson feeds"
    And I should see the text "Rule-based web frontend cache purging"
    And I should see the text "E-library"
    And I should see the text "Embedded images "
    And I should see the text "Embedded videos"
    And I should see the text "Audio"
    And I should see the text "Media Gallery"
    And I should see the text "Multilingual tools"
    And I should see the text "Translation requests"
    And I should see the text "Splash screen"
    And I should see the text "Fat footer"
    And I should see the text "Mega menu"
    And I should see the text "Node pager"
    And I should see the text "Sitemap"
    And I should see the text "Contact form"
    And I should see the text "Ideas"
    And I should see the text "Surveys"
    And I should see the text "Extend Profiles"
    And I should see the text "Notifications"
