The "Multilingual" feature supplies default settings and permissions linked to
multilingual features of the Next Europa platform.

It also contains alterations of:
* The path alias generation made by the "Pathauto" module in order
to force the use of neutral language for all created aliases;
* The path alias saving made by the "Path" module in order to ensure
that it is data of the source content that is always used to set the alias and
that the neutral language is set for all defined aliases;
* The "Drupal core" language negotiation system in order to
 implement the platform specific process;
* The display of the language switcher.
* The default language for administration pages

# Important

 Concerning content, this module is designed for supporting the
 "Entity translation" module but not the "Content translation" module.

# Installation

The module is activated when the platform is installed.

# Configuration

The module by default sets some permissions and variables used by the different
multilingual features.
It comes also with the default definition of the sentence set below the
content edit form and the workbench moderation state form. It is stored in the
Drupal variable "nexteuropa_multilingual_warning_message_languages".
The value can contain tokens and HTML tags and by default, the message is:

"The state of the content <b>[node:title]</b> and all its validated translations <b>[node:entity-translation-languages]</b> will be updated!"

# Administration language

For multilingual sites, the site owners have the option to choose on which
'admin' pages they want to display a fixed language (typically english), for 
all users.
The configuration is based on *paths* not on user type, or user preferences.
To enable the feature, reach *admin/config/regional/language/configure* and 
check 'Administration path' detection method.
Configuration is explained in the [documentation page of drupal.org](https://www.drupal.org/project/administration_language_negotiation) 
Please also review [the readme file](http://cgit.drupalcode.org/administration_language_negotiation/tree/README.md?h=7.x-1.2)
By default, the English "Administration language negotiation" is active on edit 
pages, and admin/* pages. 
In the event that you uploaded .po file and want to see english on a non admin
page you should to delete the translation from your imported strings.

To delete translations, go to "admin/config/regional/translate/translate_en",
select "Built-in interface" from the "Limit search to ", then click "delete" 
in the operation column facing the string you do not want to see translated.

An example is visible on the [feature wiki page](https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Administration+language+negotiation)
