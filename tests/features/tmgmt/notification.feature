@poetry
Feature: Server notifications

  Background:
    Given these modules are enabled
    | modules                     |
    | ne_tmgmt_dgt_ftt_translator |
  @wip
  Scenario: Poetry server can notify the client using raw XML.
    When Poetry notifies the client with the following XML:
    """
    <?xml version="1.0" encoding="UTF-8"?>
    <POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd">
      <request communication="synchrone" id="1069698" type="status">
        <demandeId>
          <codeDemandeur>WEB</codeDemandeur>
          <annee>2017</annee>
          <numero>40029</numero>
          <version>0</version>
          <partie>0</partie>
          <produit>TRA</produit>
        </demandeId>
        <status code="0" type="request">
          <statusDate>29/09/2017</statusDate>
          <statusTime>15:44:02</statusTime>
          <statusMessage>OK</statusMessage>
        </status>
        <status code="ONG" type="demande">
          <statusDate>29/09/2017</statusDate>
          <statusTime>15:42:34</statusTime>
          <statusMessage>REQUEST ACCEPTED</statusMessage>
        </status>
        <status code="ONG" lgCode="FR" type="attribution">
          <statusDate>29/09/2017</statusDate>
          <statusTime>00:00:00</statusTime>
        </status>
        <attributions format="HTML" lgCode="FR">
          <attributionsDelai>04/10/2017 23:59</attributionsDelai>
          <attributionsDelaiAccepted>04/10/2017 23:59</attributionsDelaiAccepted>
        </attributions>
      </request>
    </POETRY>
    """