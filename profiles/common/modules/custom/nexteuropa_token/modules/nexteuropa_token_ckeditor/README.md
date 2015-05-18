NextEuropa Token CKEditor
=========================

NextEuropa Token CKEditor exposes a CKEditor plugin that would expand entity 
tokens exposed by NextEuropa Token into their HTML/textual representation.
Entity tokens handlers are namespaces by ```\Drupal\nexteuropa_token\Entity```.

Installation
------------

After enabling the module make sure you enable "Replace tokens" in your text 
format
in order for the module to actually perform the replacement.

Also activate the "NextEuropa Token" CKEditor plugin by visiting the "Buttons 
and Plugins" section of the CKEditor setting page for relevant text formats.
 
In order to search for entities the plugin uses a default view, provided by the 
module, although you can select your own view by visiting the module's setting
page under ```admin/config/system/nexteuropa-tokens```.
