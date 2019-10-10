Table of Contents
- [Nexteuropa Varnish](#nexteuropa-varnish)
    - [Requirements](#requirements)
    - [General settings](#general-settings-first-tab)
    - [Purge rules](#purge-rules-second-tab)
    - [Rules logic](#purge-rules-logic)
    - [Tests](#tests-and-custom-behat-feature-context)
    - [Developer's notes](#developers-notes)
    - [Blocking of the rules](#blocking-temporary-the-purge-mechanism)
 - [Varnish Mock](#testing-varnish-calls)


# Nexteuropa Varnish

Varnish is a very fast reverse-proxy system which serves static 
files and anonymous page views based on the previously processed
requests.
The Nexteuropa Varnish module provides functionality which allows to
send customized HTTP request to the Varnish server based on the
configured 'purge rules' in the form of regular expressions.
The main purpose of those requests is to invalidate the Varnish cache to
display recently published content changes.

## Requirements
This feature can be enabled only with the support of the QA/Maintenance
team.

The following environment specific variables have to be configured
before enabling the feature:
```
 'nexteuropa_varnish_request_user' - a string with the username
 'nexteuropa_varnish_request_password' - a string with the password
 'nexteuropa_varnish_http_targets', - an array with the urls ex. 'http://localhost'
 'nexteuropa_varnish_tag', - a string with the tag
 'nexteuropa_varnish_request_method' - a string with the HTTP request method
 'nexteuropa_varnish_http_timeout' - a float representing the maximum number
    of seconds the function call may take (by default 2.0)
```

In order to enable the feature make sure that above variables are set
and if so then go to the `admin/structure/feature-set` page,
select the 'Rule-based web frontend cache purging' feature 
and click on the 'Validate' button.

Nexteuropa Varnish provides a 'Administer frontend cache purge rules'
permission which allows to create and maintain 'purge rules'.

## General settings (First Tab)
Configuration page is located here `admin/config/system/nexteuropa-varnish`.

### "Purge all caches" Button

The configuration page provides a "Purge all caches" button.

Once it is clicked, this button will trigger:
- The cleaning of the "Drupal cache" if **Clear drupal cache as well** is also ticked;
- The purging of **ALL** site's entries indexed in the Varnish cache.

Checking "Drupal cache"  has impact on the site's performance as it forces
Drupal to rebuild all requested pages, use cautiously.

### Default rule "Enable the default purge rule"
See description in UI.

## "Purge rules" (Second Tab)
The module provides an custom entity type allowing to define purge rules:

`Purge rule - machine name: 'nexteuropa_varnish_cache_purge_rule'`

Click the **'Add cache purge rule'** link.
You will be redirected to the **'Add cache purge rule'** form.

### Content type

The `Content type` select box allows to limit triggering a rule to one type of *node*.
For example, you want to trigger the clearing of `my-news` only when content of type `news` is added,
edited or removed.

Selecting 'All' will apply to all node types.

### What should be purged
#### Purge the edited node !
If the default purge rule is disabled, the option **`Paths of the node the action is performed on`** will appear.

Just save it. The behaviour is similar to the default, except you can restrict to content types.
#### Purge nodes that match this regex!
The option **`A specific list of regex`**  allows defining a set of regex matching the paths you want to clear.

The field description provides hints for testing validity of the regex you entered in the field.

The `Check scope` button allows evaluating if the regex is built to return the paths you would expect to clear.

After setting up a rule you need to submit it by clicking the **'Save'** button.
If the regular expression you entered is not valid, the following warning will be shown
```
Regex is invalid. 
Please check your expression at the Regex101 page.
```

After the creation of a new rule you will be redirected to the page with the list of rules.
From that page you can use option to add a new rule or edit, delete existing rules.

## Purge rules logic
The Nexteuropa Varnish provides hardcoded logic for triggering
configured rules. Current version implements two workflow cases for:
- content types moderated via the workbench moderation module
- content types without additional moderation (default Drupal settings)

### Content moderated via the workbench moderation module
For the content types which are controlled via the workbench moderation
module, created purge rules will be triggered in the following cases:
- when a given content has a workflow state change to 'Published'
- when a given content has a workflow state change from 'Published' to any other

### Content without moderation
For the content types which are not moderated (default Drupal content
type with two states: published and unpublished), created purge rules
will be triggered in the following cases:
- when a node of the given content type is created and saved with the 'Publish' state
- when a published node of the given content type is updated

### Rules integration
To set up workflows, more intricate scenarios, for flushing varnish paths
a rules action 'Varnish flush' was added under the 'Nexteuropa Varnish' group.

This way you can add one or more path aliases in regexp format, even use available
tokens and create your own flushing rules in admin/config/workflow/rules.



## Tests and custom Behat Feature Context
The Nexteuropa Varnish provides complete a Behat test suite and additional
Feature Context located in the FrontendCacheContext class.

Tests are performed against a mocked HTTP server. The only difference is that
the mocked HTTP server doesn't support 'PURGE' method and uses
the 'POST' method instead.

You can find the Behat scenarios in the frontend_cache_purge.feature file
located under the test folder.

## Developer's notes
### Specificities
Nexteuropa Varnish uses the https://www.drupal.org/project/chr module
which overrides the default `drupal_http_request()` function.

A custom patch was created for this specific feature
The patch can be found [here](https://www.drupal.org/files/issues/chr-purge-2825701-2.patch)

The patch adds the 'PURGE' HTTP method, which is commonly used by systems such
as Varnish, Squid and SAAS CDNs like Fastly to clear cached versions of
certain paths.

All of HTTP requests are send by the `_nexteuropa_varnish_purge_paths()`
function.

To support rules integration for file entities we added another [path](https://www.drupal.org/files/issues/file_events-826986-31_0.patch).

### Blocking temporary the purge mechanism

Next Europa Varnish feature provides a feature to prevent from sending all supported purge requests.

To do so, the following line must be added to the settings file:
`$conf['nexteuropa_varnish_prevent_purge'] = TRUE;`

Once it is added, no purge request will be sent to Varnish and the "Purge all caches" button will be disabled.

Nevertheless, it is still possible to manage the purge rules during the blocking period.

### Testing varnish calls locally

In order to test varnish on C9 environement, please perform these steps:

1. Make sure your environement is up to date. See FAQs on confluence for more information or type :
```
sudo salt-call state.apply tools.varnish-mock
```

2. Add this to your settings.php file
```
$conf['nexteuropa_varnish_request_method'] = "PURGE";
$conf['nexteuropa_varnish_http_targets'] = array ("http://127.0.0.1:6081");
$conf['nexteuropa_varnish_tag'] = "drupal-760";
$conf['nexteuropa_varnish_request_user'] = "user";
$conf['nexteuropa_varnish_request_password'] = "password";
$conf['nexteuropa_varnish_http_timeout'] = "30";
```
3. Launch the mock
```varnish-mock```

4. By default, the mock prints information on console. Output file can be used with the "-filePath" parameter:
Type ```varnish-mock -h``` to get help

Please note that the value of the `base_path` variable on your site has an impact on the `path of the node` sent.

### Upgrading from a previous version
Because previous versions of the module did not support fully regular expressions , the validation of the rules 
exceptions have been added upon saving a new rule **and** upon triggering a rule.
Therefore, if you entered a rule in a previous version and this rule does not match the more strict criterias now
in place, a warning will appear :
```
Please check your varnish rules , the regex ^an-already-inserted/rule you are trying to flush is not valid.
We suggest you review and save your regex rules again using the documentation available and the
"Check Scope" button. In case of doubt, please contact your site administrator or the devops team. 
```
