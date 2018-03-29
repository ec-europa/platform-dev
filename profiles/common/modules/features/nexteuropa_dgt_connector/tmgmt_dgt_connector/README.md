TMGMT DGT Connector
===================
This module integrates the [TMGMT module](https://www.drupal.org/project/tmgmt) 
and the European Commission DGT connector services, enabling translation managers,
a custom cart and all required logic.

# Usage

After enabling this module, it will be possible to translate:

#### Content with length above 300 characters

This will work like when using only the  ```TMGMT Poetry``` module and translator ```DGT Connector```.

#### Other translatable items using Small Jobs Cart

It is now possible to bundle other different translatable items
in the ```Small Jobs Cart```, using the translator ```TMGMT DGT Translator```:

* Content with length under 300 characters;
* Menu and Menu items;
* Taxonomies and Terms;
* Blocks 

To add one translatable item to the ``Small Jobs Cart``, 
go to the translation page of that item,
chose the target languages and then use the "Send to cart" button.

Then, in the ```Small Jobs Cart (admin/tmgmt/dgt_cart)```, you can send a bundle to be translated.
Each bundle is a set of items having the same target languages set.
Before sending a bundle for translation, please edit the bundle, then revise and complete
the context information: Context URL should be filled and also any other
hints that may help the person in charge of translation to understand the
context where the item will be displayed.

In the translation checkout page, the translator ```TMGMT DGT Translator``` must be used.

## Other translatable items using TMGMT Cart

It is also possible to bundle these translatable items:

* Strings/Locale
* Form labels/Field Instances

Currently we are using the ```TMGMT Cart``` for this purpose. Using the ```Small Jobs Cart```
is not possible yet but should be possible soon. The main difference between
the two carts is the workflow for choosing the target languages.
To make these translations, go to the ```TMGMT Sources (admin/tmgmt/sources)``` page
and chose "Locale" or "Field Instance" tabs. After adding all desired items
to the cart, go to the ```TMGMT Cart (admin/tmgmt/cart)``` page and request the translation.

In translation checkout page, like the one in the ```Small Jobs Cart (admin/tmgmt/dgt_cart)```,
the translator ```TMGMT DGT Translator``` must be used.

# Configuration

* Install and configure [NextEuropa DGT Connector](https://github.com/ec-europa/platform-dev/tree/master/profiles/common/modules/features/nexteuropa_dgt_connector);
* Enable modules ```TMGMT DGT connector (tmgmt_dgt_connector)``` and ```TMGMT DGT Connector Cart (tmgmt_dgt_connector_cart)```;
* Configure settings in ```admin/config/regional/poetry-client``` for the helper module
[Nexteuropa Poetry](https://github.com/ec-europa/nexteuropa_poetry#configuration),
as described in "Configuration" section.

# Next developments

In the first phase, this module will run in parallel with
[TMGMT poetry](https://github.com/ec-europa/platform-dev/tree/master/profiles/common/modules/features/nexteuropa_dgt_connector/tmgmt_poetry)
module and will focus on "Small jobs" (content translations of
less than 300 characters). It is foreseen to eventually abandon the
```TMGMT Poetry``` module and to integrate all its features in this module.

```TMGMT Cart``` should be deprecated in favor of ```Small Jobs Cart```.
