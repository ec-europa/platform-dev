Next Europa TMGMT DGT FTT TRANSLATOR
====================================
This module provides custom TMGMT translator for the DGT Fast Track
Translations workflow.

It allows to send, receive and process translations according to the
fast track translations workflow needs.

## 1. Custom entity for the translator mapping
Module provides a custom entity in order to store information about reference
number and other details for a content which was processed by the DGT Services.

## 2. Rules elements
In order to configure translation workflow which is using the Poetry Service,
this module provides custom rules elements. Together with other rules
elements which are provided by the ne_dgt_rules module you can configure
an expected translation workflow.
### 2.1. Custom event - FTT Translation received
Custom event which allows to react on received translations.
