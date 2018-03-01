@api @poetry
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
    And Poetry will return the following "response.status" message response:
    """
    identifier:
      code: WEB
      year: 2017
      number: 40012
      version: 0
      part: 0
      product: REV
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
    { "rules_ne_dgt_opc_send_translation_request" : {
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
                "target_languages" : { "value" : [] }
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
    And the following entity mapping entry has been created:
      | entity_id     | 2                                  |
      | entity_type   | node                               |
      | client_action | request.create_translation_request |
      | code          | WEB                                |
      | year          | 2017                               |
      | number        | 40012                              |
      | part          | 0                                  |
      | version       | 0                                  |
