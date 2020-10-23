NextEuropa cookie consent kit module
------------------------------------
is integrating your site with <a href="https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+V2">webtool</a> (
Cookie consent kit - cck).

INSTALLATION
------------
* Install as you would normally install a contributed Drupal module.<br />
  See https://drupal.org/documentation/install/modules-themes/modules-7
  for further information.

CONFIGURATION
-------------
* Go to the _admin/config/services/webtools_ page to enable/disable and configure the banner.
* In case you would like to have the "Cookie Consent Kit" for 3rd party video
providers (YouTube, Vimeo and Dailymotion), you also need to enable the video 
cookie banner.

TROUBLESHOOTING
----------------
* For non ec.europa.eu domains, after activating the banner in the administration interface, if the CCK banner 
does not appear or does not block the third party cookies.<br />
Please make sure that you set up the policy url.

DEVELOPERS
----------
* Non ec.europa.eu domains, should set up a policy url and can add an appendix to the banner. 
For more information see the configuration page of the module.

* By default, the Cookie consent banner is not inserted in the pages related to:
  - The "back-end",
  - The contents management ("Edit draft", "View draft"...),
  - The files management ("file/add", "file/%file/edit"...).<br />

  The list of pages without displayed banner is nevertheless controlled through
this variable: `nexteuropa_cookie_consent_kit_no_banner_paths` <br />
Its value follows the pattern of the parameter `$patterns` of the Drupal function
[drupal_match_path()](https://api.drupal.org/api/drupal/includes%21path.inc/function/drupal_match_path/7.x).<br />
Its default value is
`admin\nadmin/*\nmedia/browser\nmedia/ajax\nsystem/ajax\nmedia/*/format-form\nfile/*/edit\nnode/*/*\nnode/add*\nfile/add*`
