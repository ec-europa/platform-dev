@api
Feature: Feature set menu
  In order to easily enable a feature
  As an administrative user
  I want to have a list of features to be enabled

  @api
  Scenario Outline: Test feature set screen as administrator
    Given I am logged in as a user with the "administrator" role
    When I am on "admin/structure/feature-set_en"
    Then I should see the text "<feature_name>"
    And I should not see the text "Nexteuropa DGT Connector"

    Examples:
      | feature_name                          |
      | Content slider                        |
      | Events                                |
      | Links                                 |
      | Multi-user blog                       |
      | Meta tags                             |
      | Registration                          |
      | Webtools                              |
      | Text collapse                         |
      | Wiki                                  |
      | WYSIWYG Tracked Changes               |
      | World Countries                       |
      | F.A.Q                                 |
      | Press Release                         |
      | Site activity                         |
      | Maxlength                             |
      | News                                  |
      | Newsletters                           |
      | GIS field                             |
      | GeoJson feeds                         |
      | Notices                               |
      | Integration module                    |
      | Rule-based web frontend cache purging |
      | E-library                             |
      | Embedded images                       |
      | Embedded videos                       |
      | Audio                                 |
      | Crop & Resize                         |
      | Media Gallery                         |
      | Multilingual tools                    |
      | Multilingual reference                |
      | Translation requests                  |
      | Splash screen                         |
      | Fat footer                            |
      | Mega menu                             |
      | Node pager                            |
      | Sitemap                               |
      | Business indicators                   |
      | Contact form                          |
      | Ideas                                 |
      | Surveys                               |
      | Extend Profiles                       |
      | Notifications                         |


  @api
  Scenario: Test feature set screen as cem
    Given I am logged in as a user with the "cem" role
    When I am on "admin/structure/feature-set_en"
    Then I should not see the text "Content slider"
    Then I should not see the text "Events"
    Then I should not see the text "Links"
    Then I should not see the text "Multi-user blog"
    Then I should not see the text "Meta tags"
    Then I should not see the text "Registration"
    Then I should not see the text "Webtools"
    Then I should not see the text "Wiki"
    Then I should not see the text "WYSIWYG Tracked Changes"
    Then I should not see the text "World Countries"
    Then I should not see the text "WYSIWYG Tracked Changes"
    Then I should not see the text "F.A.Q"
    Then I should not see the text "Press Release"
    Then I should not see the text "Site activity"
    Then I should not see the text "Maxlength"
    Then I should not see the text "News"
    Then I should not see the text "Newsletters"
    Then I should not see the text "GIS field"
    Then I should not see the text "GeoJson feeds"
    Then I should not see the text "Notices"
    Then I should not see the text "Integration"
    Then I should not see the text "Rule-based web frontend cache purging"
    Then I should not see the text "E-library"
    Then I should not see the text "Embedded images"
    Then I should not see the text "Embedded videos"
    Then I should not see the text "Audio"
    Then I should not see the text "Crop & Resize"
    Then I should not see the text "Media Gallery"
    Then I should not see the text "Multilingual tools"
    Then I should not see the text "Multilingual reference"
    Then I should not see the text "Translation requests"
    Then I should not see the text "Splash screen"
    Then I should not see the text "Fat footer"
    Then I should not see the text "Mega menu"
    Then I should not see the text "Node pager"
    Then I should not see the text "Business indicators"
    Then I should not see the text "Sitemap"
    Then I should not see the text "Contact form"
    Then I should not see the text "Ideas"
    Then I should not see the text "Surveys"
    Then I should not see the text "Extend Profiles"
    Then I should not see the text "Notifications"
    And I should see the text "Nexteuropa DGT Connector"
