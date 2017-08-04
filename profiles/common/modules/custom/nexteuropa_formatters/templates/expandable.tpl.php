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

<div class="expandable__group">
  <a href="#<?php print $id; ?>" class="collapsed expandable__toggle" data-toggle="collapse" data-target="#<?php print $id; ?>" aria-expanded="false">
    <h3>
      <span class="<?php print $icon; ?>"></span>
      <?php print $title; ?>
    </h3>
  </a>
  <div id="<?php print $id; ?>" class="expandable__content collapse">
    <?php print render($body); ?>
  </div>
</div>
