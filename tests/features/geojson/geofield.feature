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
      | field_ui            |

  Scenario: add field to a content type
    When  I go to "/admin/structure/types/manage/article/fields"
    And   I fill in "New field label" with "geofield test"
    When  I select "geofield_geojson" from "edit-fields-add-new-field-type"
    And   I press "Save"
    And   I press "Save field settings"
    When  I fill in "Latitude" with "41.65"
    And   I fill in "Longitude" with "0.92"
    And   I check "polygon"
    And   I check "rectangle"
    And   I check "marker"
    And   I check "polyline"
    And   I press "Save"
    Then  I should see the text "Saved geofield test configuration"
    When  I go to "node/add/article"
    Then  I should see the text "geofield test"
    Then  the page should contain the element with following id "geofield_geojson_map" and given attributes:
      | Attribute | Value                                                               |
      | class     | geofield-geojson-map-processed leaflet-container leaflet-fade-anim  |
