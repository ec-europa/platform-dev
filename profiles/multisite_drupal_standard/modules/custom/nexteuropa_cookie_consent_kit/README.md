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
* Go to the admin/config/system/nexteuropa-cookie-consent-kit page to enable and
disable the banner.
* After activating the banner, you need to make sure that the consent.js file is
being the first loaded JS file in the head tag in all your website's pages.
* If it is required, when a site creates a persistent cookie, this cookie should
be listed in your site's cookie_config.js. For more information check
<a href="https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+-+Technical+details">here</a>.
* In case you would like to have the "Cookie Consent Kit for 3rd party videos
(YouTube, Vimeo and Dailymation) and other iframe content providers", you also
need to enable the cookie videos.
