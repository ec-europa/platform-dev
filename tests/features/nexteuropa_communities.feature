@api 
Feature: Communities
  In order to effectively manage groups of people
  As a site administrator
  I want to be able to add, edit and delete communities

  
  Background:
	Given these modules are enabled
		| modules            	  |
		| nexteuropa_communities |
		| nexteuropa_news |
		
  Scenario: As an anonymous user, I cannot see content of private community
    Given I am not logged in
    When I am viewing a "community" content:
      | title                 | A private community    |
	  | Group visibility          |  Private - accessible only to group members   |
     Then I should see the heading "A private community"
	  When I am viewing a "nexteuropa_news" content:
      | title                 | A News in a private community   |
      | og_group_ref          | A private community                   |
      | field_ne_body         | Lorem ipsum dolor sit amet body.     |
      | field_farnet_abstract | Lorem ipsum dolor sit amet abstract. |
      | workbench_moderation_state     | published                   |
      | workbench_moderation_state_new | published                   |
    Then I should get an access denied error
    
  Scenario: As an anonymous user, I can see content of public community
    Given I am not logged in
    When I am viewing a "community" content:
      | title                 | A public community    |
	  | Group visibility          |  Public - accessible to all site users    |
     Then I should see the heading "A private community"
	  When I am viewing a "nexteuropa_news" content:
      | title                 | A News in a public community   |
      | og_group_ref          | A public community                   |
      | field_ne_body         | Lorem ipsum dolor sit amet body.     |
      | field_farnet_abstract | Lorem ipsum dolor sit amet abstract. |
      | workbench_moderation_state     | published                   |
      | workbench_moderation_state_new | published                   |
    Then I should see the heading "A News in a public community"