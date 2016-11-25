Feature: Check Piwik
  In order to check if the the type attribute is set for the Piwik element.
  As an administrator
  I want to check Piwik is available.

@api
Scenario: Administrator user can check Piwik Script with the theme Bootstrap
  Given the module is enabled
    | modules            |
    | nexteuropa_piwik   |
  Given I am logged in as a user with the 'administrator' role
  When I run drush "pm-enable bootstrap -y"
  And I run drush "vset theme_default bootstrap"
  And the cache has been cleared
  Then I am on the homepage
  And the response should contain "{\"utility\":\"piwik\",\"siteID\":\"\",\"sitePath\":[\"\"],\"is404\":false,\"instance\":\"\"}"
  When I run drush "vset theme_default ec_resp"
  And the cache has been cleared
  Then I am on the homepage
  And the response should contain "{\"utility\":\"piwik\",\"siteID\":\"\",\"sitePath\":[\"\"],\"is404\":false,\"instance\":\"\"}"

