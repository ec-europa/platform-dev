# Usage
The module allows to use the ECL components inside view.
It provides 1 row style plugin. This plugin launch a set of templates inside
views rows.
This allows to output a row as a timeline for example.

# Extend
Any subsite can reuse the row plugins and extend the options provided by the 
select box.
To achieve this, you need to create a custom module that alters the list of
components inside hook_ne_core_views_row_styles_alter().
See _nexteuropa_core_views_row_styles.
