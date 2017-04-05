The TMGMT DGT connector module allows tailoring the [TMGMT module](https://www.drupal.org/project/tmgmt) 
for the creation of translation managers, that make use of the European Commission DGT connector services
(translations served by DGT).

In a first phase, it will run in parallel of the TMGMT poetry module and will focus on "small jobs" (content translations of 
less than 300 characters).<br />
For more information, please consult the [roadmap](#development-roadmap).


Table of content:
=================
- [Development roadmap](#development-roadmap)
- [Installation](#a-installation)
- [Configuration](#configuration)

# Development roadmap

2 milestones are foreseen during the module development.

## Milestone 1: Small jobs (Target end of June)

To reach this milestone, the following development tasks will be executed:

1. Adapting the TMGMT's "Add to card" feature for allowing users selecting elements to translate and
 for each of them, attaching an URL that will be communicated to DGT as reference for helping the content translators 
 (NEPT-869).
2. Tailoring the TMGMT's "Add to card" checkout page to business requirements like the possibility to edit the URL
 for a card's element (NEPT-870, NEPT-871, NEPT-872 and NEPT-873).
3. Creating the TMGMT translator that will allow submitting small jobs to DGT European Commission DGT connector services 
(NEPT-874, NEPT-876).<br />
This translator will consume services supplied by a dedicated PHP component for communicating with the 
Poetry European Service (coming soon, see NEPT-27).

## Milestone 2: Merging of the TMGMT Poetry module (Big jobs, unplanned yet)

It is foreseen to abandon eventually the "TMGMT Poetry" module and to integrate its features in this module.

Until then, the "TMGMT Poetry" module and its features will be kept for managing the translation requests for 
big contents.

# Installation

The installation has the same perquisites as the "NextEuropa DGT Connector" feature. 

So, please follow the instructions of the "[installation section](../README.md#a-installation)" of the "NextEuropa 
DGT Connector" README in order to install it.

# Configuration

This section will be completed during the different implementation tasks.