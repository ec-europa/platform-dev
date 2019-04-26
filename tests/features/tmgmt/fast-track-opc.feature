@api @poetry @wip
Feature: Fast track

  Background:
    Given these modules are enabled
      | modules                     |
      | ne_dgt_rules                |
      | ne_tmgmt_dgt_ftt_translator |
    And the following languages are available:
      | languages |
      | en        |
      | fr        |
      | es        |
    And the following Poetry settings:
    """
      address: http://localhost:28080/wsdl
      method: requestService
    """
    And I request to change the variable "ne_dgt_rules_translator" to "dgt_ftt"

  Scenario: Fast track OPC workflow.
    Given I update the "dgt_ftt" translator settings with the following values:
    """
      settings:
        dgt_counter: '40012'
        dgt_code: WEB
        callback_username: poetry
        callback_password: pass
        dgt_ftt_username: user
        dgt_ftt_password: pass
        dgt_ftt_workflow_code: OPC
      organization:
        responsible: DIGIT
        author: IE/CE/DIGIT
        requester: IE/CE/DIGIT/A/3
      contacts:
        author: john_smith
        secretary: john_smith
        contact: john_smith
        responsible: john_smith
      feedback_contacts:
        email_to: john.smith@example.com
        email_cc: john.smith@example.com
    """
    And Poetry service uses the following settings:
    """
      username: poetry
      password: pass
    """
    And Poetry will return the following "response.status" message response:
    """
    identifier:
      code: WEB
      year: 2017
      number: 40012
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
    And I have the following rule:
    """
    {
      "rules_ne_dgt_opc_send_translation_request" : {
        "LABEL" : "NE DGT OPC | Send translation request",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "draft",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "validated"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_translation_request" : {
              "USING" : {
                "direct_translation" : "1",
                "node" : [ "node" ],
                "delay" : "2017-12-01 15:00:00",
                "target_languages" : { "value" : [] },
                "dgt_ftt_workflow_code" : "OPC"
              },
              "PROVIDE" : {
                "tmgmt_job" : { "tmgmt_job" : "Translation Job" },
                "dgt_service_response" : { "dgt_service_response" : "DGT Service response" },
                "dgt_service_response_status" : { "dgt_service_response_status" : "DGT Service Response - Response status" },
                "dgt_service_demand_status" : { "dgt_service_demand_status" : "DGT Service Response - Demand status" }
              }
            }
          }
        ]
      }
    }
    """
    And I have the following rule:
    """
    {
      "rules_dgt_ftt_translation_received" : {
        "LABEL" : "DGT FTT Translation received",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "ne_tmgmt_dgt_ftt_translator" ],
        "ON" : { "ftt_translation_received" : [] },
        "IF" : [
          { "received_translation_belongs_to_specified_workflow" : { "dgt_ftt_workflow_code" : "OPC", "job" : [ "job" ] } },
          { "all_translations_are_received" : {
              "identifier" : [ "identifier" ],
              "excluded_langs" : { "value" : { "es" : "es" } }
            }
          }
        ],
        "DO" : [
          { "accept_all_translations" : {
              "USING" : { "identifier" : [ "identifier" ] },
              "PROVIDE" : { "entity_id" : { "entity_id" : "Translated content ID." } }
            }
          }
        ]
      }
    }
    """
    And "page" content:
      | language | title     |
      | en       | Test page |
    And I am logged in as a user with the "administrator" role
    And I visit the "page" content with title "Test page"
    Then I should see "Revision state: Draft"
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see "Revision state: Validated"
    And Poetry service received request should contain the following text:
      | <titre>Test page</titre>                                      |
      | <organisationResponsable>DIGIT</organisationResponsable>      |
      | <organisationAuteur>IE/CE/DIGIT</organisationAuteur>          |
      | <serviceDemandeur>IE/CE/DIGIT/A/3</serviceDemandeur>          |
      | <applicationReference>FPFIS</applicationReference>            |
      | <workflowCode>OPC</workflowCode>                              |
      | <delai>01/12/2017</delai>                                     |
      | <attributionsDelai>01/12/2017</attributionsDelai>             |
    When Poetry notifies the client with the following XML:
    """
    <POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="">
      <request communication="synchrone" id="3558615" type="translation">
        <demandeId>
           <codeDemandeur>WEB</codeDemandeur>
           <annee>2017</annee>
           <numero>40012</numero>
           <version>0</version>
           <partie>0</partie>
           <produit>TRA</produit>
        </demandeId>
        <attributions format="HTML" lgCode="FR">
           <attributionsFile>PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4KPCFET0NUWVBFIGh0bWwgUFVCTElDICItLy9XM0MvL0RURCBYSFRNTCAxLjAgU3RyaWN0Ly9FTiIgImh0dHA6Ly93d3cudzMub3JnL1RSL3hodG1sMS9EVEQveGh0bWwxLXN0cmljdC5kdGQiPgo8aHRtbCB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94aHRtbCI+CiAgPGhlYWQ+CiAgICA8bWV0YSBodHRwLWVxdWl2PSJDb250ZW50LVR5cGUiIGNvbnRlbnQ9InRleHQvaHRtbDsgY2hhcnNldD1VVEYtOCIgLz4KICAgIDxtZXRhIG5hbWU9IkpvYklEIiBjb250ZW50PSIxIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VTb3VyY2UiIGNvbnRlbnQ9ImVuIiAvPgogICAgPG1ldGEgbmFtZT0ibGFuZ3VhZ2VUYXJnZXQiIGNvbnRlbnQ9ImZyIiAvPgogICAgPHRpdGxlPkpvYiBJRCAxPC90aXRsZT4KICA8L2hlYWQ+CiAgPGJvZHk+CiAgICAgICAgICA8ZGl2IGNsYXNzPSJhc3NldCIgaWQ9Iml0ZW0tMSI+CiAgICAgICAgICAgICAgICAgICAgICAgICAgPCEtLQogICAgICAgICAgbGFiZWw9IlRpdGxlIgogICAgICAgICAgY29udGV4dD0iWzFdW3RpdGxlX2ZpZWxkXVswXVt2YWx1ZV0iCiAgICAgICAgLS0+CiAgICAgICAgPGRpdiBjbGFzcz0iYXRvbSIgaWQ9ImJNVjFiZEdsMGJHVmZabWxsYkdSZFd6QmRXM1poYkhWbCI+VGVzdCBwYWdlIEZSPC9kaXY+CiAgICAgICAgICAgICAgPC9kaXY+CiAgICAgIDwvYm9keT4KPC9odG1sPgo=</attributionsFile>
        </attributions>
     </request>
   </POETRY>
    """
    And I go to "admin/tmgmt"
    Then I should see "Finished" in the "Spanish" row
