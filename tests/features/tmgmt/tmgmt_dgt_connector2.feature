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
