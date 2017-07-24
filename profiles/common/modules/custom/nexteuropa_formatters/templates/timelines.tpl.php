<?php

/**
 * @file
 * Contains the template file for the timelines component.
 *
 * Available variables:
 * - $title: string or a render array.
 * - $text: string or a render array.
 * - $footer: string or a render array.
 */
?>

<div class="timeline">
  <div class="timeline__item">
    <div class="timeline__item-title">
      <?php print render($title); ?>
    </div>
    <div class="timeline__text">
      <?php print render($text); ?>
    </div>
  </div>
  <div class="timeline__footer">
    <?php print render($footer); ?>
  </div>
</div>
