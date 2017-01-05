Feature: Check the Sitemap
  In order to let search engines know about the pages in my site and improve traffic from them
  As an administrator
  I can publish a sitemap

  Scenario: Administrator user can check the sitemap
    Given the module is enabled
      | modules     |
      | sitemap     |
    Given I am an anonymous user
    When I go to "/sitemap.xml"
    And the response should not contain "Page not found"
    And the response should contain "<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\" xmlns:xhtml=\"http://www.w3.org/1999/xhtml\">"