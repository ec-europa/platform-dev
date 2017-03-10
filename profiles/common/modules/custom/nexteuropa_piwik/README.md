Next Europa PIWIK
=================

This feature provides the Piwik web statistics tracking system integration.

Usage
=====
On the settings page you need to enter the Piwik website ID and define
other properties like what user roles should be tracked.

After configuration all pages that follow the settings scope will have
the required JavaScript added to the HTML footer. You can check this by
viewing the page source from your browser.

Advance PIWIK rules
===================
**"The advanced PIWIK rules"** is an additional functionality available in the Next
Europa PIWIK feature. It allows to create custom rules for setting up
site section value.
To keep backward compatibility the "Advanced PIWIK rules" option is disabled
by default.

### Table of Contents
1. [How to enable Advanced PIWIK rules](#how-to-enable)
2. [Custom PIWIK rule types](#rule-types)
3. [Overlapping rules](#overlapping-rules)
4. [How to add a new custom PIWIK rule](#how-to-add-rule)

#### How to enable Advanced PIWIK rules <a name="how-to-enable"></a>
Feature can be enabled on the PIWIK configuration page which is available
on the following path `admin/config/system/webtools/piwik`. 

On the configuration page click on the "Advanced PIWIK rules" tab which is located
at the bottom of the page. 
On the tab section tick the "Enable advanced PIWIK rules" checkbox and
after that click on the "Save configuration" button.
The notification with the following message should be displayed:
"The PIWIK advanced rules are turned on."
A new configuration tab "Advanced PIWIK rules" should become visible.

#### Custom PIWIK rule types <a name="rule-types"></a>
There are two types of PIWIK rules:
- **Direct path** - which is based on the direct full path of a page
- **Regexp path** - which is based on the regular expression
  
#### Overlapping rules <a name="overlapping-rules"></a>
If for a given page there will be more than one rule a log entry will be
created with the information about overlapping rules IDs.

The "Direct path" rules have a priority over the "Regexp path".
It means that if two rules or more are applicable for the given page and
one of them is the "Direct path" rule, that rule will be applied.
Similar rule applies to the language selection. If there is more
than a one rule, the rule with the defined language will be selected 
instead of the one with an 'all' languages option.

Function which is filtering rules will return the first result from
the stack. It means that rules will be applied in the IDs ascending order.

#### How to add a new custom PIWIK rule <a name="how-to-add-rule"></a>
To add the custom rule click on the "Advanced PIWIK rules" tab or go to 
the following path `admin/config/system/webtools/piwik/advanced_rules`

Next click on the **"+ Add piwik rule"** and fill the form by following
description tips located beneath the fields.
When all of the fields are filled you can click save button.
After submission you will be redirected to the rule list from where you
can manage your rules (edit / delete).
