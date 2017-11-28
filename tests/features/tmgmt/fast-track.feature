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
    And I update the "dgt_ftt" translator settings with the following values:
    """
      settings:
        dgt_counter: '40012'
        dgt_code: WEB
        callback_username: poetry
        callback_password: pass
        dgt_ftt_username: user
        dgt_ftt_password: pass
        dgt_ftt_workflow_code: STS
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
    And I request to change the variable "ne_dgt_rules_translator" to "dgt_ftt"
    And Poetry will return the following "response.status" message response:
    """
    identifier:
      code: WEB
      year: 2017
      number: 40029
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

  Scenario: Fast track workflow.
    Given I have the following rule:
    """
    {
      "rules_dgt_ftt_translations" : {
        "LABEL" : "DGT FTT Translations",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "needs_review",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "validated"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_translation_request" : {
              "USING" : { "node" : [ "node" ] },
              "PROVIDE" : {
                "tmgmt_job" : { "tmgmt_job" : "Translation Job" },
                "dgt_service_response" : { "dgt_service_response" : "DGT Service response" },
                "dgt_service_response_status" : { "dgt_service_response_status" : "DGT Service Response - Response status" },
                "dgt_service_demand_status" : { "dgt_service_demand_status" : "DGT Service Response - Demand status" }
              }
            }
          },
          { "drupal_message" : { "message" : [ "dgt-service-response-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-demand-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-response:raw-xml" ] } }
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
    When I select "Needs Review" from "state"
    And I press "Apply"
    Then I should see "Revision state: Needs Review"
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see "Revision state: Validated"
    And Poetry service received request should contain the following text:
      | <titre>Test page</titre>                                      |
      | <organisationResponsable>DIGIT</organisationResponsable> |
      | <organisationAuteur>IE/CE/DIGIT</organisationAuteur>           |
      | <serviceDemandeur>IE/CE/DIGIT/A/3</serviceDemandeur>          |
      | <applicationReference>FPFIS</applicationReference>            |

  Scenario: Optional action parameters.
    Given I have the following rule:
    """
    {
      "rules_dgt_ftt_review" : {
        "LABEL" : "DGT FTT Review",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "draft",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "needs_review"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_review_request" : {
              "USING" : { "node" : [ "node" ] ,
                "code" : "WEBREVIEW",
                "org_responsible" : "DIGIT_REVIEW",
                "org_dg_author" : "IE/CE/DIGIT/REVIEW",
                "org_requester" : "IE/CE/DIGIT/A/3/REVIEW",
                "dgt_ftt_workflow_code" : "STS_REVIEW"
              },
              "PROVIDE" : {
                "tmgmt_job" : { "tmgmt_job" : "Translation Job" },
                "dgt_service_response" : { "dgt_service_response" : "DGT Service response" },
                "dgt_service_response_status" : { "dgt_service_response_status" : "DGT Service Response - Response status" },
                "dgt_service_demand_status" : { "dgt_service_demand_status" : "DGT Service Response - Demand status" }
              }
            }
          },
          { "drupal_message" : { "message" : [ "dgt-service-response-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-demand-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-response:raw-xml" ] } }
        ]
      }
    }
    """
    And I have the following rule:
    """
    {
      "rules_dgt_ftt_translations" : {
        "LABEL" : "DGT FTT Translations",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "needs_review",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "validated"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_translation_request" : {
              "USING" : { "node" : [ "node" ],
                "code" : "WEBTRANSLATION",
                "org_responsible" : "DIGIT_TRANSLATION",
                "org_dg_author" : "IE/CE/DIGIT/TRANSLATION",
                "org_requester" : "IE/CE/DIGIT/A/3/TRANSLATION",
                "dgt_ftt_workflow_code" : "STS_TRANSLATION"
              },
              "PROVIDE" : {
                "tmgmt_job" : { "tmgmt_job" : "Translation Job" },
                "dgt_service_response" : { "dgt_service_response" : "DGT Service response" },
                "dgt_service_response_status" : { "dgt_service_response_status" : "DGT Service Response - Response status" },
                "dgt_service_demand_status" : { "dgt_service_demand_status" : "DGT Service Response - Demand status" }
              }
            }
          },
          { "drupal_message" : { "message" : [ "dgt-service-response-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-demand-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-response:raw-xml" ] } }
        ]
      }
    }
    """
    And "page" content:
      | language | title     |
      | en       | Test page |
    And I am logged in as a user with the "administrator" role
    When I visit the "page" content with title "Test page"
    Then I should see "Revision state: Draft"
    When I select "Needs Review" from "state"
    And I press "Apply"
    Then I should see "Revision state: Needs Review"
    And Poetry service received request should contain the following text:
      | <codeDemandeur>WEBREVIEW</codeDemandeur>                        |
      | <organisationResponsable>DIGIT_REVIEW</organisationResponsable> |
      | <organisationAuteur>IE/CE/DIGIT/REVIEW</organisationAuteur>     |
      | <serviceDemandeur>IE/CE/DIGIT/A/3/REVIEW</serviceDemandeur>     |
      | <workflowCode>STS_REVIEW</workflowCode>                         |
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see "Revision state: Validated"
    And Poetry service received request should contain the following text:
      | <codeDemandeur>WEBTRANSLATION</codeDemandeur>                        |
      | <organisationResponsable>DIGIT_TRANSLATION</organisationResponsable> |
      | <organisationAuteur>IE/CE/DIGIT/TRANSLATION</organisationAuteur>     |
      | <serviceDemandeur>IE/CE/DIGIT/A/3/TRANSLATION</serviceDemandeur>     |
      | <workflowCode>STS_TRANSLATION</workflowCode>                         |
