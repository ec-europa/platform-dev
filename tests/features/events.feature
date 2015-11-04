Feature: Event features
  In order programm events
  As a citizen of the European Union
  I want to be able to see a callendar with events
  
  @api
  Scenario: Users can see the calendar
    Given I am an anonymous user
    Given these modules are enabled
      |modules|
      |events_standard|
    When I go to "calendar_en"
    Then I should see an "div.fullcalendar" element
    Then I should see the text "Consult planned events"
