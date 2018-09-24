@api @javascript
Feature: Failing test

Scenario: Failing scenario
  When I am on the homepage
  Then I should see the text "If this text is present, we have a problem"
