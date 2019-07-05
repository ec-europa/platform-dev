NextEuropa cookie consent kit module
------------------------------------
is integrating your site with <a href="https://webgate.ec.europa.eu/fpfis/wikis/pages/viewpage.action?spaceKey=webtools&title=Cookie+Consent+Kit">webtool</a> (
Cookie consent kit - cck).

INSTALLATION
------------
* Install as you would normally install a contributed Drupal module. See:
  https://drupal.org/documentation/install/modules-themes/modules-7
  for further information.

CONFIGURATION
-------------
* Go to the admin/config/system/nexteuropa-cookie-consent-kit page to enable or
to disable the banner.
* If it is required, when a site creates a persistent cookie, this cookie should
be listed in your site's cookie_config.js.<br /> For more information, check
<a href="https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+-+Technical+details">here</a>.<br />
See also the DEVELOPER section in order to know how to inject the "cookie_config.js" file.
* In case you would like to have the "Cookie Consent Kit for 3rd party videos
(YouTube, Vimeo and Dailymotion) and other iframe content providers", you also
need to enable the cookie videos.

TROUBLESHOOTING
----------------
* After activating the banner in the administration interface, the CCK banner 
does not appear or does not block the third party cookies.<br />
Please make sure make sure that the consent.js file is the first loaded JS file 
in the head tag of your website's pages. Without that it cannot work properly.

DEVELOPERS
----------
* Concerning the "cookie_config.js" file, there is no 
administration interface allowing injecting it.<br />
Due to security constraints, it must be added manually to the site's code 
base and it must be referenced programmatically in the Drupal pages, via a 
hook_preprocess_html() or a hook_page_alter().
 
* **Reminder**: If you need to inject JS files in your site, please 
make sure that the consent.js file is always the first loaded JS file 
in the head tag in every site pages.
