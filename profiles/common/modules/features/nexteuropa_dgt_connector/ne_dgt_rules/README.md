Next Europa DGT Rules
===========================
This module provides rules events, conditions, actions and components
which could be used to build customised translation workflow.

Current functionalities are focused on delivering elements which are 
needed to configure the DGT Fast Track Translations (FFT) workflow.

# 1. Configuration
Before you can start to use features provided by module, first you have
to configure the module. Below you can find information how to do that.
## 1.1. Default TMGMT translator.
To implement the DGT FTT workflow you need to setup default TMGMT
translator which will be used to communicate with the DGT Translation
Service (DGT TS). You can configure default translator at the
configuration page available at 
```admin/config/workflow/rules/ne_dgt_rules```
by picking the expected value from the drop down list.

# 2. Rules elements
In order to configure different workflow for dealing with the DGT
Translation Service, this module provides custom rules elements.
By using them you can configure an expected workflow.
## 2.1. Custom conditions
Module provides custom conditions which have to be used in order to
configure DGT FTT workflow.
### 2.1.1. Content meets requirements of the DGT FTT workflow
Checks if given content (node) meets the basic requirements of the DGT
FTT workflow. It checks if the integration with the DGT FTT workflow is
enabled and if given content type has enabled the entity translation
mechanism.
### 2.1.2. Comparison of moderation states after transition
Compares a moderation states transition. You can configure this condition
by providing expected values for the previous and new state. You have to
also provide the source for those states.

## 2.2. Custom actions
### 2.2.1. Send the review request
Allows to send the review request to the DGT TS.
You need to send review request for the content that should be translated
under the FTT workflow.
To use this action you need to set the source for the 'node' parameter.
Action provides variable 'dgt_service_response' which includes
information received from the DGT TS.
**Please, remember to use custom conditions before triggering this action.**

## 2.3. Custom data types.
### 2.3.1. DGT Translation Service response
Custom data type which provides a wrapper around the DGT TS response.
It allows to use a response properties in further steps of a workflow.
