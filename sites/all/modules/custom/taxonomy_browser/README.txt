INSTALLATION
------------

1. Download the module 

2. The module needs the jstree library.
   Download the jstree libray at http://www.jstree.com
   Unzip the archive in the directory sites/all/libraries
   
3. enable the module




GETTING STARTED
---------------

1. go to admin/config/taxonomy_browser/settings

2. choose a taxonomy to display as tree
The taxonomy selected must be used to categorize your contents

3. choose the displays of views (block, page, ...) where you want to display the tree taxonmy at the left.

***The displays that will use the tree taxonomy must have a contextual filter related to the taxonomy selected in the 
settings of the module (contextual filter like => Content: Has taxonomy term ID (with depth) ).

***If the view that you want to choose doesn't appear in the list, go to the views backoffice, edit the view and save it 
to force drupal to save it in database. Then the view must appear in the module settings.

4. Finally display the view and test the taxonomy tree




REQUIREMENTS
------------

1. The module needs the jstree library installed in the sites/all/libraries directory






