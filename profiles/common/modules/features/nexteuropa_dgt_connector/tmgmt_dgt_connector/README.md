The TMGMT DGT connector module allows tailoring the [TMGMT module](https://www.drupal.org/project/tmgmt) 
for the creation of translation managers, that make use of the European Commission DGT connector services
(translations served by DGT).

In a first phase, it will run in parallel of the TMGMT poetry module and will focus on "small jobs" (content translations of 
less than 300 characters).

"Add to card" feature allows users selecting elements to translate and for each of them
attaching an URL that will be communicated to DGT as reference for helping the content translators. 

This translator will consume services supplied by a dedicated PHP component for communicating with the 
Poetry European Service.

It is foreseen to abandon eventually the "TMGMT Poetry" module and to integrate its features in this module.
Until then, the "TMGMT Poetry" module and its features will be kept for managing the translation requests for 
big contents.
