<?php

/**
 * @file
 * Contains the template file of the expandable component.
 *
 * Available variables:
 * - $id: string which contains an anchor ID.
 * - $icon: string which contains an icon class name.
 * - $title: string which contains a title.
 * - $body: string or a render array which contains a content.
 */
?>

<div<?php print $attributes; ?>>
  <?php print render($link); ?>
    <div<?php print $content_attributes; ?>>
      <?php print render($body); ?>
    </div>
</div>
