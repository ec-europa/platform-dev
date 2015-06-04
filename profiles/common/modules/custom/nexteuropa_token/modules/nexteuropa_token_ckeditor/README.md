NextEuropa Token CKEditor
=========================

NextEuropa Token CKEditor exposes a CKEditor plugin that would expand entity 
tokens exposed by NextEuropa Token into their HTML/textual representation.
Entity tokens handlers are namespaces by ```\Drupal\nexteuropa_token\Entity```.

Installation
------------

After enabling the module make sure you enable "Replace tokens" in your text 
format in order for the module to actually perform token replacement.

Also activate the "NextEuropa Token" CKEditor plugin by visiting the "Buttons 
and Plugins" section of the CKEditor setting page for relevant text formats.
 
NextEuropa Token CKEditor plugin uses a default view to allow editors to look
for entities, such a view is provided by the module implementing 
```hook_views_default_views()```.

It is still possible to select a different search view by visiting the module's
setting page at ```admin/config/system/nexteuropa-tokens```.
