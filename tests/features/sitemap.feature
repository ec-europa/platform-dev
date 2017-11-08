Feature: Check the Sitemap
  In order to let search engines know about the pages in my site and improve traffic from them
  As an administrator
  I can publish a sitemap

  @api
  Scenario: Value of the variable xmlsitemap_prefetch_aliases is zero
    Given the module is enabled
      | modules     |
      | sitemap     |
    Given I am logged in as a user with the "administrator" role
    When I go to "/admin/config/search/xmlsitemap/settings"
    Then "Prefetch URL aliases during sitemap generation." checkbox should not be checked

  @api
  Scenario: Administrator user can check the sitemap
    Given the module is enabled
      | modules     |
      | sitemap     |
    Given I am logged in as a user with the "anonymous" role
    When I go to "/sitemap.xml"
    Then the response should not contain "Page not found"
    And the response should contain "<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\" xmlns:xhtml=\"http://www.w3.org/1999/xhtml\">"
