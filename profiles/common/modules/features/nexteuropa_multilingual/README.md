This "FEATURE" module supplies default settings and permissions linked to
multilingual feature of the Next Europa platform.

It also contains alteration of:
* The path alias generation made by the "Pathauto" module in order
to force the use of neutral language for all created alias;
*The path alias saving made by "Path" module in order to ensure
that it is data of the source content that is always used to set the alias and
that the neutral language is set for all defined alias;
* The "Drupal core" language negotiation system in order to
 implement the platform specific process;
* The display of the language switcher.

# Important

 Concerning content, this module is designed for supporting "Entity translation"
 module but not "Content  translation" one.

# Installation

The module is activated when the platform is installed.

# Configuration

The module set by default some permissions and variables used by the different
multilingual features.
It comes also with the default definition of the sentence set below the
content edit form and the workbench moderation state form. it is stored in the
Drupal variable "nexteuropa_multilingual_warning_message_languages".

It can be modified this administration page: Configuration > Content authoring
 > MULTISITE WYSIWYG > settings (path: "admin/config/content/multisite_wysiwyg/setup_en");
 The value can contains tokens and HTML tags.