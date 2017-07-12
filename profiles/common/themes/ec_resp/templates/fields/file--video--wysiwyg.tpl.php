<?php
/**
 * @file
 * Template to display an video file value inside a WYSIWYG field.
 *
 * It diverts from the file_entity one by displaying the value without any
 * additional DIV container.
 * It is then recommended to use it without setting image caption.
 *
 * It is implemented for NEPT-639.
 */
?>
<?php print render($content); ?>
