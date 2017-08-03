<?php

/**
 * @file
 * Contains the template file of the card component.
 *
 * Available variables:
 * - $url: string which contains an url.
 * - $image: string which contains an image source.
 * - $label: string which contains a label.
 */
?>

<a href="<?php print $url; ?>" class="card">
  <img class="card__image" src="<?php print $image; ?>" alt="cards image" />
  <div class="card__body"><?php print $label; ?></div>
</a>
