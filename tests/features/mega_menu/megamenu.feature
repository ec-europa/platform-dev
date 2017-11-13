@api @javascript
Feature: megamenu
  In order to use megamenu feature
  As different types of users
  I want to be able to create and view mega menus

  Background:
    Given I use device with "1080" px and "1920" px resolution
    And the module is enabled
      | modules            |
      | multisite_megamenu |
      | om_maximenu        |

  Scenario: As an administrator I can create a mega menu
    Given I am logged in as a user with the "administrator" role
    When  I go to "/admin/structure/om-maximenu/"
    And   I click "Edit" in the "Main Menu" row
    # Add new element to main menu to add to it mega menu elements
    # And   I click "MENU LINKS"
    And   I click "Menu Links"
    And   I break
    And   print last response
    And   I click on the element with xpath "//*[@id='edit-om-maximenus-1-links-750']/legend/span/a"
    # And   I click "New Link"
    And   inside fieldset "edit-om-maximenus-1-links-750" I fill in "Link Title" with "MEGA MENU"
    And   inside fieldset "edit-om-maximenus-1-links-750" I fill in "Path" with ""
    # And   I fill in "Link Title" with "MEGA MENU"
    # And   I fill in "Path" with ""
    And   I click "Save"
    # I create a block to add in the MEGA MENU in the menu
    And   I go to "/admin/structure/block/add"
    And   I fill in "Block title" with "Mega Menu element 1"
    And   I fill in "Block description" with "block to add to the mega menu element in main menu"
    And   I click "Disable rich-text"
    And   I fill in "Block body" with "<p><a href='https://www.google.es/'>google</a></p><p><a href='https://es.wikipedia.org/'>wikipedia</a></p><p><a href='https://www.drupal.org/'>drupal</a></p>"
    And   I press "Save block"
    And   I should see the success message "The block has been created."
    # I add the new block to the MEGA MENU in the menu
    When  I go to "/admin/structure/om-maximenu/"
    And   I click "Edit" in the "Main Menu" row
    And   I click "Menu Links"
    And   I click "Edit attached blocks" in the "MEGA MENU" row
    And   I wait
    And   I click "edit-om-maximenu-content-block"
    # Given I check the box on the :row_text row
    And   I check the box on the "Mega menu element 1" row
    # And   I check "edit-om-maximenu-content-block-om-blocks-block-1-checked" in the "Mega menu element 1"
    And   I press "Save"
    Then  I should see the success message "Your settings have been saved."









