Feature: Nexteuropa Newsroom
  Testing nexteuropa newsroom feature

@api
Scenario: Checks access to newsroom settings
  Given I am logged in as a user with the "administrator" role
  When I visit "admin/config/content/newsroom"
  Then I should see the text "Universe ID value"
  And I should see the text "Newsroom proposal URL"

@api
Scenario: Saves Universe ID
  Given I am logged in as a user with the "administrator" role
  When I visit "admin/config/content/newsroom"
  And I fill in "newsroom_universe_id" with "dae"
  When I press "Save configuration"
  Then I should see "The configuration options have been saved."
  And I press "Rebuild importers on the fly"

@api
Scenario: Checks generated importers
  Given I am logged in as a user with the "administrator" role
  When I visit "import"
  Then I should see "Newsroom Items Multilanguage"
  And I should see "Newsroom Services Multilingual"
  And I should see "Newsroom Topics Multilingual"
  And I should see "Newsroom Type Multilingual"