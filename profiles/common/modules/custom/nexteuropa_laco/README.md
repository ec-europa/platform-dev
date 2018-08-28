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
the "Next Europa LACO - Settings" page.<br />
For each parameter described in the WebTools Language Coverage 
[Technical documentation](https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Language+Coverage+-+Technical+details),
a feature setting is to be defined.

On this settings page, the "Pages where the LACO icon feature must be active" 
settings allow defining which pages must be processed for adding the LACO icon
beside hyperlinks.

Current status
-----

NextEuropa LACO is currently only working with contents using Entity Translation.
