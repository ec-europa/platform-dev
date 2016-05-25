@api
Feature: Creating maps
  In order to inform the general public about country related policies
  As an administrator
  I can create maps via the UI

  Scenario: As a user with the administrator role I can see the map form
    Given I am logged in as a user with the 'administrator' role
    And I am on "/admin/structure/maps"
    Then I should see the heading "Maps"
    And I should see "Add map"
    When I follow "Add map"
    Then I should see the heading "Add map"
    And I should see "Name" in the "page" region
    And I should see "Description" in the "page" region
    And I should see "Layers" in the "page" region
    And I should see "Map height" in the "page" region
    And I should see "Map center" in the "page" region
    And I should see "Latitude" in the "page" region
    And I should see "Longitude" in the "page" region
    And I should see "Zooming" in the "page" region
    And I should see "Initial zoom level" in the "page" region
    And I should see "Minimum zoom level" in the "page" region
    And I should see "Maximum zoom level" in the "page" region
    And I should see "Attribution" in the "page" region
    And I should see "Show attribution" in the "page" region
    And I should see "Attribution text" in the "page" region
    And I should see "Map background" in the "page" region
    And I should see "Tiles" in the "page" region
    And I should see "Show settings" in the "page" region
    When I check the box "Show settings"
    Then I should see "Settings" in the "page" region

  Scenario: As a user with the administrator role I can see the map form with URL layer
    Given I am logged in as a user with the 'administrator' role
    And I am on "/admin/structure/maps/add"
    Then I should see the heading "Add map"
    When I select "URL layer" from "edit-map-layers-und-actions-bundle"
    When I press "Add new entity"
    Then I should see "Label" in the "page" region
    And I should see "URL" in the "page" region
    And I should see the button "Add another item"
    And I should see "Layer control" in the "page" region
    And I should see "Enable the layer by default in the map" in the "page" region
    And I should see "Show the layer in the layer control" in the "page" region
    And I should see "Icon" in the "page" region
    And I should see "Pop-up" in the "page" region
    And I should see "Show a popup when markers are clicked." in the "page" region
    And I should see "Use pop-in (show details in right side bar)" in the "page" region
    And I should see "Cluster markers" in the "page" region
    And I should see the button "Create entity"
    And I should see the button "Cancel"

  Scenario: As a user with the administrator role I can create a map with a URL layer
    Given I am logged in as a user with the "administrator" role
    When I follow "Structure"
    And I follow "Maps"
    And I follow "Add map"
    Then I should see the heading "Add map"
    And I fill in "Name" with "My URL map"
    And I fill in "Description" with "Tack Plate Fleet pirate run a shot across the bow crack Jennys tea cup hulk jolly boat boom poop deck sutler. List barkadeer mizzenmast carouser me pink take a caulk interloper belaying pin yard. Code of conduct provost hornswaggle furl strike colors run a shot across the bow rope's end lookout handsomely sutler."
    When I select "URL layer" from "edit-map-layers-und-actions-bundle"
    And I press "Add new entity"
    Then I should see "Label" in the "page" region
    And I fill in "Label" with "My URL map layer"
    And I fill in "URL" with "http://europa.eu/webtools/test/data/kml_demo.kml?toto=tutu"
    And I select "Orange" from "Icon"
    And I press "Create entity"
    And I fill in "Map height" with "600"
    And I fill in "Latitude" with "33.33"
    And I fill in "Longitude" with "66.66"
    And I fill in "Initial zoom level" with "4"
    And I fill in "Minimum zoom level" with "1"
    And I fill in "Maximum zoom level" with "3"
    And I select "Satellite images of earth" from "Tiles"
    And I press "Save map"
    Then I should see "Map My URL map saved."
    And I should see "\"height\":\"600\""
    And I should see "\"tiles\":\"bmarble\""
    And I should see "\"minZoom\":\"1\""
    And I should see "Tack PLate Fleet pirate"
    And I should see "My URL map layer"
    And I should see "Map data by Eurostat and the European Commission"

  Scenario: As a user with the administrator role I can see the map form with Country layer
    Given I am logged in as a user with the 'administrator' role
    When I follow "Structure"
    And I follow "Maps"
    And I follow "Add map"
    Then I should see the heading "Add map"
    When I select "Country layer" from "edit-map-layers-und-actions-bundle"
    When I press "Add new entity"
    Then I should see "Label" in the "page" region
    And I should see "Countries data" in the "page" region
    And I should see "Country list" in the "page" region
    And I should see "Nuts level" in the "page" region
    And I should see "Layer control" in the "page" region
    And I should see "Enable the layer by default in the map" in the "page" region
    And I should see "Show the layer in the layer control" in the "page" region
    And I should see "Show country label" in the "page" region
    And I should see "Fill color" in the "page" region
    And I should see "Fill opacity" in the "page" region
    And I should see "Border weight" in the "page" region
    And I should see "Border color" in the "page" region
    And I should see "Border opacity" in the "page" region
    And I should see "Dash array" in the "page" region
    And I should not see "Pop-up" in the "page" region
    And I should not see "Show a popup when markers are clicked." in the "page" region
    And I should not see "Use pop-in (show details in right side bar)" in the "page" region
    And I should not see "Cluster markers" in the "page" region
    And I should see the button "Create entity"
    And I should see the button "Cancel"

  Scenario: As a user with the administrator role I can create a map with a Country layer
    Given I am logged in as a user with the "administrator" role
    When I follow "Structure"
    And I follow "Maps"
    And I follow "Add map"
    Then I should see the heading "Add map"
    And I fill in "Name" with "My country map"
    And I fill in "Description" with "Tack Plate Fleet pirate run a shot across the bow crack Jennys tea cup hulk jolly boat boom poop deck sutler. List barkadeer mizzenmast carouser me pink take a caulk interloper belaying pin yard. Code of conduct provost hornswaggle furl strike colors run a shot across the bow rope's end lookout handsomely sutler."
    When I select "Country layer" from "edit-map-layers-und-actions-bundle"
    And I press "Add new entity"
    Then I should see "Label" in the "page" region
    And I should see "Countries data" in the "page" region
    And I should see "Country list" in the "page" region
    And I fill in "Label" with "My country map layer"
    And I fill in "Countries data" with "DK,Danmark,http://example.com,\"Buccaneer run a shot across bow coxswain for hearties\",2,LightPink"
    And I fill in "Country list" with "US CA FI SE SK RU CZ"
    And I fill in "Nuts level" with "2"
    And I fill in "Fill opacity" with "0.8"
    And I fill in "Border weight" with "2"
    And I fill in "Border opacity" with "0.7"
    And I fill in "Dash array" with "3"
    And I select "Satellite images of earth" from "Tiles"
    And I press "Create entity"
    Then I should see "My country map layer" in the "page" region
    And I fill in "Map height" with "500"
    And I fill in "Latitude" with "33.33"
    And I fill in "Longitude" with "66.66"
    And I fill in "Initial zoom level" with "4"
    And I fill in "Minimum zoom level" with "2"
    And I fill in "Maximum zoom level" with "3"
    And I select "City names Europe" from "Tiles"
    And I press "Save map"
    Then I should see "Map My country map saved."
    And I should see "\"height\":\"500\""
    And I should see "\"tiles\":\"citynames_europe\""
    And I should see "\"minZoom\":\"2\""
    And I should see "Tack PLate Fleet pirate"
    And I should see "My country map layer"