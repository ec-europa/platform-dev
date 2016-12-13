@api @cleanCommunityEnvironment
Feature: Nexteuropa Communities
  In order to effectively manage groups of people
  As a site administrator
  I want to be able to add, edit and delete communities

  Background:
    Given these modules are enabled
      | modules                 |
      | nexteuropa_communities  |
    # We need to rewrite value of 'group_access', because the dash in the input table does not work
    And I am logged in as a user with the 'administrator' role
    And I go to "admin/structure/types/manage/community/fields/group_access/field-settings_en"
    And I fill in "edit-on" with "Private"
    And I fill in "edit-off" with "Public"
    And I press the "Save field settings" button
    
  Scenario: As a group admin, all community's block are present.
    Given "community" content:
      | title          | workbench_moderation_state_new | status | language |
      | Test community | published                      | 1      | und      |
    And I have the "administrator member" role in the "test community" group
    When I go to "community/test-community"
    Then I should see the heading "Test community"
    And I should see "Test community" in the "#block-menu-menu-community-menu" element
    And I should see "Test community" in the "#block-views-community-members-block-1" element
    And I should see "Create Content" in the "#block-multisite-og-button-og-contextual-links" element
    When I go to "community/test-community/foo"
    Then I should see the heading "Page not found"
    And I should see "Test community" in the "#block-menu-menu-community-menu" element
    And I should see "Test community" in the "#block-views-community-members-block-1" element
    And I should see "Create Content" in the "#block-multisite-og-button-og-contextual-links" element



  Scenario: URL alias for community contents are correctly generated.
    Given these modules are enabled
      | modules                 |
      | nexteuropa_news         |
    When I am viewing a "community" content:
      | title                          | A public community |
      | group_access                   | Public             |
      | workbench_moderation_state     | published          |
      | workbench_moderation_state_new | published          |
    And I am viewing a "nexteuropa_news" content:
      | title                          | A News in a public community         |
      | og_group_ref                   | A public community                   |
      | field_ne_body                  | Lorem ipsum dolor sit amet body.     |
      | field_abstract                 | Lorem ipsum dolor sit amet abstract. |
      | workbench_moderation_state     | published                            |
      | workbench_moderation_state_new | published                            |
    And I am viewing a "page" content:
      | title                          | A page in a public community         |
      | og_group_ref                   | A public community                   |
      | field_ne_body                  | Lorem ipsum dolor sit amet body.     |
      | workbench_moderation_state     | published                            |
      | workbench_moderation_state_new | published                            |
      When I go to "community/public-community"
      Then I should see the heading "A public community"
      When I go to "community/public-community/news/news-public-community"
      Then I should see the heading "A News in a public community"
      When I go to "community/public-community/basic-page/page-public-community"
      Then I should see the heading "A page in a public community"


  Scenario: As an anonymous user, I can see content of public community, and community's block
    Given I am not logged in
    When I am viewing a "community" content:
      | title                          | A public community |
      | group_access                   | Public             |
      | workbench_moderation_state     | published          |
      | workbench_moderation_state_new | published          |
    Then I should see the heading "A public community"
    And I should see "A public community" in the "#block-menu-menu-community-menu" element
    When I am viewing a "page" content:
      | title                          | A Page in a public community         |
      | og_group_ref                   | A public community                   |
      | field_ne_body                  | Lorem ipsum dolor sit amet body.     |
      | field_abstract                 | Lorem ipsum dolor sit amet abstract. |
      | workbench_moderation_state     | published                            |
      | workbench_moderation_state_new | published                            |
    Then I should see the heading "A Page in a public community"
    And I should see "A public community" in the "#block-menu-menu-community-menu" element


  Scenario: As an anonymous user, I cannot see content of private community
    Given I am not logged in
    When I am viewing a "community" content:
      | title                          | A private community                  |
      | group_access                   | Private                              |
      | workbench_moderation_state     | published                            |
      | workbench_moderation_state_new | published                            |
    Then I should get an access denied error
      When I am viewing a "page" content:
      | title                          | A Page in a private community        |
      | og_group_ref                   | A private community                  |
      | field_ne_body                  | Lorem ipsum dolor sit amet body.     |
      | field_abstract                 | Lorem ipsum dolor sit amet abstract. |
      | workbench_moderation_state     | published                            |
      | workbench_moderation_state_new | published                            |
    Then I should get an access denied error

  Scenario: As an authenticated user, I cannot see content of private community
    Given I am logged in as a user with the 'authenticated user' role
    When I am viewing a "community" content:
      | title                          | A private community                  |
      | group_access                   | Private                              |
      | workbench_moderation_state     | published                            |
      | workbench_moderation_state_new | published                            |
    Then I should get an access denied error
    When I am viewing a "page" content:
      | title                          | A Page in a private community        |
      | og_group_ref                   | A private community                  |
      | field_ne_body                  | Lorem ipsum dolor sit amet body.     |
      | field_abstract                 | Lorem ipsum dolor sit amet abstract. |
      | workbench_moderation_state     | published                            |
      | workbench_moderation_state_new | published                            |
    Then I should get an access denied error


  Scenario: As an authenticated user, I can subscribes/un-subscribe on a public community
    Given I am logged in as a user with the 'authenticated user' role
    When I am viewing a "community" content:
      | title                          | A Public community  |
      | group_access                   | Public              |
      | workbench_moderation_state     | published           |
      | workbench_moderation_state_new | published           |
    Then I should see the heading "A Public community"
    When I click "Request group membership"
    Then I should see the heading "Are you sure you want to join the group A Public community?"
    When I press the "Join" button
    Then I should see the link "Unsubscribe from group"
    When I click "Unsubscribe from group"
    Then I should see the heading "Are you sure you want to unsubscribe from the group A Public community?"
    When I press the "Remove" button
    Then I should see the link "Request group membership"


    Scenario: As a group member, I can create/edit/delete a group content (page) on my public community
    Given I am logged in as a user with the 'authenticated user' role
    When I am viewing a "community" content:
      | title                          | My public Community |
      | group_access                   | Public              |
      | workbench_moderation_state     | published           |
      | workbench_moderation_state_new | published           |
    And I have the "member" role in the "My public Community" group
    When I reload the page
    And I click "Basic page" in the sidebar_left
    And I fill in "title_field[und][0][value]" with "Page in My public Community"
    And I fill in "field_ne_body[und][0][value]" with "Lorem ipsum dolor sit amet"
    And I press the "Save" button
    Then I should see the success message "Basic page Page in My public Community has been created."
    When I go to "community/my-public-community/basic-page/page-my-public-community"
    Then I should see the heading "Page in My public Community"
    When I click "Edit draft"
    And I fill in "title_field[en][0][value]" with "Page 1 in My public Community"
    And I press the "Save" button
    Then I should see the success message "Page 1 in My public Community has been updated."
    And I should see the heading "Page 1 in My public Community"
    When I click "Edit draft"
    And I press the "Delete" button
    Then I should see the heading "Are you sure you want to delete Page 1 in My public Community?"
    When I press the "Delete" button
    Then I should see the success message "Page 1 in My public Community has been deleted."


  Scenario: As a group member, I can create/edit/delete a group content (page) on my private community
    Given I am logged in as a user with the 'authenticated user' role
    When I am viewing a "community" content:
      | title                          | My private community |
      | group_access                   | Private              |
      | workbench_moderation_state     | published            |
      | workbench_moderation_state_new | published            |
    And I have the "member" role in the "My private Community" group
    When I reload the page
    And I click "Basic page" in the sidebar_left
    And I fill in "title_field[und][0][value]" with "Page in My private Community"
    And I fill in "field_ne_body[und][0][value]" with "Lorem ipsum dolor sit amet"
    And I press the "Save" button
    Then I should see the success message "Basic page Page in My private Community has been created."
    When I go to "community/my-private-community/basic-page/page-my-private-community"
    Then I should see the heading "Page in My private Community"
    When I click "Edit draft"
    And I fill in "title_field[en][0][value]" with "Page 1 in My private Community"
    And I press the "Save" button
    Then I should see the success message "Page 1 in My private Community has been updated."
    And I should see the heading "Page 1 in My private Community"
    When I click "Edit draft"
    And I press the "Delete" button
    Then I should see the heading "Are you sure you want to delete Page 1 in My private Community?"
    When I press the "Delete" button
    Then I should see the success message "Page 1 in My private Community has been deleted."


  Scenario: As a site administrator, I can enable/disable the private area
    When I am logged in as a user with the 'administrator' role
    And I go to "admin/config/nexteuropa_communities/nexteuropa_private_area_en"
    Then I should see the heading "NextEuropa private area"
    And I check the box "edit-nexteuropa-communities-private-area"
    And I press the "Save configuration" button
    And I should see the success message "The configuration options have been saved."
    Given I am not logged in
    When I am viewing a "community" content:
      | title                          | A Public community |
      | group_access                   | Public             |
      | workbench_moderation_state     | published          |
      | workbench_moderation_state_new | published          |
    Then I should get an access denied error
