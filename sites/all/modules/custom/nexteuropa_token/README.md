NextEuropa Token
================

NextEuropa Token exposes general-purpose tokens for NextEuropa sites. 

Installation
------------

After enabling the module make sure you enable "Replace tokens" in your text format
in order for the module to actually perform the replacement.

Provide custom token handlers 
-----------------------------

Modules can provide their own token handlers by implementing the following hook: 

```
/**
 * Implements hook_nexteuropa_token_token_handlers().
 */
function nexteuropa_token_nexteuropa_token_token_handlers() {
  return array(
    'hash_handler' => '\Drupal\nexteuropa_token\HashTokenHandler',
    'view_mode_entity_handler' => '\Drupal\nexteuropa_token\ViewModeTokenHandler',
  );
}
```

Token handlers classes should be using PSR-4 class autoloading. Classes can be
discovered using [registry_autoload module](https://www.drupal.org/project/registry_autoload)
which is already a dependency of NextEuropa Token. 

Token handlers must implement ```\Drupal\nexteuropa_token\TokenHandlerInterface```
or simply extend ```\Drupal\nexteuropa_token\TokenAbstractHandler``` abstract class.

NextEuropa Token module also exposes a simple service-container function that
returns a valid handler instance, or throws an exception otherwise:

```
nexteuropa_token_get_handler('my_handler_name')
```

For example:

```
nexteuropa_token_get_handler('hash_handler')->hookTokenInfoAlter($data);
```

Notes
-----

For implementation details of HashTokenHandler refer to:
https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/Hash+id+generation#comment-403571860
