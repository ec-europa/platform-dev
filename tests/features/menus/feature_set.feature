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
    Then I should not see "Content slider" in the "name" element
    Then I should not see "Events" in the "name" element
    Then I should not see "Links" in the "name" element
    Then I should not see "Multi-user blog" in the "name" element
    Then I should not see "Meta tags" in the "name" element
    Then I should not see "Registration" in the "name" element
    Then I should not see "Webtools" in the "name" element
    Then I should not see "Wiki" in the "name" element
    Then I should not see "WYSIWYG Tracked Changes" in the "name" element
    Then I should not see "World Countries" in the "name" element
    Then I should not see "WYSIWYG Tracked Changes" in the "name" element
    Then I should not see "F.A.Q" in the "name" element
    Then I should not see "Press Release " in the "name" element
    Then I should not see "Site activity" in the "name" element
    Then I should not see "Maxlength" in the "name" element
    Then I should not see "News" in the "name" element
    Then I should not see "Newsletters" in the "name" element
    Then I should not see "GIS field" in the "name" element
    Then I should not see "GeoJson feeds" in the "name" element
    Then I should not see "Notices" in the "name" element
    Then I should not see "Integration" in the "name" element
    Then I should not see "Rule-based web frontend cache purging" in the "name" element
    Then I should not see "E-library" in the "name" element
    Then I should not see "Embedded images " in the "name" element
    Then I should not see "Embedded videos" in the "name" element
    Then I should not see "Audio" in the "name" element
    Then I should not see "Crop & Resize" in the "name" element
    Then I should not see "Media Gallery" in the "name" element
    Then I should not see "Multilingual tools" in the "name" element
    Then I should not see "Multilingual reference" in the "name" element
    Then I should not see "Translation requests" in the "name" element
    Then I should not see "Splash screen" in the "name" element
    Then I should not see "Fat footer" in the "name" element
    Then I should not see "Mega menu" in the "name" element
    Then I should not see "Node pager" in the "name" element
    Then I should not see "Business indicators" in the "name" element
    Then I should not see "Sitemap" in the "name" element
    Then I should not see "Contact form" in the "name" element
    Then I should not see "Ideas" in the "name" element
    Then I should not see "Surveys" in the "name" element
    Then I should not see "Extend Profiles" in the "name" element
    Then I should not see "Notifications" in the "name" element
    And I should see the text "Nexteuropa DGT Connector"
