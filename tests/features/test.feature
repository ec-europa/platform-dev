@api
Feature: xxxx
  xxxx
  xxxx
  xxxx

  
  Scenario: Check for PHP warning
    Given these featureSet are enabled
      |featureSet   |
      |News| 
      And I am logged in as an administrator
	  When I am viewing a news with the title "News: Hello world"
      Then I should see "News: Hello world" 
      
