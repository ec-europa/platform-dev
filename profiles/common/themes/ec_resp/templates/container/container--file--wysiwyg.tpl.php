<?php
/**
 * @file
 * Template to display an form container used inside a WYSIWYG field.
 *
 * It diverts from the theme_container by displaying its content without any
 * additional DIV container.
 *
 * It is implemented for NEPT-639.
 */
?>
<?php print render($element['#children']); ?>
