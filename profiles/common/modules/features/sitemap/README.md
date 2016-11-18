Sitemap Feature
======================

The module aims to provide a Sitemap (XML).

# Installation

The feature can be activated using the feature set menu
(/admin/structure/feature-set).

## Developer and administrator notes

Submodule xmlsitemap_i18n is not compatible with this feature and the two
should never be enabled together.

# Usage

When the feature is enabled, the /sitemap.xml is available.

The feature provides:
- a list of XML sitemaps,
- search engines,
- an administration page (Setting),
- manually Rebuild links.

## Regenerate the XML sitemap
The feature regenerates the XML sitemap files using the cron or it's possible to
regenerate manually.

## Multilingual
The feature includes the tags (rel = "alternate") for indexation of the
various languages for each items.

## More information
https://webmasters.googleblog.com/2012/05/multilingual-and-multinational-site.html
