@api @javascript @theme_wip
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
    And   I click "Add menu"
    And   I fill in "Menu Title" with "Mega Menu"
    And   I click "Menu Links"
    # I choose one of the "New link" options
    And   I click on the element with xpath "//*[@id='edit-om-maximenus-2-links-1']/legend/span/a"
    Then  I should see "Link Title"
    When  I fill in "edit-om-maximenus-2-links-1-link-title" with "FIRST LINK MEGA MENU"
    And   I fill in "edit-om-maximenus-2-links-1-path" with "http://www.google.es"
    And   I press "Save"

    # I create a block to add in the MEGA MENU in the menu
    When  I go to "/admin/structure/block/add"
    And   I fill in "Block title" with "MEGA MENU ELEMENT 1"
    And   I fill in "Block description" with "block to add to the mega menu element in main menu"
    And   I click "Disable rich-text"
    And   I fill in "Block body" with "<p><a href='https://www.google.es/'>google</a></p><p><a href='https://es.wikipedia.org/'>wikipedia</a></p><p><a href='https://www.drupal.org/'>drupal</a></p>"
    And   I press "Save block"
    And   I should see the text "The block has been created."

    # I add the new block to the MEGA MENU in the menu
    When  I go to "/admin/structure/om-maximenu/"
    And   I click "Edit" in the "Mega Menu" row
    And   I click "Menu Links"
    And   I click "FIRST LINK MEGA MENU"
    And   I click "Edit attached blocks" in the "FIRST LINK MEGA MENU" row
    And   I wait
    Then  I should see the text "BLOCK"
    When  I click on the element with xpath "//*[@id='edit-om-maximenu-content-block']/legend/span/a"
    And   I wait
    Then  I should see "MEGA MENU ELEMENT 1"
    When  I click "MEGA MENU ELEMENT 1"
    And   I check "edit-om-maximenu-content-block-om-blocks-block-1-checked"
    And   I press "Save"
    And   I should see the text "Your settings have been saved."
    And   I press "Save"

    # I add the menu to be visible in the homepage
    When  I go to "/admin/structure/block"
    And   I select "Header Top" from "edit-blocks-om-maximenu-om-maximenu-2-region"
    And   I press "Save blocks"

    # I check that the menu has been created and is visible
    When  I go to the homepage
    Then  I should see the link "FIRST LINK MEGA MENU"
    And   I should not visibly see the link "google"
    And   I should not visibly see the link "wikipedia"
    And   I should not visibly see the link "drupal"

    # I delete the menu
    When  I go to "/admin/structure/om-maximenu/"
    And   I click "Delete" in the "Mega Menu" row
    And   I wait
    Then  I should see the text "Are you sure you want to delete Mega Menu?"
    When  I press "Delete"
    Then  I should see the text "Mega Menu has been deleted"
