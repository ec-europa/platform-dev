<?php

/**
 * @file
 * Contains the template file of the banner component.
 *
 * Available variables:
 * - $quote: string or a render array.
 * - $author: string or a render array.
 */
?>

<div class="banner">
  <div class="banner__quote">
    <blockquote class="blockquote blockquote--small">
      <span class="blockquote__open"></span>
        <?php print render($quote); ?>
        <span class="blockquote__close"></span>
    </blockquote>
  </div>
  <span class="banner__author">
    <?php print render($author); ?>
  </span>
</div>
