@api
Feature: Event features
  In order programm events
  As a citizen of the European Union
  I want to be able to see a callendar with events

  Background:
    Given I am an anonymous user
    And these featureSet are enabled
      | featureSet |
      | Events     |

  Scenario: Users can see the calendar
    When I go to "calendar"
    Then I should see an "div.fullcalendar" element
    And I should see the text "Consult planned events"

  Scenario: Users can see the calendar when a term of Resources is added
    Given the vocabulary "Resources" exists
    And "Resources" terms:
      | Term resource     |
    When I go to "calendar"
    Then I should see an "div.fullcalendar" element
    And I should see the text "Consult planned events"
