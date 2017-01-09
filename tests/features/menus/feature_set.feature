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
  Scenario Outline: Test feature set screen as cem
    Given I am logged in as a user with the "cem" role
    When I am on "admin/structure/feature-set_en"
    Then I should not see the text "<feature_name>"
    And I should see the text "Nexteuropa DGT Connector"

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
