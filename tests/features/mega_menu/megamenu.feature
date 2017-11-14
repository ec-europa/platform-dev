@api @javascript
Feature: megamenu
  In order to use megamenu feature
  As different types of users
  I want to be able to create and view mega menus

  Background:
    Given I use device with "1920" px and "1080" px resolution
    And the module is enabled
      | modules            |
      | multisite_megamenu |
      | om_maximenu        |

  Scenario: As an administrator I can create a mega menu
    Given I am logged in as a user with the "administrator" role
    When  I go to "/admin/structure/om-maximenu/"
    And   I click "Edit" in the "Main Menu" row
    And   I click "Menu Links"
    # I choose one of the "New link" options
    And   I click on the element with xpath "//*[@id='edit-om-maximenus-1-links-750']/legend/span/a"
    Then  I should see "Link Title"
    When  I fill in "edit-om-maximenus-1-links-750-link-title" with "Mega Menu"
    And   I fill in "edit-om-maximenus-1-links-750-path" with "http://www.gooogle.es"
        # Clicking the Save button gives a "Warning" and the test cannot continue.
    And   I press "Save"

    # I create a block to add in the MEGA MENU in the menu
    And   I go to "/admin/structure/block/add"
    And   I fill in "Block title" with "Mega Menu Element 1"
    And   I fill in "Block description" with "block to add to the mega menu element in main menu"
    And   I click "Disable rich-text"
    And   I fill in "Block body" with "<p><a href='https://www.google.es/'>google</a></p><p><a href='https://es.wikipedia.org/'>wikipedia</a></p><p><a href='https://www.drupal.org/'>drupal</a></p>"
    And   I press "Save block"
    And   I should see the text "The block has been created."

    # I add the new block to the MEGA MENU in the menu
    When  I go to "/admin/structure/om-maximenu/"
    And   I click "Edit" in the "Main Menu" row
    And   I click "Menu Links"
    And   I click "Mega Menu"
    And   I click "Enable / Disabled blocks attached to this link." in the "Mega Menu" row
    And   I wait
    And   I click on the element with xpath "//*[@id='edit-om-maximenu-content-block']/legend/span/a"
    And   I click "Mega Menu Element 1"
    And   I check the box on the "MEGA MENU ELEMENT 1" row
    And   I press "Save"
    Then  I should see the text "Your settings have been saved."
        # Clicking the Save button gives a "Warning" and the test cannot continue.
    And   I press "Save"

    # I check that the menu has been created and is visible
    When  I go to the homepage
    And   I break
    Then  I should see the link "Mega Menu"
    And   I should not visibly see the link "google"
    And   I should not visibly see the link "wikipedia"
    And   I should not visibly see the link "drupal"
