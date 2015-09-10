@webtools 
Feature: Webtools
  In order to embed a webtool widget into my site
  As an administrator
  I can enter my configuration in a text area using a webtools block type.

  @api
  Scenario: Administrator can create a Webtools block
    Given I am logged in as a user with the "administrator" role
    When I go to "block/add/webtools"
    Then the response status code should be 200
    And I should see the text "Create webtools block"
    And I should see the text "Label"
    And I should see the text "Title"
    And I should see the text "JSON Object"
	  When I fill in "Label" with "webtools_test_charts"
	  And I fill in "Title" with "Webtools Test Charts"
	  And I fill in "JSON Object" with "{\"service\":\"charts\",\"data\":{\"type\": \"column3d\",\"dataFormat\": \"json\",\"dataSource\": {\"data\": [{\"label\": \"foo\",\"value\": \"420000\"},{\"label\": \"bar\",\"value\": \"810000\"},{\"label\": \"baz\",\"value\": \"720000\"}]}}}"
	  And I press "Save"
	  Then I should see the success message "webtools Webtools Test Charts has been created."
	  And the response should contain "load.js"
	  And the response should contain "fusioncharts.js"
	  And the response should contain "<div class=\"wtWidgets wtEnd charts\">"

  @api @webtools_create_default_block
  Scenario Outline: User can see the rendered object of a webtools block
  	Given I am logged in as a user with the "<role>" role
    When I go to "block/webtools_test_protocol" using the "<protocol>" protocol
    Then the response status code should be 200
    And the response should contain "load.js"
	  And the response should contain "fusioncharts.js"
	  And the response should contain "<div class=\"wtWidgets wtEnd charts\">"
  Examples:
    | role               |protocol|
    | anonymous user     | http|
	  | anonymous user     | https|
    | authenticated user | http|
  	| authenticated user | https|

  @api
  Scenario Outline: Administrator cannot insert javascript on webtools block
	Given I am logged in as a user with the "administrator" role
	When I go to "block/add/webtools"
	And I fill in "Label" with "webtools_test_js_injection"
	And I fill in "Title" with "Webtools Test JS injection"
	And I fill in "JSON Object" with "<html>"
	And I press "Save"
	Then I should see the success message "webtools Webtools Test JS injection has been created."
	And the response should not contain "<expected>"
	
	Examples:
    | html                                                                | expected                      |
    | <script>alert('xss')</script>                                       | <script>alert('xss')</script> |
    | <a href=\"javascript:alert('xss')\">xss</a>                         | javascript:alert              |
    | <p style=\"background-image: url(javascript:alert('xss'))\">xss</p> | javascript:alert              |
    | <div class=\"2classname\">Applied invalid css class</div>           | classname                     |
    | <div class=\"classname?&*\">Applied invalid css class</div>         | classname                     |
    | <div id=\"2invalidid\">A container with an invalid HTML ID</div>    | invalidid                     |
    | <div id=\"invalidid.\">A container with an invalid HTML ID</div>    | invalidid                     |
