# Description
The module provides views plugins for the theme implementations provided by
the nexteuropa_formatters module.

# Usage and extending the module
The provided row plugins need to be configured following the next restrictions:

* Timelines plugin:
    * Title: Timeline item title, needs to be a text field. 
    * Text: Timeline item text, needs to be a text field.
    * Footer: Timeline footer, needs to be a text field.
* Blockquote plugin:
    * Quote: Body of the quote, needs to be a text field. 
* Card plugin:
    * URL: Target URL of the card, needs to be a url or text field. 
    * Image: Image of the card, needs to be an image field.
    * Label: Label of the card, needs to be a text field.
* Expandable plugin:
    * Id: Identifier for the row, needs to be a text field. 
    * Icon: Icon for the expandable button, needs to be an image field.
    * Title: Title for the expandable item, needs to be a text field.
    * Body: Body for the expandable item, needs to be a text field.
* Banner plugin:
    * Quote: Body of the quote, needs to be a text field. 
    * Author: Author of the quote, needs to be a text field. 

The provided plugins can be enabled in any view and can be overridden by
following standard Drupal 7 theming methods.