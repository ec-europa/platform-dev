THIS FEATURE IS DEPRECATED AND WILL BE REMOVED SOON.
PLEASE SWITCH TO NEXTEUROPA_PIWIK FEATURE.


  Business Indicators
-------------------

The Business Indicators Multisite features provide a set of blocks with figures 
about a Multisite installation's user and content. System administrators will 
be able to place said blocks in specific areas of the site by using the Context 
module, already provided on each Multisite installation. Information can be 
displayed in textual form, by using lists, tables, etc. or by using graphical 
charts.

How to use Business Indicators
------------------------------

As administrator you can access an overview page by visiting "Reports" and then
"Business Indicators", or by visiting "admin/reports/business-indicators".

In order to access the overview page and blocks the user needs to have 
"Access business indicators overview page" permission enabled. 
Permission is enabled by default for the "administrator" role.

System administrator can clone and customize default views and place blocks on 
the site bu using the Context module. 

Following the Multisite development conventions the functionalities have been 
divided into three features:

- "Business Indicators Core": contains all common configuration and code;
- "Business Indicators Standard": contains configuration working with both the 
  "Multisite Standard" and the "Multisite Community" installation profiles;
- "Business Indicators Community": contains configuration working only with the 
  "Multisite Community" installation profile.

Views exposed by the "Business Indicators Standard" feature are the following:

- business_indicators_active_users: most active users per site, it provides a 
  table and a chart block;
- business_indicators_files: figures on uploaded file types, per site, it provides a 
  table and a chart block;
- business_indicators_nodes: number of content items, per content type, per site, 
  it provides a table and a chart block;
- business_indicators_recent_comments: table listing most recent comments;
- business_indicators_recent_nodes: table listing most recent nodes.
- business_indicators_ext_index: count page accesses.

Views exposed by the "Business Indicators Community" feature are the following:

- business_indicators_community_active_users: most active users per community, 
  it provides a table block, grouped by community;
- business_indicators_community_files: figures on uploaded file types, per community, 
  it provides a table and a chart block;
- business_indicators_community_nodes: number of content items per community, 
  it provides a table and a chart block;
- business_indicators_community_recent_comments: table listing most recent comments, 
  with author, post date and link to commented node;
- business_indicators_community_users: number of users per community, it provides a 
  table and a chart block;
- business_indicators_community_recent_nodes: table listing most recent nodes, with 
  author and post date.

All views are tagged with the "Business Indicators" category.

More information at: 
https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Business+indicators

Online Documentation at:
https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Business+Indicators+Documentation
