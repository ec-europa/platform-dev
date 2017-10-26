@api @poetry_mock @i18n @poetry
Feature: TMGMT Poetry features
  In order to request Carts translations with Poetry service.
  As an Administrator
  I want to be able to create/manage translation requests.

  Background:
    Given the module is enabled
      | modules             |
      | tmgmt_poetry_mock   |
      | tmgmt_dgt_connector |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | en        |
      | es        |
      | fr        |
    And I am logged in as a user with the "administrator" role

  @javascript
  Scenario: I can translate contents with Carts1.
    When Poetry service uses the following settings:
    """
      username: MockCallback
      password: MockCallbackPWD
    """
    And Poetry will return the following "response.status" message response:
    """
    identifier:
      code: WEB
      year: 2017
      number: 1234
      version: 0
      part: 0
      product: TRA
    status:
      -
        type: request
        code: '0'
        date: 06/10/2017
        time: 02:41:53
        message: OK
    """
    # Important: remove poetry_service overrides from your settings.php as it would override the following step.
    And the following Poetry settings:
    """
        address: http://localhost:28080/wsdl
        method: requestService
    """
    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body | status |
      | en       | My page 1 | Short body    | 1      |
    And I click "Translate" in the "primary_tabs" region
    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There is 1 item in the translation cart."
    When I am viewing a multilingual "page" content:
      | language | title     | field_ne_body | status |
      | en       | My page 2 | Short body 2  | 1      |
    And I click "Translate" in the "primary_tabs" region
    Then I should see "There is 1 item in the translation cart."
    When I press "Add to cart"
    Then I should see the success message "1 content source was added into the cart."
    And I should see "There are 2 items in the translation cart."
    When I click "cart" in the "front_messages" region
    # Cart page
    And I check the box on the "My page 1" row
    And I check the box on the "My page 2" row
    And I select "French" from "Request translation into language/s" with javascript
    And I select "Spanish" from "Request translation into language/s" with javascript
    And I press "Request translation"
    # Checkout page
    And I click "Change translator"
    And I select "tmgmt_dgt_connector" from "Translator"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I store job ID of translation request page
    And I press "Submit to translator"
    Then I should see the message "Job was successfully sent for translation."
    When I visit the "page" content with title "My page 1"
    And I click "Translate" in the "primary_tabs" region
    Then I should see the message "Please wait for the translation request to be accepted before further update options."
    And Poetry notifies the client with the following XML:
    """
    <?xml version="1.0" encoding="UTF-8"?>
    <POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="">
       <request communication="synchrone" id="1071819" type="status">
          <demandeId>
             <codeDemandeur>WEB</codeDemandeur>
             <annee>2017</annee>
             <numero>1234</numero>
             <version>0</version>
             <partie>0</partie>
             <produit>TRA</produit>
          </demandeId>
          <status code="0" type="request">
             <statusDate>19/10/2017</statusDate>
             <statusTime>10:44:01</statusTime>
             <statusMessage>OK</statusMessage>
          </status>
          <status code="ONG" type="demande">
             <statusDate>19/10/2017</statusDate>
             <statusTime>10:42:44</statusTime>
             <statusMessage>REQUEST ACCEPTED</statusMessage>
          </status>
          <status code="ONG" lgCode="ES" type="attribution">
             <statusDate>19/10/2017</statusDate>
             <statusTime>00:00:00</statusTime>
          </status>
          <status code="ONG" lgCode="FR" type="attribution">
             <statusDate>19/10/2017</statusDate>
             <statusTime>00:00:00</statusTime>
          </status>
          <attributions format="HTML" lgCode="ES">
             <attributionsDelai>31/10/2017 23:59</attributionsDelai>
             <attributionsDelaiAccepted>31/10/2017 23:59</attributionsDelaiAccepted>
          </attributions>
          <attributions format="HTML" lgCode="FR">
             <attributionsDelai>31/10/2017 23:59</attributionsDelai>
             <attributionsDelaiAccepted>31/10/2017 23:59</attributionsDelaiAccepted>
          </attributions>
       </request>
    </POETRY>
    """
    And I reload the page
    Then I should not see the message "Please wait for the translation request to be accepted before further update options."
    When Poetry notifies the client with the following XML:
    """
    <?xml version="1.0" encoding="UTF-8"?>
    <POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="">
       <request communication="synchrone" id="3558615" type="translation">
          <demandeId>
             <codeDemandeur>WEB</codeDemandeur>
             <annee>2017</annee>
             <numero>1234</numero>
             <version>0</version>
             <partie>0</partie>
             <produit>TRA</produit>
          </demandeId>
          <attributions format="HTML" lgCode="FR">
             <attributionsFile>PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4NCjwhRE9DVFlQRSBodG1sIFBVQkxJQyAiLS8vVzNDLy9EVEQgWEhUTUwgMS4wIFN0cmljdC8vRU4iICJodHRwOi8vd3d3LnczLm9yZy9UUi94aHRtbDEvRFREL3hodG1sMS1zdHJpY3QuZHRkIj4NCjxodG1sIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hodG1sIj4NCiAgPGhlYWQ+DQogICAgPG1ldGEgaHR0cC1lcXVpdj0iQ29udGVudC1UeXBlIiBjb250ZW50PSJ0ZXh0L2h0bWw7IGNoYXJzZXQ9VVRGLTgiIC8+DQogICAgPG1ldGEgbmFtZT0iSm9iSUQiIGNvbnRlbnQ9IjI1IiAvPg0KICAgIDxtZXRhIG5hbWU9Imxhbmd1YWdlU291cmNlIiBjb250ZW50PSJlbiIgLz4NCiAgICA8bWV0YSBuYW1lPSJsYW5ndWFnZVRhcmdldCIgY29udGVudD0iZnIiIC8+DQogICAgPHRpdGxlPkpvYiBJRCAyNTwvdGl0bGU+DQogIDwvaGVhZD4NCiAgPGJvZHk+DQogICAgICAgICAgPGRpdiBjbGFzcz0iYXNzZXQiIGlkPSJpdGVtLTUzIj4NCiAgICAgICAgICAgICAgICAgICAgICAgICAgPCEtLQ0KICAgICAgICAgIGxhYmVsPSJUaXRsZSINCiAgICAgICAgICBjb250ZXh0PSJbNTNdW3RpdGxlX2ZpZWxkXVswXVt2YWx1ZV0iDQogICAgICAgIC0tPg0KICAgICAgICA8ZGl2IGNsYXNzPSJhdG9tIiBpZD0iYk5UTmRXM1JwZEd4bFgyWnBaV3hrWFZzd1hWdDJZV3gxWlEiPlRlc3RlIDEwMjYgNSBUUiBGUjwvZGl2Pg0KICAgICAgICAgICAgICAgICAgICAgICAgICA8IS0tDQogICAgICAgICAgbGFiZWw9IkJvZHkiDQogICAgICAgICAgY29udGV4dD0iWzUzXVtmaWVsZF9uZV9ib2R5XVswXVt2YWx1ZV0iDQogICAgICAgIC0tPg0KICAgICAgICA8ZGl2IGNsYXNzPSJhdG9tIiBpZD0iYk5UTmRXMlpwWld4a1gyNWxYMkp2WkhsZFd6QmRXM1poYkhWbCI+PHA+VGVzdGUgMTAyNiA1IFRSIEZSLjwvcD4NCjwvZGl2Pg0KICAgICAgICAgICAgICA8L2Rpdj4NCiAgICAgICAgICA8ZGl2IGNsYXNzPSJhc3NldCIgaWQ9Iml0ZW0tNTQiPg0KICAgICAgICAgICAgICAgICAgICAgICAgICA8IS0tDQogICAgICAgICAgbGFiZWw9IlRpdGxlIg0KICAgICAgICAgIGNvbnRleHQ9Ils1NF1bdGl0bGVfZmllbGRdWzBdW3ZhbHVlXSINCiAgICAgICAgLS0+DQogICAgICAgIDxkaXYgY2xhc3M9ImF0b20iIGlkPSJiTlRSZFczUnBkR3hsWDJacFpXeGtYVnN3WFZ0MllXeDFaUSI+VGVzdGUgMTAyNiA2IFRSIEZSPC9kaXY+DQogICAgICAgICAgICAgICAgICAgICAgICAgIDwhLS0NCiAgICAgICAgICBsYWJlbD0iQm9keSINCiAgICAgICAgICBjb250ZXh0PSJbNTRdW2ZpZWxkX25lX2JvZHldWzBdW3ZhbHVlXSINCiAgICAgICAgLS0+DQogICAgICAgIDxkaXYgY2xhc3M9ImF0b20iIGlkPSJiTlRSZFcyWnBaV3hrWDI1bFgySnZaSGxkV3pCZFczWmhiSFZsIj48cD5UZXN0ZSAxMDI2IDYgVFIgRlIuPC9wPg0KPC9kaXY+DQogICAgICAgICAgICAgIDwvZGl2Pg0KICAgICAgPC9ib2R5Pg0KPC9odG1sPg0K</attributionsFile>
          </attributions>
       </request>
    </POETRY>
    """
