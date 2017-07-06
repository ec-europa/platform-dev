<?php

/**
 * @file
 * Contains template file.
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
