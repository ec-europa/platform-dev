Feature: Check the Sitemap
  In order to check if the sitemap is available and correct.
  As an administrator
  I want to check the sitemap generated is available and correct.

  @api
  Scenario: Administrator user can check the sitemap
    Given the module is enabled
      | modules     |
      | sitemap     |
    Given I am logged in as a user with the 'administrator' role
    When I go to "/sitemap.xml"
    And the response should not contain "Page not found"
    And the response should contain "<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\" xmlns:xhtml=\"http://www.w3.org/1999/xhtml\">"