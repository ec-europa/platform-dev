<?php

/**
 * @file
 * Default theme implementation to display a card component.
 *
 * @todo Fill out list of available variables.
 *
 * @ingroup templates
 */
?>
<a href="<?php print $url; ?>" class="card">
  <img class="card__image" src="<?php print $image; ?>" alt="cards image" />
  <div class="card__body"><?php print $label; ?></div>
</a>
