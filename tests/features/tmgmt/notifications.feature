@poetry
Feature: Server notifications

  Scenario: Poetry server can notify the client using raw XML.

    When Poetry notifies the client with the following XML:
    """
    <?xml version="1.0" encoding="UTF-8"?>
    <POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd">
      <request communication="synchrone" id="7685067" type="translation">
        <demandeId>
          <codeDemandeur>WEB</codeDemandeur>
          <annee>2017</annee>
          <numero>40012</numero>
          <version>0</version>
          <partie>39</partie>
          <produit>TRA</produit>
        </demandeId>
        <attributions format="HTML" lgCode="FR">
          <attributionsFile>File64</attributionsFile>
        </attributions>
      </request>
    </POETRY>
    """
