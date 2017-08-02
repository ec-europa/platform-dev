NextEuropa Last Update
=========================

This module adds a default entry point
to get the last update date for any given entity.

Installation
------------

Install as usual, see http://drupal.org/node/895232 for further information.

Usage
-----
After enabling the module, a block will be available for site administrators to 
configure and place as they see fit in their site.

This block will show the last modification date of an entity if that entity
provides a callback in the "last update callback" property.

This block works with these following entities:
- node
- comment (if the module comments is enabled)
- user
- file
