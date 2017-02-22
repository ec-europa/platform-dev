Splash screen Feature
======================

This module adds extra variables available for the Nagios monitoring tool.

Installation
------------

The module will only be enabled by the DevOps team and can't be added as a dependency in any other module or feature.

Usage
-----
After enabling the module, please refer to the README.txt available in the contributed Nagios modules in order
to configure the module and the Nagios plugins.

### Monitoring a variable

In order to monitor a single variable, the entry point for Nagios must specify the module and the variable to check
following this pattern: http://domain/nagios-status/{module}/{variable}

For example, in order to monitor the CSS Aggregation settings the Nagios monitoring tool needs to point to
the following url: http://domain/nagios-status/nexteuropa_nagios/css_aggregation
