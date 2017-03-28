Next Europa PIWIK
=================

This feature provides integration with the Piwik web statistics tracking system.

Installation
============

Install the module as usual, see http://drupal.org/node/895232 for further information.

Usage
=====
Once the module is enabled in a site the general configuration must be defined
before starting the Piwik integration.

Navigate to `admin/config/system/webtools/piwik` in order to
enter the Piwik website ID and define other properties like what user
roles should be tracked.

After the configuration all pages that follow the settings' scope will have
the required JavaScript added to the HTML footer. You can check this by
viewing the page source from your browser and looking for the '"utility":"piwik"' tag.

Advanced PIWIK rules
===================
The **"Advanced PIWIK rules"** is an additional functionality available in the Next
Europa PIWIK feature. It allows to create custom rules for setting up
different site section values.
To keep backward compatibility the "Advanced PIWIK rules" option is disabled
by default.

### Table of Contents
1. [How to enable Advanced PIWIK rules](#how-to-enable)
2. [Custom PIWIK rule types](#rule-types)
3. [Overlapping rules](#overlapping-rules)
4. [How to add a new custom PIWIK rule](#how-to-add-rule)

#### How to enable Advanced PIWIK rules <a name="how-to-enable"></a>
The feature can be enabled on the PIWIK configuration page which is available
on the following path: `admin/config/system/webtools/piwik`.

On the configuration page click on the "Advanced PIWIK rules" tab which is located
at the bottom of the page. 
On the tab section tick the "Enable advanced PIWIK rules" checkbox and
after that click on the "Save configuration" button.
A notification with the following message should be displayed:
"The PIWIK advanced rules are turned on."
A new configuration tab "Advanced PIWIK rules" should have become visible.
Enabling the "Advanced PIWIK rules" option resets the entity cache info
and rebuilds the menu.

#### Custom PIWIK rule types <a name="rule-types"></a>
There are two types of PIWIK rules:
- **Direct path** rules are based on the direct full path of a page
- **Regexp path** rules are based on a regular expression
  
#### Overlapping rules <a name="overlapping-rules"></a>
If more than one rule applies for a given page, a log entry will be
created with the information about the overlapping rule IDs.

The "Direct path" rules have a priority over the "Regexp path".
It means that if two or more rules are applicable for the given page and
one of them is a "Direct path" rule, that rule will be applied.
The same rule applies to the language selection. If there is more
than a one rule, the rule with the specific language will be selected
instead of the one with an 'all' languages option.

The function that filters the rules does so by returning the first result from
the stack. This means that rules will be applied in the IDs ascending order.

If there are no rules for a given path the default settings from the
"General settings" section will be applied.

#### How to add a new custom PIWIK rule <a name="how-to-add-rule"></a>
To add the custom rule click on the "Advanced PIWIK rules" tab or go to 
the following path: `admin/config/system/webtools/piwik/advanced_rules`.

Next click on the **"+ Add piwik rule"** link and fill the form by following
the description tips located beneath the fields.
When all of the fields are filled you can click save button.
After submitting the rule you will be redirected to the rule list
from where you can manage your rules (edit / delete).
