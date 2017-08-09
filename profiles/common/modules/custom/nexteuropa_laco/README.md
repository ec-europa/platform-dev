NextEuropa LACO
===============

The language coverage service (LACO) offers end-users to check if a link to a page or document is available in other translations.

This module aims to integrate with the LACO service by providing information, upon an external request, about available languages for a requested content.

Debug
-----

Set the following value in your `settings.php` in order to get debug headers in the service response:

```php
$conf['nexteuropa_laco_debug'] = TRUE;
```

Current status
-----

NextEuropa LACO is currently only working with contents using Entity Translation.
