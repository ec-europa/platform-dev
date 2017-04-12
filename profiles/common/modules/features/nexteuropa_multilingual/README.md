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

# Important

 Concerning content, this module is designed for supporting the
 "Entity translation" module but not the "Content translation" one.

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

