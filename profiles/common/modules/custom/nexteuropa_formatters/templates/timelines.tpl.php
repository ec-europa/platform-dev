<?php

/**
 * @file
 * Contains template file.
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
