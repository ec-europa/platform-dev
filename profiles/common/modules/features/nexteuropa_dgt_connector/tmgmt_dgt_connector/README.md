TMGMT DGT Connector
===================
This module integrates the [TMGMT module](https://www.drupal.org/project/tmgmt) 
and the European Commission DGT connector services, providing translation managers,
a custom cart and all required logic.

# Translatable strings

The TMGMT DGT Connector module allows the translation of all default string types
supported by the original TMGMT module. This includes:
* Nodes
* Blocks
* Beans (when enabling Entity Translation for Blocks)
* Views
* Locale strings
* Field instances
* Files
* Menu and menu links
* Vocabularies and Taxonomy terms

The following string types are currently not currently supported:
* Webforms
* Custom metatags
* Polls
This is due to lack of support on the TMGMT module. 

The module supports strings of all sizes but Nodes with length bigger
than 300 characters will have to be sent in individual requests.

Other strings can and should be bundled together into single requests.
For consistency sake it is recommended that related strings are bundled together
(all items of a single menu for example).


# Usage

Requesting translations for content with length bigger than 300 characters
follows the usual workflow of the TMGMT module.
Please refer to the documentation of the module for more details.

In order to bundle items together a user must use the custom DGT Cart which replaces the
default TMGMT Cart.
A user can add a translatable string in two different ways: through the translation form
of the content or through the Sources page provided by TMGMT.

#### Translation forms

Translation forms for most content and string types 
can be found when editing the content itself under the tab "Translate" (for example,
node translation pages can be found at node/NODE_ID/translate).
Selecting the "Send to cart" option will add them to the cart for later usage.

#### Sources page

All translatable strings are available on the Sources page provided by the TMGMT module.
The page can be found at admin/tmgmt/sources and it provides separate tabs for each
string type.
After selecting the desired strings, they can be sent to the cart itself by selecting the target
languages and clicking the "Send to cart" button.

#### DGT Cart

The custom DGT cart can be accessed through the following url "admin/tmgmt/dgt_cart".
The cart shows all the currently created bundles.
Each bundle is created based on the target languages of the items sent into the cart.
Once in a bundle, the Edit option allows to see the items inside a bundle,
edit its context data and also to remove items if needed.
The Discard option will delete the bundle and remove all the items in it.
The Send option will create a Translation request which will then follow the usual workflow
of the TMGMT module.

#### Translation checkout page

In the translation checkout page, the translator ```TMGMT DGT Translator``` must be used.

# Configuration

* Install and configure [NextEuropa DGT Connector](https://github.com/ec-europa/platform-dev/tree/release-2.5/profiles/common/modules/features/nexteuropa_dgt_connector);
* Enable modules ```TMGMT DGT connector (tmgmt_dgt_connector)``` and ```TMGMT DGT Connector Cart (tmgmt_dgt_connector_cart)```;
* Enable translatability of your content types.
* Enable translatability of each field you want to send to translation (including
title field) in admin/structure/types/manage/my_content_type/fields/my_field_field.
* Configure settings in ```admin/config/regional/poetry-client``` for the helper module
[Nexteuropa Poetry](https://github.com/ec-europa/nexteuropa_poetry#configuration),
as described in "Configuration" section.
* Configure settings in ```admin/config/regional/tmgmt_translator/manage/tmgmt_dgt_connector```. These settings are the same as for the
[NextEuropa DGT Connector](https://github.com/ec-europa/platform-dev/tree/release-2.5/profiles/common/modules/features/nexteuropa_dgt_connector/#dgt-connector-configuration-cem);
