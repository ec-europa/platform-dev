@api @javascript @communities @internalMail
Feature: User notifications
  In order to ease community management
  As a site administrator
  I want to make sure community managers and users get notified of changes in memberships.

  Background:
    Given users:
      | name          | mail                 | pass         | roles          |
      | administrator | adminis@example.com  | password123  | administrator  |
      | contribuser   | authuser@example.com | password456  | contributor    |
    And these featureSet are enabled
      | featureSet     |
      | Notifications  |
    And these modules are enabled
      | modules    |
      | mailsystem |
    And platform is configured to use the internal mail handling
    And 'Community' content:
      | title          | author        | workbench_moderation_state_new | workbench_moderation_state | language | status |
      | Test Community | administrator | draft                          | draft                      | en       | 1      |
    And I am logged in as "administrator"

  @prueba
  Scenario: Contributor users are notified when a new community is requested
    Given I go to "node/add/community"
    And I fill in "Title" with "New Community"
    And I press the "Save" button
    Then the e-mail has been sent
    And the sent e-mail has the following properties:
      | from        | admin@example.com                  |
      | to          | adminis@example.com                |
      | subject     | administrator joined New Community |
    And I visit the "Community" content with title "New Community"
    And I select "Needs Review" from "Moderation state"
    And I press the "Apply" button
    Then the e-mail has been sent
    And the sent e-mail has the following properties:
      | from        | admin@example.com    |
      | to          | adminis@example.com  |
      | subject     | Community refused    |
    And I visit the "Community" content with title "New Community"
    And I select "Draft" from "Moderation state"
    And I press the "Apply" button
    Then the e-mail has been sent
    And the sent e-mail has the following properties:
      | from        | admin@example.com             |
      | to          | authuser@example.com          |
      | subject     | Creation of community request |


  Scenario: Community creator is notified when the created community is refused

  Scenario: Member and community creator are notified when a member is blocked from a community

  Scenario: Member and community creator are notified when a member is removed from a community

  Scenario: Member and community creator are notified when a member is approved on a community

  Scenario: Community creator and user are notified when a user becomes a Member

  Scenario: Community creator and user are notified when a user has a pending of approval membership