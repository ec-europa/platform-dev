<?php

/**
 * @file
 * Contains template file.
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
      <?php print $body; ?>
    </div>
  </div>
