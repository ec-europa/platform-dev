@api @javascript
Feature: Geofield feature
  In order to add geojson data in the content
  As an administrator
  I want to be able to add geojson data for maps and so on

  Background:
    Given I am logged in as a user with the 'administrator' role
    And the module is enabled
      | modules             |
      | nexteuropa_geofield |

  Scenario: add field to a content type
    Given I am logged in as a user with the "administrator" role
    When  I go to "/admin/structure/types/manage/article/fields"
    And   I fill in "New field label" with "geofield test"
    When  I select "geofield_geojson" from "edit-fields-add-new-field-type"
    And   I press "Save"
    And   I wait
    Then  I should see the text "FIELD SETTINGS"
    And   I press "Save field settings"
    And   I wait
    Then  I should see the text "Updated field"
    When  I go to "node/add/article"
    Then  I should see the text "geofield test"

  Scenario: manage geojson field
    And   I go to "/admin/structure/types/manage/article/fields/field_geofield_test"
    # I add a default map center
    When  I fill in "Latitude" with "41.65"
    And   I fill in "Longitude" with "0.92"
    # I select the four types of objects
    And   I check "polygon"
    And   I check "rectangle"
    And   I check "marker"
    And   I check "polyline"
    And   I press "Save"
    Then  I should see the text "Saved geofield test configuration"
    When  I go to "node/add/article"
    Then  I should see the text "geofield test"

  Scenario: create content with geofield
    When  I go to "node/add/article"
    Then  I should see the text "geofield test"
    Then  the page should contain the element with following id "geofield_geojson_map" and given attributes:
      | Attribute | Value                                                               |
      | class     | geofield-geojson-map-processed leaflet-container leaflet-fade-anim  |
