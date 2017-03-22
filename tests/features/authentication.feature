@api @communitites
Feature: User authentication
  In order to protect the integrity of the website
  As a product owner
  I want to make sure only authenticated users can access the site administration

Scenario: Anonymous user can see the user login page
  Given I am not logged in
  When I visit "user"
  Then I should see the text "EU Login"
  And I should see the text "Request new password"
  And I should see the text "Username"
  And I should see the text "Password"
  But I should not see the text "Log out"
  And I should not see the text "My account"

Scenario Outline: Anonymous user cannot access site administration
  Given I am not logged in
  When I go to "<path>"
  Then I should get an access denied error

  Examples:
  | path                        |
  | admin/config                |
  | admin/dashboard             |
  | admin/structure             |
  | admin/structure/feature-set |
  | node/add/article            |

@api
Scenario Outline: Editors can access certain administration pages
  Given I am logged in as a user with the "editor" role
  Then I visit "<path>"

  Examples:
  | path                       |
  | node/add/article           |

@api
Scenario Outline: Editors cannot access pages intended for administrators
  Given I am logged in as a user with the "editor" role
  When I go to "<path>"
  Then I should get an access denied error

  Examples:
  | path                        |
  | admin/config                |
  | admin/dashboard             |
  | admin/structure             |
  | admin/structure/feature-set |
  | node/add/editorial-team_en  |

@api
Scenario Outline: Administrators can access certain administration pages
  Given I am logged in as a user with the "administrator" role
  Then I visit "<path>"

  Examples:
  | path                        |
  | admin/config                |
  | admin/dashboard             |
  | admin/structure             |
  | admin/structure/feature-set |
  | node/add/article            |
  | node/add/editorial-team_en |

@api
Scenario Outline: Administrators should not be able to access technical pages intended for developers
  Given I am logged in as a user with the "administrator" role
  When I go to "<path>"
  Then I should get an access denied error

  Examples:
  | path                     |
  | admin/structure/features |
