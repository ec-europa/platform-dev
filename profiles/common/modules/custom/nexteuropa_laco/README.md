NextEuropa LACO
===============

The language coverage service (LACO) offers end-users to check if a link to a 
page or document is available in other translations.

By default, this module aims to integrate with the LACO service by providing 
information, upon an external request, about available languages for a 
requested content.

The module also proposes a integration with WebTools feature that add an 
language icon beside each hyperlink of a page content.
 
Usage
=====

The **feature providing information to the LACO service** does not need any 
configuration. 

Nevertheless, setting the following value in your `settings.php` allows 
getting debug headers in the service response:

```php
$conf['nexteuropa_laco_debug'] = TRUE;
```

The **LACO icon feature** can be enabled on the "Next Europa LACO - Settings" 
page (path: admin/config/regional/nexteuropa_laco).

The feature is configured for a site that uses a default installation of the 
NextEuropa platform but the module allows configuring the feature on 
the "Next Europa LACO - Settings" page.
For each parameter describe in the WebTools Language Coverage 
[Technical documentation](https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Language+Coverage+-+Technical+details).

On this settings page, it is also possible to define which page must be covered 
by the LACO icon feature.

Current status
-----

NextEuropa LACO is currently only working with contents using Entity Translation.
