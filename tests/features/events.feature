@api @wip
Feature: Event features
  In order programm events
  As a citizen of the European Union
  I want to be able to see a callendar with events
  
  @api
  Scenario: Users can see the calendar
    Given I am an anonymous user
    Given these featureSet are enabled
      |featureSet|
      |Events|
    When I go to "calendar"
    Then I should see an "div.fullcalendar" element
    Then I should see the text "Consult planned events"
