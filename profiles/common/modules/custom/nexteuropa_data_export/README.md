NextEuropa Data Export
======================

The module aims to provide a flexible way to export data by leveraging two very
popular contributed modules:
 
- [Views Bulk Operations (VBO)](https://www.drupal.org/project/views_bulk_operations)
- [Views data export](https://www.drupal.org/project/views_data_export)

The module exposes a VBO action that allows to use a "Data export" display 
(provided by the "Views data export" module) as an export engine for a views 
bulk operation action.
 
Installation
------------

Enable the module.

Usage
-----

The custom VBO action exposed by "NextEuropa Data Export" needs to use an 
existing "Data export" display, so you will typically have a view with two
displays:
   
- A VBO-enalbed display, typically a table exposing a bulk operation field for 
  the current entity type.
- A "Data export" display which will be used as a render engine.
      
After creating the two displays above make sure to enable "Export data using a 
"Data Export" display" in the "Selected bulk operations" fieldset on the VBO
display choosing the "Data export" you have just created.  
 
Note that fields on the two displays do not have to be necessarily the same:
those provided by the "Data export" display will be, in fact, presented to the
user as possible options right before performing the export.

You can find a working example of a correctly setup view in the
```nexteuropa_data_export_test``` feature.
    

