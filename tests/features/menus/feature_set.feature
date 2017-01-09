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
    Then I should see "Content slider" in the "feature-set__name" element
    Then I should see "Events" in the "feature-set__name" element
    Then I should see "Links" in the "feature-set__name" element
    Then I should see "Multi-user blog" in the "feature-set__name" element
    Then I should see "Meta tags" in the "feature-set__name" element
    Then I should see "Registration" in the "feature-set__name" element
    Then I should see "Webtools" in the "feature-set__name" element
    Then I should see "Wiki" in the "feature-set__name" element
    Then I should see "WYSIWYG Tracked Changes" in the "feature-set__name" element
    Then I should see "World Countries" in the "feature-set__name" element
    Then I should see "WYSIWYG Tracked Changes" in the "feature-set__name" element
    Then I should see "F.A.Q" in the "feature-set__name" element
    Then I should see "Press Release " in the "feature-set__name" element
    Then I should see "Site activity" in the "feature-set__name" element
    Then I should see "Maxlength" in the "feature-set__name" element
    Then I should see "News" in the "feature-set__name" element
    Then I should see "Newsletters" in the "feature-set__name" element
    Then I should see "GIS field" in the "feature-set__name" element
    Then I should see "GeoJson feeds" in the "feature-set__name" element
    Then I should see "Notices" in the "feature-set__name" element
    Then I should see "Integration" in the "feature-set__name" element
    Then I should see "Rule-based web frontend cache purging" in the "feature-set__name" element
    Then I should see "E-library" in the "feature-set__name" element
    Then I should see "Embedded images " in the "feature-set__name" element
    Then I should see "Embedded videos" in the "feature-set__name" element
    Then I should see "Audio" in the "feature-set__name" element
    Then I should see "Crop & Resize" in the "feature-set__name" element
    Then I should see "Media Gallery" in the "feature-set__name" element
    Then I should see "Multilingual tools" in the "feature-set__name" element
    Then I should see "Multilingual reference" in the "feature-set__name" element
    Then I should see "Translation requests" in the "feature-set__name" element
    Then I should see "Splash screen" in the "feature-set__name" element
    Then I should see "Fat footer" in the "feature-set__name" element
    Then I should see "Mega menu" in the "feature-set__name" element
    Then I should see "Node pager" in the "feature-set__name" element
    Then I should see "Business indicators" in the "feature-set__name" element
    Then I should see "Sitemap" in the "feature-set__name" element
    Then I should see "Contact form" in the "feature-set__name" element
    Then I should see "Ideas" in the "feature-set__name" element
    Then I should see "Surveys" in the "feature-set__name" element
    Then I should see "Extend Profiles" in the "feature-set__name" element
    Then I should see "Notifications" in the "feature-set__name" element
    And I should see the text "Nexteuropa DGT Connector"
